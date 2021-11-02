#pragma once
#include <iterator>

template <class DataType>
class Iterator
{
public:
	virtual ~Iterator();
	virtual Iterator &operator=(const Iterator &iter) = 0;
	virtual const bool operator!=(const Iterator &iter) const = 0;
	virtual const DataType operator*() const = 0;
	virtual Iterator &operator++() = 0;
};

template <class DataType>
class ProxyIterator
{
private:
	Iterator<DataType> *iterator_;
public:
	ProxyIterator(Iterator<DataType> *iterator);
	virtual ~ProxyIterator();
	ProxyIterator<DataType> &operator=(const ProxyIterator<DataType> &iter);
	const bool operator!=(const ProxyIterator<DataType> &iter) const;
	const DataType operator*() const;
	const ProxyIterator<DataType> &operator++();
};

template <class DataType>
class IIterable
{
public:
	ProxyIterator<DataType> begin() const;
	ProxyIterator<DataType> end() const;
	virtual Iterator<DataType> *begin_iterator() const = 0;
	virtual Iterator<DataType> *end_iterator() const = 0;
};

template<class DataType>
inline Iterator<DataType>::~Iterator() {
}

template<class DataType>
inline ProxyIterator<DataType>::ProxyIterator(Iterator<DataType> *iterator) :
	iterator_(iterator) {
}

template<class DataType>
inline ProxyIterator<DataType>::~ProxyIterator() {
	delete this->iterator_;
}

template<class DataType>
inline ProxyIterator<DataType> &ProxyIterator<DataType>::operator=(const ProxyIterator<DataType> &iter) {
	*this->iterator_ = *iter.iterator_;
}

template<class DataType>
inline const DataType ProxyIterator<DataType>::operator*() const {
	return **this->iterator_;
}

template<class DataType>
inline const bool ProxyIterator<DataType>::operator!=(const ProxyIterator<DataType> &iter) const {
	return *this->iterator_ != *iter.iterator_;
}

template<class DataType>
inline const ProxyIterator<DataType> &ProxyIterator<DataType>::operator++() {
	Iterator<DataType> *iterator = &(++ * this->iterator_);
	if (iterator != this->iterator_) {
		delete this->iterator_;
		this->iterator_ = iterator;
	}
	return *this;
}

template<class DataType>
inline ProxyIterator<DataType> IIterable<DataType>::begin() const {
	return ProxyIterator<DataType>(this->begin_iterator());
}

template<class DataType>
inline ProxyIterator<DataType> IIterable<DataType>::end() const {
	return ProxyIterator<DataType>(this->end_iterator());
}
