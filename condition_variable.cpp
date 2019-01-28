#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <deque>
using namespace std;
deque <int> q;
mutex mu;
void function1()
{
	int count = 10;
	while (count > 0)
	{
		unique_lock<mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		this_thread::sleep_for(chrono::seconds(1));
		--count;
	}
}
void function2()
{
	int data = 0;
	while (data != 1)
	{
		unique_lock<mutex> locker(mu);
		if (!q.empty())
		{
			data = q.back();
			q.pop_back();
			locker.unlock();
			cout << "got a value : " << data << endl;
		}
		else
		{
			mu.unlock();
		}
	}

}
int main()
{
	thread t1(function1);
	thread t2(function2);
	t1.join();
	t2.join();
	return 0;
}
