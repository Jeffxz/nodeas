
package nodeas
{
    /**
     * The Nodeas class creates objects that hold memory analysis information over distinct durations.
     * For Flash Player debugger version only.
     *
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword Nodeas      
     */
    [native(cls="NodeasClass", instance="NodeasObject", methods="auto", constsetters="true")]
    public class Nodeas
    {
    /**
     * get version
     */
    public native static function getVersion(): String;
    /**
     * start listening
     */
    public native static function startlisten(port:uint, f:Function): Number;
    };
};
