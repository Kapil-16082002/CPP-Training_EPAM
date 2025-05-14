#include <bits/stdc++.h>
using namespace std;
class myclass2
{
  int* ptr2;
public:
  myclass2()
  {
    ptr2 = new int(20);
    cout << "Inside myClass2 cons" << endl;
  }
  ~myclass2()
  {
    if (ptr2 !=  nullptr) delete ptr2;
    cout << "Inside myclass2 des" << endl;
  }
};
// class myException
// {
// };
class myClass1
{
  int x;
  int* ptr;
  myclass2 obj;
public:
  myClass1()
  {
    try
    {
      x = 10;
      cout << "Inside myClass1 cons" << endl;
      ptr = new int(10); // smart pointers
      //some code
      throw runtime_error("some run time error");
      //throw 10;
    }
    //catch (exception ex)
    //{
    //  cout << "Inside generic exception handler" << endl;
    //}
    //catch (myException ex)
    //{
    //  cout << "Custom class exception" << endl;
    //}
    //catch (int x)
    //{
    //  cout << "Inside int handler" << endl;
    //}
    catch (...)
    {
      cout << "Inside def handler" << endl;
      //cout << "Catch inside constructor and exception is: "<<ex.what() << endl; 
      throw;
    }
    //finally
    //{
    //}
    cout << "Outside try catch of myClass1 constructor" << endl;
  }
  ~myClass1()
  {
    cout << "Inside myclass1 des" << endl;
  }
  void mymemFunc()
  {
  }
};
int main()
{
  try
  {
    myClass1 obj;
    obj.mymemFunc();
  }
  catch (exception ex)
  {
    cout << "Inside catch handelr in main and exception is : "<<ex.what() << endl;
  }
  //myClass1 obj[10];
  //cout << obj[1];
  //try
  //{
  //  int x, y;
  //  x = 10;
  //  y = 0;
  //  if (y == 0)
  //    throw std::runtime_error("denom zer");
  //  int result = x / y;
  //}
  //catch (exception ex)
  //{
  //  cout << "Exception is:"<<ex.what() << endl;
  //}
  //cout << "After catch" << endl;
    //throw
  //myClass obj(10);
  //obj.print();
  //myClass obj2;
  //obj2 = ++obj;
  //obj2.print();
  //myClass* ptr = new myClass;
  //myClass obj3;
  //myClass* objPtr = new myClass;
  //objPtr = ptr++; //numb1 = numb2
  //objPtr = ++ptr;
  //obj3 = obj++; //obj3.operator++(int)
  //obj3.print();
  //obj.print();
  //obj3 = obj + obj2;
  ////obj + obj2;
  ////obj3 = obj1 + obj2; //obj3.operator=(obj1.operator+(obj2))
  //delete ptr;
  //vector<int> myVector{ 1,2,4 };
  //for (auto iter = myVector.begin(); iter != myVector.end(); ++iter)
  //{
  //  cout << "*ire" << endl << endl;
  //}
  //myClass obj2(++obj);
  //myClass obj2(obj++);
  //obj2.print();
  //obj++;
  //int x, y;
  //x = 10;
  //y = ++x;
  //y = x++;
  return 0;
}