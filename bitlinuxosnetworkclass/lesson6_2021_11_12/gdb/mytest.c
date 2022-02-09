#include <stdio.h>
int sum(int top) {
	
	int _sum = 0;
	int i = 0;
	for(;i <= top; i++) {
		_sum += i;
	}
	return _sum;
}
int main() {
	int max = 0;
	printf("please enter your data# ");
	//scanf("%d",&max);
	int _sum = sum(100);
	printf("1:%d\n", _sum);
	printf("2:%d\n", _sum);
	printf("3:%d\n", _sum);
	printf("4:%d\n", _sum);
	printf("5:%d\n", _sum);
	printf("6:%d\n", _sum);
	return 0;
}
