#pragma once
#include <list>
#include <random>
#include <stdexcept>
#include <iostream>

namespace AUS2
{
	template <class Table>
	class Tester
	{
	public:
		static void test(int operations, int insert = 50, int remove = 50);
	};


	template<class Table>
	inline void Tester<Table>::test(int operations, int insert, int remove) {
		Table *table = new Table();
		std::list<int> list;
		int rem = insert + remove;
		int roll, rand;
		for (int i = 0; i < operations; i++) {
			rand = std::rand() % 100;
			if (rand < insert) {
				try {
					roll = std::rand();
					table->insert(roll, i);
					list.push_front(roll);
					//std::cout << "Vlozena hodnota " << i << " s klucom " << list.front() << '\n';
				}
				catch (...) {
					//std::cout << "Nepodarilo sa vlozit hodnotu\n";
				}
			}
			else if (rand < rem) {
				if (list.empty()) {
					//std::cout << "Nepodarilo sa vymazat hodnotu\n";
				}
				else {
					roll = table->remove(list.front());
					//std::cout << "Vymazana hodnota " << roll << " s klucom " << list.front() << '\n';
					list.pop_front();
				}
			}
			else {
				if (list.empty()) {
					//std::cout << "Nepodarilo sa vymazat hodnotu\n";
				}
				else {
					roll = table->get(list.front());
					//std::cout << "Najdena hodnota " << roll << " s klucom " << list.front() << '\n';
				}
			}
		}
		list.clear();
		delete table;
	}
}