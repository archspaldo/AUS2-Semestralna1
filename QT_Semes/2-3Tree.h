#pragma once
#include <list>
#include <iterator>
#include <iostream>
#include "Table.h"

//Všetky štruktúry sú implementované pomocou prednášok

namespace AUS2
{
	template <PrimaryKeyProtocol KeyType, class DataType>
	class TwoThreeTree : public Table<KeyType, DataType>
	{
	protected:
		class TwoThreeTableNode;
		class TwoThreeTableIterator;

		const bool try_find(const KeyType &key, TwoThreeTableNode *&last_checked, int &layer) const;
		const bool try_find(const KeyType &key, TwoThreeTableNode *&last_checked) const;

		TwoThreeTableNode *root_;
		size_t size_;
	public:
		TwoThreeTree();
		~TwoThreeTree();

		const bool contains_key(const KeyType &key);
		virtual const size_t size() const override;
		virtual void clear() override;

		virtual void insert(const KeyType &key, const DataType &data) override;
		virtual bool insert_or_replace(const KeyType &key, const DataType &data, DataType &old_data) override;
		virtual DataType &remove(const KeyType &key) override;

		virtual DataType &get(const KeyType &key) override;
		virtual const DataType get(const KeyType &key) const override; 

		virtual std::list<DataType> *get_interval(const KeyType &lower_bound, const KeyType &upper_bound) override;

		virtual Iterator<DataType> *begin_iterator() const override;
		virtual Iterator<DataType> *end_iterator() const override;
	};

	template <PrimaryKeyProtocol KeyType, class DataType>
	class TwoThreeTree<KeyType, DataType>::TwoThreeTableNode
	{
	protected:
		TwoThreeTableNode *parent_;
		std::list<typename Table<KeyType, DataType>::DataNode *> *data_nodes_;
		std::list<TwoThreeTableNode *> *children_;
	public:
		void rotate_left(const int index);
		void rotate_right(const int index);

		TwoThreeTableNode();
		TwoThreeTableNode(const KeyType &key, const DataType &data);
		virtual ~TwoThreeTableNode();

		const bool is_leaf() const;
		const bool has_data_node(const KeyType &key) const;
		const short data_node_count() const;
		const short index(const KeyType &key) const;

		typename Table<KeyType, DataType>::DataNode *data_node(const KeyType &key);

		typename Table<KeyType, DataType>::DataNode *data_by_index(const int order);
		TwoThreeTableNode *child_node(const KeyType &key);
		TwoThreeTableNode *child_by_index(const int order);
		void remove_child_by_index(const int index);
		TwoThreeTableNode *parent_node();
		void parent_node(TwoThreeTableNode *node);

		TwoThreeTableNode *add_node(typename Table<KeyType, DataType>::DataNode *data_node);
		typename Table<KeyType, DataType>::DataNode *remove_node(const KeyType &key);
		typename Table<KeyType, DataType>::DataNode *remove_by_index(const int index);

		TwoThreeTableNode *add_and_split(TwoThreeTableNode *node, bool &was_split);
		TwoThreeTableNode *remove_and_merge(TwoThreeTableNode *node);
	};

