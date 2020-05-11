#include <iostream>
#include <vector>

class bloom_filter
{
    std::vector<bool> data;
    int nBits;

    int hash(int num, int key)
    {
        switch (num)
        {
        case 0:
            return key % nBits;
        case 1:
            return (key / 7) % nBits;
        case 2:
            return (key / 11) % nBits;
        }
        return 0;
    }

public:
    bloom_filter(int n) : nBits(n)
    {
        data = std::vector<bool>(nBits, false);
    }

    void lookup(int key)
    {
        bool result = data[hash(0, key)] & data[hash(1, key)] & data[hash(2, key)];
        if (result)
        {
            std::cout << key << " may be present." << std::endl;
        }
        else
        {
            std::cout << key << " is not present." << std::endl;
        }
    }

    void insert(int key)
    {
        data[hash(0, key)] = true;
        data[hash(1, key)] = true;
        data[hash(2, key)] = true;
        std::cout << key << " inserted." << std::endl;
    }
};

int main()
{
    bloom_filter bf(11);
    bf.insert(100);
    bf.insert(54);
    bf.insert(82);
    bf.lookup(5);
    bf.lookup(50);
    bf.lookup(2);
    bf.lookup(100);
    bf.lookup(8);
    bf.lookup(65);
}
