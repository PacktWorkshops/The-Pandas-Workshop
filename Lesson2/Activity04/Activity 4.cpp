#include <iostream>
#include <vector>
#include <algorithm>

struct n_ary_node
{
    std::string name;
    bool is_dir;

    std::vector<n_ary_node *> children;
};

struct file_system
{
    using node = n_ary_node;
    using node_ptr = node *;

private:
    node_ptr root;
    node_ptr cwd;

public:
    file_system()
    {
        root = new node{"/", true, {}};
        cwd = root; // We’ll keep the current directory as root in the beginning
    }

    node_ptr find(const std::string &path)
    {
        if (path[0] == '/') // Absolute path
        {
            return find_impl(root, path.substr(1));
        }
        else
        {
            return find_impl(cwd, path);
        }
    }

private:
    node_ptr find_impl(node_ptr directory, const std::string &path)
    {
        if (path.empty())
            return directory;
        auto sep = path.find('/');
        std::string current_path = sep == std::string::npos ? path : path.substr(0, sep);
        std::string rest_path = sep == std::string::npos ? "" : path.substr(sep + 1);
        auto found = std::find_if(directory->children.begin(), directory->children.end(),
                                  [&](const node_ptr child) {
                                      return child->name == current_path;
                                  });
        if (found != directory->children.end())
        {
            return find_impl(*found, rest_path);
        }
        return NULL;
    }

public:
    bool add(const std::string &path, bool is_dir)
    {
        if (path[0] == '/')
        {
            return add_impl(root, path.substr(1), is_dir);
        }
        else
        {
            return add_impl(cwd, path, is_dir);
        }
    }

private:
    bool add_impl(node_ptr directory, const std::string &path, bool is_dir)
    {
        if (not directory->is_dir)
        {
            std::cout << directory->name << " is a file." << std::endl;
            return false;
        }

        auto sep = path.find('/');

        // This is the last part of the path for adding directory. It’s a base condition of the recursion
        if (sep == std::string::npos)
        {
            auto found = std::find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr child) {
                return child->name == path;
            });
            if (found != directory->children.end())
            {
                std::cout << "There’s already a file/directory named " << path << " inside " << directory->name << "." << std::endl;
                return false;
            }

            directory->children.push_back(new node{path, is_dir, {}});
            return true;
        }

        // If the next segment of the path is still a directory
        std::string next_dir = path.substr(0, sep);
        auto found = std::find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr child) {
            return child->name == next_dir && child->is_dir;
        });
        if (found != directory->children.end())
        {
            return add_impl(*found, path.substr(sep + 1), is_dir);
        }

        std::cout << "There’s no directory named " << next_dir << " inside " << directory->name << "." << std::endl;
        return false;
    }

public:
    bool change_dir(const std::string &path)
    {
        auto found = find(path);
        if (found && found->is_dir)
        {
            cwd = found;
            std::cout << "Current working directory changed to " << cwd->name << "." << std::endl;
            return true;
        }

        std::cout << "Path not found." << std::endl;
        return false;
    }

public:
    void show_path(const std::string &path)
    {
        auto found = find(path);
        if (not found)
        {
            std::cout << "No such path: " << path << "." << std::endl;
            return;
        }

        if (found->is_dir)
        {
            for (auto child : found->children)
            {
                std::cout << (child->is_dir ? "d " : "- ") << child->name << std::endl;
            }
        }
        else
        {
            std::cout << "- " << found->name << std::endl;
        }
    }
};

int main()
{
    file_system fs;
    fs.add("usr", true);       // Add directory usr in "/"
    fs.add("etc", true);       // Add directory etc in "/"
    fs.add("var", true);       // Add directory var in "/"
    fs.add("tmp_file", false); // Add file tmp_file in "/"

    std::cout << "Files/Directories under \"/\"" << std::endl;
    fs.show_path("/"); // List files/directories in "/"

    std::cout << std::endl;
    fs.change_dir("usr");
    fs.add("Packt", true);
    fs.add("Packt/Downloads", true);
    fs.add("Packt/Downloads/newFile.cpp", false);

    std::cout << "Let’s see the contents of dir usr: " << std::endl;
    fs.show_path("usr"); // This will not print the path successfully, since we’re already inside the dir usr. And there’s no directory named usr inside it.

    std::cout << "Let’s see the contents of \"/usr\"" << std::endl;
    fs.show_path("/usr");

    std::cout << "Let’s see the contents of \"/usr/Packt/Downloads\"" << std::endl;
    fs.show_path("/usr/Packt/Downloads");
}
