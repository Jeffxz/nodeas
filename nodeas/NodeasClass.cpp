
#ifdef AVMSHELL_BUILD
#include "avmshell.h"
#else
// player
#include "platformbuild.h"
#include "avmplayer.h"
#include "NodeasClass.h"
#endif

#include "nodeassocket.h"

using namespace MMgc;

namespace avmplus
{
 using namespace MMgc;

#ifdef DEBUGGER

 class NodeasIterator : public ScriptObject
 {
 public:
  NodeasIterator(Nodeas *sampler, ScriptObject* script, VTable *vt) : 
   ScriptObject(vt, NULL),
   sampler(sampler),
   script(script)
  {
   cursor = sampler->getNodeass(count);   
  }

  int nextNameIndex(int index) 
  {
   if(count == 0)
   {
    return 0;
   }    
   return index+1;
  }

  Atom nextValue(int i)
  {
   (void) i;
   Nodeas s;
   sampler->readNodeas(cursor, s);
   count--;
   ScriptObject* sam = NodeasScript::makeNodeas(script, s);
   if(!sam) {
    count = 0;   
    return undefinedAtom;
   }
   return sam->atom();
  }

  
  Atom nextName(int)
  {
   // they are iterating over the names, bail
   count = 0;
   return undefinedAtom;
  }

 private:
  uint32 count;
  byte *cursor;
  Nodeas *sampler;
  DRCWB(ScriptObject*) script;
 };

 class SlotIterator : public ScriptObject
 {
 public:
  SlotIterator(Traits *t, VTable *vtable)
   : ScriptObject(vtable, NULL) 
   , currTraits(t ? t->getTraitsBindings() : NULL)
  {
  }

  int nextNameIndex(int index)
  {
   while (currTraits != NULL)
   {
    while ((index = currTraits->next(index)) != 0)
    {
      return index;
    }

    currTraits = currTraits->base;
   }

   return 0;
  }

  Atom nextValue(int index)
  {
   Multiname mn(currTraits->nsAt(index), currTraits->keyAt(index), true);
   QNameObject *qname = new (gc(), toplevel()->qnameClass()->ivtable()->getExtraSize())
         QNameObject(toplevel()->qnameClass(), mn);

   return qname->atom();
  }

  Atom nextName(int)
  {
   // they are iterating over the names, bail
   currTraits = NULL;
   return undefinedAtom;
  }

 private:
  DWB(TraitsBindingsp) currTraits;
 };

#endif // DEBUGGER

#ifdef DEBUGGER
 static VTable* _newVT(Toplevel* toplevel, PoolObject* pool, uint16_t sz)
 {
  Traits* t = Traits::newTraits(pool, NULL, sz, 0, 0, TRAITSTYPE_RT);
  return toplevel->core()->newVTable(t, NULL, toplevel);
 }
#endif

 Atom NodeasScript::getNodeass(ScriptObject* self)
 { 
#ifdef DEBUGGER
  AvmCore* core = self->core();
  Nodeas *s = core->get_sampler();
  if (!s || !s->sampling() || s->sampleCount() == 0 || !trusted(self))
   return undefinedAtom;
  
  if (s->sampleIteratorVTable == NULL)
   s->sampleIteratorVTable = _newVT(self->toplevel(), self->traits()->pool, sizeof(NodeasIterator));
  ScriptObject *iter = new (self->gc()) NodeasIterator(s, self, s->sampleIteratorVTable);
  return iter->atom();
#else
  (void)self;
  return undefinedAtom;
#endif
 }

