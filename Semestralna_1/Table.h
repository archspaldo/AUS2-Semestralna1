#pragma once
#include <utility>
#include <concepts>
#include <list>
#include <stdexcept>
#include "Iterator.h"
#include "Comparator.h"

namespace AUS2
{
	template <class DataType>
	requires CheckType<DataType, IComparable<DataType>> class Table : public IIterable<DataType>
	{
	public:
		virtual const size_t size() const = 0;
		virtual void clear() = 0;

		virtual bool insert(const DataType &data) = 0;
		virtual DataType &remove(const ICompare<DataType> &comparator) = 0;

		virtual DataType &get(const ICompare<DataType> &comparator) = 0;
		virtual const DataType get(const ICompare<DataType> &comparator) const = 0;

		virtual DataType &get(std::list<const ICompare<DataType> &> comparator_list) = 0;
		virtual const DataType get(std::list<const ICompare<DataType> &> comparator_list) const = 0;

		virtual Iterator<DataType> *begin_iterator() const = 0;
		virtual Iterator<DataType> *end_iterator() const = 0;
	};
}