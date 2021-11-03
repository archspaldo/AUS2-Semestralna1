#pragma once
#include <list>
#include <random>
#include <stdexcept>
#include <iostream>
#include <string>
#include "2-3Tree.h"

namespace AUS2
{
	class Tester
	{
	private:
		TwoThreeTree<int, int> *tree_;
		std::list<int> *list_;
		int operations_;
		int insert_;
		int remove_;
		int get_;
		int interval_;
		int operation_count_;
	public:
		Tester();
		~Tester();
		void set(int operations, int insert, int remove, int get, int interval);
		bool has_next();
		std::string next();
		void reset();
	};
}