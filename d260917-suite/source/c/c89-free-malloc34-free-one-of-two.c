// <svf-test-suite>@64f017e/src/mem_leak/malloc34.c

#include <stdio.h>


#include <stdlib.h>
int* readcolor(){

	int*image = malloc(100);
	return image;

}

int main(){

	int* image1 = readcolor();

	int* image2 = readcolor();

	free(image1);

	printf("%p%p",(void*)image1,(void*)image2);

}
