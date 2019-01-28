#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
std::mutex mtConsole;
void funcA(void)
{
    int loop=0;
    while(loop <10)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1333));
        std::cout << "thread A " << loop << std::endl;
        loop++;
    }
}
void funcB(void)
{
    int loop=0;
    while(loop <10)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2222));
        std::cout << "thread B " << loop << std::endl;
        loop++;
    }
}
void funcC(int thread_number, int iterations, long delay)
{
    int loop = 0;
    // Loop some 'iterations' number of times
    while(loop < iterations)
    {
        // Sleep for some time 
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        mtConsole.lock();
        std::cout << "Thread " << thread_number << " Reporting: " << loop << " with delay " << delay << std::endl;
        mtConsole.unlock();
        loop++;
    }
}
int main()
{
    char result;
    //std::thread thA(funcA);
    //std::thread thB(funcB);
    std::thread thC(funcC, 1, 10, 1222);
    std::thread thC1(funcC, 2, 10, 2333);
    std::cout << "press a key" << std::endl;
    std::cin >> result;
    //thA.join();
    //thB.join();
    thC.join();
    thC1.join();
    return 1;
}
