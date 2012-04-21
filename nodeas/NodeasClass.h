/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __avmplus_NodeasScript__
#define __avmplus_NodeasScript__

namespace avmplus
{
 struct Nodeas;
 
 class NodeasScript
 {
 private:
  static bool trusted(ScriptObject* self) { return self->toplevel()->sampler_trusted(self); }
  explicit NodeasScript(); // unimplemented, not constructable
  
 public:
  enum { GET = 1, SET = 2 };

  static double getSize(ScriptObject* self, Atom o);
  static Atom getMemberNames(ScriptObject* self, Atom o, bool instanceNames);
  static Atom getNodeass(ScriptObject* self);
  static void clearNodeass(ScriptObject* self);
  static void startSampling(ScriptObject* self);
  static void stopSampling(ScriptObject* self);
  static void pauseSampling(ScriptObject* self);
  static void sampleInternalAllocs(ScriptObject* self, bool b);
  static double getNodeasCount(ScriptObject* self);
  static void _setNodeasCallback(ScriptObject* self, ScriptObject* callback);
  static double _getInvocationCount(ScriptObject* self, Atom a, QNameObject* qname, uint32 type);
  static bool isGetterSetter(ScriptObject* self, Atom a, QNameObject* name);

#ifdef DEBUGGER
 private:  
  static ClassClosure* getType(Toplevel* toplevel, NodeasObjectType sot, const void *obj);
  
  friend class NodeasIterator;
  static ScriptObject* makeNodeas(ScriptObject* self, const Nodeas& sample);
  static bool set_stack(ScriptObject* self, const Nodeas& sample, NodeasObject* sam);
  static NodeasObject* new_sam(ScriptObject* self, const Nodeas& sample, int clsid);
#endif
 };

 class NodeasClass : public ClassClosure
 {
 public:
  NodeasClass(VTable *vtable);
  ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);

  Stringp getVersion();
  double  startlisten(uint32 port);

  DECLARE_SLOTS_NodeasClass;
 };

 class NodeasObject : public ScriptObject
 {
  friend class NodeasScript;
 public:
  NodeasObject(VTable *vtable, ScriptObject *delegate);

  DECLARE_SLOTS_NodeasObject;
 };

 class NewObjectNodeasObject : public NodeasObject
 {
  friend class NodeasScript;
 public:
  NewObjectNodeasObject(VTable *vtable, ScriptObject *delegate);
  Atom get_object();
  double get_size();
  void setRef(AvmPlusScriptableObject* o) { obj = o; }
  void setSize(uint64 s) { size = s; }
 private:
  DRCWB(AvmPlusScriptableObject*) obj;
  uint64 size;
        
  DECLARE_SLOTS_NewObjectNodeasObject;
 };

 class NewObjectNodeasClass : public NodeasClass
 {
 public:
  NewObjectNodeasClass(VTable *vtable);
  ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);
  
  DECLARE_SLOTS_NewObjectNodeasClass;
 };

 class DeleteObjectNodeasObject : public NodeasObject
 {
  friend class NodeasScript;
 public:
  DeleteObjectNodeasObject(VTable *vtable, ScriptObject *delegate);

  DECLARE_SLOTS_DeleteObjectNodeasObject;
 };

 class DeleteObjectNodeasClass : public NodeasClass
 {
 public:
  DeleteObjectNodeasClass(VTable *vtable);
  ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);
  
  DECLARE_SLOTS_DeleteObjectNodeasClass;
 };
}
#endif // __avmplus_NodeasScript__
