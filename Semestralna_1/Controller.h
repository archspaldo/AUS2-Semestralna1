#pragma once
#include "Factory.h"
#include "DataStorage.h"
#include <iostream>

namespace AUS2
{
	class Controller
	{
	private:
		DataStorage *storage_;
	public:
		Controller();
		~Controller();
		void add_person(const std::string &id, const std::string &name, const std::string &surname);
		void add_person();
		void add_test(const std::string &id, const int &district,
			const int &county, const int &station, const bool &result,
			const std::string &date_of_test, const std::string &comment);
		void add_test();
		void remove_person(const std::string &id);
		void remove_test(const std::string &uuid);
		void test_by_uuid_id(const std::string &uuid, const std::string &id);
		void test_list_by_id(const std::string &id);
		void test_list_by_date(bool positive_only, const tm *date_start, const tm *date_end);
		void test_list_by_county(bool positive_only, const int county, const tm *date, const tm *date_end);
		void test_list_by_district(bool positive_only, const int district, const tm *date, const tm *date_end);
		void test_list_by_station(const int station, const tm *date, const tm *date_end);
		void person();
		void test();
	};
}
