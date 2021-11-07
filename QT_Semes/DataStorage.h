#pragma once
#include "2-3Tree.h"
#include "DataItems.h"

namespace AUS2
{
	class DataStorage
	{
	private:
		TwoThreeTree<const std::string &, Person *> *person_;
		TwoThreeTree<const std::string &, Test *> *test_;
		TwoThreeTree<const std::string &, TwoThreeTree<const time_t, Test *> *> *person_test_;
		TwoThreeTree<const time_t, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *> *date_test_;
		TwoThreeTree<const int, TwoThreeTree<const time_t, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *> *> *county_test_;
		TwoThreeTree<const int, TwoThreeTree<const time_t, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *> *> *district_test_;
		TwoThreeTree<const int, TwoThreeTree<const time_t, TwoThreeTree<const std::string &, Test *> *> *> *station_test_;
	public:
		DataStorage();
		~DataStorage();
		bool add_person(Person *person);
		bool add_test(Test *test);
		void remove_person(const std::string &id);
		void remove_test(const std::string &uuid);
		Person *person_by_id(const std::string &id);
		Test *test_by_uuid(const std::string &uuid);
		std::string next_id(const std::string &id);
		std::list<Person *> *people();
		std::list<Test *> *tests();
		std::list<Test *> *test_list_by_id(const std::string &id);
		std::list<Test *> *test_list_by_date(bool positive_only, const time_t date_start, const time_t date_end);
		std::list<Test *> *test_list_by_county(bool positive_only, const int county, const time_t date_start, const time_t date_end);
		std::list<Test *> *test_list_by_district(bool positive_only, const int district, const time_t date_start, const time_t date_end) ;
		std::list<Test *> *test_list_by_station(const int station, const time_t date_start, const time_t date_end);
	};
}