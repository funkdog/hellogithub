#include <iostream>
#include <string>
#include <utility>
using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T>
class Stack
{
  public:
    Stack() : theSize{0}, theCapacity{16}
    {
        objects = new T[theCapacity];
    }

    ~Stack()
    {
        delete[] objects;
    }

    void push(T &&x)
    {
        if (theSize == theCapacity)
            resize(2 * theCapacity + 1);
        objects[theSize++] = std::move(x);
    }

    void push(const T &x)
    {
        if (theSize == theCapacity)
            resize(2 * theCapacity + 1);
        objects[theSize++] = x;
    }

    void pop()
    {
        if (!empty())
            --theSize;
    }

    void popall()
    {
        theSize = 0;
    }

    int size()
    {
        return theSize;
    }

    const T &top()
    {
        return objects[theSize - 1];
    }

    void resize(int newCapacity)
    {
        if (newCapacity < theSize)
            return;

        T *newArray = new T[newCapacity];
        for (int k = 0; k < theSize; k++)
            newArray[k] = std::move(objects[k]);

        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[] newArray;
    }

    bool empty()
    {
        return theSize == 0;
    }

    typedef T *iterator;

    iterator begin()
    {
        return &objects[0];
    }

    iterator end()
    {
        return &objects[theSize];
    }

  private:
    int theSize;
    int theCapacity;
    T *objects;
};

struct Queen
{
    int row;
    int col;
};

Stack<Queen> queen;

bool isAvailable(int row, int col)
{
    for (auto &queen : queen)
        if (queen.col == col || queen.row == row ||
            abs(queen.col - col) == abs(queen.row - row))
            return false;
    return true;
}

void print(int N)
{
    for (auto &queen : queen)
    {
        cout << "   ";
        for (int i = 1; i <= queen.col - 1; i++)
            cout << "[]";
        cout << "XX";
        for (int i = 1; i <= N - queen.col; i++)
            cout << "[]";
        cout << endl;
    }
    cout << endl;
}

void Solve(int N)
{
    int row = 1, col = 1;
    while (row > 0)
    {
        while (col <= N)
        {
            if (row == N + 1)
            {
                print(N);
                return;
            }
            if (isAvailable(row, col))
            {
                queen.push(Queen{row, col});
                row++;
                col = 1;
            }
            else
                col++;
        }
        col = queen.top().col + 1;
        queen.pop();
        row--;
    }
}

int main()
{
    for (int i = 5; i <= 12; i++)
    {
        Solve(i);
        queen.popall();
    }
    return 0;
}