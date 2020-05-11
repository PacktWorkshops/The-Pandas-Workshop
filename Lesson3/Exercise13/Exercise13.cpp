#include <iostream>
#include <vector>

using uint = unsigned int;
class hash_map
{
    std::vector<int> data;

public:
    hash_map(size_t n)
    {
        data = std::vector<int>(n, -1);
    }

    void insert(uint value)
    {
        int n = data.size();
        data[value % n] = value;
        std::cout << "Inserted " << value << std::endl;
    }

    bool find(uint value)
    {
        int n = data.size();
        return (data[value % n] == value);
    }

    void erase(uint value)
    {
        int n = data.size();
        if (data[value % n] == value)
        {
            data[value % n] = -1;
            std::cout << "Removed " << value << std::endl;
        }
    }
};

int main()
{
    hash_map map(7);

    auto print = [&](int value) {
        if (map.find(value))
            std::cout << value << " found in the hash map";
        else
            std::cout << value << " NOT found in the hash map";
        std::cout << std::endl;
    };

    map.insert(2);
    map.insert(25);
    map.insert(290);

    print(25);
    print(100);

    map.insert(100);
    print(100);
    map.erase(25);
}
