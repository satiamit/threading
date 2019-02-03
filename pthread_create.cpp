#include <stdio.h>
#include <pthread.h>
#include <string.h>
long long sum = 0;
void* sum_thread(void *param)
{
    long long *limit_ptr = (long long *)(param);
    long long  val = *limit_ptr;
    for(int i=0; i<=val; i++)
        sum += i;
    pthread_exit(0);
}
int main(int argc, char* argv[])
{
    long long limit = 0;
    scanf("%lld", &limit);
    //printf("%d\n", argc);
    printf("%lld\n", limit);
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, sum_thread, (void*)(&limit)); 
    pthread_join(tid, NULL);
    printf("sum is %lld", sum);
    return 0;
}
