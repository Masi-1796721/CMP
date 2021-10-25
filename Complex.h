// Complex.h

using namespace std;

class Complex {

 public:

  //constructors
  Complex(); //default 
  Complex(double re, double im); //regular
  Complex(const Complex& complex); //copy
  ~Complex() {}; //destructor
 
  //getters
  double re() const { return re_; }
  double im() const { return im_; }
 
  //setters
  void SetRe( double re ){ re_=re; }
  void SetIm( double im ){ im_=im; }
 
  //other member functions
  double mag(); //complex number magnitude
  void r();
  double phase(); //complex number phase
  void phi();
  void print() const;
 
  //overloading operations betw complex numbers
  Complex operator+(const Complex& rhs) const; //sum betw two complexes
  Complex operator-(const Complex& rhs) const; //subtraction betw two complexes
  Complex operator/(const Complex& rhs) const; //division betw two complexes
  
  const Complex& operator=(const Complex& rhs);
  const Complex& operator+=(const Complex& rhs);
  const Complex& operator-=(const Complex& rhs);
  const Complex& operator*=(const Complex& rhs);
  const Complex& operator/=(const Complex& rhs);
  
  Complex operator*(const Complex& rhs) const; //product betw two complexes
  Complex operator*(const double& rhs) const; //complex*double
  friend Complex operator*(const double& lhs, const Complex& rhs); //double*complex
  //friend ostream& operator<<(ostream& os, const Datum& rhs);

 private:
  double re_;
  double im_;
 
};

