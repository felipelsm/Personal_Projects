/*
    Complex_Numbers.cpp
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <string.h>
#include <math.h>

# define PI M_PI
# define E M_E

using namespace std;

double Round(double num, int dig = 0)
{
    num *= pow(10, dig);
    num = round(num) / pow(10, dig);
    if (num == -0)
        num = 0;
    return num;
}

template <typename T = double>
class complex
{
protected:
    /*** Protected Variables ***/
    T _real, _imag;
    int precision = 0;

    /*** Protected Methods ***/
    complex mult(complex &t, complex &c)
    {
        T r = t._real * c._real - t._imag * c._imag;
        T i = t._real * c._imag + t._imag * c._real;

        return complex(r, i);
    }
    complex div(complex& t, complex& c)
    {
        T denominator = c._real * c._real + c._imag * c._imag;

        T r = (t._real * c._real - t._imag * (-c._imag)) / denominator;
        T i = (t._real * (-c._imag) + t._imag * c._real) / denominator;
    }

public:
    /*** Constructor ***/
    complex(T r, T i, int p = 6) { _real = r;   _imag = i; precision = p; }
    
    /*** Public Methods ***/
    complex add(double r, double i)
    {
        return  complex(this->_real + r, this->_imag + i);
    }

    /* Get */
    T real()
    {
        return this->_real;
    }
    T imag()
    {
        return this->_imag;
    }
    complex conj()
    {
        return complex(this->_real, -this->_imag);
    }
    T mod()
    {
        return sqrt(_real * _real + _imag * _imag);
    }
    T arg()
    {
        return (T)atan((T)_imag / (T)_real);
    }
    static T mod(T r, T i)
    {
        return sqrt(r * r + i * i);
    }
    static T arg(T r, T i)
    {
        return (T)atan((T)i / (T)r);
    }
    static complex polar(T r, T i)
    {
        T r = mod(r, i) * cos(arg(r, i));
        T i = mod(r, i) * sin(arg(r, i));

        return complex(r, i);
    }

    /* Display */
    static void display_polar(complex& c)
    {
        T _arg = arg(c._real, c._imag);
        cout << mod(c._real, c._imag)
             << " * ( cos(" << _arg
             << ") + i*sin(" << _arg << ") )";
    }
    static void display_polar_degrees(complex& c)
    {
        T _arg = arg(c._real, c._imag) * 180 / M_PI;
        cout << mod(c._real, c._imag)
            << " * ( cos(" << _arg
            << ") + i*sin(" << _arg << ") )";
    }

    /*** Operators ***/
    /* Sum */
    complex operator + (complex& c) {
        return complex(this->_real + c._real, this->_imag + c._imag);
    }
    complex operator + (T num) {
        return complex(_real + num, _imag);
    }
    void operator += (complex& c)
    { 
        this->_real += c._real;
        this->_imag += c._imag;
    }
    void operator += (T num) {
        this->_real += num;
    }

    /*Subtraction */
    complex operator - (complex& c) {
        return complex(this->_real - c._real, this->_imag - c._imag);
    }
    complex operator - (T num) {
        return complex(_real - num, _imag);
    }
    void operator -= (complex& c)
    {
        this->_real -= c._real;
        this->_imag -= c._imag;
    }
    void operator -= (T num) {
        this->_real -= num;
    }

    /* Multiplication */
    complex operator * (complex& c)
    {
        return mult(*this, c);
    }
    complex operator * (T num) {
        return complex(_real * num, _imag * num);
    }
    void operator *= (complex& c)
    {
        mult(*this, c);
    }
    void operator *= (T num) {
        this->_real *= num;
        this->_imag *= num;
    }

    /* Division */
    complex operator / (T num) {
        return complex(_real / num, _imag / num);
    }
    complex operator / (complex& c)
    {
        return div(*this, c);
    }
    void operator /= (complex& c)
    {
        div(*this, c);
    }
    void operator /= (T num) {
        this->_real /= num;
        this->_imag /= num;
    }

    /* Power */
    /*complex operator ^ (complex& c)
    {

    }
    complex operator ^ (double n)
    {

    }*/
    complex operator ^ (int n)
    {
        T r;
        T i;
        switch (n)
        {
        case 0:
            r = 1, i = 0;
            break;
        case 1:
            break;
        case 2:
            mult(*this, *this);
        default:
            r = pow(mod(this->_real, this->_imag), n) * (cos(n * arg(this->_real, this->_imag)));
            i = pow(mod(this->_real, this->_imag), n) * (sin(n * arg(this->_real, this->_imag)));
        }

        return complex(r, i);
    }
    /*void operator ^= (complex& c)
    {

    }
    complex operator ^= (double n)
    {

    }*/
    void operator ^= (int n)
    {
        T m = mod(this->_real, this->_imag);
        T a = n * arg(this->_real, this->_imag);

        double r = Round(pow(m, n) * (cos(a)), precision);
        double i = Round(pow(m, n) * (sin(a)), precision);

        this->_real = r;
        this->_imag = i;
    }

    /* Output Stream */
    friend ostream& operator<<(ostream& os, complex& c)
    {
        char sign;
        if (c._imag < 0) {
            sign = '-';
        }
        else {
            sign = '+';
        }
        os << "(" << c._real << " " << sign << " " << c._imag << "i )";
        return os;
    }

};


int main()
{
    complex<double> c1(sqrt(3), 1, 5);
    c1 ^= 6;
    cout << c1 << endl;

    return 0;
}