 double NodeasScript::getNodeasCount(ScriptObject* self)
 {
#ifdef DEBUGGER
  Nodeas* s = self->core()->get_sampler();
  if (!s) 
   return -1;
  uint32 num;
  s->getNodeass(num);
  return (double)num;
#else
  (void)self;
  return -1;
#endif
 }

#ifdef DEBUGGER
 ClassClosure *NodeasScript::getType(Toplevel* ss_toplevel, NodeasObjectType sot, const void *ptr)
 {
        Toplevel* tl;
        
        switch (sotGetKind(sot))
        {
            case kSOT_String:
            {
                // toplevel can be null here if there was no CodeContext active
                // when the sample was taken (ie, string was allocated from C++ code).
                // in that case, use the TL from the NodeasScript itself... it isn't
                // technically the right one to use, but is adequate for our purposes here
                // (it will return a stringClass or namespaceClass that will be valid
                // for the sampler)
                tl = sotGetToplevel(sot);
                if (!tl) tl = ss_toplevel;
    return tl->stringClass;
            }
            case kSOT_Namespace:
            {
                tl = sotGetToplevel(sot);
                if (!tl) tl = ss_toplevel;
    return tl->namespaceClass;
            }
            default:
                AvmAssert(0);
            case kSOT_Object:
                break;
  }
  
        VTable* vt = sotGetVTable(sot);
        tl = vt->toplevel();
        AvmCore* core = tl->core();
        
  ClassClosure *type;
  ScriptObject* obj = (ScriptObject*)ptr;
  if (obj && AvmCore::istype(obj->atom(), core->traits.class_itraits))
  {
   type = tl->classClass;
  } 
  else if (obj && AvmCore::istype(obj->atom(), core->traits.function_itraits))
  {
   type = tl->functionClass;
  }
  else if (obj && obj->traits()->isActivationTraits())
  {
   type = tl->objectClass;
  }
  else
  {
   // fallback answer
   type = tl->objectClass;
   
   // note that note all types will have an init method,
   // so those types may get reported as "objectClass" rather
   // than something more specific. However, it's not clear
   // that the Nodeas ever really cared about reporting those
   // objects well in the first place (eg activation or catch objects),
   // so it doesn't seem we're a lot worse off than before.
   ScopeChain* sc = NULL;
   if (vt->init)
    sc = vt->init->scope();
   
   if (sc && sc->getSize() <= 1) 
            {
    if(sc->getSize() == 1)
     type = tl->classClass;
   } 
            else if (sc) 
            {
    Atom ccAtom = sc->getScope(sc->getSize()-1);
    if(AvmCore::isObject(ccAtom))
    {
     type = (ClassClosure*) AvmCore::atomToScriptObject(ccAtom);
     if(!AvmCore::istype(type->atom(), core->traits.class_itraits))
     {
      // obj is a ClassClosure
      type = tl->classClass;
     }
    }
   }
  }
  AvmAssert(AvmCore::istype(type->atom(), core->traits.class_itraits)); 
  return type; 
 }
#endif // DEBUGGER

#ifdef DEBUGGER
 bool NodeasScript::set_stack(ScriptObject* self, const Nodeas& sample, NodeasObject* sam)
 {
  if (sample.stack.depth > 0)
  {
   Toplevel* toplevel = self->toplevel();
   AvmCore* core = toplevel->core();
   Nodeas* s = core->get_sampler();

   StackFrameClass* sfcc = (StackFrameClass*)toplevel->getBuiltinExtensionClass(NativeID::abcclass_flash_sampler_StackFrame);
   ArrayObject* stack = toplevel->arrayClass->newArray(sample.stack.depth);
   StackTrace::Element* e = (StackTrace::Element*)sample.stack.trace;
   for(uint32 i=0; i < sample.stack.depth; i++, e++)
   {
    StackFrameObject* sf = (StackFrameObject*)sfcc->createInstance(sfcc->ivtable(), NULL);
    
    // at every allocation the sample buffer could overflow and the samples could be deleted
    // the StackTrace::Element pointer is a raw pointer into that buffer so we need to check
    // that its still around before dereferencing e
    uint32_t num;
    if (s->getNodeass(num) == NULL)
     return false;
    
    sf->set_name(e->name()); // NOT e->info()->name() because e->name() can be a fake name
    if(e->filename())
     sf->set_file(e->filename());
    sf->set_line(e->linenum());
    sf->set_scriptID(static_cast<double>(e->functionId()));

    stack->setUintProperty(i, sf->atom());
   }   
   sam->set_stack(stack);
  }
  return true;
 }

 NodeasObject* NodeasScript::new_sam(ScriptObject* self, const Nodeas& sample, int clsid)
 {
  Toplevel* toplevel = self->toplevel();
  ClassClosure* cc = toplevel->getBuiltinExtensionClass(clsid);
  NodeasObject* sam = (NodeasObject*)cc->createInstance(cc->ivtable(), NULL);
  sam->set_time(static_cast<double>(sample.micros));
  return sam;
 }

