import nodeas.*;
import nodeas.socket.*;

trace("hello, world!");
var nodeas: Nodeas = new Nodeas();
trace(nodeas);
trace(Nodeas.getVersion());
var socket: uint = Socket.startlisten(8080);
var connfd: uint;
var test_html:String = "HTTP/1.0 200 OK\r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n<div style=\"color:#f00;\">received</div>\r\n";
for (;;) {
	connfd = Socket.accept(socket);
	trace(Socket.recv(connfd));
	Socket.send(connfd, test_html);
}
Socket.close(socket);

