#include <iostream>
#include <cassert>
//#include "pair.h"
#include "seq.h"
#include "listseq.h"
#include "arseq.h"
//#include "zip.h"




using std::cout;
using std::cin;
using std::endl;

void test_creating()
{
	ArraySequence<int> array_1;
	LinkedListSequence<int> list_1;
	int* items = new int[3];
	items[0] = 1;
	items[1] = 2;
	items[2] = 3;
	ArraySequence<int> array_2(items, 3);
	assert(array_2.get_length() != 0);
	cout << "ArraySequence constructor from array OK\n";
	LinkedListSequence<int> list_2(items, 3);
	assert(list_2.get_length() != 0);
	cout << "LinkedListSequence constructor from array OK\n";
	ArraySequence<int> array_3(array_2);
	assert(array_3.get_length() != 0);
	cout << "ArraySequence copy constructor OK\n";
	LinkedListSequence<int> list_3(list_2);
	assert(list_3.get_length() != 0);
	cout << "LinkedListSequence copy constructor OK\n";	
}


void test_comparing(ArraySequence<int> array_1, ArraySequence<int> array_2, LinkedListSequence<int> list_1, LinkedListSequence<int> list_2)
{
	assert(array_1 == list_1);
	assert(array_2 == array_1);
	assert(list_2 == list_1);
	cout << "Comparing sequences by all elements OK\n";
}

void test_concat(ArraySequence<int> array_1, ArraySequence<int> array_2, LinkedListSequence<int> list_1, LinkedListSequence<int> list_2)
{
	Sequence<int>* seq_1 = array_1.concat(&array_2);
	assert(seq_1->get_length() == 6 && seq_1->get_first() == 1 && seq_1->get_last() == 3);
	cout << "Concatinating ArraySequence to ArraySequence OK\n";
	Sequence<int>* seq_2 = array_1.concat(&list_1);
	assert(seq_2->get_length() == 6 && seq_2->get_first() == 1 && seq_2->get_last() == 3);
	cout << "Concatinating LinkedListSequence to ArraySequence OK\n";
	Sequence<int>* seq_3 = list_1.concat(&list_2);
	assert(seq_3->get_length() == 6 && seq_3->get_first() == 1 && seq_3->get_last() == 3);
	cout << "Concatinating LinkedListSequence to LinkedListSequence OK\n";
	Sequence<int>* seq_4 = list_2.concat(&array_1);
	assert(seq_4->get_length() == 6 && seq_4->get_first() == 1 && seq_4->get_last() == 3);
	cout << "Concatinating ArraySequence to LinkedListSequence OK\n";
}

void test_subsequence(ArraySequence<int> array, LinkedListSequence<int> list)
{
	Sequence<int>* seq_5 = array.get_subsequence(0,1);
	assert(seq_5->get_first() == 1 && seq_5->get_last() == 2);
	cout << "Geting subsequence of ArraySequence OK\n";
	Sequence<int>* seq_6 = list.get_subsequence(0,1);
	assert(seq_6->get_first() == 1 && seq_6->get_last() == 2);
	cout << "Geting subsequence of LinkedListSequence OK\n";
}

void test_append_prepend_insert(ArraySequence<int> array, LinkedListSequence<int> list)
{
	array.append(7);
	assert(array.get_last() == 7);
	cout << "ArraySequence append OK\n";
	array.prepend(4);
	assert(array.get_first() == 4);
	cout << "ArraySequence prepend OK\n";
	array.insert(12, -3);
	assert(array[-3] == 12);
	cout << "ArraySequence insert OK\n";
	list.append(6);
	assert(list.get_last() == 6);
	cout << "LinkedListSequence append OK\n";
	list.prepend(11);
	assert(list.get_first() == 11);
	cout << "LinkedListSequence prepend OK\n";
	list.insert(9, 4);
	assert(list[4] == 9);
	cout << "LinkedListSequence insert OK\n";
}


int get_sqr(int num)
{
	return num*num;
}


void test_map(ArraySequence<int> array)
{
	Sequence<int>* mapped = array.map(get_sqr);
	assert((*mapped)[0] == 1 && (*mapped)[1] == 4 && (*mapped)[2] == 9);
	cout << "Map OK\n";
}


int get_sum(int a, int b)
{
	return a+b;
}


void test_reduce(Sequence<int>* array)
{
	int result = array->reduce(get_sum, 10);
	assert(result == 16);
	cout << "Reduce OK\n";
}


void test_zip(Sequence<int>* list_1, Sequence<int>* list_2)
{
	Sequence<Pair<int, int>>* p1 = zip<Pair, Sequence, int, int>(list_1, list_2);
	assert(p1->get_first().get_first() == 1 && p1->get_first().get_second() == 1);
	assert(p1->get_last().get_first() == 9 && p1->get_last().get_second() == 3);
	assert((*p1)[1].get_first() == 4 && (*p1)[1].get_second() == 2);
	cout << "Zip OK\n";
}


void test_unzip(Sequence<Pair<int,int>>* zipped_list, Sequence<int>* list_1, Sequence<int>* list_2)
{
	Pair<Sequence<int>*,Sequence<int>*> p2 = unzip(zipped_list);
	assert(*(p2.get_first()) == *list_1);
	assert(*(p2.get_second()) == *list_2);
	cout << "Unzip OK\n";
}


int main()
{
	ArraySequence<int> array_1;
	LinkedListSequence<int> list_1;
	int* items = new int[3];
	items[0] = 1;
	items[1] = 2;
	items[2] = 3;
	ArraySequence<int> array_2(items, 3);
	LinkedListSequence<int> list_2(items, 3);
	ArraySequence<int> array_3(array_2);
	LinkedListSequence<int> list_3(list_2);
	test_creating();
	test_comparing(array_2, array_3, list_2, list_3);
	test_concat(array_2, array_3, list_2, list_3);
	test_subsequence(array_2, list_2);
	test_append_prepend_insert(array_2, list_3);
	test_map(array_3);
	test_reduce(&list_2);
	test_zip(&array_3, &list_2);
	Sequence<Pair<int, int>>* p1 = zip<Pair, Sequence, int, int>(&array_3, &list_2);
	test_unzip(p1, &array_3, &list_2);
	return 0;
}