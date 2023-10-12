/**
 * author     ：HE XIPING
 * email      ：he.xiping@infiz.khpi.edu.ua
 * date       ：Created in 2023/10/12
 * description：Task3
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <cstdlib>
#include <ctime>

std::mutex mtx;
std::list<int> lst;

void thread_func1() {
    srand((unsigned)time(NULL));
    while (true) {
        mtx.lock();
        if (lst.size() >= 10) {
            mtx.unlock();
            return;
        }
        int random_variable = std::rand();
        lst.push_back(random_variable);
        mtx.unlock();
    }
}

void thread_func2() {
    while (true) {
        mtx.lock();
        if (lst.size() >= 10) {
            for (const auto& i : lst) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            mtx.unlock();
            return;
        }
        mtx.unlock();
    }
}

int main() {
    std::thread t1(thread_func1);
    std::thread t2(thread_func2);

    t1.join();
    t2.join();

    return 0;
}