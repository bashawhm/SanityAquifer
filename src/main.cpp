#include <iostream>
#include <stdlib.h>
#include "stage.h"

using namespace std;

int main(){
	srand(time(NULL));
	Stage stage; 

	while (stage.isAlive()){
		stage.setTime(time(NULL));
		stage.render();
		stage.handleEvents();

	}

	return 0;
}
