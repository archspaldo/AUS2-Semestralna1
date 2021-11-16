#include "DataStorage.h"

namespace AUS2
{
	DataStorage::DataStorage() :
		person_(new TwoThreeTree<const std::string &, Person *>()),
		test_(new TwoThreeTree<const std::string &, Test *>()),
		locations_(new TwoThreeTree<const CKLocID, TestLocation *>()),
		tests_by_person_(new TwoThreeTree<const std::string &, TwoThreeTree<const time_t, Test *> *>()),
		tests_by_location_(new TwoThreeTree<const CKLocResult, TwoThreeTree<const time_t, std::list<Test *> *> *>()) {
	}

	DataStorage::~DataStorage() {
		this->clear();
		delete this->person_;
		delete this->test_;
		delete this->locations_;
		delete this->tests_by_person_;
		delete this->tests_by_location_;
	}

	void DataStorage::clear() {
		for (auto node : *this->tests_by_person_) {
			delete node;
		}
		for (auto node : *this->tests_by_location_) {
			for (auto t : *node) {
				delete t;
			}
			delete node;
		}
		for (auto node : *this->person_) {
			delete node;
		}
		for (auto node : *this->test_) {
			delete node;
		}
		for (auto node : *this->locations_) {
			delete node;
		}

		this->person_->clear();
		this->test_->clear();
		this->locations_->clear();
		this->tests_by_person_->clear();
		this->tests_by_location_->clear();
	}

	void DataStorage::save_data(const std::string &directory) {
		std::ofstream output;

		output.open(directory + "person.csv");
		output << "ID,Name,Surname";
		for (Person *person : *this->person_) {
			output << '\n' << person->id() << ',' << person->name() << ',' << person->surname();
		}
		output.close();

		output.open(directory + "test.csv");
		output << "UUID,ID,Station,County,District,Result,Date,Comment";
		for (Test *test : *this->test_) {
			output << '\n' << test->uuid() << ',' << test->person()->id() << ',' << test->location(location_t::station) << ','
				<< test->location(location_t::county) << ',' << test->location(location_t::district) << ','
				<< test->result() << ',' << test->date_of_test() << ',' << test->comment();
		}
		output.close();

		std::string str[3] = { "station.csv", "county.csv", "district.csv" };
		for (location_t loc = location_t::station; loc != location_t::state; ++loc) {
			output.open(directory + str[static_cast<int>(loc)]);
			output << "ID";
			for (TestLocation *location : *this->locations_->get_interval(CKLocID(loc, INT_MIN), CKLocID(loc, INT_MAX))) {
				output << '\n' << location->id();
			}
			output.close();
		}
	}

	void DataStorage::load_data(const std::string &directory) {
		std::list<std::string> buffer;
		std::ifstream input;
		std::string line, colname;
		
		this->clear();

		input.open(directory + "person.csv");
		std::getline(input, line);
		std::string id, name, surname;
		while (std::getline(input, line)) {
			std::stringstream sstream(line);
			while (std::getline(sstream, line, ',')) {
				buffer.push_back(line);
			}
			id = buffer.front();
			buffer.pop_front();
			name = buffer.front();
			buffer.pop_front();
			surname = buffer.front();
			buffer.pop_front();
			this->add_person(new Person(id, name, surname));
		}
		input.close();

		int lid;
		input.open(directory + "station.csv");
		while (std::getline(input, line)) {
			std::stringstream sstream(line);
			sstream >> lid;
			this->add_location(new Station(lid));
		}

		input.close();
		input.open(directory + "county.csv");
		while (std::getline(input, line)) {
			std::stringstream sstream(line);
			sstream >> lid;
			this->add_location(new County(lid));
		}
		input.close();
		input.open(directory + "district.csv");
		while (std::getline(input, line)) {
			std::stringstream sstream(line);
			sstream >> lid;
			this->add_location(new District(lid));
		}
		input.close();
		
		input.open(directory + "test.csv");
		std::getline(input, line);
		std::string uuid, person, comment;
		int station, county, district;
		bool result;
		while (std::getline(input, line)) {
			std::stringstream sstream(line);
			while (std::getline(sstream, line, ',')) {
				buffer.push_back(line);
			}
			uuid = buffer.front();
			buffer.pop_front();
			person = buffer.front();
			buffer.pop_front();
			station = std::stoi(buffer.front());
			buffer.pop_front();
			county = std::stoi(buffer.front());
			buffer.pop_front();
			district = std::stoi(buffer.front());
			buffer.pop_front();
			result = std::stoi(buffer.front());
			buffer.pop_front();

			struct tm *date = new tm;
			std::istringstream ss{ buffer.front() };
			ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
			buffer.pop_front();

			comment = buffer.front();
			buffer.pop_front();

			this->add_test(new Test(uuid, this->person(person), this->location(location_t::county, county),
				this->location(location_t::district, district), this->location(location_t::station, station),
				result, std::mktime(date), comment));

			delete date;
		}
		input.close();

	}

