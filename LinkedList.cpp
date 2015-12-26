// LinkedList.cpp:
//    Содержит реализации методов LinkedList и некоторых функций.
//    Наибольшая часть лабораторной работы связана с этим файлом.

#include <iostream>     // std::ostream
#include <stdexcept>    // std::out_of_range
#include <string>       // std::to_string()
#include <utility>      // std::swap()

#include "LinkedList.h"

using std::swap;  // Чтобы использовать swap() без std::


LinkedList& LinkedList::operator=(LinkedList rhs) //копирующее присваивание
{
    // TODO+
    swap(*this ,rhs);
    return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& rhs) //перемещающее присваивание
{
    // TODO+
    clear();
    swap(*this, rhs);
    return *this;
}

bool LinkedList::operator ==(const LinkedList& other) const
{
    // TODO+
    if (this->size() == other.size())
    {
        Node* left = other.first;
        Node* right = this->first;
        while (left)
        {
            if (left->value != right->value)
            {
                return false;
            }
            left = left->next;
            right = right->next;
        }
        return true;
    }
    else throw std::logic_error("Error: not equal size of object !");
}

bool LinkedList::operator!=(const LinkedList& other) const
{
    return !(*this == other);
}

void LinkedList::erase(const Node* node)//удаление узла из списка (8слайд)
{
    // TODO+
    if (node->previous)
        node->previous->next = node->next;
    else
        first = node->next;
    if (node->next)
        node->next->previous = node->previous;
    else
        last = node->previous;
    delete node;
    --size_;
}

void LinkedList::pop_back()
{
    // TODO+
    erase(last);
}

void LinkedList::pop_front()
{
    // TODO+
    erase(first);
}

LinkedList::Node* LinkedList::insert_after(LinkedList::Node* after)
{
    return nullptr;
}

LinkedList::Node* LinkedList::insert_before(LinkedList::Node* before)
{
    return nullptr;
}

void LinkedList::push_back(const Data& value) //вставка элемента в конец списка
{
    // TODO+
    Node* node = new Node;
    node->value = value;
    node->next = nullptr;
    node->previous = last;
    if (last != nullptr)
    {
        last->next = node;
    }
    last = node;
    if (first == nullptr)
    {
        first = last = node;
    }
    ++size_;
}

void LinkedList::push_front(const Data& value) //вставка элемента в начало списка
{
    // TODO+
    Node* node = new Node; //создаем новый элемент
    node->value = value; //вводим в него значение
    node->previous = nullptr;
    node->next = first;
    if (first != nullptr)
    {
        first->previous = node;
    }
    first = node;
    if (last == nullptr)
    {
        last = node;
    }
    ++size_;
}

void LinkedList::clear() //очистка списка
{
    // TODO+
    while (size_)
        erase (first);
}

void swap(LinkedList& left, LinkedList& right)
{
    // TODO+
    swap(left.first, right.first);
    swap(left.last, right.last);
    swap(left.size_, right.size_);
    // HINT: Функция std::swap() меняет значения простых типов
}
LinkedList::LinkedList(): first {nullptr},last {nullptr},size_ {0}
{
}

LinkedList::LinkedList(const std::initializer_list<Data> values) :
    LinkedList()
{
    // По std::initializer_list<T> возможен диапазонный for.
    for (const Data& value : values)
    {
        push_back(value);
    }
}

LinkedList::LinkedList(const LinkedList& source) //копирование
    : LinkedList()
{
    // TODO+
    Node*current = source.first;
    while (current)
    {
        push_back(current->value);
        current=current->next;
    }
    // HINT:
    // Здесь нельзя воспользоваться диапазонным for, потому что на данном
    // этапе задания у списка не реализованы итераторы, begin() и end().
}

LinkedList::LinkedList(LinkedList&& source) // перемещение
    : LinkedList()
{
    // TODO+
    swap(*this, source);
}

LinkedList::~LinkedList()
{
    // TODO+
    clear();   //пустой список
}


size_t LinkedList::size() const
{
    // TODO+
    return size_;
}

Data& LinkedList::value_at(size_t index) //
{
    //TODO+
    LinkedList::Node* current = first;
    size_t current_index = 0;
    if (index >= size_) throw std::out_of_range("Invalid index!");
    else
    {
        while (current)
        {
            if (current_index == index)
            {
                return current->value;;
            }
            ++current_index;
            current = current->next;
        }
    }
}

void LinkedList::remove_at(size_t index)
{
    // TODO+
    Node* node = (*this).node_at(index);
    if (index >= size_) throw std::out_of_range("Invalid index!");
    else erase(node); //удаление
}

void LinkedList::insert_before(size_t index, const Data& value)
{
    // TODO+
    Node* before = (*this).node_at(index); // TODO+
    if (index >= size_) throw std::out_of_range("Invalid index!");
    else
    {
        if (before->previous == nullptr)
            push_front(value);
        else
        {
            Node* node = new Node; //создаем новый элемент
            node->value = value; //вводим в него значение
            node->previous = before->previous;
            node->next = before;;
            node->previous->next = node;
            before->previous = node;
            ++size_;
        }
    }
}
void LinkedList::insert_after(size_t index, const Data& value)
{
    // TODO+
    Node* after = (*this).node_at(index);
    if (index >= size_) throw std::out_of_range("Invalid index!");
    else
    {
        if (after->previous == nullptr)
            push_back(value);
        else
        {
            Node* node = new Node; //создаем новый элемент
            node->value = value; //вводим в него значение
            node->previous = after;
            node->next = after->next;;
            node->next->previous = node;
            after->next = node;
            ++size_;
        }
    }
}
LinkedList::Node* LinkedList::node_at(size_t index)//поиск узла (9 слйад)
{
    // TODO+
    Node* current = first;
    size_t current_index = 0;
    if (index >= LinkedList::size_) throw std::out_of_range("Invalid index!");
    else
    {
        while (current)
        {
            if (current_index == index)
            {
                return current;
            }
            ++current_index;
            current = current->next;
        }
    }
}
std::ostream& operator<<(std::ostream& output, const LinkedList& xs)//обход и печать списка (7слайд)
{
    // TODO+
    LinkedList::Node* current = xs.first;
    if (xs.size() == 0) output<<"[]";
    else
    {
        output<<'[';
        while (current != xs.last)
        {
            output<<current -> value<<", ";
            current = current->next;
        }
        output<<xs.last->value<<']';
    }
    return output;
}

