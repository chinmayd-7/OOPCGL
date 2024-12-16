#include <iostream>
using namespace std;
class Complex {
private:
    double real;  // Real part
    double imag;  // Imaginary part

public:
    // Default constructor
    Complex() {
        real = 0;
        imag = 0;
    }

    // Parameterized constructor 
    Complex(double r, double i) {
        real = r;
        imag = i;
    }

    // Overloaded + operator to add two complex numbers
    Complex operator+( Complex other) {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overloaded * operator to multiply two complex numbers
    Complex operator*( Complex other)  {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }

    // Overloaded << operator to print complex numbers
    friend ostream& operator<<(ostream& ,  Complex& );

    // Overloaded >> operator to read complex numbers
    friend istream& operator>>(istream& , Complex&);
};
ostream& operator<<(ostream& os,  Complex& c) {
        os << c.real;
        os<<"+"<<c.imag<<"i";
        return os;
    }
    istream& operator>>(istream& is, Complex& c) {
        is >> c.real >> c.imag;
        return is;
    }

int main() {
    Complex c1, c2;

    // std::cout << "Enter two complex numbers (format: real imag):\n";
    cin >> c1 >> c2;
    // std::cout<<c1;
    Complex c3=c1*c2;
    cout <<c3; 

    return 0;
}