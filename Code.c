#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
sem_t semaphore;
int size;
pthread_mutex_t mutex;
pthread_mutex_t mutex1;
struct customer
{
	int customer_id[100];
	int time[100];
};
struct barber
{
	int state;
}ptr2;
void mainfunc();
void *working1(void *args2);
void *sleep11(void *args1);
void *sleeping(void *args3);
void *check(void *args)
{
	pthread_t slept;
	int i,j;
	pthread_mutex_lock(&mutex);
	struct customer *ptr1=args;
	for(i=0;i<size;i++)
	{
		if(ptr1->customer_id[i]!=0)
		{
			ptr2.state=1;
			break;	
		}
		for(j=0;j<size;j++)
		{
		if(ptr1->customer_id[j]==0)
		{
			ptr2.state=0;
			goto j2;
		}
		}
	}
	j2:	
		pthread_create(&slept,NULL,sleep11 ,NULL);
		pthread_join(slept,NULL);
	pthread_mutex_unlock(&mutex);
//	return 0;
}
void *sleep11(void *args1)
{
    	ptr2.state=0;
}
void *sleeping(void *args3)
{
	int i,a;
	printf("Enter 1 for new customer:\n");
	printf("\nBarber Sleeping: \n");
	pthread_mutex_lock(&mutex1);
	for(i=0;i<100;i++)
	{
		scanf("%d",&a);
		if(a==1)
		{
			goto j3;
		}
		sleep(i-(i-2));
	}
	j3:
		main();
	pthread_mutex_unlock(&mutex1);
}
void *working1(void *args2)
{
	int i,sum,a;
	pthread_t slept12;
	struct customer *ptr1=args2;
	ptr2.state=1;
	sem_wait(&semaphore);
		printf("To Continue Press 0 and to go back Press1:\n");
		for(i=0;i<size;i++)
		{
			if(ptr1->customer_id[i]!=0)
			{
			printf("Barber cutting -->Customer ID :%d  for  %d seconds...\n",ptr1->customer_id[i],ptr1->time[i]);
			sleep(ptr1->time[i]);
			}
		}
	sem_post(&semaphore);
		pthread_create(&slept12,NULL,sleeping ,NULL);
		pthread_join(slept12,NULL);	
}
int main()
{
	int i,loop=0,var,time1=0,temp=0,remove,*ptr;
	pthread_t request,work;
	sem_init(&semaphore,1,1);
	struct customer ptr1;
	printf("Enter the number of chairs in waiting room\n");
	scanf("%d",&size);
	ptr=&size;
	int queue[*ptr];
	//struct barber ptr2;
	for(i=0;i<size;i++)
	{
		ptr1.customer_id[i]=0;
		ptr1.time[i]=0;
	}
	void mainfunc()
	{
	while(loop==0)
	{
	printf("\nPlease ENTER The Following choices:\n");
	printf("1. ADD a new customer\n");
	printf("2. REMOVE an old customer\n");
	printf("3. DISPLAY current Scenario\n");
	printf("4. EXIT\n");
	scanf("%d",&var);
	switch(var)
	{
		case 1:
			printf("\nEnter the ID of customer\n");
			scanf("%d",&temp);
			printf("Enter the time taken by customer in seconds\n");
			scanf("%d",&time1);
			for(i=0;i<size;i++)
			{
				if(queue[i]!=1)
				{
					queue[i]=1;
					goto j1;
				}
				else
				{
					printf("Chair %d id occupied\n",i);
				}
			}
			printf("SORRY WAIT FOR SOME TIME\n");
			break;
			j1:
			printf("Thanks for your entry\n");
			ptr1.customer_id[i]=temp;
			ptr1.time[i]=time1;
			pthread_create(&request,NULL,check ,&ptr1);
			pthread_join(request,NULL);
			break;
		case 2:
			printf("\ncustomer ID with Time:\n");
			for(i=0;i<size;i++)
			{
				printf("%d. Id:%d ->Time:%d\n",i,ptr1.customer_id[i],ptr1.time[i]);
			}
			printf("\nEnter the ID of customer to be removed:\n");
			scanf("%d",&remove);
			for(i=0;i<size;i++)
			{
				if(ptr1.customer_id[i]==remove)
				{
					ptr1.customer_id[i]=0;
					ptr1.time[i]=0;
					queue[i]=0;
				}
			}
			pthread_create(&request,NULL,check ,&ptr1);
			pthread_join(request,NULL);
			break;
		case 3:
			printf("\nSCENARIO\n");
			for(i=0;i<size;i++)
			{
				printf("ID: %d  Time: %d\n",ptr1.customer_id[i],ptr1.time[i]);
			}
			pthread_create(&work,NULL,working1 ,&ptr1);
			pthread_join(work,NULL);
			break;
		case 4:
			printf("\nTHANKYOU YOU FOR USING\nDEVELOPED BY:\nRAHUL VERMA \n11811619\nK18lE");
			sleep(5);
			loop=1;
			break;
	}
	}
	}
	mainfunc();
}
