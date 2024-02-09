#include "Person.hpp"
#include <iostream>

Person::Person(int age)
{
    _age = age;
}
void Person::get_age()
{
    std::cout << "Age: " << _age << std::endl;
}