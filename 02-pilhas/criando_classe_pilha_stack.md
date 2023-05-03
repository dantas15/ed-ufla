# Pilha

## Criando uma classe para a pilha

- Usei o [`template<>`](https://en.cppreference.com/w/cpp/language/templates) para que a classe possa receber qualquer tipo de dado (generics)

```cpp
#include <iostream>

using namespace std;

const int DEFAULT_MAX_STACK_SIZE = 10;
const int EMPTY_STACK = -1;

const string EMPTY_STACK_ERROR = "Erro: pilha vazia!";

struct Item
{
  string nome;
  char tipo;
  int valor;
};

template <class T, int capacity = DEFAULT_MAX_STACK_SIZE>
class Stack
{
private:
  T *pool;
  int top;

public:
  Stack()
  {
    pool = new T[capacity];
    top = EMPTY_STACK;
  }
  ~Stack()
  {
    delete[] pool;
  }
  void clear()
  {
    top = EMPTY_STACK;
  }
  bool isEmpty()
  {
    return top == EMPTY_STACK;
  }
  bool isFull()
  {
    return top == capacity - 1;
  }
  T topEl()
  {
    if (isEmpty())
    {
      throw runtime_error(EMPTY_STACK_ERROR)
    }

    return pool[this->top];
  }
  T pop()
  {
    if (isEmpty())
    {
      throw runtime_error(EMPTY_STACK_ERROR)
    }

    Item poppedEl = pool[this->top];
    this->top--;
    return poppedEl;
  }
  void push(const T &data)
  {
    if (isFull())
    {
      throw runtime_error("Stack overflow!")
    }
    pool[++this->top] = data;
  }
};```
