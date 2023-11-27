#ifndef LISTN_H
#define LISTN_H


template <class T> class LinkedList;


template <class T> 
class ListNode
{
	friend class LinkedList<T>;
private:
	T data;
	ListNode<T>* next_ptr;
public:
	ListNode(const T &info) : data(info), next_ptr(0){};
	T* get_next_ptr() const;
	T &operator*();
};


template <class T>
T* ListNode<T>::get_next_ptr() const
{
	return next_ptr;
}


template <class T>
T &ListNode<T>::operator*()
{
	return data;
}



#endif