//#include <iostream>
#include <stdio.h>
#include <cstring>
#include <pthread.h>
#define THREADS 8
#include <iostream>
#include <unistd.h>
//using namespace std;
using std::cout;
using std::endl;
char *messages[THREADS];

struct thread_data
{
   int	thread_id;
   int  sum;
   char *message;
};

thread_data struct_thread_data[THREADS];

void* printHello(void *threadId)
{
    usleep(1);
    struct thread_data *thTemp;
    thTemp = (thread_data *)(threadId);
    cout << thTemp->thread_id << " is the thread_id\t" ;
    cout << thTemp->sum << " is the sumi\t" ;
    cout << thTemp->message << " is the message" << endl;
    pthread_exit(NULL);
}
int main()
{
    pthread_t thread[THREADS];
    int sum = 0;
    int *taskids[THREADS];
    int t = 0;
    int rc;
    messages[0] = "English: Hello World!";
    messages[1] = "French: Bonjour, le monde!";
    messages[2] = "Spanish: Hola al mundo";
    messages[3] = "Klingon: Nuq neH!";
    messages[4] = "German: Guten Tag, Welt!"; 
    messages[5] = "Russian: Zdravstvytye, mir!";
    messages[6] = "Japan: Sekai e konnichiwa!";
    messages[7] = "Latin: Orbis, te saluto!";
    for(t = 0; t<THREADS; t++)
    {
        sum += t;
        struct_thread_data[t].sum = sum;
        struct_thread_data[t].thread_id = t;
        struct_thread_data[t].message = messages[t];
        rc = pthread_create(&thread[t], NULL, printHello, (void *) &struct_thread_data[t]);
        pthread_join(thread[t], NULL);
        if(rc != 0)
        {
            fprintf(stderr, "Error in thread_creation\n");
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
