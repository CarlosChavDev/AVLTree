#include <iostream>
using namespace std;

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

struct node {
	int data;
	node* left;
	node* right;
	int height;
	node(int d) {
		data = d;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};

class avlTree {
private:
	node* root;

public:
	avlTree() { root = nullptr; }

	void add(int data) { root = insert(root, data); }

	node* getRoot() { return root; }

	node* insert(node* t, int x) {
		if (t == nullptr)
			t = new node(x);
		else if (x < t->data) {
			t->left = insert(t->left, x);
			if (bFactor(t) == 2) {
				if (x < t->left->data)
					t = singleRight(t);
				else
					t = leftRight(t);
			}
		}
		else if (x > t->data) {
			t->right = insert(t->right, x);
			if (bFactor(t) == -2) {
				if (x > t->right->data)
					t = singleLeft(t);
				else
					t = rightLeft(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node* singleRight(node* t) {
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node* singleLeft(node* t) {
		node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node* leftRight(node* t) {
		t->left = singleLeft(t->left);
		return singleRight(t);
	}

	node* rightLeft(node* t) {
		t->right = singleRight(t->right);
		return singleLeft(t);
	}

	int height(node* cu) {
		if (cu == nullptr)
			return -1;
		else
			return cu->height;
	}

	int bFactor(node* cu) {
		return (height(cu->left) - height(cu->right));
	}

	node* lastNode(node* t) {
		if (height(t) == 0) {
			return t;
		}
		if (height(t->left) > height(t->right)) {
			return lastNode(t->left);
		}
		else {
			return lastNode(t->right);
		}
	}

	void inOrder(node* root) {
		if (root == nullptr) {
			return;
		}
		inOrder(root->left);
		cout << root->data << " ";
		inOrder(root->right);
	}

	void printLevelOrder(node* root) {
		int h = height(root);
		int i;
		for (i = 1; i <= h + 1; i++)
			printCurrentLevel(root, i);
	}

	void printCurrentLevel(node* t, int level) {
		bool check = true;
		if (t == nullptr)
			return;
		if (level == 1) {
			if (lastNode(root) == t)
				cout << t->data;
			else
				cout << t->data << " ";
		}
		else if (level > 1) {
			printCurrentLevel(t->left, level - 1);
			printCurrentLevel(t->right, level - 1);
		}
	}

	int getBalanceFactor(node* n) {
		if (n == nullptr) {
			return 0;
		}
		return(height(n->left) - height(n->right));
	}
};

int main() {
	avlTree tree;
	tree.add(5);
	tree.add(25);
	tree.add(13);
	tree.add(11);
	tree.add(9);
	tree.add(2);
	tree.printLevelOrder(tree.getRoot());
	cout << endl;
	tree.inOrder(tree.getRoot());
	cout << endl;
	cout << tree.getBalanceFactor(tree.getRoot()) << endl;
}