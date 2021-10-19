#include "Controller.h"

namespace AUS2
{
    Controller::Controller()
    {
    }

    Controller::~Controller()
    {
        delete this->storage_;
    }

    void Controller::add_person(const std::string &id, const std::string &name, const std::string &surname, tm *date_of_birth)
    {
        DataStorage::instance().add_person(PersonFactory::create(id, name, surname, date_of_birth));
    }

    void Controller::add_person()
    {
        DataStorage::instance().add_person(PersonFactory::create());
    }

    void Controller::add_test(const std::string &id, const int &district, const int &county, const bool &result, tm *date_of_test, const std::string &comment)
    {
        Person *person = DataStorage::instance().person_by_id(id);
        DataStorage::instance().add_test(TestFactory::create(person, district, county, result, date_of_test, comment));
    }

    void Controller::add_test()
    {
        Person *person = PersonFactory::create();
        DataStorage::instance().add_person(person);
        DataStorage::instance().add_test(TestFactory::create(person));
    }

    void Controller::remove_person(const std::string &id)
    {
        DataStorage::instance().remove_person(id);
    }

    void Controller::remove_test(const std::string &uuid)
    {
        DataStorage::instance().remove_test(uuid);
    }

    void Controller::test_by_uuid_id(const std::string &uuid, const std::string &id)
    {
    }

    void Controller::test_list_by_id(const std::string &id)
    {
    }

    void Controller::test_list_by_date(bool positive_only, const tm *date_start, const tm *date_end)
    {
    }

    void Controller::test_list_by_county(bool positive_only, const int county, const tm *date, const tm *date_end)
    {
    }

    void Controller::test_list_by_district(bool positive_only, const int district, const tm *date, const tm *date_end)
    {
    }

    void Controller::test_list_by_station(const int station, const tm *date, const tm *date_end)
    {
    }
}

