#include<bits/stdc++.h>
using namespace std;

class Node {
  public:
    int data;
    Node* ptr;

    Node() {
      int data = 0;
      ptr = NULL;
    }

    Node(int data) {
      this->data = data;
      ptr = NULL;
    }

    Node(Node* ptr) {
      data = 0;
      this->ptr = ptr;
    }

    Node(int data, Node* ptr) {
      this->data = data;
      this->ptr = ptr;
    }

};

class XorList {
  private:
    Node* head = NULL;

    Node* XOR(Node* a, Node* b) {
      return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
    }

    void movePtr(Node** curr, Node** prevOrNext) {
      Node* next = XOR(*prevOrNext, (*curr)->ptr);
      *prevOrNext = *curr;
      *curr = next;
    }

  public:
    void insertAtBeg(int data) {
      Node* newNode = new Node(data, head);

      if(head != NULL)
        head->ptr = XOR(newNode, head->ptr);

      head = newNode;
    }

    void deleteFromBeg() {
      if(head == NULL)
        return;

      Node* prev = head;
      head = head->ptr;

      if(head != NULL) 
        head->ptr = XOR(prev, head->ptr);

      delete prev;
    }


    void printList() {
      Node* prev = NULL;
      Node* curr = head;

      while(curr != NULL) {
        cout << curr->data << " ";
        movePtr(&curr, &prev);
      }

      cout << endl;
    }
};

int main() {
  int n;
  cin >> n;

  XorList list;
  while(n--) {
    int x;
    cin >> x;
    list.insertAtBeg(x);
  }

  list.printList();
}


