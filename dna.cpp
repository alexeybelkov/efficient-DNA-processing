#include <iostream>
#include <string>
#include <ext/rope>
#include <algorithm>
using namespace __gnu_cxx;
using namespace std;

class rope_node {
	public:
	string s;
	int l = s.length();
	rope_node* left;
	rope_node* right;
	int h; //height
	rope_node(string s = "", int h = 1, rope_node* left = nullptr, rope_node* right = nullptr) : h(h), s(s), left(left), right(right) {}
};

class Rope {
	public:
	rope_node* root;
	rope_node* insert(rope_node*, string& s);
	Rope(rope_node* root = nullptr) : root(root) {}
};

int height(rope_node* q);
int get_balance(rope_node* q);
rope_node* left_rotate(rope_node* p);
rope_node* right_rotate(rope_node* q);

int main() {
	crope r = "something";
	return 0;
}

rope_node* Rope::insert(rope_node* q,string& s) {
	
	if (q == nullptr) {
		rope_node new_rope_node(s);
		q = &new_rope_node;
	}
	
	if (s.length() < q -> l) {
		q -> left = insert(q -> left, s);
	}
	
	else if (s.length() > q -> l) {
		q -> right = insert(q -> right, s);
	}
	
	else {
		return q;
	}
	
	q -> h = 1 + std::max(height(q -> left),height(q -> right));
	
	int balance = get_balance(q);
	
	if (balance > 1 and s.length() < q -> left -> h) {
		return right_rotate(q);
	}
	
	if (balance < -1 and s.length() > q -> right -> h) {
		return left_rotate(q);
	}
	
	if (balance > 1 and s.length() > q -> left -> h) {
		q -> left = left_rotate(q -> left);
		return right_rotate(q);
	}
	
	if (balance < -1 and s.length() < q -> right -> h) {
		q -> right = right_rotate(q -> right);
		return left_rotate(q);
	}
	
	return q;
	
}

int height(rope_node* q) {
	if (q == nullptr)
		return 0;
	return q -> h;
}

int get_balance(rope_node* q) {
	if (q == nullptr) {
		return 0;
	}
	else {
		return height(q -> left) - height(q -> right);
	}
}

rope_node* left_rotate(rope_node* p) {
	rope_node* q =  p -> left;
	rope_node* t = q -> right;
	q -> left = p;
	p -> right = t;
	p -> h  = std::max(height(p -> left), height(p -> right)) + 1;
	q -> h = std::max(height(q -> left), height(q -> right)) + 1;
	return q;
}

rope_node* right_rotate(rope_node* q) {
	rope_node* p =  q -> left;
	rope_node* t = p -> right;
	p -> right = q;
	q -> left = t;
	q -> h  = std::max(height(q -> left), height(q -> right)) + 1;
	p -> h = std::max(height(p -> left), height(p -> right)) + 1;
	return p;
}