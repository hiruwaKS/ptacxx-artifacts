// <svf-test-suite>@64f017e/src/basic_cpp_tests/variant-gep.cpp

struct Point{
	int x;
	int y;
};
struct D3Point:public Point{
	int z;
};
struct Data{
	int d;
	int a;
	int t;
	Point p;

};

int main(int argc, char * argv[]){
	Data *dt = new Data[16];

	Point * ptr = &dt[argc].p;
	D3Point * c = static_cast<D3Point*>(ptr);

	ptr = &dt[3].p;
	c = static_cast<D3Point*>(ptr);
}
