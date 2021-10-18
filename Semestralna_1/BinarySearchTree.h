#pragma once
#include "Table.h"
#include <queue>

namespace AUS2
{
	template <class DataType>
	requires CheckType<DataType, IComparable<DataType>> class BinarySearchTree : public Table<DataType>
	{
	protected:
		class BSTNode;
		class TreeIterator;
		class InOrderTreeIterator;
		bool try_find(const DataType &data, BSTNode *&last_checked);
		void extract_node(BSTNode *node);
	public:
		BinarySearchTree();
		~BinarySearchTree();

		virtual const size_t size() const override;
		virtual void clear() override;

		virtual bool insert(const DataType &data) override;
		virtual DataType &remove(const DataType &pattern) override;

		virtual DataType &get(const IComparator<DataType> &comparator);
		virtual const DataType get(const IComparator<DataType> &comparator) const;

		virtual DataType &get(std::list<const IComparator<DataType> &> comparator_list);
		virtual const DataType get(std::list<const IComparator<DataType> &> comparator_list) const;

		virtual Iterator<DataType> *begin_iterator() const;
		virtual Iterator<DataType> *end_iterator() const;

		void 
	private:
		BSTNode *root_;
		size_t size_;
	};

	template <class DataType>
	class BinarySearchTree<DataType>::BSTNode : public Table<DataType>::DataNode
	{
	public:
		BSTNode(const DataType &data);
		virtual ~BSTNode() override;

		BSTNode *left_son() const;
		BSTNode *right_son() const;
		BSTNode *parent() const;
		void left_son(BSTNode *node);
		void right_son(BSTNode *node);
		void parent(BSTNode *node);
		void add_son(BSTNode *node);

		const bool is_left_son() const;
		const int number_of_sons() const;
	protected:
		BSTNode *left_son_;
		BSTNode *right_son_;
		BSTNode *parent_;
	};

	template <class DataType>
	class BinarySearchTree<DataType>::TreeIterator : public Iterator<DataType>
	{
	public:
		virtual ~TreeIterator() override;
		virtual Iterator<DataType> &operator=(const Iterator<DataType> &iter) override;
		virtual const int operator==(const Iterator<DataType> &iter) const override;
		virtual const DataType operator*() const override;
		virtual Iterator<DataType> &operator++() override;
		virtual void populate_path() = 0;
	private:
		std::queue<BinarySearchTree<DataType>::BSTNode *, std::list<BinarySearchTree<DataType>::BSTNode *>> path_;

	};

	template <class DataType>
	class BinarySearchTree<DataType>::InOrderTreeIterator : public BinarySearchTree<DataType>::TreeIterator
	{

	};

#pragma region BSTIItem definition
	template <class DataType>
	inline BinarySearchTree<DataType>::BSTNode::BSTNode(const DataType &data) :
		Table<DataType>::DataNode(data), data_(data), left_son_(nullptr), right_son_(nullptr) {
	}

	template <class DataType>
	inline BinarySearchTree<DataType>::BSTNode::~BSTNode() {
		this->left_son_ = nullptr;
		this->right_son_ = nullptr;
		this->parent_ = nullptr;
	}

	template <class DataType>
	inline BinarySearchTree<DataType>::BSTNode *BinarySearchTree<DataType>::BSTNode::left_son() const {
		return this->left_son_;
	}

	template <class DataType>
	inline BinarySearchTree<DataType>::BSTNode *BinarySearchTree<DataType>::BSTNode::right_son() const {
		return this->right_son_;
	}

	template <class DataType>
	inline BinarySearchTree<DataType>::BSTNode *BinarySearchTree<DataType>::BSTNode::parent() const {
		return this->parent_;
	}

	template <class DataType>
	inline void BinarySearchTree<DataType>::BSTNode::left_son(BSTNode *node) {
		this->left_son_ = node;
	}

	template <class DataType>
	inline void BinarySearchTree<DataType>::BSTNode::right_son(BSTNode *node) {
		this->right_son_ = node;
	}

	template <class DataType>
	inline void BinarySearchTree<DataType>::BSTNode::parent(BSTNode *node) {
		this->parent_ = node;
	}

	template <class DataType>
	inline void BinarySearchTree<DataType>::BSTNode::add_son(BSTNode *node) {
		if (node->data_ < this->data_) {
			this->left_son_ = node;
		}
		else {
			this->right_son_ = node;
		}
		node->parent_ = this;
	}

	template <class DataType>
	inline const int BinarySearchTree<DataType>::BSTNode::number_of_sons() const {
		return bool(this->left_son_) + bool(this->right_son_);
	}

