// <svf-test-suite>@64f017e/src/basic_c_tests/spec-gap.c

#include <stdlib.h>

static long BagRaw[16];

static char *SyGetmem(long size) { (void)size; return (char *)BagRaw; }

typedef struct TypHeader {
	struct TypHeader    * * ptr;
}    * TypHandle;

static struct TypHeader FreeHandleCell = { (TypHandle*)((char *)BagRaw + 104) };

TypHandle HdFree;
TypHandle FreeHandle = &FreeHandleCell;
TypHandle* FirstBag = (TypHandle*)((char *)BagRaw + 128);

void IntComm () {}

TypHandle NewBag() {
	long needed = 0;
	TypHandle *d, *s, *e;
	TypHandle h;

	d = ((TypHandle*)((HdFree)->ptr)) + needed / (sizeof(TypHandle)) - 1;
	s = ((TypHandle*)((HdFree)->ptr)) - 1;
	e = (FirstBag-1);
	while ( e <= s )  *d-- = *s--;

	for (h=HdFree; h < (TypHandle)(FirstBag-1); ++h)
		h->ptr += needed / (sizeof(TypHandle));

	h->ptr = (TypHandle*)FreeHandle;
	FreeHandle = h;

	return FreeHandle;
}

void InstIntFunc(void (*func)()) {
	TypHandle hdDef = NewBag();
	*(void(**)())((TypHandle*)((hdDef)->ptr)) = func;
}

void InitGasman() {
	long SyMemory = (long)sizeof(BagRaw);
	HdFree = (TypHandle)SyGetmem( SyMemory );
	HdFree->ptr = FirstBag;
	FreeHandle = (TypHandle)((TypHandle*)((FreeHandle)->ptr));
}

int main() {
	InitGasman();
	InstIntFunc(IntComm);
	return 0;
}
