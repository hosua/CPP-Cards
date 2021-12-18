#include "Test.h"
void drawTest(){
	drawTest1();
	drawTest2();
	drawTest3();
}

int main(){
	// If we ever decide to take this project seriously, we should use a better means
	// of number generation. srand() is not a good way to generate random numbers, but it's good enough
	// for testing.
	srand(time(0)); 
	//drawTest();
	//testProg2();
	testProg3();
}

