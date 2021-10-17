#ifndef QUEUE_HXX
#define QUEUE_HXX
#pragma once
#include <stdlib.h>
#include <stdexcept>
#include <array>
#include <iostream>

template<typename T, int N>
class Queue
{
private:
    std::array<T, N> data;
    int cap;
    int frontptr;    
    int rear;     
public:
    Queue();
    Queue(const Queue& q);
	Queue(Queue&& q);
    ~Queue();
    template<class U>
    void push(U&& x);
    T pop();
    T& front();
    int size();
    bool isEmpty();
    Queue& operator=(const Queue& q);
	Queue& operator=(Queue&& q);
};

template<typename T, int N>
inline Queue<T, N>& Queue<T, N>::operator=(const Queue& q){
    if(this == &q){
        return *this;
    }
    data = q.data;
    cap = q.cap;
    frontptr = q.frontptr;
    rear = q.rear;
}

template<typename T, int N>
inline Queue<T, N>& Queue<T, N>::operator=(Queue&& q){
    if(this == &q){
        return *this;
    }

    data = std::move(q.data);
    cap = std::move(q.cap);
    frontptr = std::move(q.frontptr);
    rear = std::move(q.rear);
}

template<typename T, int N>
inline Queue<T, N>::Queue() : cap(0), frontptr(0), rear(0)
{
}

template<typename T, int N>
inline Queue<T, N>::Queue(const Queue& q) : data(q.data), cap(q.cap), frontptr(q.frontptr), rear(q.rear)
{
}

template<typename T, int N>
inline Queue<T, N>::Queue(Queue&& q) : data(std::move(q.data)), cap(std::move(q.cap)), frontptr(std::move(q.frontptr)), rear(std::move(q.rear))
{
}

template<typename T, int N>
inline Queue<T, N>::~Queue()
{
}

template<typename T, int N>
template<class U>
inline void Queue<T, N>::push(U&& x)
{
    if (size() == N)
    {
        throw std::out_of_range("push() : too many objects!");
    }
    cap++;
    data.at(frontptr) = std::move(x);
    ++frontptr;
    if(frontptr == N){
        frontptr = 0;
    }

}

template<typename T, int N>
inline T Queue<T, N>::pop()
{
    if(isEmpty()){
        throw std::out_of_range("EMPTY QUEUE");
    }
    if(rear == N){
        rear = 0;
    }
    --cap;
    // T value = std::move(data.at(rear));


    return std::move(data.at(rear++));
}

template<typename T, int N>
inline T& Queue<T, N>::front()
{
    if(isEmpty()){
        throw std::out_of_range("front(): EMPTY QUEUE");
    }
    
    return data.at(rear);
}

template<typename T, int N>
inline int Queue<T, N>::size()
{
    return cap;
}

template<typename T, int N>
inline bool Queue<T, N>::isEmpty()
{
    return cap == 0;
}



#endif