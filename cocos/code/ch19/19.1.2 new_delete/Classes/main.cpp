
#include <iostream>

using namespace std;

class MyObject  
{  
public : 
	MyObject(){
		cout << "call constructor." << endl; 
	}  

	~MyObject(){ 
		cout << "call destructor." << endl; 
	}  

	void initialize(){ 
		cout << "call initialization." << endl; 
	}  

	void destroy(){ 
		cout << "call destroy." << endl; 
	}  
};  

int main(){

	MyObject *obj = new MyObject(); // ÉêÇë¶¯Ì¬ÄÚ´æ  

	//TODO

	delete obj;
	obj = NULL;

	return 0;
}