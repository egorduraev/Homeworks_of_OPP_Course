#include <iostream>
#include <cmath>
#include <cstdint>

class Power {
private:
    int a;
    int b;
public:
    Power() { a = 5; b = 2;}
    void set(int sa, int sb) { a = sa; b = sb; }
    void calculate() { std::cout<< pow(a, b) << std::endl; }
};

class RGBA {
private:
    std::uint8_t m_red;
    std::uint8_t m_green;
    std::uint8_t m_blue;
    std::uint8_t m_alpha;
public:
    RGBA(int red = 0, int green = 0, int blue = 0, int alpha = 255)
    : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha)
    {}
    void print() { std::cout << "red = "<< (int)m_red << ", green = " << (int)m_green << ", blue = " << (int)m_blue << ", alpha = " << (int)m_alpha<< "." << std::endl;}
};

class Stack {
private:
    int arr[10];
    int len;
public:
    void reset() {
        len = 0;
        for (int i = 0; i < 10; i++) {
            arr[i] = 0;
        }
    }
    bool push(int a) {
        if (len == 10) return false;
        else {
            arr[len++] = a;
            return true;
        }
    }
    int pop() {
        int s;
        if (len == 0) {
            std::cout << "Warning! Stack is empty" << std::endl;
            return 0;
        }
        else {
            s = arr[len - 1];
            arr[len - 1] = 0;
            --len;
            return s;
        }
    }
    void print() {
        std::cout << "( ";
        for (int i = 0; i < len; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << ")" << std::endl;
    }
};

int main()
{
    Power power;
    power.calculate();
    power.set(3, 3);
    power.calculate();
    RGBA rgba(4, 8, 5);
    rgba.print();
    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    return 0;
}
