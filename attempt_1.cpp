#include <iostream>
#include <vector>

using namespace std;

const int LEAF_LEN = 2;

class rope_node {
	public:
	rope_node* left;
	rope_node* right;
	rope_node* parent;
	char* s(LEAF_LEN);
	int l;
};

void createRope(rope_node*& q, rope_node* p, char c[], int l, int r) {
	rope_node* temp = new rope_node();
	temp -> left = temp -> right = nullptr;
	temp -> parent = p;
	if ((r - l) > LEAF_LEN) {
		temp -> s = nullptr;
		temp -> l = (r - 1) / 2;
		q = temp;
		int m = (l + r) / 2;
		createRope(q -> left, q, c, l, m);
		createRope(q -> right, q, c, m + 1, r);
	}
	
	else {
		q = temp;
		temp -> l = r - l;
		int j = 0;
		temp -> s = new char[LEAF_LEN];
		for (int i = l; i <= r; i++) {
			temp -> str[j++] = a[i];
		}
	}
}

void concat(rope_node*& r3, rope_node* r1, rope_node* r2, int n1) {
	rope_node* temp = new rope_node();
	temp -> parent = nullptr;
	temp -> left = r1;
	temp -> right = r2;
	r1 -> parent = r2 -> parent = temp;
	temp -> l = n1;
	temp -> s = nullptr;
	r3 = temp;
}

int main() {
	return 0;
}
