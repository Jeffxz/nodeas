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
        private var socket: uint;
        private var connfd: uint;

        public function HttpServer(port:uint)
        {
            trace("HttpServer is starting at port:" + port);
            socket = Socket.startlisten(port);
        }

        public function start(fn:Function):void
        {
            for (;;) {
                connfd = Socket.accept(socket);
                var request:String = Socket.recv(connfd);
                trace(request);
                var path:String = request.substring(4, request.indexOf("HTTP/") - 1);
                trace("[debug]" + path);
                fn.call(this, path, connfd);
            }
        }

        public function stop():void
        {
            Socket.close(socket);
        }
    }

};

