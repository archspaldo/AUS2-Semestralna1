#pragma once
#include "Common.h"

namespace AUS2
{
	template <class DataType>
	class IComparator
	{
	public:
		virtual ~IComparator();
		virtual const bool operator==(const DataType &data) const = 0;
		virtual const bool operator<(const DataType &data) const = 0;
		const bool operator<=(const DataType &data) const;
		const bool operator>(const DataType &data) const;
		const bool operator>=(const DataType &data) const;
	};

	template <class DataType, class AttributeType>
	class AttributeComparator
	{
	protected:
		AttributeType &attribute_value_;
		AttributeComparator(const AttributeType &attribute_value);
	public:
		virtual const bool operator==(const DataType &data) const = 0;
		virtual const bool operator<(const DataType &data) const = 0;
	};

	template<class DataType>
	inline IComparator<DataType>::~IComparator() {
	}

	template<class DataType>
	inline const bool IComparator<DataType>::operator<=(const DataType &data) const {
		return !(data < *this);
	}

	template<class DataType>
	inline const bool IComparator<DataType>::operator>(const DataType &data) const {
		return data < *this
	}

	template<class DataType>
	inline const bool IComparator<DataType>::operator>=(const DataType &data) const {
		return !(*this < data);
	}

	template<class DataType, class AttributeType>
	inline AttributeComparator<DataType, AttributeType>::AttributeComparator(const AttributeType &attribute_value) :
		IComparator<DataType>(), attribute_value_(attribute_value) {
	}
}