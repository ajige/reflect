/* class iclass */
#ifndef _ICLASS_H
#define _ICLASS_H

#include "typedefs.h"
#include <stdlib.h>
#include <map>

class IMember;
class IObject;

class IClass
{
 public:
   IClass* _base;
   string _name;
   vector<IMember> _members;
   int32_t _offset;  // offset used to add members
   
   IClass(const string name);

   void setBaseClass(IClass* base)
   {
      _base = base;
   }

   int32_t size()  // size of this class
   {
     return _offset;
   }
   
   
   void add_member(uchar type, const string name);
   IMember get_member(const string name);
   IObject* newInstance();     // delete is necessary after use this
   void dumpInfo(ostream& os);
   
 private:
   int32_t calcOffset(uchar type);   
   
   // add functors here
};

class IClassTable
{
  public:
  	static std::map<string, IClass*> _classMap;
	static void registerClass(string className, IClass* clazz)
	{
	   _classMap.insert(std::make_pair(className, clazz));
	}
	static IClass* getClass(string className)
	{
       std::map<string, IClass*>::iterator iter = _classMap.find(className);
	   if(iter != _classMap.end())
	   	 return iter->second;
	   else
	   	 return NULL;
	}
};

#endif