	template <class DataType>
	inline const bool BinarySearchTree<DataType>::BSTNode::is_left_son() const {
		return this->parent_ && this->parent_->left_son_ == this;
	}
#pragma endregion

#pragma region BinarySearchTree definition
	template<class DataType>
	inline bool BinarySearchTree<DataType>::try_find(const DataType &data, BSTNode *&last_checked) {
		BSTNode *checking = this->root_;
		last_checked = this->root_;
		while (checking && checking != data) {
			last_checked = checking;
			if (checking->data() < data) {
				checking = checking->left_son();
			}
			else {
				checking = checking->right_son();
			}
		}
		if (checking) {
			last_checked = checking;
		}
		return checking;
	}

	template<class DataType>
	inline void BinarySearchTree<DataType>::extract_node(BSTNode *node) {
		BSTNode *parent = node->parent();
		bool is_left = node->is_left_son();
		int sons = node->number_of_sons();
		node->parent(nullptr);
		switch (sons) {
		case 0:
			if (parent) {
				if (is_left) {
					parent->left_son(nullptr);
				}
				else {
					parent->right_son(nullptr);
				}
			}
			else {
				this->root_ = nullptr;
			}
			break;
		case 1:
			BSTNode * son;
			son = node->left_son() ? node->left_son() : node->right_son();
			son->parent(parent);
			if (parent) {
				if (is_left) {
					parent->left_son(son);
				}
				else {
					parent->right_son(son);
				}
			}
			else {
				this->root_ = son;
			}
			break;
		case 2:
			BSTNode * son = node->right_son();
			while (son->left_son()) {
				son = son->left_son();
			}
			if (son->right_son()) {
				son->right_son()->parent(son->parent());
				son->parent()->right_son(son->right_son())
			}
			son->left_son(node->left_son());
			son->right_son(node->right_son());
			son->parent(node->parent());
			node->left_son()->parent(son);
			node->right_son()->parent(son);
			if (parent) {
				if (is_left) {
					parent->left_son(son);
				}
				else {
					parent->right_son(son);
				}
			}
			else {
				this->root_ = son;
			}
			break;
		}
		node->left_son(nullptr);
		node->right_son(nullptr);
		node->parent(nullptr);
	}

	template<class DataType>
	inline BinarySearchTree<DataType>::BinarySearchTree() {
	}

	template<class DataType>
	inline BinarySearchTree<DataType>::~BinarySearchTree() {
	}

	template<class DataType>
	inline const size_t BinarySearchTree<DataType>::size() const {
		return this->size_;
	}

	template<class DataType>
	inline void BinarySearchTree<DataType>::clear() {
	}

	template<class DataType>
	inline bool BinarySearchTree<DataType>::insert(const DataType &data) {
		BSTNode *parent;
		if (try_find(data, parent)) {
			return false;
		}
		if (parent) {
			parent->add_son(new BSTNode(data));
		}
		else {
			this->root_ = new BSTNode(data);
		}
		this->size_++;
		return true;
	}

	template<class DataType>
	inline DataType &BinarySearchTree<DataType>::remove(const DataType &pattern) {
		BSTNode *node;
		if (try_find(pattern, node)) {
			DataType &data = node->data();
			delete node;
			this->size_--;
			return data;
		}
	}

	template<class DataType>
	inline BinarySearchTree<DataType>::TreeIterator::~TreeIterator() {
		delete this->path_;
		this->path_ = nullptr;
	}

	template<class DataType>
	inline Iterator<DataType> &BinarySearchTree<DataType>::TreeIterator::operator=(const Iterator<DataType> &iter) {
		if (this != &iter) {
			*this->path_ = *dynamic_cast<const TreeIterator &>(iter).path_;
		}
		return *this;
	}

	template<class DataType>
	inline const DataType BinarySearchTree<DataType>::TreeIterator::operator*() const {
		return this->path_->front()->data();
	}

	template<class DataType>
	inline Iterator<DataType> &BinarySearchTree<DataType>::TreeIterator::operator++() {
		if (!this->path_.empty()) {
			this->path_.pop();
		}
		return *this;
	}

	template<class DataType>
	inline const int BinarySearchTree<DataType>::TreeIterator::operator==(const Iterator<DataType> &iter) const {
		TreeIterator cast_iter = dynamic_cast<const TreeIterator &>(iter);
		return this->path_.empty() : this->path_.size() == cast_iter->path_.size() && this->path_.front()->data() == cast_iter.front()->data() ? false;
	}
}
#pragma endregion

