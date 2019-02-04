#include <stdio.h>
#include <pthread.h>
struct str
{
    long long limit;
    long long output;
};
void *get_sum(void *arg)
{
    struct str *inp = (struct str*)(arg);
    long long sum = 0;
    for(long long i=0; i<=((inp->limit)); i++)
        sum += i;
    inp->output = sum;
    printf("%lu is the thread id\n", pthread_self());
    printf("%d is the process id \n", (int)(getpid()));
    pthread_exit(0);
}
int main()
{
    long long input[3];
    scanf("%lld", &input[0]);
    printf("%lu is the thread id in main thread\n", pthread_self());
    scanf("%lld", &input[1]);
    scanf("%lld", &input[2]);
    pthread_t pt[3];
    struct str inStr[3];
    for(int i=0; i<3; i++)
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        inStr[i].limit = input[i];
        pthread_create(&pt[i], &attr, get_sum, (void*)(&inStr[i]));
    }
    for(int i=0; i<3; i++)
    {
        pthread_join(pt[i], NULL);
        printf("sum is %lld\n", inStr[i].output);
    }
    printf("%lu is the thread id in main thread after exit\n", pthread_self());
    //printf("sum is %lld", sum);
    return 0;
}
