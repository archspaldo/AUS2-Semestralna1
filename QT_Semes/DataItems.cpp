#include "DataItems.h"

namespace AUS2
{
	Person::Person(const std::string id, const std::string name, const std::string surname) :
		id_(id), name_(name), surname_(surname)
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
	const std::string Person::date_of_birth()
	{
		std::string year = this->id_.substr(0, 2), month = this->id_.substr(2, 2);
		year = std::to_string(1900 + std::stoi(year));
		if (month > "50") {
			month.data()[0] -= 5;
		}
		return this->id_.substr(4, 2) + "." + month + "." + year;
	}
	Test::Test(const std::string uuid, Person *person, const int county, const int district, const int station,
		const bool result, tm *date_of_test, const std::string comment) :
		uuid_(uuid), person_(person), district_(district), county_(county), station_(station), result_(result),
		date_of_test_(date_of_test), comment_(comment)
	{
	}
	Test::~Test()
	{
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
	const std::string Test::date() {
		char buff[100];
		std::strftime(buff, 100, "%d.%m.%Y %H:%M:%S", this->date_of_test_);
		return std::string(buff);
	}
}


