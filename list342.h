#ifndef LIST342_H_
#define LIST342_H_
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <class T>
struct Node {
    T* data;
    Node *next;
};

template <class T>
class List342;

template <class T>
ostream& operator<<(ostream& os, const List342<T>& list);

template <class T>
class List342{

    public:
        List342(); // default constructor
        List342(List342<T> &source);// copy constructor

        bool BuildList(string file_name);
        bool Insert(T* obj); 
        bool Remove(T target, T& result);
        bool Peek(T target, T& result) const;
        int Size() const;
        void DeleteList();
        bool Merge(List342<T>& list1);
        //operator overloads
        List342<T> operator+(const List342<T>& rhs) const;
        List342<T>& operator+=(const List342<T>& rhs);
        bool operator==(const List342<T>& rhs) const;
        bool operator!=(const List342<T>& rhs) const;
        void operator=(const List342& rhs);
        // output list
        template <class U>
        friend ostream& operator<<(ostream& os, const List342<U>& list);

    private:
        Node<T>* recursiveMerge(Node<T> *node1, Node<T> *node2); // helper method for merge function
        Node<T>* head_;
        int length_;

};

template <class T>
List342<T>::List342()
{
	this->head_ = nullptr;
}

template <class T>
List342<T>::List342(List342<T> &source)
{
	this->head_ = nullptr;
	*this = source;
}

template <class T>
bool List342<T>::BuildList(string file_name) {
    ifstream myfile(file_name);

    if (!myfile.is_open()) {
        // Handle the case where the file couldn't be opened
        return false;
    }

    T myobj;

    while (myfile >> myobj) {
        // Check if the item is already in the list
        bool isDuplicate = false;
        Node<T>* current = head_;
        while (current != nullptr) {
            if (*(current->data) == myobj) {
                isDuplicate = true;
                break;
            }
            current = current->next;
        }

        if (!isDuplicate) {
            Insert(myobj);
        }
    }

    myfile.close();
    return true;
}

// insert method
template <class T>
bool List342<T>::Insert(T* obj) {
    Node<T>* newNode = new Node<T>;
    newNode->data = new T;
    *newNode->data = *obj;

    Node<T>* iterator = head_;
    // if list is empty
    if (head_ == nullptr) {
        head_ = newNode;
        return true;
    }
    // if newNode should be new head of list
    if (*(newNode->data) < *(iterator->data)) {
        newNode->next = head_;
        head_ = newNode;
        return true;
    }

    while (iterator->next != nullptr && *(iterator->next->data) <= *(newNode->data)) {
        if (*(iterator->next->data) == *(newNode->data)) {
            delete newNode->data; // Clean up the copied data in case of a duplicate
            delete newNode; // Clean up the new node
            return false;
        }
        iterator = iterator->next;
    }

    newNode->next = iterator->next;
    iterator->next = newNode;
    return true;
}



template <class T>
bool List342<T>::Remove(T target, T& result) {
    // Check if the list is empty
    if (head_ == nullptr) {
        return false;
    }

    // Check if the target is at the head of the list
    if (*(head_->data) == target) {
        result = *(head_->data);
        Node<T>* iterator = head_;
        head_ = head_->next;
        delete iterator;
        return true;
    }

    // Search for the target in the rest of the list
    Node<T>* current = head_;
    Node<T>* previous = nullptr;

    while (current != nullptr && *(current->data) != target) {
        previous = current;
        current = current->next;
    }

    // If the target is found, remove it
    if (current != nullptr) {
        result = *(current->data);

        // Handle removing the second-to-last node
        if (current->next == nullptr) { // Check if it's the second-to-last node
            previous->next = nullptr; // Set the previous node's next pointer to null
        } else { // Handle removing a node in the middle of the list
            previous->next = current->next; // Connect the previous node to the node after the one being removed
        }

        delete current;
        return true;
    }

    // Target not found
    return false;
}



