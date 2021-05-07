#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const int LEAF_LEN = 100000;

typedef class Node* pNode;
//typedef pair<Rope,Rope> rope_pair;
typedef pair<pNode, pNode> node_pair;

class Node {
public:
    pNode left;
    pNode right;
    pNode parent;
    int x;
    string S;
    Node(string _S = "", pNode _left = nullptr, pNode _right = nullptr, pNode _parent = nullptr) : S(_S), left(_left), right(_right), parent(_parent) {
        this->x = _S.length() ? _S.length() : 0;
    }
};

class Rope {
public:
    pNode root;
    Rope(pNode _root = nullptr) : root(_root) {}
    pNode get_root(pNode& q);
    void rope_init(pNode& root, pNode parent, string& S, int L, int R);
};

void inorder(pNode q, map<char, int>& M);
void postorder(pNode q);
void leaf_trav(pNode q);
pNode merge(pNode q1, pNode q2);
node_pair split(pNode node, int i);
void char_at(pNode& q, int i, char c);



node_pair X_req(pNode q1, pNode q2, int j1, int j2) {
    node_pair res;
    node_pair p1, p2;
    if (j1 > 0) {
        p1 = split(q1, j1);
    }
    else {
        p1 = make_pair(new Node(),q1);
    }
    if (j2 < q2 -> x) {
        p2 = split(q2, j2);
    }
    else {
        p2 = make_pair(q2, new Node());
    }
    res = make_pair(merge(p1.first, p2.second),merge(p1.second,p2.first));
    //cout << "res: ";
    //leaf_trav(res);
    //cout << endl;
    return res;
}

void Count(Rope r, int i, int j) {
    pNode p_i, p_j;
    p_i = split(r.root, i - 1 >= 0 ? i - 1 : 0).second;
    p_j = split(p_i, j - i + 1).first;
    map<char, int> M;
    M['A'] = 0;
    M['C'] = 0;
    M['G'] = 0;
    M['T'] = 0;
    inorder(p_j, M);
    cout << M['A'] << ' ' << M['C'] << ' ' << M['G'] << ' ' << M['T'] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<Rope> V(n);
    string input_dna;
    for (int i = 0; i < n; i++) {
        cin >> input_dna;
        Rope r;
        r.rope_init(r.root, nullptr, input_dna, 0, input_dna.length());
        V[i] = r;
    }

    int req_num;
    cin >> req_num;
    char req_type;
    for (int k = 0; k < req_num; k++) {
        cin >> req_type;

        if (req_type == 'X') {
            int i1, i2, j1, j2;
            cin >> i1 >> i2 >> j1 >> j2;
            node_pair p;
            p = X_req(V[i1 - 1].root, V[i2 - 1].root, j1, j2);
            V.push_back(p.first);
            V.push_back(p.second);
            //Rope r2;
            //r2.root = X_req(V[i1 - 1].root, V[i2 - 1].root, j2, j1);
            //V.push_back(r2);
        }
        else if (req_type == '=') {
            int i, j;
            char c;
            cin >> i >> j >> c;
            char_at(V[i - 1].root, j - 1, c);
        }

        else {
            int i, j1, j2;
            cin >> i >> j1 >> j2;
            Count(V[i - 1], j1, j2);
        }
    }


    //leaf_trav(V[15].root);
}

void inorder(pNode q, map<char, int>& M) {
    if (!q) return;
    inorder(q->left, M);
    if (q->S.length())
        for (char x : q->S)
            M[x]++;
    inorder(q->right, M);

}


void char_at(pNode& node, int i, char c) {
    if (node -> left) {
        if (node -> left -> x > i) {
            return char_at(node -> left, i, c);
        }
        else {
            return char_at(node -> right, i - node -> left -> x, c);
        }
    }
    else {
        (node -> S)[i] = c;
    }
}

node_pair split(pNode node, int i) {
    pNode tree1 = new Node();
    pNode tree2 = new Node();
    if (node->left) {
        if (node->left->x >= i) {
            node_pair res = split(node->left, i);
            tree1 = res.first;
            tree2->left = res.second;
            tree2->right = node->right;
            tree2->x = tree2->left->x + tree2->right->x;
        }

        else {
            node_pair res = split(node->right, i - node->left->x);
            tree1->left = node->left;
            tree1->right = res.first;
            tree1->x = tree1->left->x + tree1->right->x;
            tree2 = res.second;
        }
    }

    else {
        tree1->S = node->S.substr(0, i);
        tree2->S = node->S.substr(i, node->S.length());
        tree1->x = i;
        tree2->x = node->S.length() - i;
    }
    return make_pair(tree1, tree2);

}

void Rope::rope_init(pNode& root, pNode parent, string& S, int L, int R) {
    pNode temp = new Node();
    if (R - L > LEAF_LEN) {
        temp->x = R - L;
        root = temp;
        int m = (R + L) / 2;
        rope_init(root->left, root, S, L, m);
        rope_init(root->right, root, S, m, R);
    }

    else {
        root = temp;
        temp->x = R - L;
        temp->S = S.substr(L, R - L);
    }
}

pNode merge(pNode q1, pNode q2) {
    pNode new_root = new Node();
    new_root->left = q1;
    q1->parent = new_root;
    new_root->right = q2;
    q2->parent = new_root;
    new_root->x = q1->x + q2->x;
    return new_root;
}

pNode Rope::get_root(pNode& q) {
    pNode temp = q;
    while (temp) {
        q = temp;
        temp = temp->parent;
    }
    return q;
}

void postorder(pNode q) {
    if (!q) return;

    postorder(q->left);
    postorder(q->right);
    cout << q->S << ' ' << q->x << '\n';
}

void leaf_trav(pNode q) {
    if (q == nullptr) return;
    if (q->left == nullptr && q->right == nullptr) {
        cout << q->S;
    }

    leaf_trav(q->left);
    leaf_trav(q->right);
}