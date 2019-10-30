#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;
public:
  TStack(int _size)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }
  int GetTop() {  return top; }
  int GetSize() { return size; }

  bool empty() {
	  return top == -1;
  }

  bool full() {
	  return top == size;
  }

  void push(const T val) {
	  if (full() == 1)
		  throw 1;
	  pMem[++top] = val;
  }

   T pop() {
	  if (empty() == 1)
		  throw 1;
	  return  pMem[top--];
  }
   T gettop() {
	   if (empty() == 1)
		   throw 1;
	   return  pMem[top];
   }

  ~TStack()
  {
    delete [] pMem;
  }
};

#endif
