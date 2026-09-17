// <original>

using namespace std;
struct sk_buff {
  int len;
  char* data;
  sk_buff* next;
};
int main() {
  char buf[8];
  int a = 1;
  sk_buff pkt;
  pkt.data = buf;
  pkt.next = nullptr;
  char* p = pkt.data;
  return 0;
}
