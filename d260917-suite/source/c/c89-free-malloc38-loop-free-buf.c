// <svf-test-suite>@64f017e/src/mem_leak/malloc38.c

#include <stdio.h>


#include <stdlib.h>
struct Buf {

	char* name;

}Buf;

struct Buf* readBuf(){

	struct Buf *buf = malloc(10);
	buf->name = malloc(10);

	return buf;

}

void freeBuf(struct Buf* buf){
	free(buf->name);
	free(buf);

}
void SerialReadBuf(){

	int n = 1;
	while(n){

		struct Buf*	buf = readBuf();
			printf("%d%p",n,(void*)buf);

		n = 0;
		freeBuf(buf);

	};

}

int main(){
SerialReadBuf();

}
