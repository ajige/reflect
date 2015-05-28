#ifndef _IMEMBER_H
#define _IMEMBER_H

#include "typedefs.h"
#include "traits.h"
#include "base/exception.h"

class IMember
{
 public:
   uchar _type;   
   int32_t _offset;
   int32_t _size;
   string _name;
   
   IMember(uchar type, string name, int32_t offset):
   	_type(type), _offset(offset), _name(name)
   {
      _size = sizeVec[type];
   }

   template<typename T>
   T get_value(void* object);

   template<typename T>
   void set_value(void* object, T src);

   void dumpValue(void* object, ostream& os);

   void dumpInfo(ostream& os);

   // this should be modified when add new type, 
   // change later..
   const static uchar sizeVec[];
   const static int32_t alignmentVec[];
};

template<typename T>
T IMember::get_value(void* object)
{
   //check type
   if ( ! TypeChecker<T>::check(_type))
	  throw ReflectException("type unmatch");
   
   return *((T*)((uint8_t*)object + _offset));		 
}

template<typename T>
void IMember::set_value(void* object, T src)
{
  //check type
  if ( ! TypeChecker<T>::check(_type))
	  throw ReflectException("type unmatch");
  
   *((T*)((uint8_t*)object + _offset)) = src;
}

/*
template<>
string IMember::get_value<string>(void* object)
{
  if(!TypeChecker<string>::check(_type))
	 throw ReflectException("type unmatch");

  return (char*)*((uint8_t*)object + _offset);
}

template<>
void IMember::set_value<string>(void* object, string& src)
{
	if(!TypeChecker<string>::check(_type))
		  throw ReflectException("type unmatch");

	char* start = (char*)malloc(src.size() + 1);
	memcpy(start, src.c_str(), src.size());
	start[src.size() - 1] = '\0';
	
	*(char**)((uint8_t*)object + _offset) = start; 
}
*/

#endif
