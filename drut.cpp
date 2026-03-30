#include <iostream>
#include <vector>
using namespace std;

// ─────────────────────────────────────────────
//  Node
// ─────────────────────────────────────────────
struct Node {
    int data;
    Node* next;
    Node(const int& val) : data(val), next(nullptr) {}
};

// ─────────────────────────────────────────────
//  SinglyLinkedList
// ─────────────────────────────────────────────
class SinglyLinkedList {
private:
    Node* head;
    int size;

public:
    // Constructor
    SinglyLinkedList() : head(nullptr), size(0) {}

    // Destructor
    ~SinglyLinkedList() {
        clear();
    }

    // Copy constructor
    SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), size(0) {
        Node* cur = other.head;
        while (cur) {
            pushBack(cur->data);
            cur = cur->next;
        }
    }

    // Copy assignment
    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* cur = other.head;
            while (cur) {
                pushBack(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    // ── Capacity ──────────────────────────────
    bool isEmpty() const { return head == nullptr; }
    int  getSize() const { return size; }

    // ── Modifiers ─────────────────────────────

    // Insert at the front — O(1)
    void pushFront(const int& val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        ++size;
    }

    // Insert at the back — O(n)
    void pushBack(const int& val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        } else {
            Node* cur = head;
            while (cur->next)
                cur = cur->next;
            cur->next = newNode;
        }
        ++size;
    }

    // Insert after a given node — O(1)
    void insertAfter(Node* prev, const int& val) {
        if (!prev) return;
        Node* newNode = new Node(val);
        newNode->next = prev->next;
        prev->next = newNode;
        ++size;
    }

    // Remove from the front — O(1)
    void popFront() {
        if (!head) return;
        Node* tmp = head;
        head = head->next;
        delete tmp;
        --size;
    }

    // Remove first occurrence of a value — O(n)
    bool remove(const int& val) {
        if (!head) return false;

        if (head->data == val) {
            popFront();
            return true;
        }

        Node* cur = head;
        while (cur->next && cur->next->data != val)
            cur = cur->next;

        if (!cur->next) return false;   // not found

        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        --size;
        return true;
    }

    // Delete all nodes — O(n)
    void clear() {
        while (head)
            popFront();
    }

    // ── Access / Search ───────────────────────

    // Return pointer to the head node
    Node* getHead() const { return head; }

    // Search for a value — O(n)
    Node* find(const int& val) const {
        Node* cur = head;
        while (cur) {
            if (cur->data == val) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    // Return value at index (0-based) — O(n)
    int& operator[](int index) {
        Node* cur = head;
        for (int i = 0; i < index && cur; ++i)
            cur = cur->next;
        if (!cur) throw out_of_range("Index out of range");
        return cur->data;
    }

    // ── Utilities ─────────────────────────────

    // Reverse the list in-place — O(n)
    void reverse() {
        Node* prev = nullptr;
        Node* cur  = head;
        while (cur) {
            Node* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur  = next;
        }
        head = prev;
    }

    // Print the list
    void print() const {
        Node* cur = head;
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "\n";
    }
};


void deleteDups(Node* head){

    if(!head || !head->next){
        return;
    }

    vector<int> dummies;
    Node* prev = head;
    Node* curr = head->next;
    Node* temp;
    dummies.push_back(head->data);

    while(curr){
        // first we need to push the value to the vector.
        dummies.push_back(curr->data);
        bool isDuplicated = false;
        int count = 0;
        // now we need to check if the value is duplicated or not
        for(int i = 0; i<dummies.size(); i++){
            if(dummies[i] == curr->data){
                count++;
                    if(count > 1){
                        isDuplicated = true;
                        break;
                    }
            }
        }
        // now we need to deal with the duplication.
        if(isDuplicated){
            temp = curr;
            curr = curr->next;
            prev->next = curr;
            delete temp;
        }
        else{
            curr = curr->next;
            prev = prev->next;
        }
    }
}


void deleteNode(Node* & head, int num){
    // we need to delete the node that carries num.

    if(!head){
        return;
    }


    Node* curr = head->next;
    Node* prev = head;


    while(curr){
        if(curr->data == num){
            prev->next = curr->next; // we attached with 0-2 to eliminate 1.
            delete curr;
            return;
        }
        curr = curr->next;
        prev = prev->next;
    }

    if(!curr){
        cout<<"There is no node to be deleted."<<endl;
        return;
    }



    
}



// ─────────────────────────────────────────────
//  Demo
// ─────────────────────────────────────────────
int main() {
    SinglyLinkedList list;

    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushFront(5);
    list.print();          // 5 -> 10 -> 20 -> 30

    list.remove(20);
    list.print();          // 5 -> 10 -> 30

    list.reverse();
    list.print();          // 30 -> 10 -> 5

    cout << "Size: " << list.getSize() << "\n";   // 3
    cout << "Find 10: " << (list.find(10) ? "found" : "not found") << "\n";

    return 0;
}