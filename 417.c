#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
double inCircle = 0;
double total = 0;

void* child(){
	srand(time(NULL));
	int i;
	double point[2];
	for(i = 0; i < 100000; i++){
		total++;
		point[0] = (double)((rand()%100)*pow(-1,(rand()%2+1)))/100;
		point[1] = (double)((rand()%100)*pow(-1,(rand()%2+1)))/100;
	    //printf("%lf, %lf\n", point[0],point[1]);
		if((point[0]*point[0]+point[1]*point[1]) <= 1)
			inCircle ++;
	}
	pthread_exit(0);
}

int main(){
	pthread_t thr;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&thr,&attr,child,NULL);

	pthread_join(thr,NULL);
	double pi = 4 * inCircle / total;
	printf("pi ~= %lf\n",pi);
	
	return 0;
}
