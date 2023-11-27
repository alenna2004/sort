#ifndef PAIR_H
#define PAIR_H

template <class T1, class T2>
class Pair
{
private:
	T1 first_element{0};
	T2 second_element{0};
public:
	Pair(T1 item_1, T2 item_2);
	Pair(){};
	~Pair(){};
	T1 get_first() const;
	T2 get_second() const;
};

template <class T1, class T2>
Pair<T1, T2>::Pair(T1 item_1, T2 item_2)
{
	first_element = item_1;
	second_element = item_2;
}


template <class T1, class T2>
T1 Pair<T1, T2>::get_first() const
{
	return first_element;
}


template <class T1, class T2>
T2 Pair<T1, T2>::get_second() const
{
	return second_element;
}


#endif