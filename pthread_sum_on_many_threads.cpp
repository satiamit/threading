#include <stdio.h>
#include <pthread.h>
#include <string.h>
struct sum_runner
{
	long long limit;
	long long answer;
};
void* sum_thread(void *param)
{
    struct sum_runner *limit_ptr = (struct sum_runner *)(param);
    long long  sum = 0;
    for(long long i=0; i<=limit_ptr->limit; i++)
        sum += i;
	limit_ptr->answer = sum;
    pthread_exit(0);
}
int main(int argc, char* argv[])
{
    //printf("%d\n", argc);
	int num_of_args = 3;
	//printf("%lld number of arguments\n", num_of_args);
    pthread_t tid[num_of_args];
    struct sum_runner str_run[num_of_args];
	for(int i=0; i<num_of_args; i++)
	{		
		
		long long limit = 0;
		scanf("%lld", &limit);
		str_run[i].limit = limit;
        //printf("%dth input is %d\n", i, limit);
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid[i], &attr, sum_thread, (void*)(&str_run[i])); 
	}
	for(int i=0; i<num_of_args; i++)
	{
		pthread_join(tid[i], NULL);
        printf("sum is %lld\n", str_run[i].answer);
	}
   
    
    return 0;
}
