// <svf-test-suite>@64f017e/src/basic_c_tests/struct-incompab-typecast.c

struct SrcStruct {
	int* f1;
	int* f2;
	char f3;
};

struct DstStruct {
	char f1;
	int* f2;
	int* f3;
};

int main() {
	struct DstStruct* pdst;
	struct SrcStruct* psrc;
	struct SrcStruct s;
	int x, y, z;

	psrc = &s;
	psrc->f1 = &x;
	psrc->f2 = &y;

	pdst = (struct DstStruct*)psrc;

	pdst->f3 = &z;

	return 0;
}
