import nodeas.*;
import nodeas.socket.*;
import nodeas.http.HttpServer;
import nodeas.http.HttpResponse;
import nodeas.http.HttpRequest;

trace("Start!");
var test_html1:String = "<div style=\"color:#f00;\">This is in html1</div>\r\n";
var test_html2:String = "<div style=\"color:#f00;\">This is in html2</div>\r\n";
var html_404: String = "<div style=\"color:#f00;\">Not found</div>\r\n";

function send_socket(in_request:HttpRequest, in_response:HttpResponse)
{
    var path = in_request.getPath();
    if(path == "/") {
        in_response.send(test_html1);
    } else if (path == "/test.html") {
        in_response.send(test_html2);
    } else {
        in_response.send(html_404, 404);
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

