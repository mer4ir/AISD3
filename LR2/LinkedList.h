#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cstddef>

class LinkedList
{
private:
    struct Node
    {
        int value;
        Node *next;
        Node(int v, Node *n = nullptr);
    };

    Node *head;
    std::size_t size_;

    void copy_from(const LinkedList &other); 
    void clear(); 
    void print_reverse(std::ostream &os, Node *n) const; 

public:
    LinkedList();
    LinkedList(const LinkedList &other);
    LinkedList(std::size_t count, int min_val, int max_val);
    ~LinkedList();

    LinkedList &operator=(const LinkedList &other);

    std::size_t size() const;
    bool empty() const;

    void push_tail(int value); 
    void push_tail(const LinkedList &other);

    void push_head(int value); 
    void push_head(const LinkedList &other); 

    void pop_head(); 
    void pop_tail(); 
    void delete_node(int value); 

    int &operator[](std::size_t index); 
    const int &operator[](std::size_t index) const; 

    friend std::ostream &operator<<(std::ostream &os, const LinkedList &list);
};

#endif