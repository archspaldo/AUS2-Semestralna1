#include "ItemGenerator.h"

AUS2::ItemGenerator::ItemGenerator() {
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

AUS2::ItemGenerator::~ItemGenerator() {
	delete this->names_f_;
	delete this->names_m_;
	delete this->surnames_;
}

void AUS2::ItemGenerator::generate_to_directory(const int station_count,
	const int county_count, const int district_count,
	const int person_count, const int test_count,
	const std::string &directory) {
	TwoThreeTree<std::string, std::string> id_tree;
	std::string id, next, name, surname, uuid, str_date;
	bool female;
	long long tmp;
	std::ofstream output_person, output_test, output;

	std::string str[3] = { "station.csv", "county.csv", "district.csv" };
	int count[3] = { station_count , county_count, district_count };
	for (location_t loc = location_t::station; loc != location_t::state; ++loc) {
		output.open(directory + str[static_cast<int>(loc)]);
		output << "ID";
		for (int i = 0; i < count[static_cast<int>(loc)]; i++) {
			output << '\n' << i;
		}
		output.close();
	}

	output_person.open(directory + "person.csv");
	output_person << "ID,Name,Surname";

	output_test.open(directory + "test.csv");
	output_test << "UUID,ID,Station,County,District,Result,Date,Comment";

	for (int j = 0; j < person_count; j++) {
		female = rand() % 2;
		name = female ? (*this->names_f_)[rand() % this->names_f_->size()] : (*this->names_m_)[rand() % this->names_m_->size()];
		surname = (*this->surnames_)[rand() % this->surnames_->size()];

		id = "";
		next = std::to_string(rand() % 100);
		if (next.size() < 2) {
			next.insert(0, 2 - next.size(), '0');
		}
		id += next;
		next = std::to_string(rand() % 12 + (female ? 51 : 1));
		if (next.size() < 2) {
			next.insert(0, 2 - next.size(), '0');
		}
		id += next;
		next = std::to_string((rand() % 28) + 1);
		if (next.size() < 2) {
			next.insert(0, 2 - next.size(), '0');
		}
		id += next;

		female = id_tree.contains_key(id);
		next = id + (female ? id_tree.get(id) : "0000");

		tmp = std::stoll(next);
		tmp += 11 - (tmp % 11);
		next = std::to_string(tmp);
		if (female) {
			id_tree.get(id) = next.substr(next.size() - 4, 4);
		}
		else {
			id_tree.insert(id, next.substr(next.size() - 4, 4));
		}
		id += '/' + next.substr(next.size() - 4, 4);
		output_person << '\n' << id << ',' << name << ',' << surname;

		for (int i = 0; i < test_count; i++) {
			uuid = boost::lexical_cast<std::string>(boost::uuids::random_generator()());

			str_date = "";
			str_date += std::to_string((rand() % 28) + 1) + "." + std::to_string((rand() % 12) + 1) + ".2021 ";
			str_date += std::to_string((rand() % 9) + 7) + ':' + std::to_string(rand() % 60) + ':' + std::to_string(rand() % 60);

			output_test << '\n' << uuid << ',' << id << ',' << rand() % station_count << ','
				<< rand() % county_count << ',' << rand() % district_count << ','
				<< rand() % 2 << ',' << str_date << ',' << "none";
		}
	}

	output_test.close();
	output_person.close();
}
