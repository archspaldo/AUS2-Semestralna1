#pragma once
#pragma comment(lib, "rpcrt4.lib")
#include <Windows.h>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>

namespace AUS2
{
	enum class location_t { station = 0, county = 1, district = 2, state = 3};
	location_t &operator++(location_t &c);

	class TestLocation
	{
	private:
		const location_t location_;
		int id_;
	protected:
		TestLocation(int id, location_t location);
	public:
		const int &id();
		const location_t location_type();
	};

	class County : public TestLocation
	{
	public:
		County(const int id);
	};

	class District : public TestLocation
	{
	public:
		District(const int id);
	};

	class Station : public TestLocation
	{
	public:
		Station(const int id);
	};

	class State : public TestLocation
	{
	public:
		State();
	};

	class Person
	{
	private:
		std::string id_;
		std::string name_;
		std::string surname_;
	public:
		Person(const std::string id, const std::string name, const std::string surname);
		~Person();
		const std::string &id();
		const std::string &name();
		const std::string &surname();
		const std::string date_of_birth();
	};

	class Test
	{
	private:
		std::string uuid_;
		Person *person_;
		TestLocation **locations_;
		bool result_;
		time_t date_of_test_;
		std::string comment_;
	public:
		Test(const std::string uuid, Person *person, TestLocation *county, TestLocation *district,
			TestLocation *station, const bool result,
			const time_t date_of_test, const std::string comment);
		~Test();
		const std::string &uuid();
		Person *person();
		TestLocation *location(location_t loc);
		const bool &result();
		const time_t &date_of_test();
		const std::string &comment();
		const std::string date();
	};


}