
#include "Singleton.h"

Singleton::Singleton(){
	std::cout <<"Create Singleton"<<std::endl;
}

Singleton::~Singleton(){
	std::cout <<"Destroy  Singleton"<<std::endl;
}

Singleton* Singleton::instance = new Singleton();

Singleton* Singleton::getInstance(){
	return instance;
}