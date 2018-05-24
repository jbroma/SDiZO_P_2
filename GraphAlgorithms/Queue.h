#pragma once
#include "List.h"

template <typename Type>
class Queue {

private:
	List<Type> * list;

public:
	Queue();
	~Queue();
	void enqueue(const Type * num);
	Type * dequeue();
	bool isEmpty();
};

// ----------------------------
// Member functions definitions
// ----------------------------

template <typename Type>
Queue<Type>::Queue() {
	this->list = new List<Type>();
}

template <typename Type>
Queue<Type>::~Queue() {
	delete this->list;
}

template <typename Type>
void Queue<Type>::enqueue(const Type * num) {
	this->list->pushFront(num);
}

template <typename Type>
Type * Queue<Type>::dequeue() {
	return this->list->popBack();
}

template <typename Type>
bool Queue<Type>::isEmpty() {
	return this->list->getSize() == 0 ? true : false;
}

