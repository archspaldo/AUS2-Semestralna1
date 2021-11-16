#include "Controller.h"

namespace AUS2
{
	Controller::Controller() :
		storage_(new DataStorage()), generator_(new ItemGenerator())
	{
	}

	Controller::~Controller() {
		delete this->storage_;
		delete this->generator_;
	}

	void Controller::fill_database(const int station_count, const int county_count, const int district_count, const int person_count, const int test_count) {
		this->generator_->generate_to_directory(station_count, county_count, district_count, person_count, test_count);
		this->storage_->load_data();
	}

	Person *Controller::add_person(const std::string id, const std::string name, const std::string surname) {
		Person *person = new Person(id, name, surname);
		if (!this->storage_->add_person(person)) {
			return nullptr;
		}
		return person;
	}

	Test *Controller::add_test(const std::string id, const int county, const int district, const int station, const bool result, const std::string date_of_test, const std::string comment) {
		Person *person = this->storage_->person(id);
		Test *test = nullptr;
		if (person) {
			TestLocation *_station = this->storage_->location(location_t::station, station),
				*_county = this->storage_->location(location_t::county, county),
				*_district = this->storage_->location(location_t::district, district);
			if (!_station) {
				_station = new Station(station);
				this->storage_->add_location(_station);
			}
			if (!_county) {
				_county = new County(county);
				this->storage_->add_location(_county);
			}
			if (!_county) {
				_county = new District(district);
				this->storage_->add_location(_county);
			}
			std::string uuid = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
			struct tm *date = new tm;
			std::istringstream ss{ date_of_test };
			ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
			test = new Test(uuid, person, _county, _district, _station, result, std::mktime((tm *)date), comment);
			if (!this->storage_->add_test(test)) {
				return nullptr;
			}
		}
		return test;
	}

	void Controller::remove_person(const std::string &id) {
		this->storage_->remove_person(id);
	}

	void Controller::remove_test(const std::string &uuid) {
		this->storage_->remove_test(uuid);
	}

	Person *Controller::person(const std::string &id) {
		return this->storage_->person(id);
	}

	Test *Controller::test(const std::string &uuid) {
		return this->storage_->test(uuid);
	}

	std::list<Person *> *Controller::person_list() {
		return this->storage_->person_list();
	}

	std::list<Test *> *Controller::test_list() {
		return this->storage_->test_list();
	}

	std::list<Test *> *Controller::test_list_by_id(const std::string &id) {
		return this->storage_->test_list_by_id(id);
	}

	std::list<Test *> *Controller::test_list_by_location(location_t location, bool positive_only, const int id, const std::string date_start, const std::string date_end) {
		struct tm *date = (tm *)calloc(1, sizeof(tm));
		std::istringstream ss{ date_start }, ss2{ date_end };
		ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
		time_t d_start = std::mktime(date);
		free(date);
		date = (tm *)calloc(1, sizeof(tm));
		ss2 >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
		time_t d_end = std::mktime(date);
		free(date);
		return this->storage_->test_list_by_location(location, id, positive_only, d_start, d_end);
	}
	std::list<Person *> *Controller::person_list_by_location(location_t location, const int id, const std::string date_start, const std::string date_end) {
		std::list<Test *> *test_list = this->test_list_by_location(location, true, id, date_start, date_end);
		std::list<Person *> *person_list = new std::list<Person *>();
		TwoThreeTree<Person *, Test *> *checker = new TwoThreeTree<Person *, Test *>();
		Test *bin;
		for (Test *test : *test_list) {
			checker->insert_or_replace(test->person(), test, bin);
		}
		for (Test *test : *checker) {
			person_list->push_back(test->person());
		}
		delete test_list;
		delete checker;
		return person_list;
	}
	std::list<std::pair<TestLocation *, int> *> *Controller::location_by_person(location_t location, const std::string date_start, const std::string date_end) {
		std::list<Person *> *l;
		std::list<std::pair<TestLocation *, int> *> *return_list = new std::list<std::pair<TestLocation *, int> *>();
		for (TestLocation *loc : *this->storage_->location_list(location)) {
			l = this->person_list_by_location(location, loc->id(), date_start, date_end);
			return_list->push_back(new std::pair< TestLocation *, int>(loc, l->size()));
			delete l;
		}
		return return_list;
	}
}

