#include <Complex.h>
#include <iostream>
#include <>

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

Complex::~Complex(){
 
}

double Complex::mag(double re, double im){
 mag = sqrt( re*re + im*im );
 return mag;
}

double Complex::phase(){
 phase = atan( im/re );
 return phase;
}
