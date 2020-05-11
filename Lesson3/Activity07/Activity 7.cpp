#include <iostream>
#include <vector>

#include <openssl/md5.h>

class BloomFilter
{
    int nHashes;
    std::vector<bool> bits;

    static constexpr int hashSize = 128 / 8;

    unsigned char hashValue[hashSize];

public:
    BloomFilter(int size, int hashes) : bits(size), nHashes(hashes)
    {
        if (nHashes > hashSize)
        {
            throw("Number of hash functions too high");
        }

        if (size > 255)
        {
            throw("Size of bloom filter can't be >255");
        }
    }

    void hash(const std::string &key)
    {
        MD5(reinterpret_cast<const unsigned char *>(key.data()), key.length(), hashValue);
    }

    void add(const std::string &key)
    {
        hash(key);
        for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
        {
            bits[*it] = true;
        }
        std::cout << key << " added in bloom filter." << std::endl;
    }

    bool mayContain(const std::string &key)
    {
        hash(key);
        for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
        {
            if (!bits[*it])
            {
                std::cout << key << " email can by used." << std::endl;
                return false;
            }
        }

        std::cout << key << " email is used by someone else." << std::endl;
        return true;
    }
};

int main()
{
    BloomFilter bloom(10, 15);

    bloom.add("abc@packt.com");
    bloom.add("xyz@packt.com");

    bloom.mayContain("abc");
    bloom.mayContain("xyz@packt.com");
    bloom.mayContain("xyz");

    bloom.add("abcd@packt.com");
    bloom.add("ab@packt.com");

    bloom.mayContain("abcd");
    bloom.mayContain("ab@packt.com");
}