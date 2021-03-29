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

void X_request(vector<crope>& V, int i1, int i2, int j1, int j2) {
	if (j1 < 0 and j2 >= V[i2].size()) {
		crope r = "";
		V.push_back(r);
		return;
	}
	else if (j1 < 0 xor j2 >= V[i2].size()) {
		if (j1 >= 0) {
			V.push_back(V[i1].substr(0,j1 + 1));
		}
		else {
			V.push_back(V[i2].substr(j2,V[i2].size() - j2));
		}
		return;
	}
	
	else {
		crope r = V[i1].substr(0,j1 + 1);
		r += V[i2].substr(j2,V[i2].size() - j2);
		V.push_back(r);
		return;
	}

}

void EQ_request(vector<crope>& V, int i, int j, char c) {
	crope r = c;
	V[i].replace(j,1,r);
}

void COUNT_request(vector<crope>& V, int i, int j1, int j2) {
	
	crope s_str = V[i].substr(j1,j2 - j1 + 1);
	auto it = s_str.mutable_begin();
	unordered_map<char,int> M;
	
	M['A'] = 0;
	M['C'] = 0;
	M['G'] = 0;
	M['T'] = 0;
	
	while(it != s_str.mutable_end()) {
		M[*it]++;
		it++;
	}
	
	cout << M['A'] << ' ' << M['C'] << ' ' << M['G'] << ' ' << M['T'] << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	//ifstream cin("inp.txt");
	cin >> n;
	//srand(time(0));
	string input_dna;
	vector <crope> V(n);
	for (int i = 0; i < n; i++) {
		cin >> input_dna;
		crope r = input_dna.c_str();
		V[i] = r;
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
		}
		else if (req_type == '=') {
			int i,j;
			cin >> i >> j;
			char c;
			cin >> c;
			i--; j--;
			EQ_request(V,i,j,c);
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