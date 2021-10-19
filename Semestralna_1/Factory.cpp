#include "Factory.h"
namespace AUS2
{
	Person *AUS2::PersonFactory::create(const std::string &id, const std::string &name, const std::string &surname, tm *date_of_birth)
	{
		return new Person(id, name, surname, date_of_birth);
	}

	Person *PersonFactory::create()
	{
		return nullptr;
	}

	Test *TestFactory::create(Person *person, const int &district, const int &county, const bool &result, tm *date_of_test, const std::string &comment)
	{
		UUID uuid;
		std::string s_uuid;
		UuidCreate(&uuid);
		UuidToStringA(&uuid, (RPC_CSTR *)&s_uuid);
		return new Test(s_uuid, person, district, county, result, date_of_test, comment);
	}

	Test *TestFactory::create(Person *person)
	{
		return nullptr;
	}
}
