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
		year = year > "21" ? std::to_string(1900 + std::stoi(year)) : std::to_string(2000 + std::stoi(year));
		if (month > "50") {
			month.data()[0] -= 5;
		}
		return this->id_.substr(4, 2) + "." + month + "." + year;
	}
	Test::Test(const std::string uuid, Person *person, TestLocation *county, TestLocation *district, TestLocation *station,
		const bool result, const time_t date_of_test, const std::string comment) :
		uuid_(uuid), person_(person), locations_(new TestLocation *[3]), result_(result),
		date_of_test_(date_of_test), comment_(comment)
	{
		locations_[static_cast<int>(station->location_type())] = station;
		locations_[static_cast<int>(county->location_type())] = county;
		locations_[static_cast<int>(district->location_type())] = district;
	}
	Test::~Test()
	{
		this->person_ = nullptr;
		delete[] this->locations_;
	}
	const std::string &Test::uuid()
	{
		return this->uuid_;
	}
	TestLocation *Test::location(location_t loc) {
		return locations_[static_cast<int>(loc)];
	}
	Person *Test::person()
	{
		return this->person_;
	}
	const bool &Test::result()
	{
		return this->result_;
	}
	const time_t &Test::date_of_test()
	{
		return this->date_of_test_;
	}
	const std::string &Test::comment()
	{
		return this->comment_;
	}
	const std::string Test::date() {
		tm *ltm = std::localtime(&this->date_of_test_);
		char buff[100];
		std::strftime(buff, 100, "%d.%m.%Y %H:%M:%S", ltm);
		std::string result = std::string(buff);
		return result;
	}
	TestLocation::TestLocation(int id, location_t location) : id_(id), location_(location) {
	}
	const int &TestLocation::id() {
		return this->id_;
	}
	const location_t TestLocation::location_type() {
		return this->location_;
	}
	County::County(const int id) : TestLocation(id, location_t::county){
	}
	District::District(const int id) : TestLocation(id, location_t::district) {
	}
	Station::Station(const int id) : TestLocation(id, location_t::station) {
	}
	State::State() : TestLocation(0, location_t::state) {
	}
	location_t &operator++(location_t &c) {
		if (c == location_t::state)
			c = location_t::station;
		else {
			c = static_cast<location_t>(static_cast<int>(c) + 1);
		}
		return c;
	}
}


