#pragma once
#include "List.h"

class Queue {

private:
	List * list;

public:
	Queue();
	~Queue();
	void enqueue(const int num);
	int dequeue();
};

