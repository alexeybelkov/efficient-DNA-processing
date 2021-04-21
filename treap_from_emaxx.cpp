#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef class Node* pNode;

class Node {
	public:
		int prior;
		int value;
		int count;
		bool rev;
		pNode left, right;
};

int count(pNode p) {
	return p ? p -> count : 0;
}

void update_count(pNode p) {
	if (p) {
		p -> count = count(p -> left) + count (p -> right);
	}
}

void push(pNode p) {
	if (p and p -> rev) {
		p -> rev = false;
		swap(p -> left , p -> right);
		
		if (p -> left) {
			p -> left -> rev ^= true;
		}
		
		if (p -> right) {
			p -> right -> rev ^= true;
			
		}
		
	}
}

void merge (pNode& p, pNode left , pNode right) {
	push(left);
	push(right);
	
	if (!left or !right) {
		p = left ? left : right;
	}
	
	else if (left -> prior > right -> prior) {
		merge (left -> right, left -> left, right);
	}
	
	else {
		merge (right -> left, right -> right, left);
	}
	
	update_count(p);
}

void split (pNode p, pNode& left, pNode& right, int key, int add = 0) {
	if (!p) {
		return void(left = right = 0);
	}
	
	push(p);
	int current_key = add + count(p -> right);
	if (key <= current_key) {
		split(p -> left, left, p -> left , key, add), right = p;
	}
	else {
		split(p -> right, p -> right, right, key, add + 1 + count(p -> left)), left = p;
	}
	update_count(p);
}

void reverse (pNode p, int l, int r) {
	pNode p1, p2, p3;
	split(p, p1, p2, l);
	split(p2, p2, p3, r - l + 1);
	p2 -> rev ^= true;
	merge (p, p1, p2);
	merge (p, p, p3);
}

void insert(int key, int pos) {
	split();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	return 0;
}