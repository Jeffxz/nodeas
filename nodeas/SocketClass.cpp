
#ifdef AVMSHELL_BUILD
#include "avmshell.h"
#else
// player
#include "platformbuild.h"
#include "avmplayer.h"
#include "SocketClass.h"
#endif

#include "nodeassocket.h"

using namespace MMgc;

namespace avmplus
{
 using namespace MMgc;

 /* SocketObject */
 SocketObject::SocketObject(VTable *vtable, ScriptObject *delegate)
  : ScriptObject(vtable, delegate) 
 {}

 /* SocketClass */
 SocketClass::SocketClass(VTable *vtable)
  : ClassClosure(vtable)
 {
  createVanillaPrototype();
 }

 ScriptObject *SocketClass::createInstance(VTable *ivtable, ScriptObject* /*delegate*/)
 {
  return new (core()->gc, ivtable->getExtraSize()) SocketObject(ivtable, prototype);
 }

uint32 SocketClass::startlisten(uint32 port)
 {
     int listenfd;
     struct sockaddr_in local;
     listenfd = socket(AF_INET, SOCK_STREAM, 0);

     memset((char *)&local, 0, sizeof(local));
     local.sin_family = AF_INET;
     local.sin_addr.s_addr = htonl(INADDR_ANY);
     local.sin_port = htons(port);
     bind(listenfd, (struct sockaddr *)&local, sizeof(local));
     listen(listenfd, 5);
	 core()->console << "started listening port " << port << "\n";
     return listenfd;
 }

	uint32 SocketClass::accept(uint32 socket)
	{
		 int connfd, len;
		 struct sockaddr_in client;

		 len = sizeof(client);
		 connfd = ::accept(socket, (struct sockaddr *)&client, (socklen_t *)&len);
		 core()->console << "accepted connection from " << inet_ntoa(client.sin_addr) << "\n";
		 return connfd;
	}

	uint32 SocketClass::send(uint32 connfd, Stringp data)
	{
		StUTF8String s(data);
		const char* c = s.c_str();
		::send(connfd, c, (int)strlen(c), 0);
		return 0;
	}

	Stringp SocketClass::recv(uint32 connfd)
	{
		char buf[1024];
		int count = 0;
		count = ::recv(connfd, buf, 1024, 0);
		/* TODO: if (count < 0) handle error */
		core()->console << "received: " << count << " bytes\n";
		core()->console << buf;
		while (count >= 1024)
		{
			core()->console << "received: " << count << "bytes\n";
			core()->console << buf;
			count = ::recv(connfd, buf, 1024, 0);
		}
		core()->console << "\n";
		return NULL;
	}

	void SocketClass::close(uint32 connfd)
	{
		::close(connfd);
	}
}
