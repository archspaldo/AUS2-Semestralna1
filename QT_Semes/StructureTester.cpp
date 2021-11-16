#include "StructureTester.h"

namespace AUS2
{
	Tester::Tester() : 
		list_(new std::list<int>()), tree_(new TwoThreeTree<int, int>()), control_(new std::map<int, int>()), operations_(0), insert_(0), remove_(0), get_(0), interval_(0), operation_count_(0){
	}

	Tester::~Tester() {
		delete this->tree_;
		delete this->list_;
	}

	void Tester::set(int operations, int insert, int remove, int get, int interval) {
		this->operations_ = operations;
		this->insert_ = insert;
		this->remove_ = remove;
		this->get_ = get;
		this->interval_ = interval;
		this->operation_count_ = 0;
	}

	bool Tester::has_next() {
		return this->operation_count_ < this->operations_;
	}

	bool Tester::next(std::string &output) {
		int roll, rand, a, b;
		bool return_value =  true;
		rand = std::rand() % (this->insert_ + this->remove_ + this->get_ + this->interval_);
		if (rand < this->insert_) {
			try {
				roll = std::rand();
				this->tree_->insert(roll, roll);
				(*this->control_)[roll] = roll;
				this->list_->push_front(roll);
			}
			catch (...) {
			}
		}
		else if (rand < this->insert_ + this->remove_) {
			if (this->list_->empty()) {
			}
			else {
				a = this->tree_->remove(this->list_->front());
				b = (*this->control_)[this->list_->front()];
				this->control_->erase(this->list_->front());
				this->list_->pop_front();
				return_value = a == b;
			}
		}
		else  if (rand < this->insert_ + this->remove_ + this->get_){
			if (this->list_->empty()) {
			}
			else {
				return_value = this->tree_->get(this->list_->front()) == (*this->control_)[this->list_->front()];
			}
		}
		else {
			int min = std::rand(), max = std::rand();
			if (min > max) {
				std::swap(min, max);
			}
			std::list<int> *l = this->tree_->get_interval(min, max);
			auto iter = this->control_->lower_bound(min);
			for (int i : *l) {
				if ((*iter).second != i) {
					return_value = false;
				}
			}
			delete l;
			return_value = true;
		}
		this->operation_count_++;
		return return_value;
	}
	void Tester::reset() {
		this->control_->clear();
		this->tree_->clear();
		this->list_->clear();
		this->operation_count_ = 0;
	}
}