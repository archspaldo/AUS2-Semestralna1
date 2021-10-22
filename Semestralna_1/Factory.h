#pragma once
#include "DataItems.h"

namespace AUS2
{
	class PersonFactory
	{
	public:
		static Person *create(const std::string &id, const std::string &name, const std::string &surname);
		static Person *create();
	};

	class TestFactory
	{
	public:
		static Test *create(Person *person, const int &district,
			const int &county, const int &station, const bool &result,
			const std::string &date_of_test, const std::string &comment);
		static Test *create(Person *person);
	};
}

