// <svf-test-suite>@64f017e/src/non_annotated_tests/array/array2.c

struct agg{
    int a;
    struct fgg{
	int k;
    }fgg;
}agg;

int main(){
    struct agg str1;
    struct agg* str2 = &str1;

    str2->fgg.k = 100;

}
