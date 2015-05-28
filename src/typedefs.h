#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

typedef  unsigned char uchar;

#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;
using std::cout;
using std::endl;
using std::cin;

enum {
  INT8 = 0,
  INT32, 
  STRING,	// how to handle this three type 
  POINTER,
  OBJECT,
};

#define MAXINT  INT32

#endif

