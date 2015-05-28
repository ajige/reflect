/*       
 *       Filename:  main.cpp
 *       Created:  2015年04月22日 19时59分47秒
 *       Author:  wushangqing@sogou-inc.com
 */

#include <iclass.h>
#include <imember.h>
#include <iobject.h>
#include <iostream>
using namespace std;

int main()
{
  try
  {
     IClass tclass("tclass");
     tclass.add_member(INT32, "tfirst");
     IObject* tobj = tclass.newInstance();
     tobj->set_member("tfirst", 30);
        
     IClass myclass("hello");
     myclass.add_member(INT8, "first");
     myclass.add_member(INT32, "second");
     myclass.add_member(STRING, "strmem");
     myclass.add_member(POINTER, "ptr");  // change this to object ptr instead
     myclass.add_member(OBJECT, "obj");
     
     myclass.dumpInfo(cout);
     
     IObject* myobj = myclass.newInstance();
     int8_t a = 0x0a;
     int32_t aa = 0xfffefdfb;
     string str = "helloworld";
     int* aptr = new int(0x0b0c);
     
     myobj->set_member("first", a);
     myobj->set_member("second", aa);
     myobj->set_member("strmem", str);
     myobj->set_member("ptr",aptr);
     myobj->set_member("obj", tobj); // ptr will malloc an object

     IObject* robj = myobj->get_member<IObject*>("obj");
     cout << robj << endl;
     robj->dumpValue(cout);

//     string mmm = myobj->get_member<string>("strmem");
//     cout << mmm << endl;
//     int *bptr = myobj->get_member<int*>("ptr");
//     cout << hex << *bptr << bptr << endl;
     
     myobj->dumpValue(cout);

     delete aptr;
     delete myobj;
  }

  catch(ReflectionException& ep)
  {
     cout << ep.what() << endl;
  }
}

