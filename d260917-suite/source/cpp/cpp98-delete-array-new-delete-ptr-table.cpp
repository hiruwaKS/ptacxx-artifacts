// <original>

struct Item {
	int id;
	int *ref;
};

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

Item *make_items(int n, int *seed) {
	Item *arr;
	int i;
	arr = new Item[n];
	for (i = 0; i < n; i = i + 1) {
		arr[i].id = i;
		arr[i].ref = seed;
	}
	return arr;
}

int *pick(Item *arr, int n, int idx) {
	int *r;
	if (arr == 0 || n <= 0) {
		r = 0;
	} else if (idx < 0) {
		r = arr[0].ref;
	} else if (idx >= n) {
		r = arr[n - 1].ref;
	} else {
		r = arr[idx].ref;
	}
	return r;
}

int scan(Item **grid, int rows, int cols, int **pp, int **qq) {
	int s;
	int i;
	int j;
	s = 0;
	for (i = 0; i < rows; i = i + 1) {
		for (j = 0; j < cols; j = j + 1) {
			if (i == 0) {
				s = s + *grid[i][j].ref;
			} else if (j == 0) {
				s = s + **pp;
			} else {
				s = s + **qq;
			}
		}
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	Item *arr;
	Item **grid;
	Item *row0;
	Item *row1;
	int total;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	arr = make_items(4, p);
	grid = new Item *[2];
	row0 = new Item[2];
	row1 = new Item[2];
	grid[0] = row0;
	grid[1] = row1;
	row0[0].ref = p;
	row0[1].ref = q;
	row1[0].ref = q;
	row1[1].ref = p;

	*pp = &y;
	**pp = **pp + 1;
	*q = *q + 2;
	**qq = **qq + 3;

	r = pick(arr, 4, 2);
	*r = *r + 1;
	r = pick(arr, 4, 9);
	*r = *r + 1;

	total = scan(grid, 2, 2, pp, qq);
	total = total + **pp + **qq;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	delete [] arr;
	delete [] row0;
	delete [] row1;
	delete [] grid;

	return 0;
}
