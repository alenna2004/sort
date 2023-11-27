#include "linklist.h"
#include "seq.h"
#ifndef LISTSEQ_H
#define LISTSEQ_H


template <class T>
class LinkedListSequence : public virtual Sequence<T>
{
private:
	LinkedList<T>* list_ptr;
	int length;
public:
	LinkedListSequence(T* items, int array_size);
	LinkedListSequence();
	LinkedListSequence(const LinkedListSequence<T> &list); // const
	~LinkedListSequence();
	virtual bool is_empty() const;
	virtual T get_first() const;
	virtual T get_last() const;
	virtual T &operator[](int index); 
	virtual Sequence<T>* get_subsequence(int start_index, int end_index);
	virtual int get_length() const;
	virtual void append(T item);
	virtual void prepend(T item);
	virtual void insert(T item, int index);
	virtual Sequence <T>* concat(Sequence <T> *list) override;
	virtual Sequence<T>* map(T (*func)(T)); //make immutable! return new Sequence
};


template <class T>
LinkedListSequence<T>::LinkedListSequence(T* items, int array_size)
{
	list_ptr = new LinkedList<T>(items, array_size);
	length = array_size;
}


template <class T>
LinkedListSequence<T>::LinkedListSequence()
{
	LinkedList<T>* list = new LinkedList<T>();
	list_ptr = list;
	length = 0;
}


template <class T>
LinkedListSequence<T>::LinkedListSequence(const LinkedListSequence<T> &list)
{
	list_ptr = new LinkedList<T>(*(list.list_ptr));
	length = list.length;
}


template <class T>
LinkedListSequence<T>::~LinkedListSequence()
{
	if(!is_empty()){
		delete list_ptr;
	}
}


template <class T>
bool LinkedListSequence<T>::is_empty() const
{
	return (list_ptr->is_empty());
}


template <class T>
T LinkedListSequence<T>::get_first() const
{
	return list_ptr->get_first();
}


template <class T>
T LinkedListSequence<T>::get_last() const
{
	return list_ptr->get_last();
}


template <class T>
T &LinkedListSequence<T>::operator[](int index)
{
	return (*list_ptr)[index];
}


template <class T>
Sequence<T>* LinkedListSequence<T>::get_subsequence(int start_index, int end_index)
{
	LinkedList<T>* sub_list = list_ptr->get_sublist(start_index, end_index);
	LinkedListSequence<T>* sub_seq = new LinkedListSequence<T>;
	sub_seq->list_ptr = sub_list;
	sub_seq->length = sub_list->get_length();
	return sub_seq;
}


template <class T>
int LinkedListSequence<T>::get_length() const
{
	return length;
}


template <class T>
void LinkedListSequence<T>::append(T item)
{
	list_ptr->append(item);
	length += 1;

}


template <class T>
void LinkedListSequence<T>::prepend(T item)
{
	list_ptr->prepend(item);
	length += 1;
}


template <class T>
void LinkedListSequence<T>::insert(T item, int index)
{
	list_ptr->insert(item, index);
	length += 1;
}


template <class T>
Sequence<T>* LinkedListSequence<T>::concat(Sequence <T> *list)
{
	int list_len = list->get_length();
	T* elements_array = new T[list_len + length];
	for(int i = 0; i < length; i++){
		elements_array[i] =(*this)[i];
	}
	for(int i = 0; i < list_len; i++){
		elements_array[i + length] = (*list)[i];
	}
	LinkedListSequence<T>* concated_seq = new LinkedListSequence<T>(elements_array, list_len + length);
	return concated_seq;
}


template <class T>
Sequence<T>* LinkedListSequence<T>::map(T (*func)(T))
{
	LinkedListSequence<T>* this_seq_copy = new LinkedListSequence<T>(*this);
	for(int i = 0; i < this->get_length(); i++){
		(*this_seq_copy)[i] = func((*this)[i]);
	}
	return this_seq_copy;
}



#endif