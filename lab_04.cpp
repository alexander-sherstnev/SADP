//
// Created by Aliaksandr Sharstniou.
//
#include <iostream>


#define MAX_STACK_SIZE 50

struct Stack
{
public:
    Stack() : _top(0) {};

    bool Empty() const
    {
        return _top == 0;
    }

    void Push(const char value)
    {
        if (_top == MAX_STACK_SIZE)
        {
            std::cout << "Stack overflow exception.\n";
            return;
        }

        _values[_top++] = value;
    };

    char Pop()
    {
        if (Empty())
        {
            std::cout << "Illegal operation. Stack is empty.\n";
            return 0;
        }

        return _values[--_top];
    };

private:
    char _values[MAX_STACK_SIZE];
    int _top;
};

class Converter
{
public:
    Converter(char* infix)
    {
        int i = 0;
        while (infix[i] != '\0')
        {
            _infix[i] = infix[i];
            i++;
        }

        _Prefix();
    }

    void Print() const
    {
        std::cout << "Infix:   " << _infix << "\n";
        std::cout << "Postfix: " << _postfix << "\n";
        std::cout << "Prefix:  " << _prefix << "\n";
    }

private:
    void _Prefix()
    {
        Stack s;
        for (int i = 0; _infix[i] != '\0'; i++) { s.Push(_infix[i]); }

        int i = 0;
        int length = 0;
        while(!s.Empty())
        {
            char v = s.Pop();
            if (v == '(') { v = ')'; }
            else if (v == ')') { v = '('; }
            else { length++; }

            _infixReverse[i++] = v;
        }
        _infixReverse[i] = '\0';
        _Postfix();

        for (int i = length - 1, j = 0; i >= 0; i--, j++)
        {
            _prefix[j] = _postfix[i];
        }
    };

    void _Postfix()
    {
        int postfixTop = 0;
        Stack s;
        s.Push('\0');
        for (int i = 0; _infixReverse[i] != '\0'; i++)
        {
            char current = _infixReverse[i];
            if (current == '(')
            {
                s.Push(current);
                continue;
            }

            if (current == ')')
            {
                char popped = s.Pop();
                while (popped != '(')
                {
                    _postfix[postfixTop++] = popped;
                    popped = s.Pop();
                }
                continue;
            }

            if (current == '+' || current == '-')
            {
                char popped = s.Pop();
                if (popped == '\0' || popped == '(')
                {
                    s.Push(popped);
                    s.Push(current);
                }
                else if (popped == '+' || popped == '-' || popped == '*' || popped == '/')
                {
                    _postfix[postfixTop++] = popped;
                    s.Push(current);
                }
                continue;
            }

            if (current == '*' || current == '/')
            {
                char popped =s.Pop();
                if (popped == '\0' || popped == '(' || popped == '+' || popped == '-')
                {
                    s.Push(popped);
                    s.Push(current);
                }

                if (popped == '*' || popped == '/')
                {
                    _postfix[postfixTop++] = popped;
                    s.Push(current);
                }
                continue;
            }
            else
            {
                _postfix[postfixTop++] = current;
            }
        }

        char popped = s.Pop();
        while (popped != '\0')
        {
            _postfix[postfixTop++] = popped;
            popped = s.Pop();
        }
    }

    char _infix[MAX_STACK_SIZE * 2];
    char _infixReverse[MAX_STACK_SIZE * 2];
    char _postfix[MAX_STACK_SIZE * 2];
    char _prefix[MAX_STACK_SIZE * 2];
};


int main()
{
    std::cout << "Lab 04\n\n";
    Converter c("a+b/c-(d*g-h)");
    c.Print();

    return 0;
}
