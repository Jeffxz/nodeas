
#ifdef AVMSHELL_BUILD
#include "avmshell.h"
#else
// player
#include "platformbuild.h"
#include "avmplayer.h"
#include "NodeasClass.h"
#endif

#include "nodeassocket.h"

using namespace MMgc;

namespace avmplus
{
 using namespace MMgc;

 /* NodeasObject */
 NodeasObject::NodeasObject(VTable *vtable, ScriptObject *delegate)
  : ScriptObject(vtable, delegate) 
 {}

 /* NodeasClass */
 NodeasClass::NodeasClass(VTable *vtable)
  : ClassClosure(vtable)
 {
  createVanillaPrototype();
 }

 ScriptObject *NodeasClass::createInstance(VTable *ivtable, ScriptObject* /*delegate*/)
 {
  return new (core()->gc, ivtable->getExtraSize()) NodeasObject(ivtable, prototype);
 }

 Stringp NodeasClass::getVersion()
 {
    return core()->newConstantStringLatin1("0.1");
 }

double NodeasClass::startlisten(uint32 port, ScriptObject *callback)
 {
     int listenfd, connfd, len;
     struct sockaddr_in local;
     struct sockaddr_in client;
     listenfd = socket(AF_INET, SOCK_STREAM, 0);
     char buf[2048];

     memset((char *)&local, 0, sizeof(local));
     memset(buf, 0, sizeof(buf));
     snprintf(buf, sizeof(buf),
         "HTTP/1.0 200 OK\r\n"
         "Content-Length: 20\r\n"
         "Content-Type: text/html\r\n"
         "\r\n"
         "<div style=\"color:#f00;\">received</div>\r\n");
     local.sin_family = AF_INET;
     local.sin_addr.s_addr = htonl(INADDR_ANY);
     local.sin_port = htons(port);
     bind(listenfd, (struct sockaddr *)&local, sizeof(local));
     listen(listenfd, 5);
     core()->console << "started listening port " << port << "\n";
     for (;;) {
         len = sizeof(client);
         connfd = accept(listenfd, (struct sockaddr *)&client, (socklen_t *)&len);
         core()->console << "accepted connection from " << inet_ntoa(client.sin_addr) << "\n";
         // write(connfd, "<div>received</div>", strlen("<div>received</div>"));
         Atom args[1] = {nullObjectAtom};
         callback->call(0, args);
         send(connfd, buf, (int)strlen(buf), 0);
     }
     close(connfd);
     return listenfd;
 }
}
