#pragma once
#include "List.h"

template <typename Type>
class Stack {

private:
	List<Type> * list;

public:
	Stack() { this->list = new List<Type>(); };
	~Stack() { delete this->list; };
	void push(const Type * data) { this->list->pushBack(num); };
	Type* pop() { return this->list->popBack(); };
	bool isEmpty() { return this->list->getSize() == 0 ? true : false; };
};


