#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>
using namespace std;
class Logfile
{
	ofstream file;
	mutex mutex_var;
    once_flag _flag;
public:
	Logfile()
	{
		//file.open("logs_from_multithreading.txt");
	}
	void read_write(string s, int val)
	{
		unique_lock<mutex> locker(mutex_var, defer_lock);
//		unique_lock<mutex> locker(mutex_var);
		locker.lock();
		cout << s << ": " << val << endl;
		locker.unlock();
	}
	void read_write_2(string s, int val)
	{
        call_once(_flag, [&](){file.open("logs_from_multithreading.txt");});
		cout << s << ": " << val << endl;
	}
	~Logfile()
	{
		file.close();
	}
};
void print_from_function(Logfile &log)
{
	for (int i = 0; i < 100; i++)
	{
		log.read_write_2("from function ", i);
	}
}
int main()
{
	Logfile log;
	thread t1(print_from_function, std::ref(log));
	for (int i = 0; i < 100; i++)
	{
		log.read_write_2("from main ", i);
	}
    t1.join();
	return 0;
}
