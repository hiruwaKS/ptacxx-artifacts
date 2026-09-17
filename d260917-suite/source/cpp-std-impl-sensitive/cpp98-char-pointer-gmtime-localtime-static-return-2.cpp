// <svf-test-suite>@64f017e/src/basic_cpp_tests/static-return2.cpp

#include <ctime>

using namespace std;

int main(int argc, char **argv)
{
  time_t time = 0;
  tm* p1 = gmtime(&time);
  tm* p2 = gmtime(&time);
  tm* q1 = localtime(&time);
  tm* q2 = localtime(&time);

  return 0;
}
