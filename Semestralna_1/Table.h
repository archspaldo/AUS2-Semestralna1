#pragma once
#include <utility>
#include <concepts>
#include <list>
#include <stdexcept>

namespace AUS2
{
	template <class Derived, class Base>
	concept CheckType = std::is_base_of<Base, Derived>::value;

	template <class DataType>
	class IComparable {
	public:
		// Porovná primárny k¾úè
		virtual const int operator<=>(const DataType& compd) const = 0;
		// Porovná pod¾a dát špecifikovaných maskou
		virtual const int compare(const DataType& compd, bool* mask) const = 0;
	};

	template <class DataType>
	requires CheckType<DataType, IComparable<DataType>> class ICompare
	{
	public:
		virtual const int compare(const DataType &compd) const = 0;
	};

	template <class DataType, class AttributeType>
	requires CheckType<DataType, IComparable<DataType>> class Comparator
	{
		AttributeType &value_;
	public:
		virtual const int compare(const DataType &compd) const = 0;
	};

	template <class AttributeType>
	class IntComparator : public Comparator<int, AttributeType>
	{
	public:
		virtual const int compare(const int &compd) const override;
	};

	class IntIntComparator :public IntComparator<int>
	{
	public:
		IntIntComparator();
	};



	template <class DataType>
	requires CheckType<DataType, IComparable<DataType>> class Table {
	public:
		virtual const size_t size() const = 0;
		virtual void clear() = 0;
		virtual bool contains_pk(const DataType& data) = 0;

		virtual bool insert(const DataType& data) = 0;
		virtual DataType& remove(const DataType& pattern) = 0;

		virtual DataType& get(const DataType& pattern) = 0;
		virtual const DataType get(const DataType& pattern) const = 0;

		virtual DataType& get(const DataType& pattern, const Comparator<DataType, auto> &comparator) = 0;
		virtual const DataType get(const DataType& pattern, const Comparator<DataType, auto> &comparator) const = 0;
		/*virtual DataType& get(const DataType& lower_bound_pattern, const DataType& upper_bound_pattern) = 0;
		virtual const DataType get(const DataType& lower_bound_pattern, const DataType& upper_bound_pattern) const = 0;*/
	};
}