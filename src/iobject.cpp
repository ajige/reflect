#include "iobject.h"
#include "iclass.h"

IObject::~IObject()
{
   vector<IMember>& members = _iclass->_members;
   for(size_t i = 0; i != members.size(); i++)
   {
     if(members[i]._type == STRING)
     {
        char* dest = *(char**)((uint8_t*)this + members[i]._offset);
        free(dest);
     }
     else if (members[i]._type == OBJECT)
     {
        IObject* dest = *(IObject**)((uint8_t*)this + members[i]._offset);
        free(dest);
     }
     else
        continue;
   }
}

void IObject::dumpValue(ostream& os)
{
  os << "IObject dumpValue: object of class " << _iclass->_name<<endl;
  vector<IMember>& members = _iclass->_members;
  for(size_t i = 0; i != members.size(); i++)
  {
     members[i].dumpValue((void*)this, os);
  }
}

ostream& operator<<(ostream& os, IObject* obj)
{
   obj->dumpValue(os);
   return os;
}

