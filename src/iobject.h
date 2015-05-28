#ifndef _IOBJECT_H
#define _IOBJECT_H

#include <stdlib.h>
#include <iostream>

#include "base/exception.h"
#include "typedefs.h"
#include "imember.h"
#include "iclass.h"

using std::ostream;

//add copy constructor

class IObject
{
 public:
  IClass* _iclass;

  ~IObject();
  
  template<typename T>
  T get_member(string name)
  {
     vector<IMember>& members = _iclass->_members;
     for(size_t i = 0; i != members.size(); i++)
     {
       if(members[i]._name == name)
       {
         return members[i].get_value<T>((void*)this);  
	   }
	 }
	 
	 throw ReflectException("unknown member");
  }
  
  template<typename T>
  void set_member(const string name, T src)
  {
	  vector<IMember>& members = _iclass->_members;
	  for(size_t i = 0; i != members.size(); i++)
	  {
		if(members[i]._name == name)
		{
		   members[i].set_value<T>((void*)this, src);
		   return;
		}
	  }
	  
	  throw ReflectException("unknown member");     
  }

  void dumpValue(ostream& os);
  
  int32_t size()
  {
  	  return _iclass->size();
  }

  friend ostream& operator<<(ostream& os, IObject* obj);
};

#endif
