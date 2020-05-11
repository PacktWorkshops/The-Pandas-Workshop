#include <iostream>
#include <unordered_map>

struct URLService
{
    using ActualURL = std::string;
    using TinyURL = std::string;

private:
    std::unordered_map<TinyURL, ActualURL> data;

public:
    std::pair<bool, ActualURL> lookup(const TinyURL &url) const
    {
        auto it = data.find(url);
        if (it == data.end()) // If small URL is not registered.
        {
            return std::make_pair(false, std::string());
        }
        else
        {
            return std::make_pair(true, it->second);
        }
    }

    bool registerURL(const ActualURL &actualURL, const TinyURL &tinyURL)
    {
        auto found = lookup(tinyURL).first;
        if (found)
        {
            return false;
        }

        data[tinyURL] = actualURL;
        return true;
    }

    bool deregisterURL(const TinyURL &tinyURL)
    {
        auto found = lookup(tinyURL).first;
        if (found)
        {
            data.erase(tinyURL);
            return true;
        }

        return false;
    }

    void printURLs() const
    {
        for (const auto &entry : data)
        {
            std::cout << entry.first << " -> " << entry.second << std::endl;
        }
        std::cout << std::endl;
    }
};

int main()
{
    URLService service;

    if (service.registerURL("https://www.packtpub.com/eu/big-data-and-business-intelligence/machine-learning-r-third-edition", "https://ml-r-v3"))
    {
        std::cout << "Registered https: //ml-r-v3" << std::endl;
    }
    else
    {
        std::cout << "Couldn’t register https: //ml-r-v3" << std::endl;
    }

    if (service.registerURL("https://www.packtpub.com/eu/virtualization-and-cloud/hands-aws-penetration-testing-kali-linux", "https://aws-test-kali"))
    {
        std::cout << "Registered https: //aws-test-kali" << std::endl;
    }
    else
    {
        std::cout << "Couldn’t register https: //aws-test-kali" << std::endl;
    }

    if (service.registerURL("https://www.packtpub.com/eu/application-development/hands-qt-python-developers", "https://qt-python"))
    {
        std::cout << "Registered https: //qt-python" << std::endl;
    }
    else
    {
        std::cout << "Couldn’t register https: //qt-python" << std::endl;
    }

    auto findMLBook = service.lookup("https://ml-r-v3");
    if (findMLBook.first)
    {
        std::cout << "Actual URL : " << findMLBook.second << std::endl;
    }
    else
    {
        std::cout << "Couldn’t find URL for book for ML." << std::endl;
    }

    auto findReactBook = service.lookup("https://react-cookbook");
    if (findReactBook.first)
    {
        std::cout << "Actual URL : " << findReactBook.second << std::endl;
    }
    else
    {
        std::cout << "Couldn’t find URL for book for React." << std::endl;
    }

    if (service.deregisterURL("https://qt-python"))
    {
        std::cout << "Deregistered qt python link" << std::endl;
    }
    else
    {
        std::cout << "Couldn’t deregister qt python link" << std::endl;
    }

    auto findQtBook = service.lookup("https://qt-python");
    if (findQtBook.first)
    {
        std::cout << "Actual URL : " << findQtBook.second << std::endl;
    }
    else
    {
        std::cout << "Couldn’t find Qt Python book" << std::endl;
    }

    std::cout << "List of registered URLs: " << std::endl;
    service.printURLs();
}