 ScriptObject* NodeasScript::makeNodeas(ScriptObject* self, const Nodeas& sample)
 {
  Toplevel* toplevel = self->toplevel();
  AvmCore* core = toplevel->core();
  Nodeas* s = core->get_sampler();
  if (!s)
   return NULL;
  
  switch (sample.sampleType)
  {
   case Nodeas::RAW_SAMPLE:
   {
    NodeasObject* sam = new_sam(self, sample, NativeID::abcclass_flash_sampler_Nodeas);
    if (!set_stack(self, sample, sam))
     return NULL;
    return sam;
   }
   case Nodeas::DELETED_OBJECT_SAMPLE:
   {
    DeleteObjectNodeasObject* dsam = (DeleteObjectNodeasObject*)new_sam(self, sample, NativeID::abcclass_flash_sampler_DeleteObjectNodeas);
    dsam->set_id(static_cast<double>(sample.id));
    dsam->set_size(static_cast<double>(sample.size));
    return dsam;
   }
   case Nodeas::NEW_OBJECT_SAMPLE:
   {
    NewObjectNodeasObject* nsam = (NewObjectNodeasObject*)new_sam(self, sample, NativeID::abcclass_flash_sampler_NewObjectNodeas);
    nsam->set_id(static_cast<double>(sample.id));
    if (!set_stack(self, sample, nsam))
     return NULL;
    if (sample.ptr != NULL )
     nsam->setRef((AvmPlusScriptableObject*)sample.ptr);
    nsam->set_type(getType(toplevel, sample.sot, sample.ptr));
    nsam->setSize(sample.alloc_size);
    return nsam;
   }
   case Nodeas::NEW_AUX_SAMPLE:
   {
    NewObjectNodeasObject* nsam = (NewObjectNodeasObject*)new_sam(self, sample, NativeID::abcclass_flash_sampler_NewObjectNodeas);
    nsam->set_id(static_cast<double>(sample.id));
    if (!set_stack(self, sample, nsam))
     return NULL;
    nsam->setSize(sample.alloc_size);
    return nsam;
   }
  }

  AvmAssert(0);
  return NULL;
 }
#endif // DEBUGGER

 
 Atom NodeasScript::getMemberNames(ScriptObject* self, Atom o, bool instanceNames)
 {
#ifdef DEBUGGER
  AvmCore* core = self->core();
  MMgc::GC* gc = core->GetGC();
  Nodeas* s = core->get_sampler();
  if (!s || !trusted(self))
   return undefinedAtom;

  if (AvmCore::isObject(o))
  {
   Traits *t = AvmCore::atomToScriptObject(o)->traits();
   if(AvmCore::istype(o, CLASS_TYPE) && instanceNames && t->itraits)
    t = t->itraits;
   if (s->slotIteratorVTable == NULL)
    s->slotIteratorVTable = _newVT(self->toplevel(), self->traits()->pool, sizeof(SlotIterator));
   return (new (gc) SlotIterator(t, s->slotIteratorVTable))->atom();      
  }
#else
  (void)self;
  (void)o; (void)instanceNames;
#endif
  return undefinedAtom;
 }

 static double _get_size(Atom a)
 {
#ifdef DEBUGGER
  switch(a&7)
  {
  case kDoubleType:
   return 8;
  case kObjectType:
  case kStringType:
  case kNamespaceType:
   AvmPlusScriptableObject *o = (AvmPlusScriptableObject*)(a&~7);
   if(o)
    return (double)o->size();
  }
  return 4;
#else
  (void)a;
  return 0;
#endif
 }

 double NodeasScript::getSize(ScriptObject* self, Atom a)
 {
#ifdef DEBUGGER
  AvmCore* core = self->core();
  Nodeas* s = core->get_sampler();
  if (!s)
   return 0;
  return _get_size(a);
#else
  (void)self;
  (void)a;
  return 0;
#endif
 }

 void NodeasScript::startSampling(ScriptObject* self) 
 { 
#ifdef DEBUGGER
  Nodeas* s = self->core()->get_sampler();
  if (!s || !trusted(self))
   return;
  s->startSampling(); 
#else
  (void)self;
#endif
 }
 
