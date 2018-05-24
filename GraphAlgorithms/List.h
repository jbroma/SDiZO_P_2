#pragma once
#include <string>
#include <sstream>

template <typename Type>
class List {

private:
	class List_Node;
	List_Node * head = nullptr;
	List_Node * tail = nullptr;
	int size = 0;

public:
	List();
	~List();
	void pushFront(Type * new_data);
	void pushBack(Type * new_data);
	void insert(Type * new_data, int pos);
	Type * popFront();
	Type * popBack();
	Type * remove(int pos);
	bool find(Type * data);
	void setValue(Type * new_data, int pos);
	int getSize();
	List<Type>::List_Node * getHead();
	List<Type>::List_Node * getTail();
};

// ---------------------------
// Nested List_Node definition
// ---------------------------

template <typename Type>
class List<Type>::List_Node {
	
public:
	List_Node * prev = nullptr;
	List_Node * next = nullptr;
	Type * value;
};

// ----------------------------
// Member functions definitions
// ----------------------------

template <typename Type>
List<Type>::List() {
}

template <typename Type>
List<Type>::~List() {
	while (this->size) {
		this->popFront();
	}
}

template <typename Type>
int List<Type>::getSize() {
	return this->size;
}

template <typename Type>
typename List<Type>::List_Node * List<Type>::getHead() {
	return this->head;
}

template <typename Type>
typename List<Type>::List_Node * List<Type>::getTail() {
	return this->tail;
}

template <typename Type>
void List<Type>::pushFront(Type * new_data) {
	List_Node * new_node = new List_Node();
	new_node->value = new_data;
	if (this->head)
		this->head->prev = new_node;
	else
		this->tail = new_node;
	new_node->next = this->head;
	this->head = new_node;
	this->size++;
}

template <typename Type>
void List<Type>::pushBack(Type * new_data) {
	List_Node * new_node = new List_Node();
	new_node->value = new_data;
	if (this->tail)
		this->tail->next = new_node;
	else
		this->head = new_node;
	new_node->prev = this->tail;
	this->tail = new_node;
	this->size++;
}

template <typename Type>
void List<Type>::insert(Type * new_data, int pos) {
	if (pos == 0) {
		this->pushFront(value);
		return;
	}
	if (pos == this->size) {
		this->pushBack(value);
		return;
	}
	if (pos > this->size || pos < 0)
		throw std::invalid_argument("Specified position is invalid.\n");
	List_Node * new_node = new List_Node();
	new_node->value = new_data;
	List_Node * it;
	int current_pos;

	if ((this->size - pos) >(this->size / 2)) {
		current_pos = 0;
		it = this->head;
		while (current_pos != pos) {
			it = it->next;
			current_pos++;
		}
	}
	else {
		current_pos = this->size - 1;
		it = this->tail;
		while (current_pos != pos) {
			it = it->prev;
			current_pos--;
			delete it->next;
		}
	}
	new_node->next = it;
	new_node->prev = it->prev;
	it->prev->next = new_node;
	it->prev = new_node;
	this->size++;
}

template <typename Type>
Type * List<Type>::popFront() {
	if (!this->head)
		throw  std::invalid_argument("The list is empty\n");
	List_Node * element = this->head;
	if (element->next)
		element->next->prev = nullptr;
	else
		this->tail = nullptr;
	this->head = element->next;
	Type * value = element->value;
	delete element;
	this->size--;
	return value;
}

template <typename Type>
Type * List<Type>::popBack() {
	if (this->size == 0)
		throw  std::invalid_argument("The list is empty\n");
	List_Node * element = this->tail;
	if (element->prev)
		element->prev->next = nullptr;
	else
		this->head = nullptr;
	this->tail = element->prev;
	Type * value = element->value;
	delete element;
	this->size--;
	return value;
}

template <typename Type>
Type * List<Type>::remove(int pos) {
	if (pos == 0) {
		this->popFront();
		return;
	}
	if (pos == this->size - 1) {
		this->popBack();
		return;
	}
	if (pos >= this->size || pos < 0)
		throw std::invalid_argument("Specified position is invalid\n");
	List_Node * it;
	int i;
	if ((this->size - pos) >(this->size / 2)) {
		i = 0;
		it = this->head;
		while (i != pos) {
			it = it->next;
			i++;
		}
	}
	else {
		i = this->size - 1;
		it = this->tail;
		while (i != pos) {
			it = it->prev;
			i--;
		}
	}
	it->next->prev = it->prev;
	it->prev->next = it->next;
	Type * value = it->value;
	delete it;
	this->size--;
	return value;
}

template <typename Type>
bool List<Type>::find(Type * el) {
	List_Node * it = this->head;
	while (it) {
		if (it->value == el)
			return true;
		it = it->next;
	}
	return false;
}

template <typename Type>
void List<Type>::setValue(Type * new_data, int pos) {
	if (pos < 0 || pos >= this->size)
		throw std::invalid_argument("Specified position is invalid");
	List_Node * it = this->head;
	for (int i = 0; i < pos; i++)
		it = it->next;
	it->value = new_data;
}

