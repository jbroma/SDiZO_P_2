#pragma once
#include <string>
#include <sstream>

template <typename Type>
class List {

private:
	class List_Node;
	class List_Iterator;
	List_Node * head = nullptr;
	List_Node * tail = nullptr;
	int size = 0;

public:
	List();
	~List();
	void pushFront(Type new_data);
	void pushBack(Type new_data);
	void insert(Type new_data, int pos);
	Type popFront();
	Type popBack();
	Type remove(int pos);
	int getSize();

	List_Iterator begin();
	List_Iterator end();
	List_Iterator rbegin();
	List_Iterator rend();
};

// ---------------------------
// Nested List_Node definition
// ---------------------------

template <typename Type>
class List<Type>::List_Node {
	
public:
	List_Node * prev = nullptr;
	List_Node * next = nullptr;
	Type data;
};

// -------------------------------
// Nested List_Iterator definition
// -------------------------------

template <typename Type>
class List<Type>::List_Iterator {

private:
	List_Node *pos;

public:
	List_Iterator(List_Node *p = nullptr) : pos(p) {}

	Type& operator*() { 
		return pos->data; 
	}

	Type* operator->() { 
		return &(pos->data);
	}

	bool operator!=(const List_Iterator &other) { 
		return this->pos != other.pos;
	}

	List_Iterator& operator++() {
		pos = pos->next;
		return *this;
	}

	List_Iterator operator++(int unused) { 
		List_Iterator tmp(*this);
		++(*this);
		return tmp;
	}

	List_Iterator& operator--() {
		pos = pos->prev;
		return *this;
	}

	List_Iterator operator--(int) {
		List_Iterator tmp(*this);
		++(*this);
		return tmp;
	}
};

// ----------------------------
// Member functions definitions
// ----------------------------

template <typename Type>
List<Type>::List() {
}

template <typename Type>
List<Type>::~List() {
	while (this->size)
		popFront();
}

template <typename Type>
int List<Type>::getSize() {
	return this->size;
}

template <typename Type>
void List<Type>::pushFront(Type new_data) {
	List_Node * new_node = new List_Node();
	new_node->data = new_data;
	if (this->head)
		this->head->prev = new_node;
	else
		this->tail = new_node;
	new_node->next = this->head;
	this->head = new_node;
	this->size++;
}

template <typename Type>
void List<Type>::pushBack(Type new_data) {
	List_Node * new_node = new List_Node();
	new_node->data = new_data;
	if (this->tail)
		this->tail->next = new_node;
	else
		this->head = new_node;
	new_node->prev = this->tail;
	this->tail = new_node;
	this->size++;
}

template <typename Type>
void List<Type>::insert(Type new_data, int pos) {
	if (pos > this->size || pos < 0)
		throw std::invalid_argument("Specified position is invalid.\n");
	List_Node * new_node = new List_Node();
	new_node->data = new_data;
	List_Node * it;
	int current_pos;

	if ((this->size - pos) >=(this->size / 2)) {
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
Type List<Type>::popFront() {
	if (!this->head)
		throw  std::invalid_argument("The list is empty\n");
	List_Node * element = this->head;
	if (element->next)
		element->next->prev = nullptr;
	else
		this->tail = nullptr;
	this->head = element->next;
	Type data = element->data;
	delete element;
	this->size--;
	return data;
}

template <typename Type>
Type List<Type>::popBack() {
	if (this->size == 0)
		throw  std::invalid_argument("The list is empty\n");
	List_Node * element = this->tail;
	if (element->prev)
		element->prev->next = nullptr;
	else
		this->head = nullptr;
	this->tail = element->prev;
	Type data = element->data;
	delete element;
	this->size--;
	return data;
}

template <typename Type>
Type List<Type>::remove(const int pos) {
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
	Type data = it->data;
	delete it;
	this->size--;
	return data;
}

template <typename Type>
typename List<Type>::List_Iterator List<Type>::begin() {
	return List_Iterator(this->head);
}

template <typename Type>
typename List<Type>::List_Iterator List<Type>::end() {
	return List_Iterator();
}

template <typename Type>
typename List<Type>::List_Iterator List<Type>::rbegin() {
	return List_Iterator(this->tail);
}

template <typename Type>
typename List<Type>::List_Iterator List<Type>::rend() {
	return List_Iterator();
}


