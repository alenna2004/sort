#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include "listnode.h"
#ifndef LINKLIST_H
#define LINKLIST_H




//read about const and leak avoiding
template <class T> 
class LinkedList
{
	private:
		ListNode<T>* first_ptr{0};
		ListNode<T>* last_ptr{0};
		int length{0};
		ListNode<T>* get_new_node(T item); 
		ListNode<T>* get_node_by_index(int index) const; // get_node just this name of function
	public:
		LinkedList() {};
		LinkedList(T* items, int array_size);
		LinkedList(const LinkedList<T> & list); // const!
		~LinkedList();
		bool operator==(const LinkedList &right) const;
		bool operator!=(const LinkedList &right) const; 
		T &operator[](int index);
		int get_length() const;
		bool is_empty() const;
		ListNode<T>* get_first_node() const; //get_first_node
		ListNode<T>* get_last_node() const; //get_last_node
		T get_first() const;
		T get_last() const;
		LinkedList<T>* get_sublist(int start_index, int end_index);
		void append(T item);
		void prepend(T item); 
		void insert(T item, int index);
		LinkedList<T>* concat(LinkedList<T>* list);
};


template <class T> 
LinkedList<T>::LinkedList(T* items, int array_size)
{
	if(array_size <= 0){
		throw std::invalid_argument("Invalid array size");
	}
	length = array_size;
	ListNode<T>* first = get_new_node(items[0]);
	first_ptr = first;
	ListNode<T>* cur_node = first;
	for (int i = 1; i < length; i++){
		ListNode<T>*new_node = get_new_node(items[i]);
		cur_node->next_ptr = new_node;
		cur_node = new_node;
	}
	last_ptr = cur_node;
}


template <class T> 
LinkedList<T>::LinkedList(const LinkedList<T> &list) : length(list.length)
{
	ListNode<T>* first = get_new_node(list.first_ptr->data);
	first_ptr = first;
	ListNode<T>* cur_node = first;
	ListNode<T>* src_node = list.first_ptr->next_ptr;
	for (int i = 1; i < length; i++){
		ListNode<T>*new_node = get_new_node(src_node->data);
		cur_node->next_ptr = new_node;
		cur_node = new_node;
		src_node = src_node->next_ptr;
	}
	last_ptr = cur_node;
}


template <class T> 
LinkedList<T>::~LinkedList()
{
	if(!is_empty()){
		ListNode<T>* cur_ptr = first_ptr;
		ListNode<T>* temp_ptr;
		while(cur_ptr != 0){
			temp_ptr = cur_ptr;
			cur_ptr = cur_ptr->next_ptr;
			delete temp_ptr;
		}
	}
}


template <class T>
ListNode<T>* LinkedList<T>::get_new_node(T item){
	ListNode<T>* node_ptr = new ListNode<T>(item);
	if(!node_ptr){
		throw std::length_error("Failed to allocate memory");
	}
	return node_ptr;
}


template <class T>
bool LinkedList<T>::operator==(const LinkedList &right) const
{
	if(length != right.length){
		return false;
	}
	ListNode<T>* cur_this_ptr = first_ptr;
	ListNode<T>* cur_right_ptr = right.first_ptr;
	while(cur_this_ptr != 0){
		if(cur_this_ptr->data != cur_right_ptr->data){
			return false;
		}
		cur_this_ptr = cur_this_ptr->next_ptr;
		cur_right_ptr = cur_right_ptr->next_ptr;
	}
	return true;
}


template <class T>
bool LinkedList<T>::operator!=(const LinkedList &right) const
{
	return !(*this == right);
}


template <class T>
T &LinkedList<T>::operator[](int index)
{
	ListNode<T>* node = get_node_by_index(index);
	return node->data;
}


template <class T>
ListNode<T>* LinkedList<T>::get_node_by_index(int index) const
{
	if(index < 0){
		index += length;
	}
	if(index >= length || index < 0){
		throw std::out_of_range("List index out of range");
	}
	int counter = 0;
	ListNode<T>* cur_ptr = first_ptr;
	while(counter != index){
		cur_ptr = cur_ptr->next_ptr;
		counter += 1;
	}
	return cur_ptr;
}


