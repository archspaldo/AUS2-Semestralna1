#include "Factory.h"
namespace AUS2
{
	Person *AUS2::PersonFactory::create(const std::string &id, const std::string &name, const std::string &surname)
	{
		return new Person(id, name, surname);
	}

	Person *PersonFactory::create()
	{
		return nullptr;
	}

	Test *TestFactory::create(Person *person, const int &district, const int &county, const int &station, const bool &result, const std::string &date_of_test, const std::string &comment)
	{
		UUID uuid;
		std::string s_uuid;
		UuidCreate(&uuid);
		UuidToStringA(&uuid, (RPC_CSTR *)&s_uuid);
		struct tm *date = new tm;
		std::istringstream ss{ date_of_test };
		ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S ");
		return new Test(s_uuid, person, district, county, station, result, date, comment);
	}

	Test *TestFactory::create(Person *person)
	{
		return nullptr;
	}
}