template <class T>
bool List342<T>::Peek(T target, T &result) const{
    // Check if the list is empty
    if (head_ == nullptr) {
        return false;
    }

    // Check if the target is at the head of the list
    if (*(head_->data) == target) {
        result = *(head_->data);
        return true;
    }

    // Search for the target in the rest of the list
    Node<T>* current = head_;
    Node<T>* previous = nullptr;

    while (current != nullptr && *(current->data) != target) {
        previous = current;
        current = current->next;
    }

    // If the target is found assign to result
    if (current != nullptr) {
        result = *(current->data);
        return true;
    }

    // Target not found
    return false;
}

template <class T>
int List342<T>::Size() const {
    Node<T>* current = head_;
    int size = 0;
    while (current != nullptr) {
        size += 1;
        current = current->next;
    }

    return size;
}

template <class T>
void List342<T>::DeleteList() {
    Node<T> *curr = head_;
    Node<T> * next;

    while(curr != nullptr){
        next = curr->next;
        curr = nullptr;
        curr = next;
    }
    head_ = nullptr;
}

template <class T>
bool List342<T>::Merge(List342<T>& list1) {
    if (this == &list1) {
        return false;
    }

    head_ = recursiveMerge(head_, list1.head_);
    list1.head_ = nullptr;

    return true;
}

template <class T>
Node<T>* List342<T>::recursiveMerge(Node<T>* node1, Node<T>* node2) {
    if (node1 == nullptr) {
        return node2;
    }
    if (node2 == nullptr) {
        return node1;
    }

    if (*(node1->data) < *(node2->data)) {
        node1->next = recursiveMerge(node1->next, node2);
        return node1;
    } else {
        node2->next = recursiveMerge(node2->next, node1);
        return node2;
    }
}

template <class T>
List342<T> List342<T>::operator+(const List342<T>& rhs) const {
    List342<T> result = *this; // Create a copy of the current list
    result += rhs; // Use the modified operator+= to merge the lists
    return result;
}

template <class T>
List342<T>& List342<T>::operator+=(const List342<T>& rhs) {
    if (this == &rhs) {
        return *this;  // Avoid merging with itself
    }

    Node<T>* ptr1 = this->head_;
    Node<T>* ptr2 = rhs.head_;
    Node<T>* prev = nullptr;
    Node<T>* temp = nullptr;

    while (ptr1 != nullptr && ptr2 != nullptr) {
        if (*(ptr1->data) == *(ptr2->data)) {
            // Skip duplicates
            ptr2 = ptr2->next;
        } else if (*(ptr1->data) < *(ptr2->data)) {
            prev = ptr1;
            ptr1 = ptr1->next;
        } else {
            // Insert node from rhs into the current list
            if (prev == nullptr) {
                this->head_ = ptr2;
            } else {
                prev->next = ptr2;
            }
            temp = ptr2->next;
            ptr2->next = ptr1;
            prev = ptr2;
            ptr2 = temp;
        }
    }

    if (ptr2 != nullptr) {
        if (prev == nullptr) {
            this->head_ = ptr2;
        } else {
            prev->next = ptr2;
        }
    }

    return *this;
}


template <class T>
bool List342<T>::operator==(const List342& rhs) const {
    Node<T>* ptr1 = head_;
    Node<T>* ptr2 = rhs.head_;
    // iteratre through list to check each node
    while (ptr1 != nullptr && ptr2 != nullptr) {
        if (*(ptr1->data) != *(ptr2->data)) {
            return false;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    // If one list is longer than the other, they are not equal
    return (ptr1 == nullptr && ptr2 == nullptr);
}

template <class T> // not equals
bool List342<T>::operator!=(const List342& rhs) const{
   return !(*this == rhs);
}

template <class T>
void List342<T>::operator=(const List342& rhs) {
    if (this == &rhs) {
        // Self-assignment; no need to do anything
        return;
    }

    // Clear the current list to release any existing memory
    DeleteList();

    Node<T>* rhsCurrent = rhs.head_;

    while (rhsCurrent != nullptr) {
        T* childPtr = new T(*(rhsCurrent->data));
        Insert(childPtr);
        rhsCurrent = rhsCurrent->next;
    }
}

// ostream
template <class T>
ostream& operator<<(ostream& os, const List342<T>& list) {
    Node<T>* current = list.head_;
    
    while (current != nullptr) {
        os << *(current->data);
        current = current->next;
    }
    
    return os;
}



#endif