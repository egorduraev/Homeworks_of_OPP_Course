#include <iostream>
#include <cmath>

using namespace std;

//Task 1

class Figure {
public:
    virtual float area() = 0;
};

class Parallelogram : public Figure {
private:
    float m_a;
    float m_b;
    float m_height;
protected:
    float getA() const {
        return m_a;
    }
    float getB() const {
        return m_b;
    }
public:
    Parallelogram(float a, float height, float b = 0.0)
        : m_a(a), m_b(b), m_height(height) {}
    float area() {
        float area = m_a * m_height;
        cout << "The area of the parallelogram is " << area << endl;
        return area;
    }
};

class Circle : public Figure {
private:
    float m_r;
public:
    Circle(float r)
    : m_r(r) {}
    float area() {
        float area = 3.14 * pow(m_r, 2);
        cout << "The area of the circle is " << area << endl;
        return area;
    }
};

class Rectangle : public Parallelogram {
public:
    Rectangle(float a, float b)
    : Parallelogram(a, b, b) {}
    float area() {
        float area = getA() * getB();
        cout << "The area of the rectangle is " << area << endl;
        return area;
    }
};

class Square : public Parallelogram {
public:
    Square(float a, float b)
    : Parallelogram(a, b, b) {}
    float area() {
        float area = getA() * getB();
        cout << "The area of the square is " << area << endl;
        return area;
    }
};

class Rhombus : public Parallelogram
{
public:
    Rhombus(float a, float b)
    : Parallelogram(a, b, b) {}
    float area() {
        float area = getA() * getB();
        cout << "The area of the rhombus is " << area << endl;
        return area;
    }
};

//Task 2

class Car {
private:
    string m_company;
    string m_model;
protected:
    string getCompany() const {
        return m_company;
    }
    string getModel() const {
        return m_model;
    }
public:
    Car(string company, string model)
    : m_company(company), m_model(model) {
        cout << "Company: " << getCompany() << ", model: " << getModel() << endl;
    }
};

class PassengerCar : virtual public Car {
public:
    PassengerCar(string company, string model)
    : Car(company, model) {
        cout << "Company: " << getCompany() << ", model: " << getModel() << endl;
    }
};

class Bus : virtual public Car {
public:
    Bus(string company, string model)
    : Car(company, model) {
        cout << "Bus: " << getCompany() << ", model: " << getModel() << endl;
    }
};

class Minivan : public PassengerCar, public Bus {
public:
    Minivan(string company, string model)
    : PassengerCar(company, model), Bus(company, model), Car(company, model) {
        cout << "Minivan: " << getCompany() << ", model: " << getModel() << endl;
    }
};

//Task 3

class Fraction {
private:
    bool zero;
    bool is_integer;
    int num;
    int denom;
    int NOD(int n1, int n2) {
        int div;
        if (n1 == n2)  return n1;
        int d = n1 - n2;
        if (d < 0) {
            d = -d;
            div = NOD(n1, d);
        }
        else
            div = NOD(n2, d);
        return div;
    }
    int NOK(int n1, int n2) {
        return n1 * n2 / NOD(n1, n2);
    }
    void reduceFraction(int& a, int& b) {
        int divisor = NOD(abs(a), abs(b));
        a = a / divisor;
        b = b / divisor;
    }
public:
    Fraction () : num(0), denom(0) {
        zero = true;
        is_integer = true;
    }
    Fraction(int num, int dnum) : num(num), denom(dnum) {
        if (num == 0 || denom == 0)
        {
            cout << "The numerator or denominator cannot be zero\n"
            << "The number will be initialized to zero" << endl;
            num = 0;
            denom = 0;
            zero = true;
            is_integer = true;
        }
        else {
            zero = false;
            is_integer = (abs(num) == abs(denom) || denom == 1);
        }
    }
    friend std::ostream& operator<<(std::ostream&, const Fraction&);
    Fraction operator+(const Fraction&);
    Fraction operator-(const Fraction&);
    Fraction operator*(const Fraction&);
    Fraction operator/(const Fraction&);
    Fraction operator-() const;
    bool operator==(const Fraction&);
    bool operator!=(const Fraction&);
    bool operator<(const Fraction&);
    bool operator>=(const Fraction&);
    bool operator>(const Fraction&);
    bool operator<=(const Fraction&);
};

ostream& operator<<(ostream& s, const Fraction& f) {
    if (f.is_integer) {
        if (f.zero)
            s << f.num;
        else
            s << f.num / f.denom;
    }
    else
        s << f.num << '/' << f.denom;
    return s;
}

Fraction Fraction::operator+(const Fraction& f) {
    if (f.zero)
        return Fraction(num, denom);
    if (zero)
        return Fraction(f.num, f.denom);
    int new_denom = NOK(denom, f.denom);
    int new_num = num * (new_denom / denom) + f.num * (new_denom / f.denom);
    reduceFraction(new_num, new_denom);
    return Fraction(new_num, new_denom);
}

Fraction Fraction::operator-(const Fraction& f) {
    if (f.zero)
        return Fraction(num, denom);
    if (zero)
        return Fraction(-f.num, f.denom);
    int new_denom = NOK(denom, f.denom);
    int new_num = num * (new_denom / denom) - f.num * (new_denom / f.denom);
    if (new_num == 0)
        return Fraction();
    reduceFraction(new_num, new_denom);
    return Fraction(new_num, new_denom);
}

