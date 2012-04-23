import nodeas.*;
import nodeas.http.*;

trace("hello, world!");
var nodeas: Nodeas = new Nodeas();
trace(nodeas);
trace(Nodeas.getVersion());
var socket: uint = Http.startlisten(8080);
var connfd: uint;
var test_html:String = "HTTP/1.0 200 OK\r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n<div style=\"color:#f00;\">received</div>\r\n";
for (;;) {
	connfd = Http.accept(socket);
	Http.recv(connfd);
	Http.send(connfd, test_html);
}
Http.close(socket);
