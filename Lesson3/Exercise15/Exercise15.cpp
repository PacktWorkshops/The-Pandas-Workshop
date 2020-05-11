#include <iostream>
#include <vector>

class hash_map
{
    std::vector<int> data1;
    std::vector<int> data2;
    int size;

    int hash1(int key) const
    {
        return key % size;
    }

    int hash2(int key) const
    {
        return (key / size) % size;
    }

public:
    hash_map(int n) : size(n)
    {
        data1 = std::vector<int>(size, -1);
        data2 = std::vector<int>(size, -1);
    }

    std::vector<int>::iterator lookup(int key)
    {
        auto hash_value1 = hash1(key);
        if (data1[hash_value1] == key)
        {
            std::cout << "Found " << key << " in first table" << std::endl;
            return data1.begin() + hash_value1;
        }

        auto hash_value2 = hash2(key);
        if (data2[hash_value2] == key)
        {
            std::cout << "Found " << key << " in second table" << std::endl;
            return data2.begin() + hash_value2;
        }

        return data2.end();
    }

    void erase(int key)
    {
        auto position = lookup(key);
        if (position != data2.end())
        {
            *position = -1;
            std::cout << "Removed the element " << key << std::endl;
        }
        else
        {
            std::cout << "Key " << key << " not found." << std::endl;
        }
    }

    void insert(int key)
    {
        insert_impl(key, 0, 1);
    }

    void insert_impl(int key, int cnt, int table)
    {
        if (cnt >= size)
        {
            std::cout << "Cycle detected, while inserting " << key << ". Rehashing required." << std::endl;
            return;
        }

        if (table == 1)
        {
            int hash = hash1(key);
            if (data1[hash] == -1)
            {
                std::cout << "Inserted key " << key << " in table " << table << std::endl;
                data1[hash] = key;
            }
            else
            {
                int old = data1[hash];
                data1[hash] = key;
                std::cout << "Inserted key " << key << " in table " << table << " by replacing " << old << std::endl;
                insert_impl(old, cnt + 1, 2);
            }
        }
        else
        {
            int hash = hash2(key);
            if (data2[hash] == -1)
            {
                std::cout << "Inserted key " << key << " in table " << table << std::endl;
                data2[hash] = key;
            }
            else
            {
                int old = data2[hash];
                data2[hash] = key;
                std::cout << "Inserted key " << key << " in table " << table << " by replacing " << old << std::endl;
                insert_impl(old, cnt + 1, 2);
            }
        }
    }

    void print()
    {
        std::cout << "Index: ";
        for (int i = 0; i < size; i++)
            std::cout << i << '\t';
        std::cout << std::endl;

        std::cout << "Data1: ";
        for (auto i : data1)
            std::cout << i << '\t';
        std::cout << std::endl;

        std::cout << "Data2: ";
        for (auto i : data2)
            std::cout << i << '\t';
        std::cout << std::endl;
    }
};

int main()
{
    hash_map map(7);
    map.print();

    map.insert(10);
    map.insert(20);
    map.insert(30);
    std::cout << std::endl;

    map.insert(104);
    map.insert(2);
    map.insert(70);
    map.insert(9);
    map.insert(90);
    map.insert(2);
    map.insert(7);

    std::cout << std::endl;

    map.print();

    std::cout << std::endl;

    map.insert(14); // This will cause cycle.
}
