#pragma once
#include "List.h"

class Stack {

private:
	List * list;

public:
	Stack();
	~Stack();
	void push(const int num);
	int pop();
	bool isEmpty();
};

