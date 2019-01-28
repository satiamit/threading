#include <iostream>
#include <pthread.h>
using namespace std;
long long var = 0;
void *func(void *ptr)
{
    long long *intVal = (long long*) ptr;
    for(long long i = 0; i <= (*intVal); i++)
        var += i;
    
    pthread_exit(0);
}
int main(int argc, char* argv[])
{
    long long limit;
    limit = atoll(argv[1]); 
    pthread_t th;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&th, &attr, func, &limit);
    pthread_join(th, NULL);
    cout << var << endl;
    cout << __func__<< endl;
}