Fraction Fraction::operator*(const Fraction& f) {
    if (zero || f.zero)
        return Fraction();
    int new_num = num * f.num;
    int new_denom = denom * f.denom;
    reduceFraction(new_num, new_denom);
    return Fraction(new_num, new_denom);
}

Fraction Fraction::operator/(const Fraction& f) {
    if (f.zero) {
        std::cout << " Error! ";
        return Fraction();
    }
    if (zero)
        return Fraction();
    return *this * Fraction(f.denom, f.num);
}

Fraction Fraction::operator-() const {
    return Fraction(-num, denom);
}

bool Fraction::operator==(const Fraction& f) {
    if (zero || f.zero)
        return num == f.num;
    int a_n = num;
    int a_d = denom;
    int b_n = f.num;
    int b_d = f.denom;
    reduceFraction(a_n, a_d);
    reduceFraction(b_n, b_d);
    return a_n == b_n && a_d == b_d;
}

bool Fraction::operator!=(const Fraction& f) {
    return !(*this == f);
}
bool Fraction::operator<(const Fraction& f) {
    if (zero || f.zero)
        return num < f.num;
    int new_denom = NOK(denom, f.denom);
    int a_n = num * (new_denom / denom);
    int b_n = f.num * (new_denom / f.denom);
    return a_n < b_n;
}

bool Fraction::operator>=(const Fraction& f) {
    return (*this == f || !(*this < f));
}

bool Fraction::operator>(const Fraction& f) {
    return (*this != f && !(*this < f));
}

bool Fraction::operator<=(const Fraction& f) {
    return (*this == f || *this < f);
}

//Task 4

class Card {
public:
    enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};
    Card(rank r = ACE, suit s = SPADES, bool Revealed = true):  m_Rank(r), m_Suit(s), m_revealedcard(Revealed) {}
    int GetValue() const;
    void Flip();
private:
    rank m_Rank;
    suit m_Suit;
    bool m_revealedcard;
};

int Card::GetValue() const {
    int value = 0;
    if (m_revealedcard) {
        value = m_Rank;
        if (value > 10) {
            value = 10;
        }
    }
    return value;
}

void Card::Flip() {
    m_revealedcard = !m_revealedcard;
}

int main() {
    //Task 1
    Parallelogram parallelogram(12.4, 7.7);
    Circle circle(13.4);
    Rectangle rectangle(14.0, 8.2);
    Square square(17.5, 17.5);
    Rhombus rhombus(17.4, 13.2);
    parallelogram.area();
    circle.area();
    rectangle.area();
    square.area();
    rhombus.area();

    //Task 2
    Minivan m("Yandex", "Polonez");

    //Task 3
    Fraction a(4, 10);
    Fraction b(3, 5);
    Fraction c; // 0
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "[a + b] " << a << " + " << b << " = " << a + b << endl;
    cout << "[a - b] " << a << " - " << b << " = " << a - b << endl;
    cout << "[a * b] " << a << " * " << b << " = " << a * b << endl;
    cout << "[a / b] " << a << " / " << b << " = " << a / b << endl;
    cout << "[c + b] " << c << " + " << b << " = " << c + b << endl;
    cout << "[b + c] " << b << " + " << c << " = " << b + c << endl;
    cout << "[c - b] " << c << " - " << b << " = " << c - b << endl;
    cout << "[b - c] " << b << " - " << c << " = " << b - c << endl;
    cout << "[c * b] " << c << " * " << b << " = " << c * b << endl;
    cout << "[b * c] " << b << " * " << c << " = " << b * c << endl;
    cout << "[c / b] " << c << " / " << b << " = " << c / b << endl;
    cout << "[b / c] " << b << " / " << c << " = " << b / c << endl;
    cout << "-a = " << -a << endl;
    cout << "[a == b] " << a << " == " << b << " is " << ((a == b) ? "true" : "false") << endl;
    cout << "[a != b] " << a << " != " << b << " is " << ((a != b) ? "true" : "false") << endl;
    cout << "[a < b]  " << a << " < " << b << " is " << ((a < b) ? "true" : "false") << endl;
    cout << "[a <= b] " << a << " <= " << b << " is " << ((a <= b) ? "true" : "false") << endl;
    cout << "[a > b]  " << a << " > " << b << " is " << ((a > b) ? "true" : "false") << endl;
    cout << "[a >= b] " << a << " >= " << b << " is " << ((a >= b) ? "true" : "false") << endl;
    cout << "[c == a] " << c << " == " << a << " is " << ((c == a) ? "true" : "false") << endl;
    cout << "[c != a] " << c << " != " << a << " is " << ((c != a) ? "true" : "false") << endl;
    cout << "[c < a]  " << c << " < " << a << " is " << ((c < a) ? "true" : "false") << endl;
    cout << "[c <= a] " << c << " <= " << a << " is " << ((c <= a) ? "true" : "false") << endl;
    cout << "[c > a]  " << c << " > " << a << " is " << ((c > a) ? "true" : "false") << endl;
    cout << "[c >= a] " << c << " >= " << a << " is " << ((c >= a) ? "true" : "false") << endl;

    //Task4
    Card card;
    card.GetValue();
    return 0;
}
