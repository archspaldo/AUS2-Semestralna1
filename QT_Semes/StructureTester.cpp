#include "StructureTester.h"

namespace AUS2
{
	Tester::Tester() : 
		list_(new std::list<int>()), tree_(new TwoThreeTree<int, int>()), control_(new std::map<int, int>()), operations_(0), insert_(0), remove_(0), get_(0), interval_(0), operation_count_(0){
	}

	Tester::~Tester() {
		this->reset();
		delete this->tree_;
		delete this->list_;
		delete this->control_;
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
				this->control_->insert({ roll, roll });
				this->list_->push_front(roll);
				output = "Pridany prvok " + std::to_string(roll) + ':' + std::to_string(roll);
			}
			catch (...) {
				output = "Prvok uz bol pridany";
			}
		}
		else if (rand < this->insert_ + this->remove_) {
			if (this->list_->empty()) {
				output = "Zoznam je prazdny";
			}
			else {
				auto pos = std::next(this->list_->begin(), std::rand() % this->list_->size());
				a = this->tree_->remove(*pos);
				b = (*this->control_)[*pos];
				this->control_->erase(*pos);
				this->list_->erase(pos);
				return_value = a == b;
				output = "Odobraty prvok " + std::to_string(a) + ':' + std::to_string(a);
			}
		}
		else  if (rand < this->insert_ + this->remove_ + this->get_){
			if (this->list_->empty()) {
				output = "Zoznam je prazdny";
			}
			else {
				auto pos = std::next(this->list_->begin(), std::rand() % this->list_->size());
				return_value = this->tree_->get(*pos) == (*this->control_)[*pos];
				output = "Spristupneny prvok " + std::to_string(*pos) + ':' + std::to_string(*pos);
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
				iter = std::next(iter);
			}
			delete l;
			output = "Prvky v rozsahu " + std::to_string(min) + ':' + std::to_string(max);
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