 void NodeasScript::stopSampling(ScriptObject* self) 
 { 
#ifdef DEBUGGER
  Nodeas* s = self->core()->get_sampler();
  if (!s || !trusted(self))
   return;
  s->stopSampling(); 
#else
  (void)self;
#endif
 }

 void NodeasScript::clearNodeass(ScriptObject* self) 
 {
#ifdef DEBUGGER
  Nodeas* s = self->core()->get_sampler();
  if (!s || !trusted(self))
   return;
  s->clearNodeass();
#else
  (void)self;
#endif
 }  

 void NodeasScript::pauseSampling(ScriptObject* self) 
 {
#ifdef DEBUGGER
  Nodeas* s = self->core()->get_sampler();
  if (!s || !trusted(self))
   return;
  s->pauseSampling();
#else
  (void)self;
#endif
 } 

 void NodeasScript::sampleInternalAllocs(ScriptObject* self, bool b)
 {
#ifdef DEBUGGER
  Nodeas* s = self->core()->get_sampler();
  if (!s || !trusted(self))
   return;
  s->sampleInternalAllocs(b);
#else
  (void)self;
  (void)b;
#endif
 }

 void NodeasScript::_setNodeasCallback(ScriptObject* self, ScriptObject *callback)
 {
#ifdef DEBUGGER
  Nodeas* s = self->core()->get_sampler();
  if (!s || !trusted(self))
   return;
  s->setCallback(callback);
#else
  (void)self;
  (void)callback;
#endif
 }

 double NodeasScript::_getInvocationCount(ScriptObject* self, Atom a, QNameObject* qname, uint32 type) 
 {
#ifdef DEBUGGER
  AvmCore* core = self->core();
  Nodeas* s = core->get_sampler();
  if (!s || !trusted(self))
   return -1;

  Multiname multiname;
  if(qname)
   qname->getMultiname(multiname);

  ScriptObject* object = self->toplevel()->global();
  if(!AvmCore::isObject(a))
  {
   // not sure if this will be true for standalone avmplus
   AvmAssert(core->codeContext() != NULL);
   DomainEnv *domainEnv = core->codeContext()->domainEnv();
   ScriptEnv* script = (ScriptEnv*) domainEnv->getScriptInit(multiname);
   if (script != (ScriptEnv*)BIND_NONE)
   {
    if (script == (ScriptEnv*)BIND_AMBIGUOUS)
     self->toplevel()->throwReferenceError(kAmbiguousBindingError, &multiname);

    object = script->global;
    if (object == NULL)
    {
     object = script->initGlobal();
     script->coerceEnter(script->global->atom());
    }    
   }
  }
  else
  {
   object = AvmCore::atomToScriptObject(a);

   if(AvmCore::istype(a, CLASS_TYPE) && !qname) {
    // return constructor count
    ClassClosure *cc = (ClassClosure*)object;
    if (cc->vtable->init) // Vector related crash here, Tommy says: I didn't think a type could ever not have a constructor but I guess there's no reason it has to.
     return (double)cc->vtable->init->invocationCount();
   }
  }

  if(!object || !qname)   
   return -1;

  VTable *v = object->vtable;
 
 again:

  MethodEnv *env = NULL;
  Binding b = self->toplevel()->getBinding(v->traits, &multiname);
  switch (AvmCore::bindingKind(b))
  {
  case BKIND_VAR:
  case BKIND_CONST:
  { 
   // only look at slots for first pass, otherwise we're applying instance traits to the Class
   if(v == object->vtable) {
    Atom method = object->getSlotAtom(AvmCore::bindingToSlotId(b));
    if(AvmCore::isObject(method))
    {
     env = AvmCore::atomToScriptObject(method)->getCallMethodEnv();
    }
   }
   break;
  }
  case BKIND_METHOD:
  {
   int m = AvmCore::bindingToMethodId(b);
   env = v->methods[m];
   break;
  }
  case BKIND_GET:
  case BKIND_GETSET:
  case BKIND_SET:
  { 
   if(type == GET && AvmCore::hasGetterBinding(b))
    env = v->methods[AvmCore::bindingToGetterId(b)];
   else if(type == SET && AvmCore::hasSetterBinding(b))
    env = v->methods[AvmCore::bindingToSetterId(b)];
   break;
  }
  case BKIND_NONE:
  {
   Atom method = object->getStringProperty(multiname.getName());
   if(AvmCore::isObject(method))
   {
    env = AvmCore::atomToScriptObject(method)->getCallMethodEnv();
   }
   else if(v->ivtable)
   {
    v = v->ivtable;
    goto again;
   }
  }
  default:
   break;
  }

  if(env)
   return (double)env->invocationCount();
#else
  (void)self;
  (void)type;
  (void)qname;
  (void)a;
#endif

  return -1;
 }
  
