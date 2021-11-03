#include "DataStorage.h"

namespace AUS2
{
	DataStorage::DataStorage() :
		person_(new TwoThreeTree<const std::string &, Person *>()), test_(new TwoThreeTree<const std::string &, Test *>()),
		person_test_(new TwoThreeTree<const std::string &, TwoThreeTree<const time_t, Test *> *>()),
		date_test_(new TwoThreeTree<const time_t, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *>),
		county_test_(new TwoThreeTree<const int, TwoThreeTree<const time_t, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *> *>()),
		district_test_(new TwoThreeTree<const int, TwoThreeTree<const time_t, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *> *>()),
		station_test_(new TwoThreeTree<const int, TwoThreeTree<const time_t, TwoThreeTree<const std::string &, Test *> *> *>())
	{
	}

	DataStorage::~DataStorage()
	{
		for (auto node : *this->person_) {
			delete node;
		}
		for (auto node : *this->test_) {
			delete node;
		}
		for (auto node : *this->person_test_) {
			delete node;
		}
		for (auto node : *this->date_test_) {
			for (auto node_1 : *node) {
				delete node_1;
			}
			delete node;
		}
		for (auto node : *this->county_test_) {
			for (auto node_1 : *node) {
				for (auto node_2 : *node_1) {
					delete node_2;
				}
				delete node_1;
			}
			delete node;
		}
		for (auto node : *this->district_test_) {
			for (auto node_1 : *node) {
				for (auto node_2 : *node_1) {
					delete node_2;
				}
				delete node_1;
			}
			delete node;
		}
		for (auto node : *this->station_test_) {
			for (auto node_1 : *node) {
				delete node_1;
			}
			delete node;
		}
		delete this->person_;
		delete this->test_;
		delete this->person_test_;
		delete this->date_test_;
		delete this->county_test_;
		delete this->district_test_;
		delete this->station_test_;

	}
	bool DataStorage::add_person(Person *person)
	{
		try {
			this->person_->insert(person->id(), person);
		}
		catch (...) {
			delete person;
			return false;
		}
		this->person_test_->insert(person->id(), new TwoThreeTree<const time_t, Test *>());
		return true;
	}
	bool DataStorage::add_test(Test *test)
	{
		const time_t date = std::mktime((tm *)test->date_of_test());
		try {
			this->test_->insert(test->uuid(), test);
		}
		catch (...) {
			delete test;
			return false;
		}
		this->person_test_->get(test->person()->id())->insert(date, test);

		if (!this->date_test_->contains_key(date)) {
			this->date_test_->insert(date, new TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *>());
			auto t = this->date_test_->get(date);
			t->insert(true, new TwoThreeTree<const std::string &, Test *>());
			t->insert(false, new TwoThreeTree<const std::string &, Test *>());
		}
		this->date_test_->get(date)->get(test->result())->insert(test->uuid(), test);


		if (!this->county_test_->contains_key(test->county())) {
			this->county_test_->insert(test->county(), new TwoThreeTree<const time_t, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *>());
		}
		if (!this->county_test_->get(test->county())->contains_key(date)) {
			this->county_test_->get(test->county())->insert(date, new TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *>());
			auto t = this->county_test_->get(test->county())->get(date);
			t->insert(true, new TwoThreeTree<const std::string &, Test *>());
			t->insert(false, new TwoThreeTree<const std::string &, Test *>());
		}
		this->county_test_->get(test->county())->get(date)->get(test->result())->insert(test->uuid(), test);

		if (!this->district_test_->contains_key(test->district())) {
			this->district_test_->insert(test->district(), new TwoThreeTree<const time_t, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *>());
		}
		if (!this->district_test_->get(test->district())->contains_key(date)) {
			this->district_test_->get(test->district())->insert(date, new TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *>());
			auto t = this->district_test_->get(test->district())->get(date);
			t->insert(true, new TwoThreeTree<const std::string &, Test *>());
			t->insert(false, new TwoThreeTree<const std::string &, Test *>());
		}
		this->district_test_->get(test->district())->get(date)->get(test->result())->insert(test->uuid(), test);

		if (!this->station_test_->contains_key(test->station())) {
			this->station_test_->insert(test->station(), new TwoThreeTree<const time_t, TwoThreeTree<const std::string &, Test *> *>());
		}
		if (!this->station_test_->get(test->station())->contains_key(date)) {
			this->station_test_->get(test->station())->insert(date, new TwoThreeTree<const std::string &, Test *>());
		}
		this->station_test_->get(test->station())->get(date)->insert(test->uuid(), test);
		return true;
	}
	void DataStorage::remove_person(const std::string &id)
	{
		if (this->person_->contains_key(id)) {
			for (auto node : *this->person_test_->get(id)) {
				this->remove_test(node->uuid());
			}
			this->person_test_->remove(id);
			delete this->person_->remove(id);
		}
	}
	void DataStorage::remove_test(const std::string &uuid)
	{
		if (this->test_->contains_key(uuid)) {
			auto test = this->test_->get(uuid);
			const time_t date = std::mktime((tm *)test->date_of_test());
			this->date_test_->get(date)->get(test->result())->remove(uuid);
			this->county_test_->get(test->county())->get(date)->get(test->result())->remove(uuid);
			this->district_test_->get(test->district())->get(date)->get(test->result())->remove(uuid);
			this->station_test_->get(test->station())->get(date)->remove(uuid);
			this->person_test_->get(test->person()->id())->remove(date);
			delete this->test_->remove(uuid);
		}
	}
	Person *DataStorage::person_by_id(const std::string &id)
	{
		try {
			return this->person_->get(id);
		}
		catch (...) {
			return nullptr;
		}
		
	}
	Test *DataStorage::test_by_uuid(const std::string &uuid) {
		try {
			return this->test_->get(uuid);
		}
		catch (...) {
			return nullptr;
		}
	}
	std::string DataStorage::next_id(const std::string &id) {
		std::list<Person *> *l = this->person_->get(id + "/0000", id + "/9999");
		std::string next;
		if (!l->empty()) {
			next = l->back()->id();
		}
		else {
			next = id + "/0000";
		}
		delete l;
		next = next.substr(0, 6) + next.substr(7, 4);
		long long i = std::stoll(next);
		if (i % 11 == 0) {
			i += 11;
		}
		else {

			while (i % 11 != 0) {
				i++;
			}
		}
		next = std::to_string(i);
		return id + '/' + next.substr(next.size() - 4, 4);
	}
	std::list<Person *> *DataStorage::people() {
		std::list<Person *> *l = new std::list<Person *>();
		for (auto obj : *this->person_) {
			l->push_back(obj);
		}
		return l;
	}
	std::list<Test *> *DataStorage::tests() {
		std::list<Test *> *l = new std::list<Test *>();
		for (auto obj : *this->test_) {
			l->push_back(obj);
		}
		return l;
	}
	std::list<Test *> *DataStorage::test_list_by_id(const std::string &id)
	{
		std::list<Test *> *tests = new std::list<Test *>();
		for (auto test : *this->person_test_->get(id)) {
			tests->push_back(test);
		}
		return tests;
	}
	std::list<Test *> *DataStorage::test_list_by_date(bool positive_only, const time_t date_start, const time_t date_end)
	{
		std::list<Test *> *tests = new std::list<Test *>();
		for (auto obj : *this->date_test_->get(date_start, date_end)) {
			if (!positive_only) {
				for (auto o : *obj->get(false)) {
					tests->push_back(o);
				}
			}
			for (auto o : *obj->get(true)) {
				tests->push_back(o);
			}
		}
		return tests;
	}
	std::list<Test *> *DataStorage::test_list_by_county(bool positive_only, const int county, const time_t date_start, const time_t date_end)
	{
		std::list<Test *> *tests = new std::list<Test *>();
		if (this->county_test_->contains_key(county)) {
			for (auto obj : *this->county_test_->get(county)->get(date_start, date_end)) {
				if (!positive_only) {
					for (auto o : *obj->get(false)) {
						tests->push_back(o);
					}
				}
				for (auto o : *obj->get(true)) {
					tests->push_back(o);
				}
			}
		}
		return tests;
	}
	std::list<Test *> *DataStorage::test_list_by_district(bool positive_only, const int district, const time_t date_start, const time_t date_end)
	{
		std::list<Test *> *tests = new std::list<Test *>();
		if (this->district_test_->contains_key(district)) {
			for (auto obj : *this->district_test_->get(district)->get(date_start, date_end)) {
				if (!positive_only) {
					for (auto o : *obj->get(false)) {
						tests->push_back(o);
					}
				}
				for (auto o : *obj->get(true)) {
					tests->push_back(o);
				}
			}
		}
		return tests;
	}
	std::list<Test *> *DataStorage::test_list_by_station(const int station, const time_t date_start, const time_t date_end)
	{
		std::list<Test *> *tests = new std::list<Test *>();
		if (this->station_test_->contains_key(station)) {
			for (auto obj : *this->station_test_->get(station)->get(date_start, date_end)) {
				for (auto o : *obj) {
					tests->push_back(o);
				}
			}
		}
		return tests;
	}
}