// <original>

#include <vector>
#include <map>
#include <set>
#include <initializer_list>

int g_a;
int g_b;
int *g_pa = &g_a;
int *g_pb = &g_b;
int **g_pp = &g_pa;

struct Bag {
	int *one;
	int **two;
	std::vector<int *> items;

	Bag(std::initializer_list<int *> init, int **mirror) {
		items = init;
		one = 0;
		two = mirror;
	}

	void fill(std::initializer_list<int **> extra) {
		std::initializer_list<int **>::iterator it;
		for (it = extra.begin(); it != extra.end(); ++it) {
			if (**it != 0) {
				items.push_back(**it);
			}
		}
	}
};

int reduce(Bag *bag) {
	int s = 0;
	std::vector<int *>::iterator it;
	for (it = bag->items.begin(); it != bag->items.end(); ++it) {
		s = s + **it;
	}
	if (bag->two != 0) {
		s = s + **bag->two;
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	std::vector<int *> v = { &x, &y };
	std::map<int, int *> m = { { 1, &x }, { 2, &y } };
	std::set<int *> st = { &x, &y };
	int total;

	x = 5;
	y = 7;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	Bag bag({ p, q, &g_a }, pp);
	bag.fill({ pp, qq });

	total = reduce(&bag);
	total = total + **pp + **qq + *p + *q + **g_pp;
	total = total + *m[1] + **st.begin();
	total = total + *v[0] + *v[1];

	if (total > 0 && **pp > 0) {
		total = total - x;
	} else if (total < 0 || **qq < 0) {
		total = total + y;
	} else {
		total = 0;
	}

	return 0;
}
