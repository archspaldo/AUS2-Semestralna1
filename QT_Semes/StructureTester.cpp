#include "StructureTester.h"

namespace AUS2
{
	Tester::Tester() : 
		list_(new std::list<int>()), tree_(new TwoThreeTree<int, int>()), operations_(0), insert_(0), remove_(0), get_(0), interval_(0), operation_count_(0){
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

	std::string Tester::next() {
		std::string output;
		int roll, rand;
		rand = std::rand() % (this->insert_ + this->remove_ + this->get_ + this->interval_);
		if (rand < this->insert_) {
			try {
				roll = std::rand();
				this->tree_->insert(roll, roll);
				this->list_->push_front(roll);
				output = "Pridavanie: pridane " + std::to_string(roll) + '-' + std::to_string(roll);
			}
			catch (...) {
				output = "Pridavanie: kluc uz bol pridany";
			}
		}
		else if (rand < this->insert_ + this->remove_) {
			if (this->list_->empty()) {
				output = "Vymazanie: strom je prazdny";
			}
			else {
				output = "Vymazanie: vymazane " + std::to_string(this->list_->front()) + '-' + std::to_string(this->tree_->remove(this->list_->front()));
				this->list_->pop_front();
			}
		}
		else  if (rand < this->insert_ + this->remove_ + this->get_){
			if (this->list_->empty()) {
				output = "Pristup: strom je prazdny";
			}
			else {
				output = "Pristup: pristup " + std::to_string(this->list_->front()) + '-' + std::to_string(this->tree_->get(this->list_->front()));
			}
		}
		else {
			int min = std::rand(), max = std::rand();
			if (min > max) {
				std::swap(min, max);
			}
			output = "Interval: od " + std::to_string(min) + " do " + std::to_string(max) + ": ";
			std::list<int> *l = this->tree_->get(min, max);
			for (auto obj : *l) {
				output += std::to_string(obj) + ", ";
			}
			delete l;
		}
		this->operation_count_++;
		return output;
	}
	void Tester::reset() {
		this->tree_->clear();
		this->list_->clear();
		this->operation_count_ = 0;
	}
}