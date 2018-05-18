#include "stdafx.h"
#include "List.h"

List::List() {
}

List::List(int * arr) {
	for (int i = 1; i < arr[0] + 1; i++) {
		this->pushBack(arr[i]);
	}
}

List::~List() {
	while (this->size) {
		this->popFront();
	}
}

int List::getSize() {
	return this->size;
}

List::List_Node * List::getHead() {
	return this->head;
}

List::List_Node * List::getTail() {
	return this->tail;
}

void List::pushFront(const int el) {
	List_Node * new_node = new List_Node();
	new_node->value = el;
	if (this->head)
		this->head->prev = new_node;
	else
		this->tail = new_node;
	new_node->next = this->head;
	this->head = new_node;
	this->size++;
}

void List::pushBack(const int el) {
	List_Node * new_node = new List_Node();
	new_node->value = el;
	if (this->tail)
		this->tail->next = new_node;
	else
		this->head = new_node;
	new_node->prev = this->tail;
	this->tail = new_node;
	this->size++;
}

void List::insert(const int el, const int pos) {
	if (pos == 0) {
		this->pushFront(el);
		return;
	}
	if (pos == this->size) {
		this->pushBack(el);
		return;
	}
	if (pos > this->size || pos < 0) 
		throw std::invalid_argument("Specified position is invalid.\n");
	List_Node * new_node = new List_Node();
	new_node->value = el;
	List_Node * it;
	int current_pos;
	
	if ((this->size - pos) > (this->size / 2)) {
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

int List::popFront() {
	if (!this->head)
		throw  std::invalid_argument("The list is empty\n");
	List_Node * element = this->head;
	if (element->next)
		element->next->prev = nullptr;
	else
		this->tail = nullptr;
	this->head = element->next;
	int value = element->value;
	delete element;
	this->size--;
	return value;
}

int List::popBack() {
	if (this->size == 0)
		throw  std::invalid_argument("The list is empty\n");
	List_Node * element = this->tail;
	if (element->prev)
		element->prev->next = nullptr;
	else
		this->head = nullptr;
	this->tail = element->prev;
	int value = element->value;
	delete element;
	this->size--;
	return value;
}

int List::remove(const int pos) {
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
	if ((this->size - pos) > (this->size / 2)) {
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
	int value = it->value;
	delete it;
	this->size--;
	return value;
}

bool List::find(const int el) {
	List_Node * it = this->head;								
	while (it) {													
		if (it->value == el)									
			return true;										
		it = it->next;											
	}
	return false;												
}

void List::setValue(const int new_num, const int pos) {
	if (pos < 0 || pos >= this->size)
		throw std::invalid_argument("Nie mozna zmienic elementu na zadanej pozycji (out of range)");
	List_Node * it = this->head;								// ustawiam 'iterator' na poczatek listy
	for (int i = 0; i < pos; i++)
		it = it->next;
	it->value = new_num;
}

std::string List::to_string() {
	if (this->size == 0) {
		return "The list is empty.\n";
	}
	std::stringstream ss;
	ss << "List elements:\n";
	List_Node * it = this->head;								// ustawiam 'iterator' na poczatek listy
	int i = 0;													// licznik dla numerow porzadkowych elementow
	while (it != nullptr) {
		ss << "El " << i << ": " << it->value << "\n";
		it = it->next;											// ustawiam 'iterator' na kolejny element listy
		i++;													// zwiekszam licznik
	}
	return ss.str();											// konwersja strinstream na pojedynczy lancuch znakow
}


