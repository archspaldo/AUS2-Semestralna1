#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define initHeapMonitor() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#include "Controller.h"
#include "StructureTester.h"

int main() {
	AUS2::Tester<AUS2::TwoThreeTree<int, int>>::test(10000000, 90, 10);

	return 0;
}