 bool NodeasScript::isGetterSetter(ScriptObject* self, Atom a, QNameObject *qname)
 {
#ifdef DEBUGGER
  AvmCore* core = self->core();
  Nodeas* s = core->get_sampler();
  if (!s)
   return false;
   
  if(!AvmCore::isObject(a) || !AvmCore::atomToScriptObject(a))
   self->toplevel()->throwArgumentError(kInvalidArgumentError, "object");

  ScriptObject *object = AvmCore::atomToScriptObject(a);

  if(!object || !qname)   
   self->toplevel()->argumentErrorClass()->throwError(kInvalidArgumentError);

  Multiname multiname;
  qname->getMultiname(multiname);

  VTable *v = object->vtable;
 
 again:

  Binding b = self->toplevel()->getBinding(v->traits, &multiname);
 
  if(b == BIND_NONE && v->ivtable)
  {
   v = v->ivtable;
   goto again;
  }

  return AvmCore::hasSetterBinding(b) || AvmCore::hasGetterBinding(b);
#else
  (void)self;
  (void)a; (void)qname;
  return false;
#endif
 }

 
 /* NodeasObject */
 NodeasObject::NodeasObject(VTable *vtable, ScriptObject *delegate)
  : ScriptObject(vtable, delegate) 
 {}

  /* NewObjectNodeasObject */
 NewObjectNodeasObject::NewObjectNodeasObject(VTable *vtable, ScriptObject *delegate)
  : NodeasObject(vtable, delegate), size(0)
 {}

 DeleteObjectNodeasObject::DeleteObjectNodeasObject(VTable *vtable, ScriptObject *delegate)
  : NodeasObject(vtable, delegate)
 {}

 Atom NewObjectNodeasObject::get_object()
 {
  if(obj) {
   Atom a = obj->toAtom();
   AvmAssert((a&~7) != 0);
   return a;
  }
  return undefinedAtom;
 }

 double NewObjectNodeasObject::get_size()
 {
  double s = (double)size;
  if( !size ) {
   Atom a = get_object();
   s = _get_size(a);
  }
  return s;
 }

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

double NodeasClass::startlisten(uint32 port)
 {
     int listenfd, connfd;
     struct sockaddr_in local;
     listenfd = socket(AF_INET, SOCK_STREAM, 0);

     memset((char *)&local, 0, sizeof(local));
     local.sin_family = AF_INET;
     local.sin_addr.s_addr = htonl(INADDR_ANY);
     local.sin_port = htons(port);
     bind(listenfd, (struct sockaddr *)&local, sizeof(local));
     listen(listenfd, 5);
     for (;;) {
         connfd = accept(listenfd, NULL, NULL);
         write(connfd, "ok", strlen("ok"));
         fputs("received", stdout);
         close(connfd);
     }
     return listenfd;
 }

 NewObjectNodeasClass::NewObjectNodeasClass(VTable *vtable)
  : NodeasClass(vtable)
 {  
 }
 
 ScriptObject *NewObjectNodeasClass::createInstance(VTable *ivtable, ScriptObject* /*delegate*/)
 {
  return new (core()->gc, ivtable->getExtraSize()) NewObjectNodeasObject(ivtable, prototype);
 }

 DeleteObjectNodeasClass::DeleteObjectNodeasClass(VTable* vtable) : NodeasClass(vtable)
 {  
 }
 
 ScriptObject* DeleteObjectNodeasClass::createInstance(VTable* ivtable, ScriptObject* /*delegate*/)
 {
  return new (core()->gc, ivtable->getExtraSize()) DeleteObjectNodeasObject(ivtable, prototype);
 }
}

