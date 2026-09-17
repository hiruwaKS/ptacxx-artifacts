// <svf-test-suite>@64f017e/src/failed_tests/vector-field-sensitivity.cpp

#include <vector>

using namespace std;

class C {
public:
    int f1;
    int f2;
};

vector<C> g;

int main(int argc, char *argv[]) {

    C c_;
    g.push_back(c_);
    C &c = g[0];

    return 0;
}
