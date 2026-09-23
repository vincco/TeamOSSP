#include<stdio.h>
int main(){
	int *ptr=NULL;
	int x;
	ptr = &x;
	printf("x = %d",x);
	printf("address of x = %u", &x);
	printf("value of ptr=%u", ptr);
	printf("value at ptr=%d, *ptr);
	printf("address of ptr = %ls", &ptr);
	return 0;
}
