#ifndef STACK_HXX
#define STACK_HXX
#pragma once
#include <stdlib.h>
#include <stdexcept>

template<typename T, int N>
class stack
{
private:
    int topElem;
    T* arr;
    int cap;
public:
    stack();
    stack(const stack& s);
	stack(stack&& s);
    ~stack();
    template<class U>
    void push(U&& x);
    T pop();
    T& top();
    int size();
    bool isEmpty();
    stack& operator=(const stack& s);
	stack& operator=(stack&& s);
};


template<typename T, int N>
inline stack<T, N>::stack() : topElem(-1), cap(0)
{
    arr = new T[N];
}

template<typename T, int N>
inline stack<T, N>::stack(const stack& s) : arr(s.arr), cap(s.cap), topElem(s.topElem)
{
}

template<typename T, int N>
inline stack<T, N>::stack(stack&& s) : arr(std::move(s.arr)), cap(std::move(s.cap)), topElem(std::move(topElem))
{
}

template<class T, int N>
inline stack<T, N>::~stack(){
    delete[] arr;
}

template<typename T, int N>
inline T stack<T, N>::pop(){
    if(isEmpty()){
        throw std::out_of_range("EMPTY");
    }

    return arr[topElem--];
}

template<typename T, int N>
inline T& stack<T, N>::top(){
    if(!isEmpty()){
        return arr[topElem];
    }
}
template<typename T, int N>
inline int stack<T, N>::size(){
    return cap;
}
template<typename T, int N>
inline bool stack<T, N>::isEmpty(){
    return cap == 0;
}
template<typename T, int N>
template<class U>
inline void stack<T, N>::push(U&& x){
    if(cap == N){
        throw std::out_of_range("push() : too many objects to push!");
    }
    ++cap;
    arr[++topElem] = std::move(x);
}
template<typename T, int N>
inline stack<T, N>& stack<T, N>::operator=(stack<T, N>&& s){
    if(this==&s){
        return *this;
    }

    arr = std::move(s.arr);
    cap = std::move(s.cap);
    topElem = std::move(s.topElem);
}


template<typename T, int N>
inline stack<T, N>& stack<T, N>::operator=(const stack<T, N>& s){
    if(this==&s){
        return *this;
    }

    arr = s.arr;
    cap = s.cap;
    topElem = s.topElem;
}

#endif