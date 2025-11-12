CallByValue -
 In Call by Value, a copy of the actual argument is passed to the function.
 Any changes made inside the function do not affect the original variable.
 The original value remains unchanged.
Example of Call by Value:
#include <iostream>
using namespace std;

void modifyValue(int x) {  // x is a copy of the actual argument
    x = x + 10;  // Modifies the local copy, not the original
}
int main() {
    int num = 5;
    modifyValue(num);  // Passes a copy of num
    cout << "Value of num after function call: " << num << endl; // Still 5
    return 0;
}
Output: 5
Value of num after function call: 5

2. Call by Reference
In Call by Reference, a reference of the actual argument is passed to the function.
Any changes made inside the function also affect the original variable.
Avoids unnecessary copying, making it more efficient.
Example of Call by Reference:
#include <iostream>
using namespace std;

void modifyValue(int &x) {  // x is a reference to the actual argument
    x = x + 10;  // Modifies the original variable
}

int main() {
    int num = 5;
    modifyValue(num);  // Passes a reference to num
    cout << "Value of num after function call: " << num << endl; // Now 15
    return 0;
}
Output: 15
Value of num after function call: 15

#Which One to Use?
Use Call by Value:      if you don’t want the function to modify the original value.
Use Call by Reference:  if you want the function to modify the original value or 
                        to avoid unnecessary copying (especially for large objects).

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <bits/stdc++.h>
using namespace std;
 void increment(int *x){//Function1: Call by reference using pointer
    *x =*x+1;
 }
 void increment(int &x){//Function2: Call by reference using reference variable
    x=x+1;
 }
 void swapp(int &x,int &y){ // Call by reference using reference variable
    swap(x,y);
 }
 
 void swapp(int *x,int *y){   // Call by reference using pointer
   swap(*x,*y);
 }

int main()
{
    int a=10;
	int b=20;
	increment(&a); 	// Output:11  //Function1
	increment(a); // Output:11   //Function2

	swapp(&a,&b);// 
    swapp(a,b);
	cout<<a<<endl;
	cout<<b<<endl;
	
	return 0;
}