template <class T>
int LinkedList<T>::get_length() const
{
	return length;
}


template <class T>
bool LinkedList<T>::is_empty() const
{
	return (first_ptr == 0);
}


template <class T>
ListNode<T>* LinkedList<T>::get_first_node() const
{
	return first_ptr;
}


template <class T>
ListNode<T>* LinkedList<T>::get_last_node() const
{
	return last_ptr;
}


template <class T>
T LinkedList<T>::get_first() const
{
	if(!is_empty()){
		return first_ptr->data;
	}
	else{
		throw std::out_of_range("List index out of range");
	}
}


template <class T>
T LinkedList<T>::get_last() const
{
	if(!is_empty()){
		return last_ptr->data;
	}
	else{
		throw std::out_of_range("List index out of range");
	}
}


template <class T>
LinkedList<T>* LinkedList<T>::get_sublist(int start_index, int end_index)
{
	if(start_index < 0){
		start_index += length;
	}
	if(end_index < 0){
		end_index += length;
	}
	if(start_index >= end_index || start_index < 0 || end_index < 0 || start_index > length || end_index > length){
		throw std::out_of_range("List index out of range");
	}
	LinkedList<T>* this_list_copy = new LinkedList<T>(*this);
	ListNode<T>* first = this_list_copy->get_node_by_index(start_index);
	ListNode<T>* last = this_list_copy->get_node_by_index(end_index);
	ListNode<T>* cur_ptr = this_list_copy->first_ptr;
	ListNode<T>* temp_ptr;
	while(cur_ptr != first){
		temp_ptr = cur_ptr;
		cur_ptr = cur_ptr->next_ptr;
		delete temp_ptr;
	}
	cur_ptr = last->next_ptr;
	while(cur_ptr != 0){
		temp_ptr = cur_ptr;
		cur_ptr = cur_ptr->next_ptr;
		delete temp_ptr;
	}
	this_list_copy->first_ptr = first;
	this_list_copy->last_ptr = last;
	this_list_copy->last_ptr->next_ptr = 0;
	this_list_copy->length = end_index - start_index + 1;
	return this_list_copy;
}


template <class T>
void LinkedList<T>::append(T item){
	ListNode<T>* new_node_ptr = get_new_node(item);
	if(is_empty()){
		first_ptr = last_ptr = new_node_ptr;
	}
	else{
		last_ptr->next_ptr = new_node_ptr;
		last_ptr = new_node_ptr;
		new_node_ptr->next_ptr = 0;
	}
	length +=1;
}


template <class T>
void LinkedList<T>::prepend(T item)
{
	ListNode<T>* new_node_ptr = get_new_node(item);
	if(is_empty()){
		first_ptr = last_ptr = new_node_ptr;
	}
	else{
		new_node_ptr->next_ptr = first_ptr;
		first_ptr = new_node_ptr;
	}
	length +=1;
}


template <class T>
void LinkedList<T>::insert(T item, int index)
{
	if(index < 0){
		index += length;
	}
	if(index < 0 || index > length){
		throw std::out_of_range("List index out of range");
	}
	if(index == 0){
		prepend(item);
	}
	else if(index == length){
		append(item);
	}
	else{
		ListNode<T>* new_node = get_new_node(item);
		ListNode<T>* cur_node = get_node_by_index(index-1);
		ListNode<T>* node_after_inserted = cur_node->next_ptr;
		cur_node->next_ptr = new_node;
		new_node->next_ptr = node_after_inserted;
		length += 1;
	}
}


template <class T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T>* list)
{
	LinkedList<T>* this_list_copy = new LinkedList<T>(*this);
	this_list_copy->last_ptr->next_ptr = list->first_ptr;

	this_list_copy->last_ptr = list->last_ptr;
	this_list_copy->length += list->length;
	return this_list_copy;
}


#endif