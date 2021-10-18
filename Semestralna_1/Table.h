#pragma once
#include <utility>
#include <concepts>
#include <list>
#include <stdexcept>
#include "Iterator.h"
#include "Common.h"

namespace AUS2
{

	template <PrimaryKeyProtocol KeyType, class DataType>
	class Table 
		//: public IIterable<DataType>
	{
	protected:
		class DataNode;
	public:
		virtual const size_t size() const = 0;
		virtual void clear() = 0;

		virtual void insert(const KeyType &key, const DataType &data) = 0;
		virtual DataType &remove(const KeyType &key) = 0;

		virtual DataType &get(const KeyType &key) = 0;
		virtual const DataType get(const KeyType &key) const = 0;

		//virtual DataType &get(const KeyType &lower_bound, const KeyType &upper_bound) = 0;
		//virtual const DataType get(const KeyType &lower_boundr, const KeyType &upper_bound) const = 0;

		//virtual DataType &get(std::list<const IComparator<DataType> &> comparator_list) = 0;
		//virtual const DataType get(std::list<const IComparator<DataType> &> comparator_list) const = 0;

		//virtual Iterator<DataType> *begin_iterator() const = 0;
		//virtual Iterator<DataType> *end_iterator() const = 0;
	};

	template <PrimaryKeyProtocol KeyType, class DataType>
	class Table<KeyType, DataType>::DataNode
	{
	protected:
		KeyType key_;
		DataType data_;
	public:
		DataNode(const KeyType &key, const DataType &data);
		virtual ~DataNode();
		const KeyType key() const;
		KeyType &key();
		const DataType data() const;
		DataType &data();
	};

	template <PrimaryKeyProtocol KeyType, class DataType>
	inline Table<KeyType, DataType>::DataNode::DataNode(const KeyType& key,const DataType &data) :
		key_(key), data_(data)
	{
	}

	template <PrimaryKeyProtocol KeyType, class DataType>
	inline Table<KeyType, DataType>::DataNode::~DataNode() {
	}

	template <PrimaryKeyProtocol KeyType, class DataType>
	inline const KeyType Table<KeyType, DataType>::DataNode::key() const {
		return this->key_;
	}

	template <PrimaryKeyProtocol KeyType, class DataType>
	inline KeyType &Table<KeyType, DataType>::DataNode::key() {
		return this->key_;
	}

	template <PrimaryKeyProtocol KeyType, class DataType>
	inline const DataType Table<KeyType, DataType>::DataNode::data() const {
		return this->data_;
	}

	template <PrimaryKeyProtocol KeyType, class DataType>
	inline DataType &Table<KeyType, DataType>::DataNode::data() {
		return this->data_;
	}
}