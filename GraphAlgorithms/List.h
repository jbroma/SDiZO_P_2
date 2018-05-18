#pragma once
#include <string>
#include <sstream>

class List {

private:
	
	class List_Node {
	
	public:
		List_Node * prev = nullptr;
		List_Node * next = nullptr;
		int value;
	};

	List_Node * head = nullptr;
	List_Node * tail = nullptr;
	int size = 0;

public:
	
	List();
	List(int * arr);
	~List();
	void pushFront(const int el);
	void pushBack(const int el);
	void insert(const int el, const int pos);
	int popFront();
	int popBack();
	int remove(const int pos);
	bool find(const int el);
	void setValue(const int new_num, const int pos);
	std::string to_string();
	int getSize();
	List::List_Node* getHead();
	List::List_Node* getTail();
};

