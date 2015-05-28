#include "imember.h"
#include "iobject.h"

const uchar IMember::sizeVec[] = { 1, 4, 8, 8, 8 };
const int32_t IMember::alignmentVec[] = { 1, 4, 8, 8, 8 };

template<>
string IMember::get_value<string>(void* object)
{
  if(!TypeChecker<string>::check(_type))
	 throw ReflectException("type unmatch");

  return *(char**)((uint8_t*)object + _offset);
}

template<>
void IMember::set_value<string>(void* object, string src)
{
	if(!TypeChecker<string>::check(_type))
		  throw ReflectException("type unmatch");

	char* start = (char*)malloc(src.size() + 1);
	memcpy(start, src.c_str(), src.size());
	start[src.size()] = '\0';
	
	*(char**)((uint8_t*)object + _offset) = start; 
}


template<>
void IMember::set_value<IObject*>(void* object, IObject* src)
{
	if(!TypeChecker<IObject>::check(_type))
		  throw ReflectException("type unmatch");

	IObject* start = (IObject*)malloc(src->size());
	memcpy((void*)start, (void*)src, src->size());
	
	*(IObject**)((uint8_t*)object + _offset) = start; 
}

// return a object ptr is more reasonable
template<>
IObject* IMember::get_value<IObject*>(void* object)
{
  if(!TypeChecker<IObject>::check(_type))
	 throw ReflectException("type unmatch");

  return *(IObject**)((uint8_t*)object + _offset);
}

void IMember::dumpValue(void* object, ostream& os)
{
   os<< "name: " << _name << " value: ";
   switch(_type)
   {
     case INT8:
         os << (int)*((int8_t*)((uint8_t*)object + _offset)) << endl;
         break;
     case INT32:
         os << (int)*((int32_t*)((uint8_t*)object + _offset)) << endl;
         break;
     case STRING:
        os << *(char**)((uint8_t*)object + _offset) << endl;
        break;
     case POINTER:
        os << "pointer member, address: 0x" << std::hex 
           << *(int64_t*)((uint8_t*)object + _offset) << std::dec << endl;
        break;
     case OBJECT:
           os << "obj member," << get_value<IObject*>(object)
            << endl;
        break;
     default:
        break;
   }
}

void IMember::dumpInfo(ostream& os)
{
   os << "member name:" << _name  << " type: " << (int)_type << " offset: " << _offset 
    << endl; 
}

