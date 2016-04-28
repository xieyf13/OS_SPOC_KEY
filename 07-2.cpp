/*
	参考资料：c++11中信号量(semaphore)的实现 http://ilovers.sinaapp.com/article/c11中信号量semaphore的实现 
*/
#include <mutex>
#include <chrono>
#include <iostream>
#include <thread>
#include <condition_variable>

using namespace std;
using namespace std::chrono_literals;

class semaphore {
    public:
        semaphore(int value=1): count{value}{}
       
        void wait(){
            std::unique_lock<std::mutex> lock{mutex};
            if (--count<0) // count is not enough ?
                condition.wait(lock); // suspend and wait...
        }
        void signal(){
            std::lock_guard<std::mutex> lock{mutex};
            if(++count<=0) // have some thread suspended ?
                condition.notify_one(); // notify one !
        }
       
    private:
        int count;
        std::mutex mutex;
        std::condition_variable condition;
};

void driver_thread(semaphore& movable, semaphore& openable) {
    while (true) {
        movable.wait();
        cout << "started" << endl;
        cout << "driving" << endl;
        std::chrono::milliseconds dura( 1000 );
    	std::this_thread::sleep_for( dura );
        cout << "stopped" << endl;
        openable.notify();
    }
}

void conductor_thread(semaphore& movable, semaphore& openable) {
    while (true) {
        openable.wait();
        cout << "           opened" << endl;
        cout << "           conducting" << endl;
        std::chrono::milliseconds dura( 1000 );
    	std::this_thread::sleep_for( dura );
        cout << "           closed" << endl;
        movable.notify();
    }
}

int main() {
    semaphore movable(1);
    semaphore openable(0);

    cout << "Driver    Conductor" << endl;

    std::thread driver(driver_thread, std::ref(movable), std::ref(openable));
    std::thread conductor(conductor_thread, std::ref(movable), std::ref(openable));

    driver.join();
    conductor.join();

    return 0;
}
