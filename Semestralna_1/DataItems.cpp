#include "DataItems.h"

namespace AUS2
{
	Person::Person(const std::string &id, const std::string &name, const std::string &surname, tm *date_of_birth) :
		id_(id), name_(name), surname_(surname), date_of_birth_(date_of_birth)
	{
	}
	Person::~Person()
	{
	}
	const std::string &Person::id()
	{
		return this->id_;
	}
	const std::string &Person::name()
	{
		return this->name_;
	}
	const std::string &Person::surname()
	{
		return this->surname_;
	}
	const tm *Person::date_of_birth()
	{
		return this->date_of_birth_;
	}
	Test::Test(const std::string &uuid, Person *person, const int &district, const int &county,
		const bool &result, tm *date_of_test, const std::string &comment) :
		uuid_(uuid), person_(person), district_(district), county_(county), result_(result),
		date_of_test_(date_of_test), comment_(comment)
	{
	}
	Test::~Test()
	{
		RpcStringFreeA((RPC_CSTR *)&this->uuid_);
		this->person_ = nullptr;
	}
	const std::string &Test::uuid()
	{
		return this->uuid_;
	}
	Person *Test::person()
	{
		return this->person_;
	}
	const int Test::district()
	{
		return this->district_;
	}
	const int Test::county()
	{
		return this->county_;
	}
	const int Test::station()
	{
		return this->station_;
	}
	const bool Test::result()
	{
		return this->result_;
	}
	const tm *Test::date_of_test()
	{
		return this->date_of_test_;
	}
	const std::string &Test::comment()
	{
		return this->comment_;
	}
}


