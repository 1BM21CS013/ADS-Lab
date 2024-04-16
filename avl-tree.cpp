#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;

    Node(int key, Node *left, Node *right, int height)
    {
        this->key = key;
        this->left = left;
        this->right = right;
        this->height = height;
    }
};

class AVLTree
{
private:
    Node *root = nullptr;

    int getHeight(Node *node)
    {
        return node == nullptr ? 0 : node->height;
    }

    Node *leftRotate(Node *node)
    {
        Node *rightChild = node->right;
        Node *subtree = rightChild->left;

        node->right = subtree;
        rightChild->left = node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        rightChild->height = 1 + max(getHeight(rightChild->left), getHeight(rightChild->right));

        return rightChild;
    }

    Node *rightRotate(Node *node)
    {
        Node *leftChild = node->right;
        Node *subtree = leftChild->left;

        node->left = subtree;
        leftChild->right = node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        leftChild->height = 1 + max(getHeight(leftChild->left), getHeight(leftChild->right));

        return leftChild;
    }

    int getBalance(Node *node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node *getMinimumNode(Node *node)
    {
        Node *current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node *getBalancedRoot(Node *root)
    {
        int balance = getBalance(root);

        // LEFT LEFT
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // RIGHT RIGHT
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // LEFT RIGHT
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // RIGHT LEFT
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    Node *insertNodeInternally(Node *root, int key)
    {
        if (root == nullptr)
            return new Node(key, nullptr, nullptr, 1);

        if (key < root->key)
            root->left = insertNodeInternally(root->left, key);
        else if (key > root->key)
            root->right = insertNodeInternally(root->right, key);
        else
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);

        if (balance > 1 || balance < -1)
            return getBalancedRoot(root);
        else
            return root;
    }

    Node *deleteNodeInternally(Node *root, int key)
    {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNodeInternally(root->left, key);
        else if (key > root->key)
            root->right = deleteNodeInternally(root->right, key);
        else
        {
            // root is a leaf node
            if (root->left == nullptr && root->right == nullptr)
            {
                free(root);
                root = nullptr;
            }
            // root has a single child
            else if (root->left == nullptr || root->right == nullptr)
            {
                Node *child = root->left ? root->left : root->right;
                free(root);
                root = child;
            }
            // root has two children
            else
            {
                Node *successor = getMinimumNode(root->right);
                root->key = successor->key;
                root->right = deleteNodeInternally(root->right, successor->key);
            }
        }

        if (root == nullptr)
            return root;

        int balance = getBalance(root);

        if (balance > 1 || balance < -1)
            return getBalancedRoot(root);
        else
            return root;
    }

    bool searchNodeInternally(Node *root, int key)
    {
        if (root == nullptr)
            return false;

        if (key < root->key)
            return searchNodeInternally(root->left, key);
        else if (key > root->key)
            return searchNodeInternally(root->right, key);
        else
            return true;
    }

public:
    void insertNode(int key)
    {
        root = insertNodeInternally(root, key);
    }

    void deleteNode(int key)
    {
        root = deleteNodeInternally(root, key);
    }

    bool searchNode(int key)
    {
    }

    void printLevelOrder()
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        Node *curr;
        queue<Node *> bfs;
        bfs.push(root);
        int level = 1;
        while (!bfs.empty())
        {
            int size = bfs.size();
            cout << "Level " << level << ": ";
            while (size--)
            {
                curr = bfs.front();
                bfs.pop();
                cout << curr->key << " ";

                if (curr->left != nullptr)
                    bfs.push(curr->left);
                if (curr->right != nullptr)
                    bfs.push(curr->right);
            }
            cout << endl;
            level++;
        }
    }
};

int main()
{
    AVLTree tree;

    int n;
    cin >> n;

    while (n--)
    {
        int a, b, c;

        cin >> a;

        if (a <= 3)
            cin >> b;

        switch (a)
        {
        case 1:
            tree.insertNode(b);
            break;

        case 2:
            tree.deleteNode(b);
            break;

        case 3:
            tree.searchNode(b);
            break;

        case 4:
            tree.printLevelOrder();
            cout << "----------------------" << endl;
        }
    }
}