#include "array.h"
#include "seq.h"
#ifndef ARSEQ_H
#define ARSEQ_H


template <class T> 
class ArraySequence : public virtual Sequence<T>
{
private:
	DynamicArray<T>* array_ptr{0};
	int size{0};
public:
	ArraySequence(T* items, int array_size);
	ArraySequence();
	ArraySequence(const ArraySequence<T> &list); //const!!
	~ArraySequence();
	virtual bool is_empty() const;
	virtual T get_first() const;
	virtual T get_last() const;
	virtual T &operator[](int index);
	virtual Sequence<T>* get_subsequence(int start_index, int end_index);
	virtual int get_length() const;
	virtual void append(T item);
	virtual void prepend(T item);
	virtual void insert(T item, int index);
	virtual Sequence<T>* concat(Sequence<T> *list);
	virtual Sequence<T>* map(T (*func)(T)); //make immutable! return new Sequence
};


template <class T>
ArraySequence<T>::ArraySequence(T* items, int array_size)
{
	array_ptr = new DynamicArray<T>(items, array_size);
	size = array_ptr->get_size();
}


template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T> &list)
{
	array_ptr = new DynamicArray<T>(*(list.array_ptr));
	size = list.size;
}



template <class T>
ArraySequence<T>::ArraySequence()
{
	array_ptr = 0;
	size = 0;
}


template <class T>
ArraySequence<T>::~ArraySequence()
{
	if(!is_empty()){
		delete array_ptr;
	}
}


template <class T>
bool ArraySequence<T>::is_empty() const
{
	return (array_ptr == 0);
}


template <class T>
T ArraySequence<T>::get_first() const
{
	if(is_empty()){
		throw std::out_of_range("Sequence index out of range");
	}
	return (*array_ptr)[0];
}


template <class T>
T ArraySequence<T>::get_last() const
{
	if(is_empty()){
		throw std::out_of_range("Sequence index out of range");
	}
	return (*array_ptr)[-1];
}


template <class T>
T &ArraySequence<T>::operator[](int index)
{
	if(is_empty()){
		throw std::out_of_range("Sequence index out of range");
	}
	return (*array_ptr)[index];
}


template <class T>
Sequence<T>* ArraySequence<T>::get_subsequence(int start_index, int end_index)
{
	if(start_index < 0){
		start_index += size;
	}
	if(end_index < 0){
		end_index += size;
	}
	if(start_index >= end_index || start_index < 0 || end_index < 0 || start_index > size || end_index > size){
		throw std::out_of_range("Sequence index out of range");
	}
	int sub_size = end_index - start_index + 1;
	T* sub_array = new T[sub_size];
	for (int i = start_index; i < end_index+1; i++)
	{
		sub_array[i-start_index] = (*array_ptr)[i];
	}
	ArraySequence<T>* sub_seq = new ArraySequence<T>(sub_array, sub_size);
	return sub_seq;
}


template <class T>
int ArraySequence<T>::get_length() const
{
	return size;
}


template <class T>
void ArraySequence<T>::append(T item)
{
	if(!is_empty()){
		array_ptr->append(item);
		size += 1;
	}
	else{
		T* items = new T[1];
		items[0] = item;
		array_ptr = new DynamicArray<T>(items, 1);
		size = 1;
	}
}


template <class T>
void ArraySequence<T>::prepend(T item)
{
	if(!is_empty()){
		array_ptr->insert(item, 0);
		size += 1;
	}
	else{
		T* items = new T[1];
		items[0] = item;
		array_ptr = new DynamicArray<T>(items, 1);
		size = 1;
	}
}


template <class T>
void ArraySequence<T>::insert(T item, int index)
{
	if(!is_empty()){
		array_ptr->insert(item, index);
		size += 1;
	}
	else{
		T* items = new T[1];
		items[0] = item;
		array_ptr = new DynamicArray<T>(items, 1);
		size = 1;
	}
}


template <class T>
Sequence <T>* ArraySequence<T>::concat(Sequence <T> *list)
{
	int list_len = list->get_length();
	T* elements_array = new T[list_len];
	for(int i = 0; i < list_len; i++){
		elements_array[i] = (*list)[i];
	}
	ArraySequence<T>* this_seq_copy = new ArraySequence<T>(*this);
	this_seq_copy->array_ptr->resize(size + list_len);
	this_seq_copy->size += list_len;
	for(int i = 0; i < list_len; i++)
	{
		(*(this_seq_copy->array_ptr))[i + size] = elements_array[i];
	}
	return this_seq_copy;
}


template <class T>
Sequence<T>* ArraySequence<T>::map(T (*func)(T))
{
	ArraySequence<T>* this_seq_copy = new ArraySequence<T>(*this);
	for(int i = 0; i < this->get_length(); i++){
		(*this_seq_copy)[i] = func((*this)[i]);
	}
	return this_seq_copy;
}

#endif