	bool DataStorage::add_person(Person *person) {
		try {
			this->person_->insert(person->id(), person);
		}
		catch (...) {
			delete person;
			return false;
		}
		this->tests_by_person_->insert(person->id(), new TwoThreeTree<const time_t, Test *>());
		return true;
	}

	bool DataStorage::add_test(Test *test) {
		try {
			this->test_->insert(test->uuid(), test);
		}
		catch (...) {
			delete test;
			return false;
		}
		this->tests_by_person_->get(test->person()->id())->insert(test->date_of_test(), test);
		for (location_t loc = location_t::station; loc != location_t::state; ++loc) {
			CKLocResult cklr = CKLocResult(loc, test->location(loc)->id(), test->result());
			if (!this->tests_by_location_->contains_key(cklr)) {
				this->tests_by_location_->insert(cklr, new TwoThreeTree<const time_t, std::list<Test *> *>());
			}
			auto t = this->tests_by_location_->get(cklr);
			if (!t->contains_key(test->date_of_test())) {
				t->insert(test->date_of_test(), new std::list<Test *>());
			}
			t->get(test->date_of_test())->push_back(test);
		}
		CKLocResult cklr = CKLocResult(location_t::state, 0, test->result());
		if (!this->tests_by_location_->contains_key(cklr)) {
			this->tests_by_location_->insert(cklr, new TwoThreeTree<const time_t, std::list<Test *> *>());
		}
		auto t = this->tests_by_location_->get(cklr);
		if (!t->contains_key(test->date_of_test())) {
			t->insert(test->date_of_test(), new std::list<Test *>());
		}
		t->get(test->date_of_test())->push_back(test);
		return true;
	}

	bool DataStorage::add_location(TestLocation *location) {
		try {
			this->locations_->insert(CKLocID(location->location_type(), location->id()), location);
		}
		catch (...) {
			delete location;
			return false;
		}
		return true;
	}

	void DataStorage::remove_person(const std::string &id) {
		if (this->person_->contains_key(id)) {
			for (auto node : *this->tests_by_person_->get(id)) {
				this->remove_test(node->uuid());
			}
			delete this->tests_by_person_->remove(id);
			delete this->person_->remove(id);
		}
	}
	void DataStorage::remove_test(const std::string &uuid) {
		if (this->test_->contains_key(uuid)) {
			Test *test = this->test_->get(uuid);
			for (location_t loc = location_t::station; loc != location_t::state; ++loc) {
				CKLocResult cklr = CKLocResult(loc, test->location(loc)->id(), test->result());
				this->tests_by_location_->get(cklr)->get(test->date_of_test())->remove(test);
			}
			CKLocResult cklr = CKLocResult(location_t::state, 0, test->result());
			this->tests_by_location_->get(cklr)->get(test->date_of_test())->remove(test);
			this->tests_by_person_->get(test->person()->id())->remove(test->date_of_test());
			delete this->test_->remove(uuid);
		}
	}

	Person *DataStorage::person(const std::string &id) {
		try {
			return this->person_->get(id);
		}
		catch (...) {
			return nullptr;
		}

	}
	Test *DataStorage::test(const std::string &uuid) {
		try {
			return this->test_->get(uuid);
		}
		catch (...) {
			return nullptr;
		}
	}
	TestLocation *DataStorage::location(const location_t location, const int id) {
		try {
			return this->locations_->get(CKLocID(location, id));
		}
		catch (...) {
			return nullptr;
		}
	}
	std::list<Person *> *DataStorage::person_list() {
		std::list<Person *> *l = new std::list<Person *>();
		for (auto obj : *this->person_) {
			l->push_back(obj);
		}
		return l;
	}
	std::list<Test *> *DataStorage::test_list() {
		std::list<Test *> *l = new std::list<Test *>();
		for (auto obj : *this->test_) {
			l->push_back(obj);
		}
		return l;
	}
	std::list<TestLocation *> *DataStorage::location_list(const location_t location) {
		std::list<TestLocation *> *l = new std::list<TestLocation *>();
		for (auto obj : *this->locations_->get_interval(CKLocID(location, INT_MIN), CKLocID(location, INT_MAX))) {
			l->push_back(obj);
		}
		return l;
	}
	std::list<Test *> *DataStorage::test_list_by_id(const std::string &id) {
		std::list<Test *> *test_list = new std::list<Test *>();
		for (auto test : *this->tests_by_person_->get(id)) {
			test_list->push_back(test);
		}
		return test_list; 
	}
	std::list<Test *> *DataStorage::test_list_by_location(const location_t location, const int id, bool positive_only, const time_t date_start, const time_t date_end) {
		std::list<Test *> *test_list = new std::list<Test *>();
		for (auto tree : *this->tests_by_location_->get_interval(CKLocResult(location, id, positive_only), CKLocResult(location, id, true))) {
			for (auto test : *tree->get_interval(date_start, date_end)) {
				test_list->insert(test_list->end(), test->begin(), test->end());
			}
		}
		return test_list;
	}
}