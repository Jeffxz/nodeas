/* vim: set et ts=4 sw=4 : */

#ifdef AVMSHELL_BUILD
#include "avmshell.h"
#else
// player
#include "platformbuild.h"
#include "avmplayer.h"
#include "NodeasClass.h"
#endif

using namespace MMgc;

namespace avmplus
{
 using namespace MMgc;

 /* NodeasObject */
 NodeasObject::NodeasObject(VTable *vtable, ScriptObject *delegate)
  : ScriptObject(vtable, delegate) 
 {}

 /* NodeasClass */
 NodeasClass::NodeasClass(VTable *vtable)
  : ClassClosure(vtable)
 {
  createVanillaPrototype();
 }

 ScriptObject *NodeasClass::createInstance(VTable *ivtable, ScriptObject* /*delegate*/)
 {
  return new (core()->gc, ivtable->getExtraSize()) NodeasObject(ivtable, prototype);
 }

 Stringp NodeasClass::getVersion()
 {
    return core()->newConstantStringLatin1("0.1");
 }
}
