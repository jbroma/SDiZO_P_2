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
	
	void push_front(const int el);
	void push_back(const int el);
	void insert(const int el, const int pos);
	void remove_front();
	void remove_back();
	void remove(const int pos);
	bool find(const int el);
	void set_num(const int new_num, const int pos);
	std::string to_string();
	int get_size();
	List::List_Node* get_head();
	List::List_Node* get_tail();
	List();
	List(int * arr);
	~List();
};

