import nodeas.*;
import nodeas.socket.*;
import nodeas.http.HttpServer;

trace("Start!");
var test_html1:String = "HTTP/1.0 200 OK\r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n<div style=\"color:#f00;\">This is in html1</div>\r\n";
var test_html2:String = "HTTP/1.0 200 OK\r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n<div style=\"color:#f00;\">This is in html2</div>\r\n";
var html_404: String = "HTTP/1.0 404 \r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n<div style=\"color:#f00;\">Not found</div>\r\n";

function send_socket(in_path:String, in_connfd:uint)
{
    if(in_path == "/") {
        Socket.send(in_connfd, test_html1);
    } else if (in_path == "/test.html") {
        Socket.send(in_connfd, test_html2);
    } else {
        Socket.send(in_connfd, html_404);
    }
};

try {
    var server:HttpServer = new HttpServer(5689);
    server.start(send_socket);
    server.stop();
} catch (error: Error) {
    trace("catch");
    trace(error.toString());
}
