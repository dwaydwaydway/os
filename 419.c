#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
int t;
void* prime(){
	if(t <= 0)
		printf("Input error\n");
	else if(t < 3)
		printf("No result\n");
	else if(t == 2)
		printf("2");
	else{
		int *map = malloc(sizeof(int)*100);
		int overflow = 95;
		map[0] = 2;
		int i, j, f;
		int q = 1;
		for(i = 3; i < t; i++){
			f = 1;
			for(j = 0; j < q; j++){
				if(i%map[j] == 0){
					f = 0;
					break;
				}
			}
			if(f){
				map[q] = i;
				q++;
			}
				

			if(q > overflow){
				int *temp = realloc(map,sizeof(int)*100);
				if(!temp)
					map = temp;
				overflow += 100;
			}
		}
	
		for(i = 0; i < q; i++)
			printf("%d ", map[i]);
		printf("\n");
	}
	pthread_exit(0);
}
int main(){
	pthread_t thd;
	pthread_attr_t attr;
	scanf("%d",&t);
	pthread_attr_init(&attr);
	pthread_create(&thd,&attr,prime,NULL);
	pthread_join(thd,NULL);
	return 0;
}
