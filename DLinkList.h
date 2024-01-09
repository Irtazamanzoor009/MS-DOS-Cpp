#pragma once
#include <iostream>
#include<list>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T>* next;
    Node<T>* previous;

    Node(T value)
    {
        data = value;
        next = nullptr;
        previous = nullptr;
    }
};

template <typename T>
class DoubleLinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoubleLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    T operator[](int idx)
    {
        //if (idx < 0 or idx > this->size)
        //{
        //    return nullptr;
        //}
        ///*else if (idx == 0 and this->head->data != nullptr)
        //{
        //    return this->head->data;
        //}*/
        //else
        //{
        //    Node<T>* result = this->head;
        //    for (int i = 0; i < idx; i++)
        //    {
        //        result = result->next;
        //    }
        //    return result->data;
        //}
        //return nullptr;
        if (idx >= 0 && idx < this->size)
        {
            Node<T>* temp = head;
            for (int i = 0;i < idx;i++)
            {
                temp = temp->next;
            }
            return temp->data;
        }
        return nullptr;
    }

    Node<T>* fbegin()
    {
        return head;
    }

    Node<T>* fend()
    {
        return tail->next;
    }

    Node<T>* rbegin()
    {
        return tail;
    }

    Node<T>* rend()
    {
        return head->previous;
    }

    Node<T>* begin()
    {
        return head;
    }

    Node<T>* end()
    {
        return tail;
    }

    int getsize()
    {
        return size;
    }

    class ForwardIterator
    {
    public:
        Node<T>* iter;
        ForwardIterator(Node<T>* n)
        {
            iter = n;
        }

        Node<T>* operator++(int)
        {
            return iter = iter->next;
        }

        bool operator!=(ForwardIterator n)
        {
            return iter != n.iter;
        }

        bool operator==(ForwardIterator n)
        {
            return iter == n.iter;
        }

        T operator*()
        {
            return iter->data;
        }
    };

    class ReverseIterator
    {
    public:
        Node<T>* iter;
        ReverseIterator(Node<T>* n)
        {
            iter = n;
        }

        bool operator!=(ReverseIterator n)
        {
            return iter != n.iter;
        }

        Node<T>* operator++(int)
        {
            return iter = iter->previous;
        }

        bool operator==(ReverseIterator n)
        {
            return iter = n.iter;
        }

        T operator*()
        {
            return iter->data;
        }
    };

    class GeneralIterator
    {
    public:
        Node<T>* iter;
        GeneralIterator(Node<T>* n)
        {
            iter = n;
        }

        bool operator!=(GeneralIterator n)
        {
            return iter != n.iter;
        }

        bool operator==(GeneralIterator n)
        {
            return iter == n.iter;
        }

        Node<T>* operator++(int)
        {
            return iter = iter->next;
        }

        Node<T>* operator--(int)
        {
            return iter = iter->previous;
        }

        T operator*()
        {
            return iter->data;
        }
    };

    Node<T>* GetHead()
    {
        return head;
    }

    Node<T>* GetTail()
    {
        return tail;
    }

    bool isEmpty()
    {
        if (head == nullptr && tail == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void InsertAtTail(T value)
    {
        Node<T>* new_node = new Node<T>(value);
        if (isEmpty())
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            new_node->previous = tail;
            tail = new_node;
        }
        size++;
    }

    void InsertAtFront(T value)
    {
        Node<T>* new_node = new Node<T>(value);
        if (isEmpty())
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            new_node->next = head;
            head->previous = new_node;
            head = new_node;
        }
        size++;
    }

    void RemoveAtTail()
    {
        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail->previous->next = nullptr;
            tail = tail->previous;
        }
        size--;
    }

    void RemoveAtHead()
    {
        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head->next->previous = nullptr;
            head = head->next;
        }
        size--;
    }

    void InserAfter(T value, T key)
    {
        Node<T>* new_node = new Node<T>(value);
        Node<T>* temp = head;
        while (temp->data != key)
        {
            temp = temp->next;
        }
        if (temp == tail)
        {
            InsertAtTail(value);
        }
        else
        {
            temp->next->previous = new_node;
            new_node->next = temp->next;
            temp->next = new_node;
            new_node->previous = temp;
            size++;
        }
    }

    void InsertBefore(T value, T key)
    {
        Node<T>* new_node = new Node<T>(value);
        Node<T>* temp = head;
        int count = 0;
        while (temp->data != key)
        {
            count = 1;
            temp = temp->next;
        }
        if (count == 0)
        {
            InsertAtFront(value);
        }
        else
        {
            new_node->next = temp;
            temp->previous->next = new_node;
            new_node->previous = temp->previous;
            temp->previous = new_node;
            size++;
        }
    }

    void Display()
    {
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << "------->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void removeAtSpecificPosition(T key)
    {
        Node<T>* newPtr = head;
        while (newPtr != nullptr)
        {
            if (newPtr->data == key)
            {
                if (newPtr != head && newPtr != tail)
                {
                    newPtr->previous->next = newPtr->next;
                    newPtr->next->previous = newPtr->previous;
                }
                if (newPtr == head)
                {
                    RemoveAtHead();
                }
                if (newPtr == tail)
                {
                    RemoveAtTail();
                }
            }
            newPtr = newPtr->next;
        }
    }

    bool deleteDataWithIndex(int idx)
    {
        if (idx > size or idx < 0)
        {
            return false;
        }
        else if (idx == 0)
        {
            if (head == tail)
            {
                head = nullptr;
                tail = nullptr;
                size--;
            }
            else
            {
                head = head->next;
                size--;
            }
            return true;
        }
        else
        {
            Node<T>* temp = head;
            for (int i = 0; i < idx - 1; i++)
            {
                temp = temp->next;
            }
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            size--;
            return true;
        }
    }

    
};

