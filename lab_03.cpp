//
// Created by Aliaksandr Sharstniou.
//
#include <iostream>

template <class T>
struct Queue
{
public:
    void Enqueue(const T& value, float priority = 1.0f)
    {
        if (priority > 1.0f)
        {
            _priorityList.Add(priority, value);
        }
        else
        {
            _weightedLists.Add(priority, value);
        }
    };

    bool Dequeue(T& out)
    {
        bool result = false;
        if (_priorityList.Num() > 0)
        {
            out = _priorityList.Pop();
            result = true;
        }
        else if (_weightedLists.Num() > 0)
        {
            out = _weightedLists.Pop();
            result = true;
        }

        return result;
    };

    void Print()
    {
        std::cout << "Priority: "; _priorityList.Print();
        std::cout << "\n";
        std::cout << "Weighted: "; _weightedLists.Print();
    };

private:
    struct List
    {
    public:
        List() : _head(nullptr), _count(0) {};

        ~List()
        {
            ListItem* item = _head;
            while(item != nullptr)
            {
                ListItem* itemToDelete = item;
                item = item->next;
                delete itemToDelete;
            }
        };

        void Add(float priority, const T& value)
        {
            ListItem* item = new ListItem();
            item->priority = priority;
            item->value = value;
            if (_head != nullptr)
            {
                ListItem* prevItem = nullptr;
                ListItem* iterationItem = _head;
                while (iterationItem != nullptr)
                {
                    if (iterationItem->priority < priority)
                    {
                        break;
                    }
                    else
                    {
                        prevItem = iterationItem;
                        iterationItem = iterationItem->next;
                    }
                }

                if (prevItem != nullptr)
                {
                    item->next = prevItem->next;
                    prevItem->next = item;
                }
                else
                {
                    item->next = _head;
                    _head = item;
                }
            }
            else
            {
                _head = item;
            }

            ++_count;
        };

        T Pop()
        {
            ListItem* head = _head;
            _head = _head->next;
            T result = head->value;
            delete head;
            --_count;

            return result;
        };

        int Num() const
        {
            return _count;
        };

        void Print() const
        {
            ListItem* item = _head;
            while (item != nullptr)
            {
                std::cout << "P: " << item->priority << " V: " << item->value << " -> ";
                item = item->next;
            }
            std::cout << "nil";
        };

    private:
        struct ListItem
        {
            float priority;
            T value;
            ListItem* next;
        };

        ListItem* _head;
        int _count;
    };

    List _priorityList;
    List _weightedLists;
};

int main()
{
    std::cout << "Lab 03\n\n";

    Queue<float> q;
    q.Enqueue(100.0f);
    q.Enqueue(200.0f);
    q.Enqueue(300.0f);
    q.Enqueue(400.0f);
    q.Enqueue(1000.0f, 2.0f);
    q.Enqueue(2000.0f, 3.0f);
    q.Enqueue(3000.0f, 4.0f);
    q.Enqueue(4000.0f, 2.0f);

    std::cout << "Current queue: \n";
    q.Print();

    std::cout << "\nProcessing: \n";
    float value;
    while (q.Dequeue(value))
    {
        std::cout << "\tV: " << value << "\n";
    }

    return 0;
}