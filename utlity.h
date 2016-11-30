#ifndef UTLITY
#define UTLITY

namespace DT{
template<typename T>
const T& max(const T& a, const T& b)
{
    return a > b ? a : b;
}

template<typename T>
const T& min(const T& a, const T& b)
{
    return a < b ? a : b;
}

template<typename T>
void swap(T& first, T& last)
{
	const T t = first;
	first = last;
	last = t;
}

template<typename T>
class LessThan
{
public:
	bool operator()(const T& a, const T& b) const
	{
		return a < b;
	}
};

template<typename T, typename InputIter>
class ListInitializer
{
public:
	ListInitializer(InputIter iter)
		:iter(iter){}
	ListInitializer<T, InputIter> operator,(T val)
	{
		*iter = val;
		++iter;
		return ListInitializer<T, InputIter>(iter);
	}
private:
	ListInitializer();
private:
	InputIter iter;
};

template<typename Container>
class ListInitializationSwitch
{
public:
	typedef typename Container::iterator InputIter;
	typedef typename Container::value_type T;
public:
	ListInitializationSwitch(Container& ct)
		:container(ct){}
	ListInitializer<T, InputIter> operator=(T val)
	{
		InputIter itr = container.begin();
		*itr = val;
		++itr;
		return ListInitializer<T, InputIter>(itr);
	}
private:
	Container& container;
};

template<typename T>
class GreaterThan
{
public:
	bool operator()(const T& a, const T& b) const
	{
		return a > b;
	}
};

template<typename InputIter, typename Pre>
void quicksort(InputIter first, InputIter last, Pre _pre)
{
	InputIter left = first;
	InputIter right = last;
	__quicksort(first, last, *left, _pre);
}

template<typename InputIter, typename T, typename Pre>
void __quicksort(InputIter first, InputIter last, T t, Pre _pre)
{
	if (first < last)
	{
		InputIter left = first;
		InputIter right = last;
		T key = *left;

		while (left < right)
		{
			while (left < right && _pre(*right, key))
				right--;
			if (left < right)
				swap<T>(*left++, *right);
			while (left < right && !_pre(*left, key))
				left++;
			if (left < right)
				swap<T>(*left, *right--);
		}
		__quicksort(first, left, t, _pre);
		__quicksort(left + 1, last, t, _pre);
	}
}

}
#endif // UTLITY

