#include <iostream>
#include "2-3Tree.h"
#include <list>
#include <iterator>


int main() {
	AUS2::TwoThreeTree<int, int> *tree = new AUS2::TwoThreeTree<int, int>();
	for (int i = 0; i <= 1000; i++) {
		tree->insert(i, i);
	}
	for (int i = 0; i <= 1000; i++) {
		std::cout << tree->remove(i);
	}
	return 0;
}