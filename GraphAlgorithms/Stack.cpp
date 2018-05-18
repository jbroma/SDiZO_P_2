#include "stdafx.h"
#include "Stack.h"


Stack::Stack() {
	this->list = new List();
}

Stack::~Stack() {
	delete this->list;
}

//Consider exceptions
void Stack::push(const int num) {
	this->list->pushBack(num);
}

//Consider exceptions
int Stack::pop() {
	return this->list->popBack();
}

bool Stack::isEmpty() {
	return this->list->getSize() == 0 ? true : false;
}
