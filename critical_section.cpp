#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <windows.h>
using namespace std;
CRITICAL_SECTION critSection;
 
void myThread1()
{
    while (true)
    {
        // do some work

        // log it:
        EnterCriticalSection(&critSection);
        std::cout << "Hello World" << std::endl;
        LeaveCriticalSection(&critSection);
    }
}
 
void myThread2()
{
    while (true)
    {
        // do some work

        // log it:
        EnterCriticalSection(&critSection);
        std::cout << "The quick brown fox" << std::endl;
        LeaveCriticalSection(&critSection);
    }
}
 
int main()
{
  InitializeCriticalSection(&critSection);
  // make threads using myThread1 and myThread2 and wait for them to finish
  thread t1(myThread1);
  t1.join();
  thread t2(myThread2);
  DeleteCriticalSection(&critSection);
}
