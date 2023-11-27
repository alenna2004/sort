#include <cstdlib>
#include <cstring>
#include <stdexcept>
#ifndef DYNAR_H
#define DYNAR_H


template <class T> 
class DynamicArray
{
private:
	int size{0};
	T* ptr{0};
public:
	DynamicArray(int array_size);
	DynamicArray(T* items, int array_size);
	DynamicArray(const DynamicArray<T> &array); //const !
	~DynamicArray();
	bool operator==(const DynamicArray &right) const;
	bool operator!=(const DynamicArray &right) const;
	T &operator[](int index);
	int get_size() const;
	void resize(int new_size);
	void append(T item);
	void insert(T item, int index);
};


template <class T> 
DynamicArray<T>::DynamicArray(int array_size)
{
	if(array_size <= 0){
		throw std::invalid_argument("Invalid array size");
	}
	size = array_size;
	ptr = new T[size];
	if(!ptr){
		throw std::length_error("Failed to allocate memory");
	}
}


template <class T> 
DynamicArray<T>::DynamicArray(T* items, int array_size)
{
	if(array_size <= 0){
		throw std::invalid_argument("Invalid array size");
	}
	size = array_size;
	ptr = new T[size];
	if(!ptr){
		throw std::length_error("Failed to allocate memory");
	}
	for(int i = 0; i < size; i++){
		ptr[i] = items[i];
	}
}


template <class T> 
DynamicArray<T>::DynamicArray(const DynamicArray<T> &array) : size(array.size)
{
	ptr = new T[size];
	if(!ptr){
		throw std::length_error("Failed to allocate memory");
	}
	for(int i = 0; i < size; i++){
		ptr[i] = array.ptr[i];
	}
}


template <class T> 
DynamicArray<T>::~DynamicArray()
{
	delete [] ptr;
}


template <class T>
bool DynamicArray<T>::operator==(const DynamicArray &right) const
{
	if(size != right.size){
		return false;
	}
	for (int i = 0; i < size; i++)
	{
		if(ptr[i] != right.ptr[i]){
			return false;
		}
	}
	return true;
}


template <class T>
bool DynamicArray<T>::operator!=(const DynamicArray &right) const
{
	return !(*this == right);
}


template <class T>
T &DynamicArray<T>::operator[](int index)
{
	if(index < 0){
		index += size;
	}
	if(index >= size || index < 0){
		throw std::out_of_range("Array index out of range");
	}
	return ptr[index];
}


template <class T>
int DynamicArray<T>::get_size() const
{
	return size;
}


template <class T>
void DynamicArray<T>::resize(int new_size)
{
	T* new_ptr = new T[new_size];
	if(!new_ptr){
		throw std::length_error("Failed to allocate memory");
	}
	std::memcpy(new_ptr, ptr, new_size*sizeof(T));
	delete [] ptr;
	ptr = new_ptr;
	size = new_size;
}


template <class T>
void DynamicArray<T>::append(T item)
{
	this->resize(size+1);
	(*this)[size-1] = item;
}


template <class T>
void DynamicArray<T>::insert(T item, int index)
{
	size +=1;
	if(index < 0){
		index += size;
	}
	if(index < 0 || index >= size){
		throw std::out_of_range("List index out of range");
	}
	this->resize(size);
	for(int i = size-1; i > index; i--){
		(*this)[i] = (*this)[i-1];
	}
	(*this)[index] = item;
}

#endif