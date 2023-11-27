#include "seq.h"
#include "arseq.h"
#include "pair.h"
#ifndef ZIP_H
#define ZIP_H


template <template<class, class> class Pair, template<class> class Sequence, class T1, class T2>
Sequence<Pair<T1, T2>>* zip(Sequence<T1>* list_1, Sequence<T2>* list_2);

template <template<class, class> class Pair, template<class> class Sequence, class T1, class T2>
Pair<Sequence<T1>*, Sequence<T2>*> unzip(Sequence<Pair<T1,T2>>* zipped_list);



template <template<class, class> class Pair, template<class> class Sequence, class T1, class T2>
Sequence<Pair<T1, T2>>* zip(Sequence<T1>* list_1, Sequence<T2>* list_2)
{
	int zipped_len = 0;
	int len_1 = list_1->get_length();
	int len_2 = list_2->get_length();
	if(len_1 > len_2){
		zipped_len = len_2;
	}
	else{
		zipped_len = len_1;
	}
	Pair<T1, T2>* items = new Pair<T1, T2>[zipped_len];
	for(int i = 0; i < zipped_len; i++){
		items[i] = Pair((*list_1)[i], (*list_2)[i]);
	}
	ArraySequence<Pair<T1, T2>>* result = new ArraySequence(items, zipped_len);
	return result;
}


template <template<class, class> class Pair, template<class> class Sequence, class T1, class T2>
Pair<Sequence<T1>*, Sequence<T2>*> unzip(Sequence<Pair<T1,T2>>* zipped_list)
{
	int len = zipped_list->get_length();
	T1* items_1 = new T1[len];
	T2* items_2 = new T2[len];
	for(int i = 0; i < len; i++){
		T1 first = (*zipped_list)[i].get_first();
		T2 second = (*zipped_list)[i].get_second();
		items_1[i] = first;
		items_2[i] = second;
	}
	ArraySequence<T1>* first_array = new ArraySequence(items_1, len);
	ArraySequence<T2>* second_array = new ArraySequence(items_2, len);
	Sequence<T1>* seq_1 = static_cast<ArraySequence<T1>*>(first_array);
	Sequence<T2>* seq_2 = static_cast<ArraySequence<T2>*>(second_array);
	Pair<Sequence<T1>*, Sequence<T2>*> result = Pair(seq_1, seq_2);
	return result;
}

#endif