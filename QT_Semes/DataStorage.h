#pragma once
#include "2-3Tree.h"
#include "CompositeKey.h"
#include <fstream>
#include <limits>
#include <sstream>

namespace AUS2
{
	class DataStorage
	{
	private:
		TwoThreeTree<const std::string &, Person *> *person_;
		TwoThreeTree<const std::string &, Test *> *test_;
		TwoThreeTree<const CKLocID, TestLocation *> *location_;
		TwoThreeTree<const std::string &, TwoThreeTree<const time_t, Test *> *> *tests_by_person_;
		TwoThreeTree<const CKLocResult, TwoThreeTree<const time_t, std::list<Test *> *> *> *tests_by_location_;
		TwoThreeTree<const int, TwoThreeTree<const std::string &, std::list<Test *> *> *> *tests_by_county_;
		std::string max_;
	public:
		DataStorage();
		~DataStorage();
		void clear();
		void save_data(const std::string &directory = "../data_storage/");
		void load_data(const std::string &directory = "../data_storage/");
		bool add_person(Person *person);
		bool add_test(Test *test);
		bool add_location(TestLocation *location);
		void remove_person(const std::string &id);
		void remove_test(const std::string &uuid);
		Person *person(const std::string &id);
		Test *test(const std::string &uuid);
		TestLocation *location(const location_t location, const int id);
		std::list<Person *> *person_list();
		std::list<Test *> *test_list();
		std::list<TestLocation *> *location_list(const location_t location);
		std::list<Test *> *test_list_by_id(const std::string &id);
		std::list<Test *> *test_list_by_id(const std::string &id, bool positive_only, const time_t date_start, const time_t date_to);
		std::list<Test *> *test_list_by_location(const location_t location, const int id, bool positive_only, const time_t date_start, const time_t date_end);
		std::list<Test *> *test_by_county(const int id);
	};
}