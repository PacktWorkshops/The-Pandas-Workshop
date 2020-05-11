#include <iostream>
#include <unordered_map>
#include <unordered_set>

void print(const std::unordered_set<int> &container)
{
    for (const auto &element : container)
        std::cout << element << " ";
    std::cout << std::endl;
}

void print(const std::unordered_map<int, int> &container)
{
    for (const auto &element : container)
        std::cout << element.first << ": " << element.second << ", ";
    std::cout << std::endl;
}

void find(const std::unordered_set<int> &container, const auto &element)
{
    if (container.find(element) == container.end())
        std::cout << element << " not found" << std::endl;
    else
        std::cout << element << " found" << std::endl;
}

void find(const std::unordered_map<int, int> &container, const auto &element)
{
    auto it = container.find(element);
    if (it == container.end())
        std::cout << element << " not found" << std::endl;
    else
        std::cout << element << " found with value =" << it->second << std::endl;
}

int main()
{
    std::cout << "Set example : " << std::endl;
    std::unordered_set<int> set1 = {1, 2, 3, 4, 5};
    std::cout << "Initial set1 : ";
    print(set1);

    set1.insert(2);
    std::cout << "After inserting 2 : ";
    print(set1);

    set1.insert(10);
    set1.insert(351);
    std::cout << "After inserting 10 and 351 : ";
    print(set1);

    find(set1, 4);
    find(set1, 100);
    set1.erase(2);
    std::cout << "Erased 2 from set1" << std::endl;
    find(set1, 2);

    std::cout << "Map example : " << std::endl;
    std::unordered_map<int, int> squareMap;

    squareMap.insert({2, 4});
    squareMap[3] = 9;
    std::cout << "After inserting squares of 2 and 3 : ";
    print(squareMap);

    squareMap[30] = 900;
    squareMap[20] = 400;
    std::cout << "After inserting squares of 20 and 30 : ";
    print(squareMap);

    find(squareMap, 10);
    find(squareMap, 20);
    std::cout << "Value of map[3] =" << squareMap[3] << std::endl;
    std::cout << "Value of map[100] =" << squareMap[100] << std::endl;
}
