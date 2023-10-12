/**
 * author     ：HE XIPING
 * email      ：he.xiping@infiz.khpi.edu.ua
 * date       ：Created in 2023/10/12
 * description：Task3
 */


#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

// Define the Philosopher class
class Philosopher {
public:
    // Constructor that takes an id and reference to two forks (mutexes)
    Philosopher(int id, std::mutex& left_fork, std::mutex& right_fork) :
        id(id), left_fork(left_fork), right_fork(right_fork) {}

    // Method that simulates the philosopher's actions
    void dine() {
        while (true) {
            think();
            eat();
        }
    }

private:
    // Simulates thinking by making the thread sleep for a second
    void think() const {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Tries to lock both forks (mutexes) to simulate eating
    void eat() {
        // Lock both forks
        std::lock(left_fork, right_fork);

        // Use lock_guard to manage the locks, making sure they are unlocked when the function ends
        std::lock_guard<std::mutex> lock_left(left_fork, std::adopt_lock);
        std::lock_guard<std::mutex> lock_right(right_fork, std::adopt_lock);

        // Print the id of the philosopher that is currently eating
        std::cout << "Philosopher " << id << " is eating." << std::endl;

        // Simulate eating by making the thread sleep for a second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    int id; // Philosopher's id
    std::mutex& left_fork; // Reference to the left fork (mutex)
    std::mutex& right_fork; // Reference to the right fork (mutex)
};

int main() {
    const int num_philosophers = 5; // Number of philosophers
    std::vector<std::thread> threads; // Vector to hold the threads
    std::vector<std::mutex> forks(num_philosophers); // Vector to hold the forks (mutexes)

    // Create and run threads for each philosopher
    for (int i = 0; i < num_philosophers; ++i) {
        threads.emplace_back(&Philosopher::dine,
            Philosopher(i, forks[i], forks[(i + 1) % num_philosophers]));
    }

    // Join all the threads
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}