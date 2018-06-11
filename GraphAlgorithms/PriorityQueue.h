#pragma once
#include <string>
#include <sstream>

// Minimum Priority Queue - 1 has the highest priority
template <typename Type>
class PriorityQueue {

private:
	struct Pair;
	Pair** array;
	int size;
	int max_size;
	
	int parent(int& index);
	int left_child(int& index);
	int right_child(int& index);

	void fixDown(int index);
	void fixUp(int index);
	void swap(int& first, int& second);
	int find(Type data);
	// doubles the max_size of the heap
	void grow();

public:
	PriorityQueue();
	~PriorityQueue();
	
	void insert(Type data, int priority);
	Type popMin();
	void decreaseKey(Type data, int new_priority);
	bool isEnqueued(Type data);
	bool isEmpty();
	std::string toString();
	int getSize();
};

template <typename Type>
struct PriorityQueue<Type>::Pair {
	Type data;
	int priority;
	Pair(Type data, int priority) : data(data), priority(priority) {};
};

template <typename Type>
PriorityQueue<Type>::PriorityQueue() : size(0), max_size(1) {
	array = new Pair*[max_size];
}

template <typename Type>
PriorityQueue<Type>::~PriorityQueue() {
	for (int i = 0; i < size; ++i) {
		delete array[i];
	}
	delete[] array;
}

template<typename Type>
void PriorityQueue<Type>::insert(Type new_data, int priority) {
	if (size == max_size - 1)
		grow();
	array[size] = new Pair(new_data, priority);
	++size;
	fixUp(size-1);
}

template<typename Type>
Type PriorityQueue<Type>::popMin() {
	if (size == 0)
		throw std::out_of_range("The Queue is empty");
	Type data = array[0]->data;
	delete array[0];
	array[0] = array[size - 1];
	--size;
	fixDown(0);
	return data;
}

template<typename Type>
void PriorityQueue<Type>::decreaseKey(Type data, int key) {
	int index = find(data);
	if (key >= array[index]->priority)
		return;
	array[index]->priority = key;
	fixUp(index);
}

template<typename Type>
bool PriorityQueue<Type>::isEnqueued(Type data) {
	for (int i = 0; i < size; ++i) {
		if (array[i]->data == data)
			return true;
	}
	return false;
}

template<typename Type>
bool PriorityQueue<Type>::isEmpty() {
	return size == 0 ? true : false;
}

template<typename Type>
std::string PriorityQueue<Type>::toString() {
	std::stringstream ss;
	ss << "Elements:\n";
	for (int i = 0; i < size; ++i) {
		ss << i << " : " << array[i]->data << "(" << array[i]->priority << ")\n";
	}
	return ss.str();
}

template<typename Type>
int PriorityQueue<Type>::getSize() {
	return this->size;
}

template <typename Type>
int PriorityQueue<Type>::parent(int& index) {
	return (index - 1) / 2;
}

template <typename Type>
int PriorityQueue<Type>::left_child(int& index) {
	return 2 * index + 1;
}

template <typename Type>
int PriorityQueue<Type>::right_child(int& index) {
	return 2 * index + 2;
}

template <typename Type>
void PriorityQueue<Type>::fixDown(int index) {
	
	int left = left_child(index);
	int right = right_child(index);
	if (left >= size)
		return;

	int min = index;
	if (array[index]->priority > array[left]->priority) {
		min = left;
	}
	if ((right < size) && (array[min]->priority > array[right]->priority)) {
		min = right;
	}
	if (min != index) {
		swap(min, index);
		fixDown(min);
	}
}

template<typename Type>
void PriorityQueue<Type>::fixUp(int index) {
	if (index == 0)
		return;
	int par = parent(index);
	if (array[par]->priority > array[index]->priority) {
		swap(par, index);
		fixUp(par);
	}
}

template<typename Type>
void PriorityQueue<Type>::swap(int& first, int& second) {
	Pair* tmp = array[first];
	array[first] = array[second];
	array[second] = tmp;
}

template<typename Type>
int PriorityQueue<Type>::find(Type data) {
	for (int i = 0; i < size; ++i) {
		if (array[i]->data == data)
			return i;
	}
	return -1;
}

template<typename Type>
void PriorityQueue<Type>::grow() {
	Pair** new_array = new Pair*[this->max_size * 2];
	memcpy(new_array, this->array, this->max_size * sizeof(Pair*));
	delete[] this->array;
	this->array = new_array;
	this->max_size *= 2;
}


