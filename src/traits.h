#ifndef _TRAITS_H
#define _TRAITS_H

class IObject;

template <typename T>
class TypeChecker
{
public:
	static bool check(uchar type)
	{
	  return true;
	}
};

template <>
class TypeChecker<int8_t>
{
public:
   static bool check(uchar type)
   {
     if(type == INT8)
     {
       return true;
     }
     return false;
   }
};

template<>
class TypeChecker<string>
{
 public:
	static bool check(uchar type)
    {
      if(type == STRING)
	  	return true;
	  else
	  	return false;
	}
};

// how to check pointer type

template<>
class TypeChecker<IObject>
{
 public:
	static bool check(uchar type)
    {
      if(type == OBJECT)
	  	return true;
	  else
	  	return false;
	}
};


//.. add other check_type here

template<typename T>
class PointerTraits {
  static const bool isPointer = false;
};

template<typename T>
class PointerTraits<T*> {
  static const bool isPointer = true;
};

#endif

