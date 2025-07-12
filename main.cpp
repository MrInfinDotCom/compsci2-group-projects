#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val = 0) : data(val), next(nullptr), prev(nullptr) {}
};

class List {
private:
    Node* dummy;  // Dummy node to represent past-the-end

public:
    List() {
        dummy = new Node(); // dummy's data unused
        dummy->next = dummy;
        dummy->prev = dummy;
    }

    // Insert at end (before dummy)
    void insert(int val) {
        Node* newNode = new Node(val);
        Node* last = dummy->prev;

        last->next = newNode;
        newNode->prev = last;

        newNode->next = dummy;
        dummy->prev = newNode;
    }

    void remove(int val) {
        Node* curr = dummy->next;
        while (curr != dummy) {
            if (curr->data == val) {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
                return;
            }
            curr = curr->next;
        }
    }

    void print() const {
        Node* curr = dummy->next;
        while (curr != dummy) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    ~List() {
        Node* curr = dummy->next;
        while (curr != dummy) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete dummy;
        dummy = nullptr;
    }
};

int main() {
    // Testing

    List a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.print();

    a.remove(2);
    cout << "Removing 2: ";
    a.print();

    a.insert(2);
    cout << "Adding 2: ";
    a.print();

    a.remove(1);
    cout << "Removing 1: ";
    a.print();

    a.remove(2);
    cout << "Removing 2: ";
    a.print();

    return 0;
}
