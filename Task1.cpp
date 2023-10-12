/**
 * author     ：HE XIPING
 * email      ：he.xiping@infiz.khpi.edu.ua
 * date       ：Created in 2023/10/12
 * description：Task3
 */
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>

// Global variable
volatile int num = 0;

void th_01() {
    while (num < 1000) {
        ++num;
    }
}

void th_02() {
    while (num > -1000) {
        --num;
    }
}

int main() {
    // Create threads
    std::thread t1(th_01);
    std::thread t2(th_02);

    // Start threads
    t1.join();
    t2.join();

    // Print the final value
    std::cout << num << std::endl;

    return 0;
}