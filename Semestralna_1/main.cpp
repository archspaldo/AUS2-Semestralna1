#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define initHeapMonitor() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#include <iostream>
#include <list>
#include <iterator>
#include <random>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Controller.h"

int main() {
	AUS2::Controller cont;	
	
	cont.add_person("971118/4395", "Pavol", "Surin");
	cont.add_person("986118/4395", "Pavla", "Surinova");
	cont.person();
	cont.remove_person("971118/4395");
	cont.person();


	/*AUS2::TwoThreeTree<int, int> *tree = new AUS2::TwoThreeTree<int, int>();
	std::list<int> keys;
	for (int i = 0; i <= 100; i++) {
		keys.push_back(rand());
		tree->insert(keys.back(), i);
	}
	for (int i = 0; i <= 100; i++) {
		std::cout << tree->remove(keys.front());
		keys.pop_front();
	}
	return 0;*/
}