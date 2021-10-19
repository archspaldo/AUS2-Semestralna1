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
		TwoThreeTree<Person *, TwoThreeTree<const tm *, Test *>*> *person_test_;
		TwoThreeTree<const long, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *> *date_test_;
		TwoThreeTree<const int &, TwoThreeTree<const long, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *>*> *county_test_;
		TwoThreeTree<const int &, TwoThreeTree<const long, TwoThreeTree<bool, TwoThreeTree<const std::string &, Test *> *> *>*> *district_test_;
		TwoThreeTree<const int &, TwoThreeTree<const long, TwoThreeTree<const std::string &, Test *> *> *> *station_test_;
	public:
		DataStorage();
		~DataStorage();
		void add_person(Person *person);
		void add_test(Test *test);
		void remove_person(const std::string &id);
		void remove_test(const std::string &uuid);
		Person *person_by_id(const std::string &id);
		Test *test_by_uuid_id(const std::string &uuid, const std::string &id);
		std::list<Test *> *test_list_by_id(const std::string &id);
		std::list<Test *> *test_list_by_date(bool positive_only, const tm *date_start, const tm *date_end);
		std::list<Test *> *test_list_by_county(bool positive_only, const int county, const tm *date, const tm *date_end);
		std::list<Test *> *test_list_by_district(bool positive_only, const int district, const tm *date, const tm *date_end);
		std::list<Test *> *test_list_by_station(const int station, const tm *date, const tm *date_end);
	};
}