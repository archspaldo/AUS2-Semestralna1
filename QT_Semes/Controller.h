#pragma once
#include "DataStorage.h"
#include "ItemGenerator.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <utility>

namespace AUS2
{
	class Controller
	{
	private:
		DataStorage *storage_;
		ItemGenerator *generator_;
	public:
		Controller();
		~Controller();
		void fill_database(const int station_count, const int county_count, const int district_count, const int person_count, const int test_count);
		Person* add_person(const std::string id, const std::string name, const std::string surname);
		Test* add_test(const std::string id, const int county, 
			const int district, const int station, const bool result,
			const std::string date_of_test, const std::string comment);
		void remove_person(const std::string &id);
		void remove_test(const std::string &uuid);
		Person *person(const std::string &id);
		Test *test(const std::string &uuid);
		std::list<Person *> *person_list();
		std::list<Test *> *test_list();
		std::list<Test *> *test_list_by_id(const std::string &id);
		std::list<Test *> *test_list_by_location(location_t location, bool positive_only, const int id, const std::string date_start, const std::string date_end);
		std::list<Person *> *person_list_by_location(location_t location, const int id, const std::string date_start, const std::string date_end);
		std::list<std::pair<TestLocation *, int> *> *location_list_by_positive_person_count(location_t location, const std::string date_start, const std::string date_end);
	};
}
