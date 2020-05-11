#include <iostream>

struct node
{
    int data;
    node *left, *right;
};

struct bst
{
    node *root = nullptr;

    node *find(int value)
    {
        return find_impl(root, value);
    }

private:
    node *find_impl(node *current, int value)
    {
        if (!current)
        {
            std::cout << std::endl;
            return NULL;
        }
        if (current->data == value)
        {
            std::cout << "Found " << value << std::endl;
            return current;
        }
        if (value < current->data) // Value will be in the left subtree
        {
            std::cout << "Going left from " << current->data << ", ";
            return find_impl(current->left, value);
        }
        // Value will be in the right subtree
        std::cout << "Going right from " << current->data << ", ";
        return find_impl(current->right, value);
    }

public:
    void insert(int value)
    {
        if (!root)
            root = new node{value, NULL, NULL};
        else
            insert_impl(root, value);
    }

private:
    void insert_impl(node *current, int value)
    {
        if (value < current->data)
        {
            if (!current->left)
                current->left = new node{value, NULL, NULL};
            else
                insert_impl(current->left, value);
        }
        else
        {
            if (!current->right)
                current->right = new node{value, NULL, NULL};
            else
                insert_impl(current->right, value);
        }
    }

public:
    void inorder()
    {
        inorder_impl(root);
    }

private:
    void inorder_impl(node *start)
    {
        if (!start)
            return;
        inorder_impl(start->left);       // Visit the left sub-tree
        std::cout << start->data << " "; // Print out the current node
        inorder_impl(start->right);      // Visit the right sub-tree
    }

public:
    node *successor(node *start)
    {
        auto current = start->right;
        while (current && current->left)
            current = current->left;
        return current;
    }

    void deleteValue(int value)
    {
        root = delete_impl(root, value);
    }

private:
    node *delete_impl(node *start, int value)
    {
        if (!start)
            return NULL;
        if (value < start->data)
            start->left = delete_impl(start->left, value);
        else if (value > start->data)
            start->right = delete_impl(start->right, value);
        else
        {
            if (!start->left) // Either both children are absent or only left child is absent
            {
                auto tmp = start->right;
                delete start;
                return tmp;
            }
            if (!start->right) // Only right child is absent
            {
                auto tmp = start->left;
                delete start;
                return tmp;
            }

            auto succNode = successor(start);
            start->data = succNode->data;
            // Delete the successor from right subtree, since it will always be in the right subtree
            start->right = delete_impl(start->right, succNode->data);
        }
        return start;
    }
};

int main()
{
    bst tree;
    tree.insert(12);
    tree.insert(10);
    tree.insert(20);
    tree.insert(8);
    tree.insert(11);
    tree.insert(15);
    tree.insert(28);
    tree.insert(4);
    tree.insert(2);

    std::cout << "Inorder: ";
    tree.inorder(); // This will print all the elements in ascending order
    std::cout << std::endl;

    tree.deleteValue(12);
    std::cout << "Inorder after deleting 12: ";
    tree.inorder(); // This will print all the elements in ascending order
    std::cout << std::endl;

    if (tree.find(12))
        std::cout << "Element 12 is present in the tree" << std::endl;
    else
        std::cout << "Element 12 is NOT present in the tree" << std::endl;
}
