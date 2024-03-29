#ifndef __GENERIC_LINKED_LIST_HPP
#define __GENERIC_LINKED_LIST_HPP

#include <string>
#include <stdexcept>


class LinkedListEmptyException: public std::runtime_error
{
    public:
        explicit LinkedListEmptyException(const std::string &error): std::runtime_error(error) {}
};


template<typename Object>
class GenericLinkedList
{
    private:

        size_t count;
        struct Node {
            Node(Object v)
            : value{v}, next{nullptr}
            {}
            Object value;
            Node *next;
        };
        Node *head;

    public:

        GenericLinkedList(); // constructor
        GenericLinkedList(const GenericLinkedList & st); // copy constructor
        GenericLinkedList&operator=(const GenericLinkedList &st); // assignment operator
        ~GenericLinkedList(); // destructor

        size_t size() const noexcept;
        bool isEmpty() const noexcept;

        void update(const Object &elem);
        void dequeue();
};


//constructor
template<typename Object>
GenericLinkedList<Object>::GenericLinkedList(): count{0}, head{nullptr}
{ }


//copy constructor
template<typename Object>
GenericLinkedList<Object>::GenericLinkedList(const GenericLinkedList & st)
{
    Node *st_head{st.head};
    head = new Node{st_head->value}; // this should have an alternative (just direct enqueue
    count = 1;
    while (st_head->next != nullptr) {
        st_head = st_head->next;
        enqueue(st_head->value);
    }
}


//assignment operator
template<typename Object>
GenericLinkedList<Object> & GenericLinkedList<Object>::operator=(const GenericLinkedList<Object> & st)
{
    // first delete all the Nodes linked
    size_t copy_count{count};
    for (size_t i{0}; i < copy_count; i++) {
        dequeue();
    }  
    
    // then add all the Nodes of the linked list being assigned
    Node *st_head{st.head};
    head = new Node{st_head->value}; // this should have an alternative (just direct enqueue
    count = 1;
    while (st_head->next != nullptr) {
        st_head = st_head->next;
        enqueue(st_head->value);
    }

    return this*
}


//destructor
template<typename Object>
GenericLinkedList<Object>::~GenericLinkedList()
{
    size_t copy_count{count};
    for (size_t i{0}; i < copy_count; i++) {
        dequeue();
    }
}


template<typename Object>
size_t GenericLinkedList<Object>::size() const noexcept
{
    return count;
}


template<typename Object>
bool GenericLinkedList<Object>::isEmpty() const noexcept
{
    if (head == nullptr) {
        return true;
    }
    return false;
}


template<typename Object>
void GenericLinkedList<Object>::update(const Object &elem)
{
    if (head == nullptr) {
        head = new Node(elem);
        head->next = nullptr;
        count += 1;
    } else {
        Node *tmp{head};
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = new Node(elem);
        count += 1;
    }
}


template<typename Object>
void GenericLinkedList<Object>::dequeue()
{
    if (count == 1) {
        Node *tmp{head};
        delete tmp;
        head = nullptr;
        count = 0;
    } else {
        Node *tmp{head};
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        delete tmp;
    }
}

#endif