#pragma once
#include "DataStorage.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace AUS2
{
	class Controller
	{
	private:
		DataStorage *storage_;
		std::vector<std::string> *names_f_;
		std::vector<std::string> *names_m_;
		std::vector<std::string> *surnames_;
	public:
		Controller();
		~Controller();
		Person* add_person(const std::string id, const std::string name, const std::string surname);
		Person *add_person();
		Test* add_test(const std::string id, const int county, 
			const int district, const int station, const bool result,
			const std::string date_of_test, const std::string comment);
		Test* add_test(const std::string id);
		void remove_person(const std::string &id);
		void remove_test(const std::string &uuid);
		Person *person_by_id(const std::string &id);
		Test *test_by_uuid(const std::string &uuid);
		std::list<Person *> *people();
		std::list<Test *> *tests();
		std::list<Test *> *test_list_by_id(const std::string &id);
		std::list<Test *> *test_list_by_date(bool positive_only, const std::string date_start, const std::string date_end);
		std::list<Test *> *test_list_by_county(bool positive_only, const int county, const std::string date_start, const std::string date_end);
		std::list<Test *> *test_list_by_district(bool positive_only, const int district, const std::string date, const std::string date_end);
		std::list<Test *> *test_list_by_station(const int station, const std::string date, const std::string date_end);
	};
}
