// <original>

#include <stack>

using namespace std;

int main() {
  int a = 1;
  stack<int*> st;
  st.push(&a);
  int* p = st.top();
  return 0;
}
