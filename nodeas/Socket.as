/* vim: set et ts=4 sw=4 : */

package nodeas.socket
{
    /**
     * The Nodeas class creates objects that hold memory analysis information over distinct durations.
     * For Flash Player debugger version only.
     *
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword Nodeas      
     */
    [native(cls="SocketClass", instance="SocketObject", methods="auto", constsetters="true")]
    public class Socket
    {
    /**
     * start listening
     */
    public native static function startlisten(port:uint): uint;

	/**
	 * accept
	 */
    public native static function accept(socket: uint): uint;

	/**
	 * send
	 */
    public native static function send(connfd: uint, data: String): uint;

	/**
	 * recv
	 */
    public native static function recv(connfd: uint): String;

	/**
	 * close
	 */
    public native static function close(connfd: uint): void;
    };

};
