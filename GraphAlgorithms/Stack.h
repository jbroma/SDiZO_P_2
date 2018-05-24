#pragma once
#include "List.h"

template <typename Type>
class Stack {

private:
	List<Type> * list;

public:
	Stack();
	~Stack();
	void push(const Type * data);
	Type * pop();
	bool isEmpty();
};

// ----------------------------
// Member functions definitions
// ----------------------------

template <typename Type>
Stack<Type>::Stack() {
	this->list = new List<Type>();
}

template <typename Type>
Stack<Type>::~Stack() {
	delete this->list;
}

//Consider exceptions
template <typename Type>
void Stack<Type>::push(const Type * data) {
	this->list->pushBack(num);
}

//Consider exceptions
template <typename Type>
Type * Stack<Type>::pop() {
	return this->list->popBack();
}

template <typename Type>
bool Stack<Type>::isEmpty() {
	return this->list->getSize() == 0 ? true : false;
}

