//
// Created by Aliaksandr Sharstniou.
//
#include <iostream>
#include <cmath>

#define MakePolynomialItem(p, n, a) p = AddToPolynomialList(p, n, a)

struct PolynomialListItem
{
public:
    PolynomialListItem() : PolynomialListItem(0, 0) {};
    PolynomialListItem(int n, int a) : n(n), a(a), next(nullptr) {};

    int n;
    int a;
    PolynomialListItem* next;
};

PolynomialListItem* FindPolynomialListItem(PolynomialListItem* head, int n);
PolynomialListItem* AddToPolynomialList(PolynomialListItem* head, int n, int a);
void ClearPolynomialList(PolynomialListItem* head);
void PrintPolynomialList(PolynomialListItem* head);

bool CheckEquality(PolynomialListItem* pHead, PolynomialListItem* qHead);

bool Equality(PolynomialListItem* pHead, PolynomialListItem* qHead);
int Meaning(PolynomialListItem* head, int x);
PolynomialListItem* Add(PolynomialListItem* pHead, PolynomialListItem* qHead);

int main()
{
    std::cout << "Lab 01\n\n";

    const int PolynomialCount = 5;
    PolynomialListItem* p[PolynomialCount] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    PolynomialListItem* q[PolynomialCount] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    int x[PolynomialCount];

    MakePolynomialItem(p[0], 0, 2);  MakePolynomialItem(p[0], 1, -1); MakePolynomialItem(p[0], 2, 3);  MakePolynomialItem(p[0], 4, 7);
    MakePolynomialItem(p[1], 0, 6);  MakePolynomialItem(p[1], 1, 1);  MakePolynomialItem(p[1], 4, -5); MakePolynomialItem(p[1], 7, -8);
    MakePolynomialItem(p[2], 0, -9); MakePolynomialItem(p[2], 1, -1); MakePolynomialItem(p[2], 2, 2);  MakePolynomialItem(p[2], 3, 6);
    MakePolynomialItem(p[3], 0, 3);  MakePolynomialItem(p[3], 1, 1);  MakePolynomialItem(p[3], 5, -4); MakePolynomialItem(p[3], 6, -9);
    MakePolynomialItem(p[4], 0, 4);  MakePolynomialItem(p[4], 1, -1); MakePolynomialItem(p[4], 4, 7);  MakePolynomialItem(p[4], 5, 3);

    MakePolynomialItem(q[0], 0, -6); MakePolynomialItem(q[0], 1, 1);  MakePolynomialItem(q[0], 3, 2);  MakePolynomialItem(q[0], 5, -2);
    MakePolynomialItem(q[1], 0, -5); MakePolynomialItem(q[1], 1, 1);  MakePolynomialItem(q[1], 2, 5);  MakePolynomialItem(q[1], 4, 3);
    MakePolynomialItem(q[2], 0, 2);  MakePolynomialItem(q[2], 1, 1);  MakePolynomialItem(q[2], 4, -4); MakePolynomialItem(q[2], 6, -7);
    MakePolynomialItem(q[3], 0, -4); MakePolynomialItem(q[3], 1, -1); MakePolynomialItem(q[3], 8, 5);  MakePolynomialItem(q[3], 9, 6);
    MakePolynomialItem(q[4], 0, -4); MakePolynomialItem(q[4], 1, 1);  MakePolynomialItem(q[4], 5, 8);  MakePolynomialItem(q[4], 7, -4);

    x[0] = 3; x[1] = 4; x[2] = 2; x[3] = 5; x[4] = 7;

    for (int i = 0; i < PolynomialCount; i++)
    {
        std::cout << "P(x)="; PrintPolynomialList(p[i]);
        std::cout << "  ";
        std::cout << "Q(x)="; PrintPolynomialList(q[i]);

        std::cout << "\n";
        std::cout << "Equality(p, q)=" << (Equality(p[i], q[i]) ? "Yes" : "No") << "\n";
        std::cout << "Meaning(p, " << x[i] << ")=" << Meaning(p[i], x[i]) << "  ";
        std::cout << "Meaning(q, " << x[i] << ")=" << Meaning(q[i], x[i]) << "\n";

        PolynomialListItem* r = Add(p[i], q[i]);
        std::cout << "Add(p, q)="; PrintPolynomialList(r); std::cout << "\n";

        std::cout << "\n";

        ClearPolynomialList(p[i]);
        ClearPolynomialList(q[i]);
        ClearPolynomialList(r);
    }

    return 0;
}

