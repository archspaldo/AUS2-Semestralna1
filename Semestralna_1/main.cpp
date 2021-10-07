#include <iostream>
#include <list>

class ICompare
{

};


template <class DataType, class AttributeType>
//requires CheckType<DataType, IComparable<DataType>>
class Comparator : public ICompare
{

protected:
	Comparator()
	{
	};
};

template <class AttributeType>
class IntComparator : public Comparator<int, AttributeType>
{
protected:
	IntComparator()
	{
	};
};

class IntIntComparator :public IntComparator<int>
{
public:
	IntIntComparator()
	{
	};
};

int main()
{
	std::list<ICompare*> l;
	l.push_back(new IntIntComparator());
	delete l.back();
}

