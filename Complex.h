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
 double mag( double re, double im ){} //complex number magnitude
 double phase( double re, double im ){} //complex number phase

 private:
  double re_;
  double im_;
};
