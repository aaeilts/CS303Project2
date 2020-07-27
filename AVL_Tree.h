#include <algorithm>
#include <iostream>
#include "AVL_Node.h"

using namespace std;

class AVL_Tree {
public:
	int Height(AVL_Node*);
	int Difference(AVL_Node*);
	AVL_Node* RR_Rotate(AVL_Node*);
	AVL_Node* LL_Rotate(AVL_Node*);
	AVL_Node* LR_Rotate(AVL_Node*);
	AVL_Node* RL_Rotate(AVL_Node*);
	AVL_Node* Balance(AVL_Node*);
	AVL_Node* Insert(AVL_Node*, int);
	void Show(AVL_Node*, int);
	AVL_Tree() {
		r = nullptr;
	}
};

int AVL_Tree::Height(AVL_Node* t) {
	int h = 0;
	if (t != nullptr) {
		int lHeight = Height(t->left);
		int rHeight = Height(t->right);
		int maxHeight = max(lHeight, rHeight);
		h = maxHeight + 1;
	}
	return h;
}

int AVL_Tree::Difference(AVL_Node* t) {
	int lHeight = Height(t->left);
	int rHeight = Height(t->right);
	int difference = lHeight - rHeight;
	return difference;
}

AVL_Node* AVL_Tree::RR_Rotate(AVL_Node* parent) {
	AVL_Node* t;
	t = parent->right;
	parent->right = t->left;
	t->left = parent;
	return t;
}

AVL_Node* AVL_Tree::LL_Rotate(AVL_Node* parent) {
	AVL_Node* t;
	t = parent->left;
	parent->left = t->right;
	t->right = parent;
	return t;
}

AVL_Node* AVL_Tree::LR_Rotate(AVL_Node* parent) {
	AVL_Node* t;
	t = parent->left;
	parent->left = RR_Rotate(t);
	return LL_Rotate(parent);
}

AVL_Node* AVL_Tree::RL_Rotate(AVL_Node* parent) {
	AVL_Node* t;
	t = parent->right;
	parent->right = LL_Rotate(t);
	return RR_Rotate(parent);
}

AVL_Node* AVL_Tree::Balance(AVL_Node* t) {
	int bal_factor = Difference(t);
	if (bal_factor > 1) {
		if (Difference(t->left) > 0) {
			t = LL_Rotate(t);
		}
		else {
			t = LR_Rotate(t);

		}
	}
	else if (bal_factor < -1) {
		if (Difference(t->right) > 0) {
			t = RL_Rotate(t);
		}
		else {
			t = RR_Rotate(t);
		}

	}
	return t;
}

AVL_Node* AVL_Tree::Insert(AVL_Node* r, int v) {
	if (r == nullptr) {
		r = new AVL_Node;
		r->d = v;
		r->left = nullptr;
		r->right = nullptr;
		return r;
	}
	else if (v < r->d) {
		r->left = Insert(r->left, v);
		r = Balance(r);
	}
	else if (v >= r->d) {
		r->right = Insert(r->right, v);
		r = Balance(r);
	}
	return r;
}

void AVL_Tree::Show(AVL_Node* p, int left) {
	int i;
	if (p != nullptr) {
		Show(p->right, left + 1);
		cout << " ";
		if (p == r) {
			cout << "Root -> ";
		}
		for (i = 0; i < left && p != r; i++) {
			cout << " ";
			cout << p->d;
			Show(p->left, left + 1);
		}
	}
}