	template <PrimaryKeyProtocol KeyType, class DataType>
	class TwoThreeTree<KeyType, DataType>::TwoThreeTableIterator : public Iterator<DataType>
	{
	private:
		std::list<typename Table<KeyType, DataType>::DataNode *> *path_;
	public:
		TwoThreeTableIterator(TwoThreeTree<KeyType, DataType>::TwoThreeTableNode *position);
		virtual ~TwoThreeTableIterator();
		virtual Iterator<DataType> &operator=(const Iterator<DataType> &iter) override;
		virtual const bool operator!=(const Iterator<DataType> &iter) const override;
		virtual const DataType operator*() const override;
		virtual Iterator<DataType> &operator++() override;
	};

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const bool TwoThreeTree<KeyType, DataType>::try_find(const KeyType &key, TwoThreeTableNode *&last_checked, int &layer) const {
		layer = 0;
		last_checked = this->root_;
		if (!this->root_) {
			return false;
		}
		bool has_key = last_checked->has_data_node(key);
		while (!has_key && !last_checked->is_leaf()) {
			layer++;
			last_checked = last_checked->child_node(key);
			has_key = last_checked->has_data_node(key);
		}
		return has_key;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const bool TwoThreeTree<KeyType, DataType>::try_find(const KeyType &key, TwoThreeTableNode *&last_checked) const {
		int layer;
		return this->try_find(key, last_checked, layer);
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTree() :
		root_(nullptr), size_(0) {
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::~TwoThreeTree() {
		this->clear();
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const bool TwoThreeTree<KeyType, DataType>::contains_key(const KeyType &key) {
		TwoThreeTableNode *t;
		return this->try_find(key, t);
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const size_t TwoThreeTree<KeyType, DataType>::size() const {
		return this->size_;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline void TwoThreeTree<KeyType, DataType>::clear() {
		std::list<TwoThreeTableNode *> queue;
		TwoThreeTableNode *current;
		if (this->root_) {
			queue.push_back(this->root_);
			while (!queue.empty()) {
				if (!queue.front()->is_leaf()) {
					for (int i = 0; i < queue.front()->data_node_count() + 1; i++) {
						queue.push_back(queue.front()->child_by_index(i));
					}
				}
				delete queue.front();
				queue.pop_front();
			}
		}
		this->root_ = nullptr;
		this->size_ = 0;
		current = nullptr;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline void TwoThreeTree<KeyType, DataType>::insert(const KeyType &key, const DataType &data) noexcept(false) {
		if (!this->root_) {
			this->root_ = new TwoThreeTableNode(key, data);
		}
		else {
			TwoThreeTableNode *target_node;
			if (this->try_find(key, target_node)) {
				throw std::exception("Key already in table");
			}
			target_node = target_node->add_node(new typename Table<KeyType, DataType>::DataNode(key, data));
			if (target_node->data_node_count() == 1) {
				if (target_node->parent_node()) {
					bool was_split = true;
					TwoThreeTableNode *parent_node = target_node->parent_node();
					while (parent_node && was_split) {
						target_node = parent_node->add_and_split(target_node, was_split);
						parent_node = target_node->parent_node();
					}
				}
				if (!target_node->parent_node()) {
					this->root_ = target_node;
				}
			}
		}
		this->size_++;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline bool TwoThreeTree<KeyType, DataType>::insert_or_replace(const KeyType &key, const DataType &data, DataType &old_data) {
		if (!this->root_) {
			this->root_ = new TwoThreeTableNode(key, data);
		}
		else {
			TwoThreeTableNode *target_node;
			if (this->try_find(key, target_node)) {
				old_data = target_node->data_node(key)->data();
				target_node->data_node(key)->data() = data;
				return true;
			}
			target_node = target_node->add_node(new typename Table<KeyType, DataType>::DataNode(key, data));
			if (target_node->data_node_count() == 1) {
				if (target_node->parent_node()) {
					bool was_split = true;
					TwoThreeTableNode *parent_node = target_node->parent_node();
					while (parent_node && was_split) {
						target_node = parent_node->add_and_split(target_node, was_split);
						parent_node = target_node->parent_node();
					}
				}
				if (!target_node->parent_node()) {
					this->root_ = target_node;
				}
			}
		}
		this->size_++;
		return false;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline DataType &TwoThreeTree<KeyType, DataType>::remove(const KeyType &key) noexcept(false) {
		TwoThreeTableNode *target_node;
		if (!this->try_find(key, target_node)) {
			throw std::exception("Key not in table");
		}
		typename Table<KeyType, DataType>::DataNode *return_value = target_node->data_node(key);

		if (target_node->is_leaf()) {
			target_node->remove_node(key);
		}
		else {
			TwoThreeTableNode *leaf_node = target_node->child_by_index(target_node->index(key) + 1);
			target_node->remove_node(key);
			while (!leaf_node->is_leaf()) {
				leaf_node = leaf_node->child_by_index(0);
			}
			target_node->add_node(leaf_node->remove_by_index(0));
			target_node = leaf_node;
		}

		if (target_node->data_node_count() == 0) {
			while (target_node->data_node_count() == 0 && target_node->parent_node()) {
				target_node = target_node->parent_node()->remove_and_merge(target_node);
			}
			if (target_node->data_node_count() == 0 && !target_node->parent_node()) {
				this->root_ = target_node->child_by_index(0);
				delete target_node;
				if (this->root_) {
					this->root_->parent_node(nullptr);
				}
			}
		}

		this->size_--;
		DataType data = return_value->data();
		delete return_value;
		return data;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline DataType &TwoThreeTree<KeyType, DataType>::get(const KeyType &key) noexcept(false) {
		TwoThreeTableNode *target_node;
		if (!this->try_find(key, target_node)) {
			throw std::exception("Key not in table");
		}
		return target_node->data_node(key)->data();
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const DataType TwoThreeTree<KeyType, DataType>::get(const KeyType &key) const noexcept(false) {
		TwoThreeTableNode *target_node;
		if (!this->try_find(key, target_node)) {
			throw std::exception("Key not in table");
		}
		return target_node->data_node(key)->data();
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline std::list<DataType> *TwoThreeTree<KeyType, DataType>::get_interval(const KeyType &lower_bound, const KeyType &upper_bound) {
		std::list<short> *list = new std::list<short>();
		std::list<DataType> *return_list = new std::list<DataType>();
		TwoThreeTableNode *current_node = this->root_;

		if (!this->root_) {
			return return_list;
		}

		while (!current_node->has_data_node(lower_bound) && !current_node->is_leaf()) {
			list->push_front(current_node->index(lower_bound));
			current_node = current_node->child_by_index(list->front());
		}
		list->push_front(current_node->index(lower_bound));

		while (true) {
			while (!list->empty() && list->front() == current_node->data_node_count()) {
				current_node = current_node->parent_node();
				list->pop_front();
			}
			if (list->empty() || current_node->data_by_index(list->front())->key() > upper_bound) {
				break;
			}
			return_list->push_back(current_node->data_by_index(list->front())->data());
			list->front() += 1;

			while (!current_node->is_leaf()) {
				current_node = current_node->child_by_index(list->front());
				list->push_front(0);
			}
		}

		delete list;
		return return_list;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline Iterator<DataType> *TwoThreeTree<KeyType, DataType>::begin_iterator() const {
		return new TwoThreeTableIterator(this->root_);
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline Iterator<DataType> *TwoThreeTree<KeyType, DataType>::end_iterator() const {
		return new TwoThreeTableIterator(nullptr);
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::add_node(typename Table<KeyType, DataType>::DataNode *data_node) {
		if (this->data_node_count() <= 1) {
			if (this->data_node_count() == 0 || data_node->key() < this->data_nodes_->front()->key()) {
				this->data_nodes_->push_front(data_node);
			}
			else {
				this->data_nodes_->push_back(data_node);
			}
		}
		else {
			TwoThreeTableNode *left_child = new TwoThreeTableNode(), *right_child = new TwoThreeTableNode();
			this->children_->push_front(left_child);
			this->children_->push_back(right_child);
			left_child->parent_ = right_child->parent_ = this;
			if (data_node->key() < this->data_nodes_->front()->key()) {
				left_child->data_nodes_->push_front(data_node);
				right_child->data_nodes_->push_front(this->data_nodes_->back());
				this->data_nodes_->pop_back();
			}
			else if (data_node->key() < this->data_nodes_->back()->key()) {
				left_child->data_nodes_->push_front(this->data_nodes_->front());
				right_child->data_nodes_->push_front(this->data_nodes_->back());
				this->data_nodes_->clear();
				this->data_nodes_->push_front(data_node);
			}
			else {
				left_child->data_nodes_->push_front(this->data_nodes_->front());
				right_child->data_nodes_->push_front(data_node);
				this->data_nodes_->pop_front();
			}
		}
		return this;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline typename Table<KeyType, DataType>::DataNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::remove_node(const KeyType &key) {
		for (typename Table<KeyType, DataType>::DataNode *node : *this->data_nodes_) {
			if (node->key() == key) {
				this->data_nodes_->remove(node);
				return node;
			}
		}
		return nullptr;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline typename Table<KeyType, DataType>::DataNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::remove_by_index(const int index) {
		typename std::list<typename Table<KeyType, DataType>::DataNode *>::iterator it = this->data_nodes_->begin();
		std::ranges::advance(it, index);
		typename Table<KeyType, DataType>::DataNode *return_value = *it;
		this->data_nodes_->erase(it);
		return return_value;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::add_and_split(TwoThreeTableNode *node, bool &was_split) {
		if (this->data_node_count() == 1) {
			if (node->data_nodes_->front()->key() < this->data_nodes_->front()->key()) {
				this->data_nodes_->push_front(node->data_nodes_->front());
				this->children_->pop_front();
				this->children_->insert(this->children_->begin(), node->children_->begin(), node->children_->end());
			}
			else {
				this->data_nodes_->push_back(node->data_nodes_->back());
				this->children_->pop_back();
				this->children_->insert(this->children_->end(), node->children_->begin(), node->children_->end());
			}
			for (TwoThreeTableNode *node : *this->children_) {
				node->parent_ = this;
			}
			was_split = false;
		}
		else {
			TwoThreeTableNode *left_child = new TwoThreeTableNode(), *right_child = new TwoThreeTableNode();
			this->children_->remove(node);
			if (node->data_nodes_->front()->key() < this->data_nodes_->front()->key()) {
				left_child->data_nodes_->push_front(node->data_nodes_->front());
				right_child->data_nodes_->push_front(this->data_nodes_->back());

				left_child->children_->insert(left_child->children_->begin(), node->children_->begin(), node->children_->end());
				right_child->children_->insert(right_child->children_->begin(), this->children_->begin(), this->children_->end());

				this->data_nodes_->pop_back();
			}
			else if (node->data_nodes_->front()->key() < this->data_nodes_->back()->key()) {
				left_child->data_nodes_->push_front(this->data_nodes_->front());
				right_child->data_nodes_->push_front(this->data_nodes_->back());

				left_child->children_->push_front(this->children_->front());
				left_child->children_->push_back(node->children_->front());
				right_child->children_->push_front(node->children_->back());
				right_child->children_->push_back(this->children_->back());

				this->data_nodes_->clear();
				this->data_nodes_->push_front(node->data_nodes_->front());
			}
			else {
				left_child->data_nodes_->push_front(this->data_nodes_->front());
				right_child->data_nodes_->push_front(node->data_nodes_->back());

				left_child->children_->insert(left_child->children_->begin(), this->children_->begin(), this->children_->end());
				right_child->children_->insert(right_child->children_->begin(), node->children_->begin(), node->children_->end());

				this->data_nodes_->pop_front();
			}
			this->children_->clear();
			this->children_->push_front(left_child);
			this->children_->push_back(right_child);
			left_child->parent_ = right_child->parent_ = this;
			was_split = true;

			for (TwoThreeTableNode *node : *left_child->children_) {
				node->parent_ = left_child;
			}
			for (TwoThreeTableNode *node : *right_child->children_) {
				node->parent_ = right_child;
			}
		}
		node->data_nodes_->pop_front();
		delete node;
		return this;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::remove_and_merge(TwoThreeTableNode *node) {
		int index = 0;
		for (TwoThreeTableNode *child : *this->children_) {
			if (child == node) {
				break;
			}
			index++;
		}

		if (index == 0) {
			if (this->child_by_index(index + 1)->data_node_count() == 2) {
				this->rotate_left(index);
			}
			else {
				this->rotate_right(index);
			}
		}
		else if (index == this->data_node_count()) {
			if (this->child_by_index(index - 1)->data_node_count() == 2) {
				this->rotate_right(index - 1);
			}
			else {
				this->rotate_left(index - 1);
			}
		}
		else {
			if (this->child_by_index(index - 1)->data_node_count() == 2) {
				this->rotate_right(index - 1);
			}
			else if (this->child_by_index(index + 1)->data_node_count() == 2) {
				this->rotate_left(index);
			}
			else {
				this->rotate_right(index);
			}
		}
		return this;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline void TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::rotate_left(const int index) {
		typename std::list<typename Table<KeyType, DataType>::DataNode *>::iterator it = this->data_nodes_->begin();
		std::ranges::advance(it, index);
		TwoThreeTableNode *left_child = this->child_by_index(index), *right_child = this->child_by_index(index + 1);
		left_child->data_nodes_->push_back(*it);
		if (!left_child->is_leaf()) {
			left_child->children_->push_back(right_child->children_->front());
			left_child->children_->back()->parent_ = left_child;
			right_child->children_->pop_front();
		}
		if (right_child->data_node_count() > 0) {
			this->data_nodes_->insert(it, right_child->data_nodes_->front());
			right_child->data_nodes_->pop_front();
		}
		else {
			this->remove_child_by_index(index + 1);
			delete right_child;
		}
		this->data_nodes_->erase(it);
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline void TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::rotate_right(const int index) {
		typename std::list<typename Table<KeyType, DataType>::DataNode *>::iterator it = this->data_nodes_->begin();
		std::ranges::advance(it, index);
		TwoThreeTableNode *left_child = this->child_by_index(index), *right_child = this->child_by_index(index + 1);
		right_child->data_nodes_->push_front(*it);
		if (!left_child->is_leaf()) {
			right_child->children_->push_front(left_child->children_->back());
			right_child->children_->front()->parent_ = right_child;
			left_child->children_->pop_back();
		}
		if (left_child->data_node_count() > 0) {
			this->data_nodes_->insert(it, left_child->data_nodes_->back());
			left_child->data_nodes_->pop_back();
		}
		else {
			this->remove_child_by_index(index);
			delete left_child;
		}
		this->data_nodes_->erase(it);
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::TwoThreeTableNode() :
		parent_(nullptr), data_nodes_(new std::list<typename Table<KeyType, DataType>::DataNode *>()), children_(new std::list<TwoThreeTableNode *>()) {
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::TwoThreeTableNode(const KeyType &key, const DataType &data) :
		parent_(nullptr), data_nodes_(new std::list<typename Table<KeyType, DataType>::DataNode *>()), children_(new std::list<TwoThreeTableNode *>()) {
		this->data_nodes_->push_back(new Table<KeyType, DataType>::DataNode(key, data));
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::~TwoThreeTableNode() {
		this->parent_ = nullptr;
		this->children_->clear();
		for (auto node : *this->data_nodes_) {
			delete node;
		}
		this->data_nodes_->clear();
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const bool TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::is_leaf() const {
		return this->children_->size() == 0;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const bool TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::has_data_node(const KeyType &key) const {
		for (typename Table<KeyType, DataType>::DataNode *node : *this->data_nodes_) {
			if (node->key() == key) {
				return true;
			}
		}
		return false;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const short TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::data_node_count() const {
		return this->data_nodes_->size();
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const short TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::index(const KeyType &key) const {
		short index = 0;
		for (typename Table<KeyType, DataType>::DataNode *node : *this->data_nodes_) {
			if (key <= node->key()) {
				return index;
			}
			index++;
		}
		return (const short)index;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline typename Table<KeyType, DataType>::DataNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::data_node(const KeyType &key) {
		for (typename Table<KeyType, DataType>::DataNode *node : *this->data_nodes_) {
			if (node->key() == key) {
				return node;
			}
		}
		return nullptr;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline typename Table<KeyType, DataType>::DataNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::data_by_index(const int order) {
		if (this->data_nodes_->size() == 0) {
			return nullptr;
		}
		if (order == 0) {
			return this->data_nodes_->front();
		}
		return this->data_nodes_->back();
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::child_node(const KeyType &key) {
		if (this->is_leaf()) {
			return nullptr;
		}
		int index = 0;
		for (typename Table<KeyType, DataType>::DataNode *node : *this->data_nodes_) {
			if (key <= node->key()) {
				break;
			}
			index++;
		}
		return child_by_index(index);
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::child_by_index(const int order) {
		if (this->is_leaf()) {
			return nullptr;
		}
		if (order == 0) {
			return this->children_->front();
		}
		if (order > this->data_node_count()) {
			return this->children_->back();
		}
		typename std::list<TwoThreeTableNode *>::iterator it = this->children_->begin();
		std::ranges::advance(it, order, this->children_->end());
		return *it;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline void TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::remove_child_by_index(const int index) {
		typename std::list<TwoThreeTableNode *>::iterator it = this->children_->begin();
		std::ranges::advance(it, index);
		TwoThreeTableNode *return_value = *it;
		this->children_->erase(it);
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableNode *TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::parent_node() {
		return this->parent_;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline void TwoThreeTree<KeyType, DataType>::TwoThreeTableNode::parent_node(TwoThreeTableNode *node) {
		this->parent_ = node;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableIterator::TwoThreeTableIterator(TwoThreeTree<KeyType, DataType>::TwoThreeTableNode *position) :
		path_(new std::list<typename Table<KeyType, DataType>::DataNode *>()) {
		if (position) {
			std::list<TwoThreeTableNode *> queue;
			queue.push_back(position);
			while (!queue.empty()) {
				if (!queue.front()->is_leaf()) {
					for (int i = 0; i < queue.front()->data_node_count() + 1; i++) {
						queue.push_back(queue.front()->child_by_index(i));
					}
				}
				for (int i = 0; i < queue.front()->data_node_count(); i++) {
					this->path_->push_back(queue.front()->data_by_index(i));
				}
				queue.pop_front();
			}
		}
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline TwoThreeTree<KeyType, DataType>::TwoThreeTableIterator::~TwoThreeTableIterator() {
		this->path_->clear();
		delete this->path_;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline Iterator<DataType> &TwoThreeTree<KeyType, DataType>::TwoThreeTableIterator::operator=(const Iterator<DataType> &iter) {
		if (this != &iter)
			*this->path_ = *((const TwoThreeTableIterator &)iter).path_;
		return *this;
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const bool TwoThreeTree<KeyType, DataType>::TwoThreeTableIterator::operator!=(const Iterator<DataType> &iter) const {
		return this->path_->empty() ? false : (this->path_->size() != ((const TwoThreeTableIterator &)iter).path_->size() ||
			this->path_->front() != ((const TwoThreeTableIterator &)iter).path_->front());
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline const DataType TwoThreeTree<KeyType, DataType>::TwoThreeTableIterator::operator*() const {
		return this->path_->front()->data();
	}

	template<PrimaryKeyProtocol KeyType, class DataType>
	inline Iterator<DataType> &TwoThreeTree<KeyType, DataType>::TwoThreeTableIterator::operator++() {
		this->path_->pop_front();
		return *this;
	}
}
