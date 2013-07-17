/* vim: set et ts=4 sw=4 : */

package nodeas.http
{
    /**
     * The Nodeas class creates objects that hold memory analysis information over distinct durations.
     * For Flash Player debugger version only.
     *
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword Nodeas      
     */
    public class HttpRequest
    {
        var _request: String;

        public function setRequest(in_str: String) {
            trace(in_str);
            _request = in_str;
        }

        public function getPath() {
            return _request.substring(4, _request.indexOf("HTTP/") - 1);
        }
    };

};

