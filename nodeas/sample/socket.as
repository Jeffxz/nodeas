import nodeas.*;
import nodeas.socket.*;

trace("Start!");
var socket: uint = Socket.startlisten(8080);
var connfd: uint;
var test_html1:String = "HTTP/1.0 200 OK\r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n<div style=\"color:#f00;\">This is in html1</div>\r\n";
var test_html2:String = "HTTP/1.0 200 OK\r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n<div style=\"color:#f00;\">This is in html2</div>\r\n";
var html_404: String = "HTTP/1.0 404 \r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n<div style=\"color:#f00;\">Not found</div>\r\n";
for (;;) {
	connfd = Socket.accept(socket);
        var request:String = Socket.recv(connfd);
        trace(request);
        var filePath:String = request.substring(4, request.indexOf("HTTP/") - 1);
        trace("[debug]" + filePath);
        if(filePath == "/") {
            Socket.send(connfd, test_html1);
        } else if (filePath == "/test.html") {
            Socket.send(connfd, test_html2);
        } else {
            Socket.send(connfd, html_404);
        }
}
Socket.close(socket);

