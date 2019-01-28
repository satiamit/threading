#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
using namespace std;
class A
{
    mutex m;
    mutex m2;
    ofstream f; 
public:
    A()
    {
        f.open("log.txt");
    }
    void read_write(std::string s, int val)
    {
        std::lock(m, m2);
        lock_guard<mutex> lock(m, adopt_lock);          
        lock_guard<mutex> lock2(m2, adopt_lock);
        cout << s << val << endl;
    }
    void read_write_2(std::string s, int val)
    {
        lock(m, m2);
        lock_guard<mutex> lock2(m2, adopt_lock);
        lock_guard<mutex> lock(m, adopt_lock);
        cout << s << val << endl;
    }
    ~A()
    {
        f.close();
    }
};
void function_1(A &a)
{
    for (int i=0; i<100; i++)
    {
        a.read_write_2("from t1 ", i);
    }
}
int main()
{
    A a;
    thread t1(function_1, std::ref(a));
    for(int i=0; i<100; i++)
    {
        a.read_write("from main ", i);
    }
    t1.join();
}
