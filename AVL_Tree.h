#include <algorithm>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <string>

using namespace std;

struct File {
	int size;
	string name;
	struct File* left;
	struct File* right;
	File operator+(File& file1) {  //Addition overload for adding sizes later
		File file2;
		file2.size = size + file1.size;
		return file2;
	}
}*fl;
bool operator==(File& file1, File& file2) { //Comparison overload for comparing names
	return (file1.name == file2.name);
}

class AVL_Tree {
public:
	int Height(File*);
	int Difference(File*);
	File* RR_Rotate(File*);
	File* LL_Rotate(File*);
	File* LR_Rotate(File*);
	File* RL_Rotate(File*);
	File* Balance(File*);
	File* Insert(File*, string, int);				
	void Show(File*, int);							
	AVL_Tree() {
		fl = nullptr;
	}
	void AddFolder(string path, string folderName);				//Required
	void DeleteFolder(string path, string folderName);			//Required
	void AddFile(string path, string fileName, int size);		//Required
	File GetFile(string path, string fileName);					//Required
	list<File> GetFiles(string path, string fileName);			//Required
	void DeleteFile(string path, string fileName);				//Required

	vector<string> ParsePath(string path);
};

//Returns a vector of folder names
vector<string> AVL_Tree::ParsePath(string path) {
	vector<string>folders;
	stringstream ss(path);
	while (ss.good()) {
		string substring;
		getline(ss, substring, '/');
		folders.push_back(substring);
	}
	return folders;
}

//FIX ME - Adds a folder given the path
void AVL_Tree::AddFolder(string path, string folderName) {
	if (path == "none") {
		fl = Insert(fl, folderName, 0);
	}
	else {
		vector<string> folders;
		folders = ParsePath(path);
		//Have folder names, now how to compare with node names and move down to children

	}
}


int AVL_Tree::Height(File* t) {
	int h = 0;
	if (t != nullptr) {
		int lHeight = Height(t->left);
		int rHeight = Height(t->right);
		int maxHeight = max(lHeight, rHeight);
		h = maxHeight + 1;
	}
	return h;
}

int AVL_Tree::Difference(File* t) {
	int lHeight = Height(t->left);
	int rHeight = Height(t->right);
	int difference = lHeight - rHeight;
	return difference;
}

File* AVL_Tree::RR_Rotate(File* parent) {
	File* t;
	t = parent->right;
	parent->right = t->left;
	t->left = parent;
	return t;
}

File* AVL_Tree::LL_Rotate(File* parent) {
	File* t;
	t = parent->left;
	parent->left = t->right;
	t->right = parent;
	return t;
}

File* AVL_Tree::LR_Rotate(File* parent) {
	File* t;
	t = parent->left;
	parent->left = RR_Rotate(t);
	return LL_Rotate(parent);
}

File* AVL_Tree::RL_Rotate(File* parent) {
	File* t;
	t = parent->right;
	parent->right = LL_Rotate(t);
	return RR_Rotate(parent);
}

File* AVL_Tree::Balance(File* t) {
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

File* AVL_Tree::Insert(File* r, string name, int size) {
	if (r == nullptr) {
		r = new File;
		r->size = size;
		r->name = name;
		r->left = nullptr;
		r->right = nullptr;
		return r;
	}
	else if (name < r->name) {
		r->left = Insert(r->left, name, size);
		r = Balance(r);
	}
	else if (name >= r->name) {
		r->right = Insert(r->right, name, size);
		r = Balance(r);
	}
	return r;
}

void AVL_Tree::Show(File* p, int left) {
	int i;
	if (p != nullptr) {
		Show(p->right, left + 1);
		cout << " ";
		if (p == fl) {
			cout << "Root -> ";
		}
		for (i = 0; i < left && p != fl; i++) {
			cout << " ";
			cout << p->size;
			Show(p->left, left + 1);
		}
	}
}