// Complex.h

using namespace std;

class Complex {

 public:

  //constructors
  Complex(); //default 
  Complex(double re, double im); //regular
  Complex(const Complex& complex); //copy
 ~Complex(); //destructor
 
 //getters
 double re() const { return re_; }
 double im() const { return im_; }
 
 //setters
 void SetRe( double re ){ re_=re; }
 void SetIm( double im ){ im_=im; }
 
 //member functions
 double mag(); //complex number magnitude
 double phase(); //complex number phase
 void print() const;
 
 //overloading operations betw complex numbers

 private:
  double re_;
  double im_;
 
};
