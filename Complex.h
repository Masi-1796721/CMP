class Complex {

 public:

  //constructors
  Complex(); //default
  Complex(double x, double y); //regular
  Complex(const Complex& complex); //copy
 
 //getters
 double re() const { return re_; }
 double im() const { return im_; }
 
 //setters
 void SetRe( double re ){ re_=re; }
 void SetIm( double im ){ im_=im; }
 
 //member functions
 mag()
 phase()

 private:
  double re_;
  double im_;
};
