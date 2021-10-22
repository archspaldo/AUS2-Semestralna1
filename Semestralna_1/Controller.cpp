#include "Controller.h"

namespace AUS2
{
    Controller::Controller() :
        storage_(new DataStorage())
    {
    }

    Controller::~Controller()
    {
        delete this->storage_;
    }

    void Controller::add_person(const std::string &id, const std::string &name, const std::string &surname)
    {
        this->storage_->add_person(PersonFactory::create(id, name, surname));
    }

    void Controller::add_person()
    {
        this->storage_->add_person(PersonFactory::create());
    }

    void Controller::add_test(const std::string &id, const int &district, const int &county, const int &station, const bool &result, const std::string &date_of_test, const std::string &comment)
    {
        Person *person = this->storage_->person_by_id(id);
        this->storage_->add_test(TestFactory::create(person, district, county, station, result, date_of_test, comment));
    }

    void Controller::add_test()
    {
        Person *person = PersonFactory::create();
        this->storage_->add_person(person);
        this->storage_->add_test(TestFactory::create(person));
    }

    void Controller::remove_person(const std::string &id)
    {
        this->storage_->remove_person(id);
    }

    void Controller::remove_test(const std::string &uuid)
    {
        this->storage_->remove_test(uuid);
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
    void Controller::person()
    {
        std::cout << "{\n";
        for (auto person : *this->storage_->person()) {
            std::cout << person->string_representation();
        }
        std::cout << "\n}\n";
    }
    void Controller::test()
    {
        std::cout << "{\n";
        for (auto test : *this->storage_->test()) {
            std::cout << test->string_representation();
        }
        std::cout << "\n}\n";
    }
}

