// <svf-test-suite>@64f017e/src/basic_c_tests/struct-nested-array3.c

struct InnerArrayStruct {
	int in1[10];
	char in2;
	double in3;
};

struct MidArrayStruct {
	char mid1;
	struct InnerArrayStruct mid2[5];
	double mid3[20];
};

struct ArrayStruct {
	int out1;
	char out2;
	struct MidArrayStruct out3;
	int out4;
};

int main() {
	struct ArrayStruct* p;
	struct ArrayStruct s;

	p = &s;

	return 0;
}
