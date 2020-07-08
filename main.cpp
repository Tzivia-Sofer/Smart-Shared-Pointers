#include <iostream>
#include "smart_pointer.h"

class Person
{
public:
    virtual void sayHello() {std::cout<<"hello father\n";}
    virtual ~Person() {};
};

class Student:public Person
{
public:
    void sayHello() {std::cout<<"hello son\n";}
};

int main()
{
    SharedPtr<Student> s(new Student);
    SharedPtr<Person> p(new Person);
    p = s;
    p.getPtr()->sayHello();
    s.getPtr()->sayHello();
    SharedPtr<Person> p2(s);
    p2.getPtr()->sayHello();
    return 0;
}