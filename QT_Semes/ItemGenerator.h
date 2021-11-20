#pragma once
#include "DataItems.h"
#include "2-3Tree.h"
#include <fstream>
#include <sstream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace AUS2
{
	class ItemGenerator
	{
	private:
		std::vector<std::string> *names_f_;
		std::vector<std::string> *names_m_;
		std::vector<std::string> *surnames_;
	public:
		ItemGenerator();
		~ItemGenerator();
		void generate_to_directory(const int station_count, const int county_count, const int district_count,
			const int person_count, const int test_count, const std::string &directory = "../data_storage/");
	};
};


