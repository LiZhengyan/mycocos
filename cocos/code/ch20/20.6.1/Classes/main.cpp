
#include <thread>
#include <iostream>
#include <vector>


//void callfn(){
//    std::cout << "Hello thread! " << std::endl;
//}
//int main(){
//    std::thread t1(&callfn);
//	t1.join();
//    return 0;
//}

void callfn(){
    std::cout << "Hello thread! " << std::endl;
}
int main(){
    std::thread* t1 = new  std::thread(callfn);
	t1->join();
	delete	t1;
	t1 = nullptr;
    return 0;
}

//void callfn(){
//	std::cout << "Hello thread " << std::this_thread::get_id() << std::endl;
//}
//int main(){
//	std::vector<std::thread> threads;
//	for(int i = 0; i < 5; i++){
//		threads.push_back(std::thread(callfn));
//	}
//	for(auto& thread : threads){
//		thread.join();
//	}
//	return 0;
//}