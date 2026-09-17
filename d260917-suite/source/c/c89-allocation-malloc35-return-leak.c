// <svf-test-suite>@64f017e/src/mem_leak/malloc35.c

#include <stdio.h>


#include <stdlib.h>
int* readcolor(){

	int*image = calloc(25, sizeof(int));

	return image;

}

int main(){

	int* image1 = readcolor();

	printf("%p",(void*)image1);

	free(image1);
	return 0;
}
