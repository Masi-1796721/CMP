#include "Complex.h"
#include <iostream>

using namespace std;

int main(){ //main
  
  Complex c1(3.5, 2.1), c2(-1.1, 2); //numeri complessi
  
  //print data
  c1.print();
  c1.mag();
  c1.r();
  c1.phase();
  c1.phi();
  c2.print();
  c2.mag();
  c2.phase();
  
  //overloaded operations
  Complex c3 = c1 + c2;
  cout<<"sum result: ";
  c3.print();
  
  Complex c4 = c1 - c2;
  cout<<"subtraction result: ";
  c4.print();
  
  Complex c5 = c1/c2;
  cout<<"division result: ";
  c5.print();
  
  Complex c6 = c1*c2;
  cout<<"multiplication result: ";
  c6.print();
  
  Complex c7 = c1*0.5;
  cout<<"multiplication result: ";
  c7.print();
  
  Complex c8 = 0.5*c1;
  cout<<"multiplication result: ";
  c8.print();
  
  return 0;
  
}
