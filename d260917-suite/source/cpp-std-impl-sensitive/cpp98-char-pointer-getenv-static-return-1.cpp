// <svf-test-suite>@64f017e/src/basic_cpp_tests/static-return1.cpp

#include <cerrno>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
{
  char* p = getenv("HOME");
  char* q = getenv("HOME");

}

{
  int* p = __errno_location();
  int* q = __errno_location();

}

  return 0;
}
