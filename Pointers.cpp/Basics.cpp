The size of pointers in C is - 
This size of pointers in C only depends on the system architecture.
    8 bytes for a 64-bit System.
    4 bytes for a 32-bit System.
	On a 32-bit system, memory addresses are 4 bytes (32 bits), so all pointers are 4 bytes.
	On a 64-bit system, memory addresses are 8 bytes (64 bits), so all pointers are 8 bytes.
	
	The reason for the same size is that the pointers store the memory addresses, no matter what type they are. 
	As the space required to store the addresses of the different memory locations is the same, 
	the memory required by one pointer type will be equal to the memory required by other pointer types.

#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a=10;
	 int *p; p=&a;  // or  int *p=&a; Pointer to integer
	 cout<<" Address of a  "<<&a<<endl;
	 cout<<" Address of a  "<<p<<endl;// p holds address of a
	 cout<<" Address of p  "<<&p<<endl;

	 cout<<" value of a  "<<a<<endl;
	 cout<<" value of a  "<<*p<<endl;// *p gives value of a
	 cout<<endl;
	//////////////////////////////////////////////////////////////////////////
	 int b=20;
	 *p=b;
	 cout<<" value of a  "<<a<<endl;
	 cout<<" value of b  "<<b<<endl;
	 cout<<" value of *P  "<<*p<<endl;// value of *p changes and also a value changes

	 cout<<" Address of a  "<<&a<<endl; // address will not change
	 cout<<" Address of a  "<<p<<endl; // address will not change
	 cout<<" Address of p  "<<&p<<endl; // address will not change
	 cout<<" Address of b  "<<&b<<endl;
	 cout<<endl;
	 /////////////////////////////////////////////////////////////////////
	 int c=30;
	 *p=c;
	 cout<<" value of a  "<<a<<endl;
	 cout<<" value of b  "<<b<<endl;
	 cout<<" value of c  "<<c<<endl;

	////////////////////////// Pointer Arithmetic- Adding, Substracting only ////////////////////////////////
	int a=10;
	 int *p=&a;
	 cout<<"Adress of p  "<<p<<endl;
	 cout<<" value of p  "<<*p<<endl;

	 cout<<" Address of p+1 "<<p+1<<endl;// address will increased by (4*1)bytes(size of int)
	 cout<<" value of p+1  "<<*(p+1)<<endl;// gives some garbage value because no value is assigned at this address
	//////////////////////////////////////////////////////////////////////////////////////
    // Pointer to Character
	 int a=15;
	 int *p=&a;
	 cout<<"value of p  "<<*p<<endl;
	 cout<<"Adress of p  "<<p<<endl;

	 char *pp;
	 pp=(char*)p; // typecasting required(because PP is pointer to character and P is pointer to integer)
	 cout<<"value of pp  "<<(int)*pp<<endl; // output: 15 , 15 =00001111
	 cout<<"Adress of pp  "<<(void*)pp<<endl;//  by (void*) memory address will be printed otherwise nothing will be printed
	1025=00000000  00000000  00000100  00000001 Output:1
	15= 00000000  00000000  00000000  00001111 Output:15
	char can store upto 1 byte of memory i.e answer will be 00000001=1
	/////////////////////////////////////////////////////////////////////////////////////////
	Void pointer(Genric Pointer)-
    A void pointer is a general-purpose pointer that can hold the address of any data type, 
    but it is not associated with any data type.
	int a=15;
	int *p=&a;
	cout<<"value of p  "<<*p<<endl;
	cout<<"Adress of p  "<<p<<endl;

	void *pp; // void *pp=p;
	pp=p;
	cout<<"Adress of pp  "<<pp<<endl;// this will give address
	//cout<<"value of pp  "<<pp<<endl;//This will not compile because dereferencing a void is not allowed in C++.
	// To print the value stored at pp, we must typecast it to the correct pointer type before dereferencing:
	cout << "Value at pp: " << (int)pp << endl;  // typecast before dereferencing
	
	////////////////////////////////////////////////////////////////////////////////////////

	//Pointer to Pointer(Double Pointer) - 
    A pointer to pointer (also known as a double pointer) is a pointer that stores the address of another pointer. 
    It allows indirect access to a variable by first accessing the pointer that points to it.
	int a=10;
	int *p=&a;
	int **q=&p;
	int ***r=&q;
	cout<<"p  Adress of  a "<<p<<endl;
	cout<<"*p value of   a  "<<*p<<endl;// *p holds value of a

	cout<<"*q  address of a  "<<*q<<endl;// *q holds address of a
	cout<<"&p  Address of p  "<<&p<<endl;// &p holds Address of p
	cout<<"&*q  address of p  "<<&*q<<endl;// &*q holds address of p
	cout<<"**q value of   a   "<<**q<<endl;// **q holds value of a
	
	cout<<"*r  Adress of  p  "<<*r<<endl;// *r Adress of p
	cout<<"&q   Address of q  "<<&q<<endl;// &q holds Address of q
	cout<<"&*r  Adress of  q  "<<&*r<<endl;// &*r Adress of q
	cout<<"**r address of  a  "<<**r<<endl;// **r address of  a 
	cout<<"&**r address of  p  "<<&**r<<endl;// &**r address of  p
	cout<<"***r value of  a  "<<***r<<endl;// ***r value of  a 
	cout<<"Address of r  "<<&r<<endl;
    return 0;
}