#include "Controller.h"

namespace AUS2
{
    Controller::Controller() :
        storage_(new DataStorage())
    {
        std::fstream input;
        int size;
        auto f = [&](std::vector<std::string> *&vec, std::string file) {
            input.open(file, std::ios_base::in);
            input >> size;
            vec = new std::vector<std::string>(size);
            for (int i = 0; i < size; i++) {
                input >> (*vec)[i];
            }
            input.close();
        };
        f(this->names_m_, "names_m.txt");
        f(this->names_f_, "names_f.txt");
        f(this->surnames_, "surnames.txt");
    }

    Controller::~Controller()
    {
        delete this->names_f_;
        delete this->names_m_;
        delete this->surnames_;
        delete this->storage_;
    }

    Person *Controller::add_person(const std::string id, const std::string name, const std::string surname)
    {
        Person *person = new Person(id, name, surname);
        this->storage_->add_person(person);
        return person;
    }

    Person *Controller::add_person()
    {
        bool f = rand() % 2;
        std::string id = "", tmp;
        tmp = std::to_string(rand() % 100);
        if (tmp.size() < 2) {
            tmp.insert(0, 2 - tmp.size(), '0');
        }
        id += tmp;
        tmp = std::to_string(rand() % 12 + (f ? 51 : 1));
        if (tmp.size() < 2) {
            tmp.insert(0, 2 - tmp.size(), '0');
        }
        id += tmp;
        tmp = std::to_string((rand() % 28) + 1);
        if (tmp.size() < 2) {
            tmp.insert(0, 2 - tmp.size(), '0');
        }
        id += tmp;
        id = this->storage_->next_id(id);
        std::string name = f ? (*this->names_f_)[rand() % this->names_f_->size()] : (*this->names_m_)[rand() % this->names_m_->size()];
        std::string surname = (*this->surnames_)[rand() % this->surnames_->size()];

        Person *person = new Person(id, name, surname);
        this->storage_->add_person(person);
        return person;
    }

    void Controller::add_test(const std::string uuid, const std::string id, const int district, const int county, const int station, const bool result, const std::string date_of_test, const std::string comment)
    {
        struct tm *date = new tm;
        std::istringstream ss{ date_of_test };
        ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        Person *person = this->storage_->person_by_id(id);
        this->storage_->add_test(new Test(uuid, person, district, county, station, result, date, comment));
    }

    void Controller::add_test(const std::string id)
    {
        std::string uuid = boost::lexical_cast<std::string>(boost::uuids::random_generator()());

        std::string str_date = "", tmp;
        str_date += std::to_string((rand() % 28) + 1) + "." + std::to_string((rand() % 12) + 1) + ".2021 ";
        str_date += std::to_string((rand() % 9) + 7) + ':' + std::to_string(rand() % 60) + ':' + std::to_string(rand() % 60);

        struct tm *date = new tm;
        std::istringstream ss{ str_date };
        ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        Person *person = this->storage_->person_by_id(id);
        this->storage_->add_test(new Test(uuid, person, rand() % 10, rand() % 60, rand() % 300, rand() % 2, date, ""));
    }

    void Controller::remove_person(const std::string &id)
    {
        this->storage_->remove_person(id);
    }

    void Controller::remove_test(const std::string &uuid)
    {
        this->storage_->remove_test(uuid);
    }

    Person *Controller::person_by_id(const std::string &id) {
        return this->storage_->person_by_id(id);
    }

    Test *Controller::test_by_uuid(const std::string &uuid) {
        return this->storage_->test_by_uuid(uuid);
    }

    std::list<Person *> *Controller::people() {
        return this->storage_->people();
    }

    std::list<Test *> *Controller::tests() {
        return this->storage_->tests();
    }

    std::list<Test *> *Controller::test_list_by_id(const std::string &id)
    {
        return this->storage_->test_list_by_id(id);
    }

    std::list<Test *> *Controller::test_list_by_date(bool positive_only, const std::string date_start, const std::string date_end)
    {
        struct tm *date = (tm *)calloc(1, sizeof(tm));
        std::istringstream ss{ date_start }, ss2{ date_end };
        ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        time_t d_start = std::mktime(date);
        free(date);
        date = (tm *)calloc(1, sizeof(tm));
        ss2 >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        time_t d_end = std::mktime(date);
        free(date);
        return this->storage_->test_list_by_date(positive_only, d_start, d_end);
    }

    std::list<Test *> *Controller::test_list_by_county(bool positive_only, const int county, const std::string date_start, const std::string date_end)
    {
        struct tm *date = (tm *)calloc(1, sizeof(tm));
        std::istringstream ss{ date_start }, ss2{ date_end };
        ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        time_t d_start = std::mktime(date);
        free(date);
        date = (tm *)calloc(1, sizeof(tm));
        ss2 >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        time_t d_end = std::mktime(date);
        free(date);
        return this->storage_->test_list_by_county(positive_only, county, d_start, d_end);
    }

    std::list<Test *> *Controller::test_list_by_district(bool positive_only, const int district, const std::string date_start, const std::string date_end)
    {
        struct tm *date = (tm *)calloc(1, sizeof(tm));
        std::istringstream ss{ date_start }, ss2{ date_end };
        ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        time_t d_start = std::mktime(date);
        free(date);
        date = (tm *)calloc(1, sizeof(tm));
        ss2 >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        time_t d_end = std::mktime(date);
        free(date);
        return this->storage_->test_list_by_district(positive_only, district, d_start, d_end);
    }

    std::list<Test *> *Controller::test_list_by_station(const int station, const std::string date_start, const std::string date_end)
    {
        struct tm *date = (tm *)calloc(1, sizeof(tm));
        std::istringstream ss{ date_start }, ss2{ date_end };
        ss >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        time_t d_start = std::mktime(date);
        free(date);
        date = (tm *)calloc(1, sizeof(tm));
        ss2 >> std::get_time(date, "%d.%m.%Y %H:%M:%S");
        time_t d_end = std::mktime(date);
        free(date);
        return this->storage_->test_list_by_station(station, d_start, d_end);
    }
}

