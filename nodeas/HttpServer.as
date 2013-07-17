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
    public class HttpServer
    {
        private var _socket: uint;
        private var _connfd: uint;
        private var _response: HttpResponse;
        private var _request: HttpRequest;

        public function HttpServer(in_port:uint)
        {
            trace("HttpServer is starting at port:" + in_port);
            _socket = Socket.startlisten(in_port);
            _response = new HttpResponse;
            _request = new HttpRequest;
        }

        public function start(in_fn:Function):void
        {
            for (;;) {
                _connfd = Socket.accept(_socket);
                _response.setConnectHandle(_connfd);
                _request.setRequest(Socket.recv(_connfd));
                in_fn.call(this, _request, _response);
            }
        }

        public function stop():void
        {
            Socket.close(_socket);
        }
    }

};

