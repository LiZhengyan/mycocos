
#include "Singleton.h"
#include <iostream>

int main(){

	Singleton* singleton1 = Singleton::getInstance();
	Singleton* singleton2 = Singleton::getInstance();

	if (singleton1 == singleton2) {
		std::cout <<"singleton1 = singleton2"<<std::endl;
	}

	return 0;
}