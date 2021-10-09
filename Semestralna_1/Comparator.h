#pragma once
#include "Common.h"

namespace AUS2
{
	template <class DataType>
	class IComparable
	{
	public:
		// Porovná primárny k¾úè
		virtual const int operator<=>(const DataType &compd) const = 0;
	};

	template <class DataType>
	requires CheckType<DataType, IComparable<DataType>> class ICompare
	{
	public:
		virtual const int compare(const DataType &compd) const = 0;
	};

	template <class DataType, class AttributeType>
	requires CheckType<DataType, IComparable<DataType>> class Comparator : public ICompare<DataType>
	{
	protected:
		Comparator(const AttributeType &value_, const bool compares_primary_key_);
		AttributeType &value_;
		bool compares_primary_key_;
	public:
		virtual const int compare(const DataType &compd) const = 0;
	};
}