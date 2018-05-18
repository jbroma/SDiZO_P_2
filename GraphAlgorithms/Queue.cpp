#include "stdafx.h"
#include "Queue.h"

Queue::Queue() {
	this->list = new List();
}

Queue::~Queue() {
	delete this->list;
}

void Queue::enqueue(const int num) {
	this->list->pushFront(num);
}

int Queue::dequeue() {
	return this->list->popBack();
}

bool Queue::isEmpty() {
	return this->list->getSize() == 0 ? true : false;
}