PolynomialListItem* FindPolynomialListItem(PolynomialListItem* head, int n)
{
    PolynomialListItem* result = nullptr;
    PolynomialListItem* item = head;
    while (item != nullptr)
    {
        if (item->n == n)
        {
            result = item;
            break;
        }

        item = item->next;
    }

    return result;
}

PolynomialListItem* AddToPolynomialList(PolynomialListItem* head, int n, int a)
{
    if (head == nullptr)
    {
        return new PolynomialListItem(n, a);
    }

    PolynomialListItem* newHead = FindPolynomialListItem(head, n);
    if (newHead == nullptr)
    {
        newHead = new PolynomialListItem(n, a);
    }
    else
    {
        newHead->a += a;
    }

    newHead->next = head;
    return newHead;
}

void ClearPolynomialList(PolynomialListItem* head)
{
    PolynomialListItem* item = head;
    while (item != nullptr)
    {
        PolynomialListItem* itemToDelete = item;
        item = item->next;

        delete itemToDelete;
    }
}

void PrintPolynomialList(PolynomialListItem* head)
{
    PolynomialListItem* item = head;
    while (item != nullptr)
    {
        if (item->a > 0.0f && item != head)
        {
            std::cout << "+";
        }

        if (item->a == -1.0f)
        {
            std::cout << "-";
        }
        else
        {
            std::cout << item->a;
        }

        if (item->n > 1)
        {
            std::cout << "x^" << item->n;
        }
        else if (item->n == 1)
        {
            std::cout << "x";
        }

        item = item->next;
    }
}

bool CheckEquality(PolynomialListItem* pHead, PolynomialListItem* qHead)
{
    bool result = true;
    PolynomialListItem* pItem = pHead;
    while (pItem != nullptr)
    {
        PolynomialListItem* qItem = FindPolynomialListItem(qHead, pItem->n);
        if (qItem == nullptr || qItem->a != pItem->a)
        {
            result = false;
            break;
        }

        pItem = pItem->next;
    }

    return result;
}

bool Equality(PolynomialListItem* pHead, PolynomialListItem* qHead)
{
    return CheckEquality(pHead, qHead) && CheckEquality(qHead, pHead);
}

int Meaning(PolynomialListItem* head, int x)
{
    int result = 0;
    PolynomialListItem* item = head;
    while (item != nullptr)
    {
        result += item->a * std::pow(x, item->n);
        item = item->next;
    }

    return result;
}

PolynomialListItem* Add(PolynomialListItem* pHead, PolynomialListItem* qHead)
{
    PolynomialListItem* result = nullptr;

    PolynomialListItem* item = pHead;
    while (item != nullptr)
    {
        int a = item->a;
        PolynomialListItem* qItem = FindPolynomialListItem(qHead, item->n);
        if (qItem != nullptr)
        {
            a += qItem->a;
        }

        if (a != 0.0f)
        {
            result = AddToPolynomialList(result, item->n, a);
        }

        item = item->next;
    }

    item = qHead;
    while (item != nullptr)
    {
        PolynomialListItem* pItem = FindPolynomialListItem(pHead, item->n);
        if (pItem == nullptr)
        {
            result = AddToPolynomialList(result, item->n, item->a);
        }
        item = item->next;
    }

    return result;
}
