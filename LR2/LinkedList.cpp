#include "LinkedList.h"
#include <stdexcept>
#include <random>
#include <functional>

LinkedList::Node::Node(int v, Node *n) : value(v), next(n) {} // Инициализация узла

LinkedList::LinkedList() : head(nullptr), size_(0) {} // Инициализация пустого списка

// Конструктор копирования
LinkedList::LinkedList(const LinkedList &other) : head(nullptr), size_(0)
{
    copy_from(other);
}

// Конструктор с генерацией случайных значений
LinkedList::LinkedList(std::size_t count, int min_val, int max_val)
    : head(nullptr), size_(0)
{

    if (min_val > max_val)
    {
        throw std::invalid_argument("Invalid range.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min_val, max_val);

    for (std::size_t i = 0; i < count; ++i)
    {
        push_tail(dist(gen));
    }
}

// Деструктор
LinkedList::~LinkedList()
{
    clear();
}

// Оператор присваивания
LinkedList &LinkedList::operator=(const LinkedList &other)
{
    if (this != &other)
    {
        clear();
        copy_from(other);
    }
    return *this;
}

// Получение размера списка
std::size_t LinkedList::size() const
{
    return size_;
}

// Проверка на пустоту списка
bool LinkedList::empty() const
{
    return size_ == 0;
}

// Добавление элемента в конец списка
void LinkedList::push_tail(int value)
{
    Node *n = new Node(value);

    if (head == nullptr)
    {
        head = n;
    }
    else
    {
        Node *cur = head;
        while (cur->next != nullptr)
        {
            cur = cur->next;
        }
        cur->next = n;
    }
    ++size_;
}

// Добавление другого списка в конец текущего списка
void LinkedList::push_tail(const LinkedList &other)
{
    Node *cur = other.head;
    while (cur != nullptr)
    {
        push_tail(cur->value);
        cur = cur->next;
    }
}

// Добавление элемента в начало списка
void LinkedList::push_head(int value)
{
    head = new Node(value, head);
    ++size_;
}

// Добавление другого списка в начало текущего списка
void LinkedList::push_head(const LinkedList &other)
{
    std::function<void(LinkedList::Node *)> add_reverse = [&](LinkedList::Node *n)
    {
        if (n == nullptr)
            return;
        add_reverse(n->next);
        push_head(n->value);
    };

    add_reverse(other.head);
}

// Удаление элемента из начала списка
void LinkedList::pop_head()
{
    if (head == nullptr)
        throw std::out_of_range("List is empty.");

    Node *tmp = head;
    head = head->next;
    delete tmp;
    --size_;
}

// Удаление элемента из конца списка
void LinkedList::pop_tail()
{
    if (head == nullptr)
        throw std::out_of_range("List is empty.");

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        size_ = 0;
        return;
    }

    Node *cur = head;
    while (cur->next->next != nullptr)
    {
        cur = cur->next;
    }

    delete cur->next;
    cur->next = nullptr;
    --size_;
}

// Удаление всех элементов с заданным значением
void LinkedList::delete_node(int value)
{
    while (head != nullptr && head->value == value)
    {
        pop_head();
    }
    if (head == nullptr)
        return;

    Node *cur = head;
    while (cur->next != nullptr)
    {
        if (cur->next->value == value)
        {
            Node *tmp = cur->next;
            cur->next = cur->next->next;
            delete tmp;
            --size_;
        }
        else
        {
            cur = cur->next;
        }
    }
}

// Оператор индексирования для чтения и записи
int &LinkedList::operator[](std::size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");

    Node *cur = head;
    for (std::size_t i = 0; i < index; ++i)
        cur = cur->next;
    return cur->value;
}

// Оператор индексирования для чтения
const int &LinkedList::operator[](std::size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");

    Node *cur = head;
    for (std::size_t i = 0; i < index; ++i)
        cur = cur->next;
    return cur->value;
}

// Вспомогательный метод для копирования списка
void LinkedList::copy_from(const LinkedList &other)
{
    if (other.head == nullptr)
    {
        head = nullptr;
        size_ = 0;
        return;
    }

    head = new Node(other.head->value);
    Node *cur = head;
    Node *src = other.head->next;

    while (src != nullptr)
    {
        cur->next = new Node(src->value);
        cur = cur->next;
        src = src->next;
    }
    size_ = other.size_;
}

// Вспомогательный метод для очистки списка
void LinkedList::clear()
{
    while (head != nullptr)
    {
        Node *tmp = head;
        head = head->next;
        delete tmp;
    }
    size_ = 0;
}

// Вспомогательный метод для реверсивного вывода списка
void LinkedList::print_reverse(std::ostream &os, Node *n) const
{
    if (n == nullptr)
        return;
    print_reverse(os, n->next);
    os << n->value << " ";
}

// Оператор вывода списка
std::ostream &operator<<(std::ostream &os, const LinkedList &list)
{
    list.print_reverse(os, list.head);
    return os;
}