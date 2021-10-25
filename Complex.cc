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

//methods definition
double Complex::mag(){
 double r = sqrt( re_*re_ + im_*im_ );
 cout<<"magnitude:"<<r<<endl;
 return r;
}

void Complex::r(){
 this->mag();
}

double Complex::phase(){
 double phi = atan( im_/re_ );
 cout<<"phase:"<<phi<<endl;
 return phi;
}

void Complex::phi(){
 this->phase();
}

void Complex::print() const{
 cout<<""<<re_
  <<" + i"<<im_<<endl;
}

//overloaded operations betw complex numbers definition

Complex Complex::operator+(const Complex& rhs) const {
  
  //sum of real parts
  double re = re_ + rhs.re_;
  //sum of imaginary parts
  double im = im_ + rhs.im_;
  
  //result
  return Complex(re, im);

}

Complex Complex::operator-(const Complex& rhs) const {
  
  //subtraction of real parts
  double re = re_ - rhs.re_;
  //subtraction of imaginary parts
  double im = im_ - rhs.im_;
  
  //result
  return Complex(re, im);

}

Complex Complex::operator/(const Complex& rhs) const {
  
  //division rule implementation
  double re = (re_*rhs.re_ + im_*rhs.im_)/(rhs.re_*rhs.re_ + rhs.im_*rhs.im_);
  double im = (im_*rhs.re_ - re_*rhs.im_)/(rhs.re_*rhs.re_ + rhs.im_*rhs.im_);
  
  //result
  return Complex(re, im);
  
}
  
Complex Complex::operator*(const Complex& rhs) const {
  
  //product rule implementation
  double re = re_*rhs.re_ - im_*rhs.im_;
  double im = re_*rhs.im_ + im_*rhs.re_;
  
  //result
  return Complex(re, im);
  
}
  
Complex Complex::operator*(const double& rhs) const {

  return Complex(re_*rhs, im_*rhs);
  
}

//global funcion(friend method) for double*complex
Complex operator*(const double& lhs, const Complex& rhs){
  
  return Complex(lhs*rhs.re_, lhs*rhs.im_);

}

