// <svf-test-suite>@64f017e/src/basic_c_tests/spec-vortex.c

#include <stdlib.h>

typedef void *AddrType;
typedef AddrType addrtype;

typedef struct Ory
{
	addrtype *ChunkAddr;
} OryType;

static addrtype TheoryChunkBacking[1];
static addrtype TheoryChunkData[1] = { (addrtype)TheoryChunkBacking };
static OryType TheoryObj = { TheoryChunkData };
OryType *Theory = &TheoryObj;

typedef struct Rectangle
{
	void (*draw) (int* p, float* q);
} Rectangle;

void Rectangle_draw(int* p, float* q) {}
addrtype Void_ExtendCore(long* p){}

void CoreMoreCore(addrtype *Region)
{
	long AllocCore1 = 0;
	*Region = (addrtype)Void_ExtendCore(&AllocCore1);
}

void MemNewOry()
{
	addrtype *ChunkAddrPtr = NULL;
	addrtype ChunkBlk = (addrtype)calloc(1,sizeof(addrtype));

	CoreMoreCore((addrtype*)(&Theory));

	if ((Theory->ChunkAddr = (addrtype*)ChunkBlk) != NULL)
	{
		ChunkAddrPtr = Theory->ChunkAddr;
		*ChunkAddrPtr = (addrtype)ChunkAddrPtr;
	}
}

void MemGetAddr(unsigned Chunk, unsigned index, addrtype *Addr)
{
	*Addr = *(((addrtype*)((Theory->ChunkAddr[Chunk])))+index);
}

void Object_GetImage(addrtype *This)
{
	unsigned chunk = 0, index = 0;
	MemGetAddr(chunk, index, This);
}

void Rectangle_new0()
{
	Rectangle* Image = NULL;
	Object_GetImage((addrtype*)&Image);
	Image->draw = Rectangle_draw;
}

void PartLib_Create(int **PrimalObj)
{
	Object_GetImage((addrtype *)PrimalObj);
}

int* PartLib01 = NULL;

int main()
{
	PartLib_Create(&PartLib01);

	return 0;
}
