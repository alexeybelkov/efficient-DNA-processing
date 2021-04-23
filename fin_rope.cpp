#include <iostream>
#include <ext/rope>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>
#include <fstream>
using namespace __gnu_cxx;
using namespace std;

void X_request(vector<rope<char>>& V, int i1, int i2, int j1, int j2) {
	if (j1 < 0 and j2 >= V[i2].size()) {
		V.push_back(rope<char>(""));
		return;
	}
	else if (j1 < 0 xor j2 >= V[i2].length()) {
		
		if (j1 >= 0) {
			if (V[i1].size() >= j1 + 1) {
				V.push_back(V[i1].substr(0,j1 + 1));
			}
			else {
				V.push_back(rope<char>(""));
			}
		}
		
		else {
			V.push_back(V[i2].substr(j2,V[i2].length() - j2 + 1));
		}
		
		return;
	}
	
	else {
		rope<char> r = V[i1].substr(0,j1 + 1);
		r += V[i2].substr(j2,V[i2].length());
		V.push_back(r);
		return;
	}

}

void EQ_request(vector<rope<char>>& V, int i, int j, char c) {
	rope<char> r = c;
	if (V[i].size() >= j + 1) {
		auto it = V[i].mutable_begin();
		it += j;
		V[i].replace(it,c);
	}
}

void COUNT_request(vector<rope<char>>& V, int i, int j1, int j2) {
	
	if (j1 <= j2) {
		rope<char> s_str = V[i].substr(j1,j2 - j1 + 1);
		auto it = s_str.begin();
		unordered_map<char,int> M;
	
		M['A'] = 0;
		M['C'] = 0;
		M['G'] = 0;
		M['T'] = 0;
	
		while(it != s_str.end()) {
			M[*it]++;
			it++;
		}
	
		cout << M['A'] << ' ' << M['C'] << ' ' << M['G'] << ' ' << M['T'] << '\n';
	}
	
	else {
		cout << 0 << ' ' << 0 << ' ' << 0 << ' ' << 0 << '\n';
	}
	
}

int main() {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	//srand(time(0));
	string input_dna;
	vector <rope<char>> V(n);
	
	for (int i = 0; i < n; i++) {
		cin >> input_dna;
		V[i] = rope<char>(input_dna.c_str());
	}
	int req_num;
	cin >> req_num;
	char req_type;
	for (int t = 0; t < req_num; t++) {
		cin >> req_type;
		if (req_type == 'X') {
			int i1,i2,j1,j2;
			cin >> i1 >> i2 >> j1 >> j2;
			i1--; i2--;j1--;
			X_request(V,i1,i2,j1,j2);
			j1++; j2--;
			X_request(V,i2,i1,j2,j1);
			//V[V.size() - 1].balance();
			//V[V.size() - 2].balance();
		}
		else if (req_type == '=') {
			int i,j;
			cin >> i >> j;
			char c;
			cin >> c;
			i--; j--;
			EQ_request(V,i,j,c);
			//V[V.size() - 1].balance();
			//V[V.size() - 2].balance();
		}
		else {
			int i,j1,j2;
			cin >> i >> j1 >> j2;
			i--; j1--; j2--;
			COUNT_request(V,i,j1,j2);
		}
	}
	//cout << "\nTIME : " << clock() << '\n';
}