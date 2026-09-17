// <svf-test-suite>@64f017e/src/path_tests/path5.c

struct agg{
    int*pi;
    int k;
}agg;

int main(){
    int *s,k1=0,k2;
    struct agg *a,*b, obj1,obj2;

    a = &obj1;
    b = &obj2;
    if(k1){
        a = &obj1;
        s=&k1;
    }
    else{
        b = &obj2;
        s=&k2;
    }

    a->pi = s;
    b->pi = s;

}
