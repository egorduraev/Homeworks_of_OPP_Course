#include <iostream>

//Task 1

enum Gender {men, women};

class Person {
private:
    std::string m_name;
    int m_age;
    Gender m_gender;
    float m_weight;
public:
    Person(std::string name, int age, Gender gender, float weight) :
    m_name(name), m_age(age), m_gender(gender), m_weight(weight) {}

    void setName(std::string name = "")  { m_name = name; }

    void setAge(int age = 0) { m_age = age; }

    void setWeight(float weight = 0.0) { m_weight = weight; }

    void print() const {
        std::cout << "Name: " << m_name << std::endl
            << "Age: " << m_age << std::endl
            << "Gender: " << (m_gender == men ? "Male" : "Female") << std::endl
            << "Weight: " << m_weight << std::endl;
    }
};

class Student : public Person {
private:
    static int count_stud;
    int m_year;
public:
    Student(std::string name, int age, Gender gender, float weight, int year) :
        Person(name, age, gender, weight), m_year(year) {
        count_stud++;
    }

    ~Student() { count_stud--; }

    static void printCount() {
        std::cout << "Number of students: " << count_stud << std::endl;
    }

    void setYear(int year = 0) { m_year = year; }

    void increaseYear() { m_year++; }

    void print() const{
        Person::print();
        std::cout << "Year of study: " << m_year << std::endl;
    }
};

//Task 2

class Fruit
{
private:
    std::string m_name;
    std::string m_color;
public:
    void setName(std::string name) { m_name = name; }
    void setColor(std::string color) { m_color = color; }
    const std::string& getName() const { return m_name; }
    const std::string& getColor() const { return m_color; }
};

class Apple : public Fruit {
public:
    Apple(std::string color = "") {
        setName("Apple");
        setColor(color);
    }
};

class Banana : public Fruit {
public:
    Banana(std::string color = "") {
        setName("Banana");
        setColor("yellow");
    }
};

class GrannySmith : public Apple {
public:
    GrannySmith() {
        setName("Granny Smith " + Apple::getName());
        Apple::setColor("green");
    }
};

int Student::count_stud = 0;

int main()
{
    //Task 1
    Student Jan("Jan", 22, men, 81.1, 2015);
    Student Mateusz("Mateusz", 18, men, 78.4, 2015);
    Jan.print();
    Mateusz.print();
    Jan.increaseYear();
    Mateusz.setYear(2017);
    Jan.print();
    Mateusz.print();
    Student::printCount();
    Student Monika("Monika", 19, women, 55.1, 2016);
    Student Krzysztof("Krzysztof", 20, men, 78.2, 2015);
    Student Jozef("Jozef", 23, men, 67.9, 2015);
    Student::printCount();

    //Task 2
    Apple a("red");
    Banana b;
    GrannySmith c;
    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    //Task 3
    /*

    Базовые классы:

    класс: Карта
    переменные-члены: значение очков, масть.

    класс: Колода
    переменные-члены: ссылки на обьекты класса Карта.

    класс: Набор карт
    переменные-члены: ссылки на обьекты класса Карта каждого участника.

    класс: Участник
    переменные-члены: имя игрока.

    класс: Игра
    переменные-члены: ссылка на обьект класса Колода,
    ссылка на обьект класса Игрок,
    ссылка на обьект класса Дилер.


    Производные классы:

    класс: Игрок (наследует от класса Участник)
    класс: Дилер (наследует от класса Участник)

    */
    return 0;
}
