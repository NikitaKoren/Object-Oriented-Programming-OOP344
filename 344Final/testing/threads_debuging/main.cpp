#include <iostream>
#include <thread>

void task1() {
    std::cout << "task 1, " << std::endl;
}
void task2() {
    std::cout << "task 2, " <<std::endl;
}
void task3() {
    std::cout << "task 3, " <<std::endl;
}

int main() {

    //creates threads
    std::thread t1(task1);
    //std::thread t2(task2);
    //std::thread t3(task3);

    std::cout << "Join task1," << std::endl;
    t1.join();

    std::cout << "main," << std::endl;



    //std::cout << "Join task2," << std::endl;
    //t2.join();

    //std::cout << "Join task3" << std::endl;
    //t3.join();



}