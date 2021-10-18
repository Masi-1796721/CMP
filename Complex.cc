// Complex.cc

#include "Complex.h"
#include <iostream>
#include <cmath>

using namespace std;

//constructors definition
Complex::Complex(){ //default
 re_=0;
 im_=0;
};

Complex::Complex(double re, double im){ //regular
 re_=re;
 im_=im;
};

Complex::Complex(const Complex& complex){ //copy
 re_=complex.re_;
 im_=complex.im_;
};

//destructor definition
Complex::~Complex(){
cout << "Complex::~Complex() called for Complex"
<< complex_ << endl;
};

//methods definition
double Complex::mag(){
 double r = sqrt( re_*re_ + im_*im_ );
 cout<<"magnitude:"<<r<<endl;
 return re;
}

double Complex::phase(){
 double phi = atan( im_/re_ );
 cout<<"phase:"<<phi<<endl;
 return phi;
}

void Complex::print() const{
 cout<<"re:"<<re_
  <<"\tim:"<<im_<<endl;
}
