// <svf-test-suite>@64f017e/src/mem_leak/malloc39.c

#include <stdio.h>


#include <stdlib.h>
char** readBuf(){

	char ** mBuf = malloc(10);
	*mBuf = malloc(10);
	(*mBuf)[0] = '\0';
	return mBuf;

}

void freeBuf(char** fBuf){

	free(*fBuf);
	free(fBuf);
}

void SerialReadBuf(){
	int n;
	for(n = 0; n < 100; n++){

		char** buf = readBuf();
		if((*buf)[0]!='\n'){
			printf("%s",*buf);
		}
		else{
			continue;
		}

		freeBuf(buf);
	}
}

int main(){

	SerialReadBuf();
}
