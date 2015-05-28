#include "iclass.h"
#include "iobject.h"
#include "imember.h"

IClass::IClass(const string name)
{
   _name = name; 
   _base = NULL;
   _offset = sizeof(void*);// offset of _iclass in object
}

int32_t IClass::calcOffset(uchar type)
{
   int32_t alignment = IMember::alignmentVec[type];
   
   if(_offset % alignment != 0)
     _offset =  (_offset + alignment) & (~(alignment - 1)); 

   return _offset; 
}

void IClass::add_member(uchar type, const string name)
{
   int32_t offset = calcOffset(type);
   IMember imem(type, name, offset);
   _members.push_back(imem);
   _offset = _offset + IMember::sizeVec[type];
}

IMember IClass::get_member(const string name)
{
   for(size_t i = 0; i != _members.size(); i++)
   {
     if(_members[i]._name == name)
         return _members[i];
   }
   throw ReflectException( "unknown element" << name);
}

IObject* IClass::newInstance()     // delete is necessary after use this
{
   IObject* ptr = (IObject*)malloc(size());
   ptr->_iclass = this;
   return ptr;
}

void IClass::dumpInfo(ostream& os)
{
  os << "IClass dumpInfo: className:" << _name << endl;
  for(size_t i = 0; i != _members.size(); i++)
  {
      _members[i].dumpInfo(os);
  }
}

