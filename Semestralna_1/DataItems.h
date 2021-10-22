#pragma once
#pragma comment(lib, "rpcrt4.lib")
#include <Windows.h>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace AUS2
{
	class Person
	{
	private:
		std::string id_;
		std::string name_;
		std::string surname_;
	public:
		Person(const std::string &id, const std::string &name, const std::string &surname);
		~Person();
		const std::string &id();
		const std::string &name();
		const std::string &surname();
		const std::string date_of_birth();
		std::string string_representation();
	};

	class Test
	{
	private:
		std::string uuid_;
		Person *person_;
		int district_;
		int county_;
		int station_;
		bool result_;
		tm *date_of_test_;
		std::string comment_;
	public:
		Test(const std::string &uuid, Person *person, const int &district,
			const int &county, const int &station,  const bool &result,
			tm *date_of_test, const std::string &comment);
		~Test();
		const std::string &uuid();
		Person *person();
		const int district();
		const int county();
		const int station();
		const bool result();
		const tm *date_of_test();
		const std::string &comment();
		std::string string_representation();
	};
}