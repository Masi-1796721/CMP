class Complex {

 public:

  //constructors
  Complex();
  Complex(double x, double y);
  Complex(const Complex& complex);
 
 //setters
 void SetRe(double re){};
 void SetIm(double im){};

 private:
  double re_;
  double im_;
};
