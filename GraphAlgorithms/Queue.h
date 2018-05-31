#pragma once
#include "List.h"

template <typename Type>
class Queue {

private:
	List<Type> * list;

public:
	Queue() { this->list = new List<Type>(); };
	~Queue() { delete this->list; };
	void enqueue(Type data) { this->list->pushFront(data); };
	Type dequeue() { return this->list->popBack(); };
	bool isEmpty() { return this->list->getSize() == 0 ? true : false; };
};


