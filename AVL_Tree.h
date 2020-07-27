#include "AVL_Node.h"


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
	void InOrder(AVL_Node*);
	void PreOrder(AVL_Node*);
	void PostOrder(AVL_Node*);
	AVL_Tree() {
		r = nullptr;
	}
};

int Height(AVL_Node*);


