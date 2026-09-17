// <svf-test-suite>@64f017e/src/basic_c_tests/struct-nested-2-layers.c

struct InnerStruct {
	int in1;
	char in2;
};

struct MidStruct {
	int mid1;
	struct InnerStruct mid2;
	char mid3;
};

struct OuterStruct {
	struct MidStruct out1;
	char out2;
	struct InnerStruct out3;
	int out4;
};

int main() {
	struct OuterStruct* pout;
	struct MidStruct* pmid;
	struct MidStruct* ptmp;
	struct InnerStruct* itmp;
	struct InnerStruct* pin;
	struct OuterStruct s;

	pout = &s;
	pmid = &s.out1;
	ptmp = &pout->out1;

	pin = &s.out1.mid2;
	itmp = &pout->out1.mid2;

	return 0;
}
