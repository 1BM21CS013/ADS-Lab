#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    int level;
    Node **links;

    Node(int key, int level)
    {
        this->key = key;
        this->level = level;
        this->links = new Node *[level + 1];

        for (int i = 0; i <= level; i++)
            links[i] = NULL;
    }
};

class SkipList
{
private:
    Node *header;
    double P;
    int MAX_LEVEL;
    int currListLevel;

    int getRandomLevel()
    {
        float r = (float)rand() / RAND_MAX;
        int level = 0;

        while (r < P && level <= MAX_LEVEL)
        {
            level++;
            r = (float)rand() / RAND_MAX;
        }

        return level;
    }

    Node *createNewNode(int key)
    {
        int level = getRandomLevel();
        return new Node(key, level);
    }

public:
    SkipList(int maxLevel, double p)
    {
        this->MAX_LEVEL = maxLevel;
        this->P = p;
        this->header = new Node(-1, MAX_LEVEL);
        this->currListLevel = 0;
    }

    void insertNode(int key)
    {
        Node *curr = header;
        Node *update[MAX_LEVEL + 1];

        for (int i = currListLevel; i >= 0; i--)
        {
            while (curr->links[i] != NULL && curr->links[i]->key < key)
                curr = curr->links[i];
            update[i] = curr;
        }
        curr = curr->links[0];

        // don't insert if key is already present
        if (curr != NULL && curr->key == key)
            return;

        Node *newNode = createNewNode(key);
        if (newNode->level > currListLevel)
        {
            for (int i = currListLevel + 1; i <= newNode->level; i++)
                update[i] = header;
            currListLevel = newNode->level;
        }

        for (int i = 0; i <= newNode->level; i++)
        {
            newNode->links[i] = update[i]->links[i];
            update[i]->links[i] = newNode;
        }
    }

    void deleteNode(int key)
    {
        Node *curr = header;
        Node *update[MAX_LEVEL + 1];

        for (int i = currListLevel; i >= 0; i--)
        {
            while (curr->links[i] != NULL && curr->links[i]->key < key)
                curr = curr->links[i];
            update[i] = curr;
        }
        curr = curr->links[0];

        // don't delete if node is not present
        if (curr == NULL || curr->key > key)
            return;

        for (int i = 0; i <= curr->level; i++)
            update[i]->links[i] = curr->links[i];

        while (currListLevel > 0 && header->links[currListLevel] == NULL)
            currListLevel--;

        delete curr;
    }

    bool searchNode(int key)
    {
        Node *curr = header;

        for (int i = currListLevel; i >= 0; i--)
            while (curr->links[i] != NULL && curr->links[i]->key < key)
                curr = curr->links[i];

        curr = curr->links[0];

        if (curr != NULL && curr->key == key)
            return true;
        else
            return false;
    }

    void displayList()
    {
        for (int i = 0; i <= currListLevel; i++)
        {
            cout << "Level-" << i << ": ";
            Node *curr = header->links[i];

            while (curr != NULL)
            {
                cout << curr->key << " ";
                curr = curr->links[i];
            }

            cout << endl;
        }
    }
};

int main()
{
    int n;
    cin >> n;

    /* 
        Query is of the following type

        1 x -> insert key x
        2 x -> delete key x
        3 x -> search key x
        4   -> display list
        
    */

    SkipList list(5, 0.5);
    while (n--)
    {
        int query, key;
        cin >> query;

        if (query <= 3)
            cin >> key;
        
        switch (query)
        {
        case 1:
            list.insertNode(key);
            break;
        case 2:
            list.deleteNode(key);
            break;
        case 3:
            cout << (list.searchNode(key) ? "Found" : "Not Found") << endl;
            break;
        case 4:
            list.displayList();
            break;
        }
    }
}