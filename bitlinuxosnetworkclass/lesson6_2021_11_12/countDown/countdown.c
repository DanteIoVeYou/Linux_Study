#include <stdio.h>
#include <unistd.h>
int main() {
	int count = 10;
	while(count--) {
		printf("%d\r",count);
		fflush(stdout);
		sleep(1);
	}
	return 0;
}
