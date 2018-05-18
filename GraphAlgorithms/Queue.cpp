#include "stdafx.h"
#include "Queue.h"

Queue::Queue() {
	this->list = new List();
}

Queue::~Queue() {
	delete list;
}

void Queue::enqueue(const int num) {
	this->list->pushFront(num);
}

int Queue::dequeue() {
	this->list->popBack();
}
