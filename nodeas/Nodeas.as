package nodeas
{
    /**
     * The Nodeas class creates objects that hold memory analysis information over distinct durations.
     * For Flash Player debugger version only.
     *
     * @includeExample examples\NodeasTypesExample.as -noswf     
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword Nodeas      
     * @see package.html#getNodeass() flash.sampler.getNodeass()
     */
    [native(cls="NodeasClass", instance="NodeasObject", methods="auto", constsetters="true")]
    public class Nodeas
    {
    /**
     * get version
     */
    public native static function getVersion(): String;
  /**
      * The microseconds that define the duration of the Nodeas instance. For Flash Player debugger version only.
   * 
   * @playerversion Flash 9.0.115.0
      * @langversion 3.0     
      * @keyword Nodeas, Nodeas.time, time         
   */
        public const time:Number;

  /**
   * Contains information about the methods executed by Flash Player over a specified period of time. The format for the 
      * stack trace is similiar to the content shown in the exception dialog box of the Flash Player debugger version.
         * For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
      * @langversion 3.0     
      * @keyword Nodeas, Nodeas.stack, stack     
   */
        public const stack:Array;
    };

    /**
    * The NewObjectNodeas class represents objects that are created within a <code>getNodeass()</code> stream.
    * For Flash Player debugger version only.
    * @playerversion Flash 9.0.115.0
    * @langversion 3.0     
    * @keyword NewObjectNodeas 
    * @see package.html#getNodeass() flash.sampler.getNodeass()
    * @includeExample examples\NodeasTypesExample.as -noswf    
    */
    [native(cls="NewObjectNodeasClass", instance="NewObjectNodeasObject", methods="auto", constsetters="true")]
    public final class NewObjectNodeas extends Nodeas
    {
     /** 
      * The unique identification number that matches up with a DeleteObjectNodeas's identification number.
         * For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword NewObjectNodeas, NewObjectNodeas.id, id  
         * @see flash.sampler.DeleteObjectNodeas#id
      */
     public const id:Number;
     
     /**
         * The Class object corresponding to the object created within a <code>getNodeass()</code> stream.
         * For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword NewObjectNodeas, NewObjectNodeas.type, type 
      */
     public const type:Class;
     
     /**
      * The NewObjectNodeas object if it still exists. If the object has been garbage collected, this property is
      * undefined and a corresponding DeleteObjectNodeas exists. For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword NewObjectNodeas, NewObjectNodeas.object, object 
         * @see flash.sampler.DeleteObjectNodeas         
      */
     public native function get object():*;

        public native function get size() : Number;
    };
 
 /**
    * The DeleteObjectNodeas class represents objects that are created within a <code>getNodeass()</code> stream; each
    * DeleteObjectNodeas object corresponds to a NewObjectNodeas object. For Flash Player debugger version only.
    * @playerversion Flash 9.0.115.0
    * @langversion 3.0     
    * @keyword DeleteObjectNodeas 
    * @see package.html#getNodeass() flash.sampler.getNodeass()
    * @includeExample examples\NodeasTypesExample.as -noswf    
    */    
    [native(cls="DeleteObjectNodeasClass", instance="DeleteObjectNodeasObject", methods="auto", constsetters="true")] // @todo: native only for slot getter/setter
    public final class DeleteObjectNodeas extends Nodeas
    {
     /** 
         * The unique identification number that matches up with a NewObjectNodeas's identification number.
         * For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword DeleteObjectNodeas, DeleteObjectNodeas.id, id  
         * @see flash.sampler.NewObjectNodeas#id
         */
     public const id:Number;

     /**
         * The size of the DeleteObjectNodeas object before it is deleted. For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword DeleteObjectNodeas, DeleteObjectNodeas.size, size  
         * @see flash.sampler.NewObjectNodeas#id
         */
  public const size:Number;
    };


    /**
     * Clears the current set of Nodeas objects. This method is usually called after calling <code>getNodeass()</code>
     * and iterating over the Nodeas objects.
     * For Flash Player debugger version only.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword clearNodeass      
     * @see package.html#getNodeass() getNodeass()
     */
    [native("NodeasScript::clearNodeass")]
 public native function clearNodeass():void;

    /**
     * Begins the process of collecting memory usage Nodeas objects.
     * For Flash Player debugger version only.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @includeExample examples\StartSamplingExample.as -noswf      
     * @keyword startSampling      
     * @see flash.sampler.Nodeas Nodeas class
     */
    [native("NodeasScript::startSampling")]
 public native function startSampling():void;

 /**
  * Ends the process of collecting memory usage Nodeas objects and frees resources dedicated to the sampling process.
     * You start the sampling process with <code>startSampling()</code>.
     * For Flash Player debugger version only.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword stopSampling      
     * @see flash.sampler.Nodeas Nodeas class
  */
    [native("NodeasScript::stopSampling")]
 public native function stopSampling():void;

 /**
     * Stops the sampling process momentarily. Restart the sampling process using <code>startSampling()</code>.
     * For Flash Player debugger version only.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword pauseSampling      
     * @see package.html#startSampling() startSampling()
  */
    [native("NodeasScript::pauseSampling")]
 public native function pauseSampling():void;
 
 /**
     * Tells the sampler if it should create NewObjectNodeass for internal allocations from the flash player.
     * If this is set to true, then every allocation will generate a NewObjectNodeas.  These internal allocs will
     * not have a type, or a reference to the Object.  They will have the ActionScript stack trace that triggered the
     * allocation.  Defaults to false, which only collects allocations for ActionScript objects.
     * @langversion 3.0
     * @keyword sampleInternalAllocs
     */
    [native("NodeasScript::sampleInternalAllocs")]
 public native function sampleInternalAllocs(b:Boolean):void;

 /**
     * Set a callback function for the sampler - this function will be called when the sample stream is almost
     * exhausted.  This should be used to process samples before the sample buffer is filled.  pauseSampling will be called
     * before the callback is called, and startSampling will be called after the callback has been executed.
     * @langversion 3.0
     * @keyword sampleInternalAllocs
     */
 public function setNodeasCallback(f:Function):void
    {
        if( f != null )
        {
            // Use a wrapper to swallow any exceptions thrown by the callback.
            var wrapper = function() 
            {
                var ret:Boolean = true;
                try
                {
                    f();
                }
                catch(e)
                {
                    ret = false; 
                }
                return ret;
            }
            _setNodeasCallback(wrapper);
        }
        else
        {
            _setNodeasCallback(null);
        }
    }
    [native("NodeasScript::_setNodeasCallback")]
    native function _setNodeasCallback(f:Function):void;
    
 /**
 * Returns the size in memory of a specified object when used with the Flash Player 9.0.115.0 or later debugger version. If 
    * used with a Flash Player that is not the debugger version, this method returns <code>0</code>.
    * @param o The object to analyze for memory usage.
    * @return The byte count of memory used by the specified object.
    * @includeExample examples\DeletedObjectSizeExample.as -noswf      
    * @playerversion Flash 9.0.115.0
    * @langversion 3.0     
    * @keyword getSize      
 */
    [native("NodeasScript::getSize")]
 public native function getSize(o:*):Number;

    /**
     * Returns an object containing all members of a specified object, including private members. You can then 
     * iterate over the returned object to see all values. This method is similar to the flash.utils.describeType() 
     * method but also allows you to see private members and skips the intermediate step of creating an XML object.
     * For Flash Player debugger version only.
     *
     * @param o The object to analyze.
     * @param instanceNames If object is a Class and instanceNames is true report the instance names as if o was an instance of class instead of the class's member names.
     * @return An Object that you must iterate over with a <code>for each..in</code> loop to retrieve the QNames for
     * each property. 
     * @includeExample examples\GetMemberNamesExample.as -noswf       
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getMemberNames
     * @see flash.utils#describeType()
     * @see ../../statements.html#for_each..in for each..in    
     * 
     */
    [native("NodeasScript::getMemberNames")]
    public native function getMemberNames(o:Object, instanceNames:Boolean=false):Object;

 
    /**
     * Returns an object of memory usage Nodeas instances from the last sampling session. For Flash Player debugger version only.
     *
     * @return An iterator of Nodeas instances.
     * @playerversion Flash 9.0.115.0 
     * @langversion 3.0     
     * @keyword getNodeass     
     * @see flash.sampler.Nodeas
     */
    [native("NodeasScript::getNodeass")]
    public native function getNodeass():Object;

    /** 
     * Returns the number of samples collected. For Flash Player debugger version only.
     *
     * @return An iterator of Nodeas instances.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getNodeasCount     
     * @see flash.sampler.Nodeas    
     */
    [native("NodeasScript::getNodeasCount")]
    public native function getNodeasCount():Number;
 
   /**
     * Returns the number of times a method was executed. If the parameter <code>obj</code>
     * is a Class and the parameter <code>qname</code> is <code>undefined</code> then this method
     * returns the number of iterations of the constructor function. For Flash Player debugger version only.
     * @param obj A method instance or a class. A class can be used to get the invocation count of 
     * instance functions when a method instance isn't available. If <code>obj</code> is <code>undefined</code>,
     * this method returns the count of the package-scoped function named by <code>qname</code>.
     * @param qname If qname is <code>undefined</code> return the number of iterations of the constructor function.
     * @return The number of times a method was executed.
     * @includeExample examples\GetInvocationCountExample.as -noswf       
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getInvocationCount     
     */
    public function getInvocationCount(obj:Object, qname:QName):Number { return _getInvocationCount(obj, qname, 0); }
    
    /**
     * Returns the number of times a set function was executed. Use 
     * <code>isGetterSetter()</code> to verify that you have a get/set function before you use
     * <code>getSetterInvocationCount()</code>. For Flash Player debugger version only.
     * @param obj A method instance or a class.
     * @param qname If qname is <code>undefined</code> return the number of iterations of the constructor function.
     * @return The number of times a set method was executed.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getInvocationCount   
     * @see package.html#isGetterSetter() isGetterSetter()
     * @see package.html#getInvocationCount() getInvocationCount()
     */    
    public function getSetterInvocationCount(obj:Object, qname:QName):Number { return _getInvocationCount(obj, qname, 2); }
    
    /**
     * Returns the number of times a get function was executed. Use 
     * <code>isGetterSetter()</code> to verify that you have a get/set function before you use
     * <code>getGetterInvocationCount()</code>. For Flash Player debugger version only.
     * @param obj A method instance or a class.
     * @param qname If qname is <code>undefined</code> return the number of iterations of the constructor function.
     * @return The number of times a get method was executed.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getInvocationCount   
     * @see package.html#isGetterSetter() isGetterSetter()
     * @see package.html#getInvocationCount() getInvocationCount()
     */        
    public function getGetterInvocationCount(obj:Object, qname:QName):Number { return _getInvocationCount(obj, qname, 1); }

    /** 
    * @private
    */
    [native("NodeasScript::_getInvocationCount")]
    native function _getInvocationCount(obj:Object, qname:QName, type:uint):Number;

   /**
     * Checks to see if a property is defined by a get/set function. If you want to use 
     * <code>getInvocationCount()</code> on a get/set function for a property,
     * first call <code>isGetterSetter()</code> to check to see if it is a get/set function,
     * and then use either <code>getSetterInvocationCount</code>
     * or <code>getGetterInvocationCount</code> to get the respective counts. For Flash Player debugger version only.
     * @param obj A method instance or a class.
     * @param qname If qname is <code>undefined</code> return the number of iterations of the constructor function.
     * @return A Boolean value indicating if the property is defined by a get/set function (<code>true</code>)
     * or not (<code>false</code>).
     * @includeExample examples\GetInvocationCountExample.as -noswf       
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getInvocationCount   
     * @see package.html#getInvocationCount() getInvocationCount()
     * @see package.html#getSetterInvocationCount() getSetterInvocationCount() 
     * @see package.html#getGetterInvocationCount() getGetterInvocationCount() 
     */
    [native("NodeasScript::isGetterSetter")]
    public native function isGetterSetter(obj:Object, qname:QName):Boolean;
};
