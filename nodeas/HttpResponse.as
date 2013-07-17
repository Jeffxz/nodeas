/* vim: set et ts=4 sw=4 : */

package nodeas.http
{
    import nodeas.socket.Socket
    /**
     * The Nodeas class creates objects that hold memory analysis information over distinct durations.
     * For Flash Player debugger version only.
     *
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword Nodeas      
     */
    public class HttpResponse
    {
        private var _handle: uint;

        private function createHeader(): String {
            return "HTTP/1.0 200 OK\r\nContent-Length: 20\r\nContent-Type: text/html\r\n\r\n";
        }

        public function setConnectHandle(in_handle: uint) {
            _handle = in_handle;
        }

        public function send(in_html: String, in_status: uint = 200) {
            var header:String = createHeader();
            Socket.send(_handle, header + in_html);
        }
    };

};


