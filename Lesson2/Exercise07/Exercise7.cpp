#include <iostream>
#include <queue>

struct node
{
    std::string position;
    node *first, *second;
};

struct org_tree
{
    node *root;

    static org_tree create_org_structure(const std::string &pos)
    {
        org_tree tree;
        tree.root = new node{pos, NULL, NULL};
        return tree;
    }

    static node *find(node *root, const std::string &value)
    {
        if (root == NULL)
            return NULL;
        if (root->position == value)
            return root;
        auto firstFound = org_tree::find(root->first, value);
        if (firstFound != NULL)
            return firstFound;
        return org_tree::find(root->second, value);
    }

    bool addSubordinate(const std::string &manager, const std::string &subordinate)
    {
        auto managerNode = org_tree::find(root, manager);
        if (!managerNode)
        {
            std::cout << "No position named " << manager << std::endl;
            return false;
        }
        if (managerNode->first && managerNode->second)
        {
            std::cout << manager << " already has 2 subordinates." << std::endl;
            return false;
        }
        if (!managerNode->first)
            managerNode->first = new node{subordinate, NULL, NULL};
        else
            managerNode->second = new node{subordinate, NULL, NULL};
        return true;
    }
};

int main()
{
    auto tree = org_tree::create_org_structure("CEO");
    if (tree.addSubordinate("CEO", "Deputy Director"))
        std::cout << "Added Deputy Director in the tree." << std::endl;
    else
        std::cout << "Couldn't add Deputy Director in the tree" << std::endl;

    if (tree.addSubordinate("Deputy Director", "IT Head"))
        std::cout << "Added IT Head in the tree." << std::endl;
    else
        std::cout << "Couldn't add IT Head in the tree" << std::endl;

    if (tree.addSubordinate("Deputy Director", "Marketing Head"))
        std::cout << "Added Marketing Head in the tree." << std::endl;
    else
        std::cout << "Couldn't add Marketing Head in the tree" << std::endl;

    if (tree.addSubordinate("IT Head", "Security Head"))
        std::cout << "Added Security Head in the tree." << std::endl;
    else
        std::cout << "Couldn't add Security Head in the tree" << std::endl;

    if (tree.addSubordinate("IT Head", "App Development Head"))
        std::cout << "Added App Development Head in the tree." << std::endl;
    else
        std::cout << "Couldn't add App Development Head in the tree" << std::endl;

    if (tree.addSubordinate("Marketing Head", "Logistics Head"))
        std::cout << "Added Logistics Head in the tree." << std::endl;
    else
        std::cout << "Couldn't add Logistics Head in the tree" << std::endl;

    if (tree.addSubordinate("Marketing Head", "Public Relations Head"))
        std::cout << "Added Public Relations Head in the tree." << std::endl;
    else
        std::cout << "Couldn't add Public Relations Head in the tree" << std::endl;

    if (tree.addSubordinate("Deputy Director", "Finance Head"))
        std::cout << "Added Finance Head in the tree." << std::endl;
    else
        std::cout << "Couldn't add Finance Head in the tree" << std::endl;
}
