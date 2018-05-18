#include "stdafx.h"
#include "List.h"


int List::get_size()
{
	return this->size;
}

List::List_Node * List::get_head()
{
	return this->head;
}

List::List_Node * List::get_tail()
{
	return this->tail;
}

void List::push_front(const int el)
{
	List_Node * newElement = new List_Node();
	newElement->value = el;
	if (this->head)
		this->head->prev = newElement;
	else
		this->tail = newElement;
	newElement->next = this->head;
	this->head = newElement;
	this->size++;
}

void List::push_back(const int el)
{
	List_Node * newElement = new List_Node();
	newElement->value = el;
	if (this->tail)
		this->tail->next = newElement;
	else
		this->head = newElement;
	newElement->prev = this->tail;
	this->tail = newElement;
	this->size++;

}

void List::insert(const int el, const int pos)
{
	if (pos == 0) 
	{
		this->push_front(el);
		return;
	}
	if (pos == this->size)
	{
		this->push_back(el);
		return;
	}
	if (pos > this->size || pos < 0) 
		throw std::invalid_argument("Nie mozna dodac elementu na tej pozycji\n");
	List_Node * newElement = new List_Node();
	newElement->value = el;
	List_Node * it;
	int i;
	
	if ((this->size - pos) > (this->size / 2))
	{
		i = 0;
		it = this->head;
		while (i != pos)
		{
			it = it->next;
			i++;
		}
	}
	else
	{
		i = this->size - 1;
		it = this->tail;
		while (i != pos)
		{
			it = it->prev;
			i--;
			delete it->next;
		}
	}
	newElement->next = it;
	newElement->prev = it->prev;
	it->prev->next = newElement;
	it->prev = newElement;
	this->size++;
}

void List::remove_front()
{
	if (!this->head)
		throw  std::invalid_argument("Lista nie posiada zadnych elementow\n");
	List_Node * element = this->head;
	if (element->next)
		element->next->prev = nullptr;
	else
		this->tail = nullptr;
	this->head = element->next;
	delete element;
	this->size--;

}

void List::remove_back()
{
	if (this->size == 0)
		throw  std::invalid_argument("Lista nie posiada zadnych elementow\n");
	List_Node * element = this->tail;
	if (element->prev)
		element->prev->next = nullptr;
	else
		this->head = nullptr;
	this->tail = element->prev;
	delete element;
	this->size--;
}

void List::remove(const int pos)
{
	if (pos == 0)
	{
		this->remove_front();
		return;
	}
	if (pos == this->size - 1) 
	{
		this->remove_back();
		return;
	}
	if (pos >= this->size || pos < 0)
		throw std::invalid_argument("Nie mozna usunac elementu na podanej pozycji\n");
	List_Node * it;
	int i;
	if ((this->size - pos) > (this->size / 2))
	{
		i = 0;
		it = this->head;
		while (i != pos)
		{
			it = it->next;
			i++;
		}
	}
	else
	{
		i = this->size - 1;
		it = this->tail;
		while (i != pos)
		{
			it = it->prev;
			i--;
		}
	}
	it->next->prev = it->prev;
	it->prev->next = it->next;
	delete it;
	this->size--;
}

bool List::find(const int el)
{
	List_Node * it = this->head;								// ustawiam 'iterator' na poczatek listy
	while (it)													// dopoki 'iterator' != null
	{
		if (it->value == el)									// sprawdzam czy to szukany element
			return true;										// zwracam true jesli element zostal znaleziony
		it = it->next;											// ustawiam 'iterator' na kolejny element listy
	}
	return false;												// zwracam false jesli element nie zostal znaleziony
}

void List::set_num(const int new_num, const int pos)
{
	if (pos < 0 || pos >= this->size)
		throw std::invalid_argument("Nie mozna zmienic elementu na zadanej pozycji (out of range)");

	List_Node * it = this->head;								// ustawiam 'iterator' na poczatek listy
	for (int i = 0; i < pos; i++)
		it = it->next;
	it->value = new_num;

}

std::string List::to_string()
{
	if (this->size == 0)
	{
		return "Lista jest pusta\n";
	}
	std::stringstream ss;
	ss << "Elementy listy:\n";
	List_Node * it = this->head;								// ustawiam 'iterator' na poczatek listy
	int i = 0;													// licznik dla numerow porzadkowych elementow
	while (it != nullptr)
	{
		ss << "Element " << i << ": " << it->value << "\n";
		it = it->next;											// ustawiam 'iterator' na kolejny element listy
		i++;													// zwiekszam licznik
	}
	return ss.str();											// konwersja strinstream na pojedynczy lancuch znakow
}

List::List()
{
}

List::List(int * arr)
{
	for (int i = 1; i < arr[0]+1; i++)
	{
		this->push_back(arr[i]);
	}
}


List::~List()
{
	while (this->size)
	{
		this->remove_front();
	}
}
