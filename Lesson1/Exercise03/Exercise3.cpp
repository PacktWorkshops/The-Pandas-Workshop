#include <iostream>
#include <forward_list>

struct citizen
{
    std::string name;
    int age;
};

std::ostream &operator<<(std::ostream &os, const citizen &c)
{
    return (os << "[Name: " << c.name << ", Age: " << c.age << "]");
}

int main()
{
    std::forward_list<citizen> citizens = {{"Raj", 22}, {"Rohit", 25}, {"Rohan", 17}, {"Sachin", 16}};

    auto citizens_copy = citizens;

    std::cout << "All the citizens: ";
    for (const auto &c : citizens)
        std::cout << c << " ";
    std::cout << std::endl;

    citizens.remove_if(
        [](const citizen &c) {
            // Returns true if age is less than 18
            return (c.age < 18);
        });

    std::cout << "Eligible citizens for voting: ";
    for (const auto &c : citizens)
        std::cout << c << " ";
    std::cout << std::endl;

    citizens_copy.remove_if(
        [](const citizen &c) {
            return (c.age != 17);
        });

    std::cout << "Citizens that will be elgibile for voting next year: ";
    for (const auto &c : citizens_copy)
        std::cout << c << " ";
    std::cout << std::endl;
}
