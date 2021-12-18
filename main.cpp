#include "Test.h"
void drawTest(){
	DrawHandler DH;
	DH.drawTest1();
	DH.drawTest2();
	DH.drawTest3();
}

int main(){
	srand(time(0)); // Always start program with this to set RNG seed based on the time
	drawTest();
	//testProg2();
}

