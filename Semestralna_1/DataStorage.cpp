#include "DataStorage.h"

namespace AUS2
{
	DataStorage::DataStorage() :
		person_(new TwoThreeTree<const std::string &, Person *>()), test_(TwoThreeTree<const std::string &, Test *>()),
		person_test_(new TwoThreeTree<Person *, TwoThreeTree<const tm *, Test *> *>()),
		date_test_(new TwoThreeTree<const long, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *>),
		county_test_(new TwoThreeTree<const int &, TwoThreeTree<const long, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *> *>()),
		district_test_(new TwoThreeTree<const int &, TwoThreeTree<const long, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *> *>()),
		station_test_(new TwoThreeTree<const int &, TwoThreeTree<const long, TwoThreeTree<const std::string &, Test *> *> *>())
	{
	}

	DataStorage::~DataStorage()
	{
		for (auto node : *this->person_) {
			delete node;
		}
		for (auto node : *this->test) {
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
		delete this->station_test_

	}
	void DataStorage::add_person(Person *person)
	{
		this->person_->insert(person->id(), person);
		this->person_test_->insert(person, new TwoThreeTree<const tm *, Test *>());
	}
	void DataStorage::add_test(Test *test)
	{
		const long date = test->date_of_test()->tm_year * 10000 + test->date_of_test()->tm_mon * 100 + test->date_of_test()->tm_mday;
		this->test_->insert(test->uuid(), test);
		this->person_test_->get(test->person())->insert(test->date_of_test(), test);
		if (!this->date_test_->contains_key(date)) {
			this->date_test_->insert(date, new TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *>());
			auto t = this->date_test_->get(date);
			t->insert(true, new TwoThreeTree<const std::string &, Test *>());
			t->insert(false, new TwoThreeTree<const std::string &, Test *>());
		}
		this->date_test_->get(date)->get(test->result())->insert(test->uuid(), test);

		if (!this->county_test_->contains_key(test->county())) {
			this->county_test_->insert(test->county(), new TwoThreeTree<const long, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *>());
			this->county_test_->get(test->county())->insert(date, new TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *>());
			auto t = this->county_test_->get(test->county())->get(date);
			t->insert(true, new TwoThreeTree<const std::string &, Test *>());
			t->insert(false, new TwoThreeTree<const std::string &, Test *>());
		}
		this->county_test_->get(test->county())->get(date)->get(test->result())->insert(test->uuid(), test);

		if (!this->district_test_->contains_key(test->district())) {
			this->district_test_->insert(test->district(), new TwoThreeTree<const long, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *>());
			this->district_test_->get(test->district())->insert(date, new TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *>());
			auto t = this->district_test_->get(test->district())->get(date);
			t->insert(true, new TwoThreeTree<const std::string &, Test *>());
			t->insert(false, new TwoThreeTree<const std::string &, Test *>());
		}
		this->district_test_->get(test->district())->get(date)->get(test->result())->insert(test->uuid(), test);

		if (!this->station_test_->contains_key(test->station())) {
			this->station_test_->insert(test->station(), new TwoThreeTree<const long, TwoThreeTree<const std::string &, Test *> *>());
			this->station_test_->get(test->station())->insert(date, new TwoThreeTree<const std::string &, Test *>());
		}
		this->station_test_->get(test->station())->get(date)->insert(test->uuid(), test);
	}
	void DataStorage::remove_person(const std::string &id)
	{
		if (this->person_.contains_key(id)) {
			for (auto node : *this->person_test_->get(this->person_.get(id))) {
				this->remove_test(node->uuid());
			}
			this->person_test_->remove(this->person_.get(id));
			delete this->person_->get(id);
			this->person_->remove(id);
		}
	}
	void DataStorage::remove_test(const std::string &uuid)
	{
		if (this->test_->contains_key(uuid)) {
			auto test = this->test_->get(uuid);
			const long date = test->date_of_test()->tm_year * 10000 + test->date_of_test()->tm_mon * 100 + test->date_of_test()->tm_mday;
			this->date_test_->get(date)->get(test->result())->remove(uuid);
			this->county_test_->get(test->county())->get(date)->get(test->result())->remove(uuid);
			this->district_test_->get(test->district())->get(date)->get(test->result())->remove(uuid);
			this->station_test_->get(test->station())->get(date)->remove(uuid);
			this->person_test_->get(test->person())->remove(test->date_of_test());
			delete test;
			this->test_->remove(uuid);
		}
	}
	Person *DataStorage::person_by_id(const std::string &id)
	{
		return nullptr;
	}
	Test *DataStorage::test_by_uuid_id(const std::string &uuid, const std::string &id)
	{
		return nullptr;
	}
	std::list<Test *> *DataStorage::test_list_by_id(const std::string &id)
	{
		return nullptr;
	}
	std::list<Test *> *DataStorage::test_list_by_date(bool positive_only, const tm *date_start, const tm *date_end)
	{
		return nullptr;
	}
	std::list<Test *> *DataStorage::test_list_by_county(bool positive_only, const int county, const tm *date, const tm *date_end)
	{
		return nullptr;
	}
	std::list<Test *> *DataStorage::test_list_by_district(bool positive_only, const int district, const tm *date, const tm *date_end)
	{
		return nullptr;
	}
	std::list<Test *> *DataStorage::test_list_by_station(const int station, const tm *date, const tm *date_end)
	{
		return nullptr;
	}
}