#include <algorithm>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <string>

using namespace std;

struct File {
	int size;
	string name, parentFolder;
	struct File* left;
	struct File* right;
	File operator+(File& file1) {  //Addition overload for adding sizes later
		File file2;
		file2.size = size + file1.size;
		return file2;
	}
	File();
	//File(string name);
	File(string parent, string name, int size);
	
}*fl;
bool operator==(File& file1, File& file2) { //Comparison overload for comparing names
	return (file1.name == file2.name);
}
File::File() {};

File::File(string name, string parent = "", int size=0) {
	this->parentFolder = parent;
	this->name = name;
	this->size = size;
	this->left = NULL;
	this->right = NULL;
}
/*
File::File(string name) {
	this->size = 0;
	this->name = name;
	this->parentFolder = "";
}
*/
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
	void inorder(File*);
	File* AddFolder(File* t, string path, string folderName);				//Required
	void DeleteFolder(string path, string folderName);			//Required
	void AddFile(string path, string fileName, int size);		//Required
	File GetFile(string path, string fileName);					//Required
	list<File> GetFiles(string path, string fileName);			//Required
	void DeleteFile(string path, string fileName);				//Required
	void AddAttempt(File* t);

	string ParsePath(string path);
};

//Returns final folder name
string AVL_Tree::ParsePath(string path) {
	vector<string>folders;
	stringstream ss(path);
	while (ss.good()) {
		string substring;
		getline(ss, substring, '/');
		folders.push_back(substring);
	}
	return folders.back();
}


/*File AVL_Tree::GetFile(string path, string fileName) {					//Required
	string folderName;
	folderName = ParsePath(path);

	return  //return parent folder's size?
}*/

void AVL_Tree::AddAttempt(File* t) {

}

//Adds a folder given the path
File* AVL_Tree::AddFolder(File* r, string path, string folderName) {      //Assumption of passing the tree with function
	string filePath;
	filePath = ParsePath(path);
	if (r == NULL) {			//Base Case
		r = new File;
		r->parentFolder = filePath;
		r->name = folderName;
		r->left = NULL;
		r->right = NULL;
		return r;
	}
	else if (folderName < r->name) {
		r->left = AddFolder(r->left, filePath, folderName);
		r = Balance(r);
	}
	else if (folderName >= r->name) {
		r->right = AddFolder(r->right, filePath, folderName);
		r = Balance(r);
	}
	return r;
																		  
																		  
	/*if (path == "none") {			//Base Case
		File r;
		r = File("none", folderName);
	}
	else {
		string parent;
		parent = ParsePath(path);
	}*/
}


File* AVL_Tree::Insert(File* r, string name, int size = 0) {
	if (r == NULL) {			//Base Case
		r = new File;
		r->parentFolder = //
		r->size = size;
		r->name = name;
		r->left = NULL;
		r->right = NULL;
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

int AVL_Tree::Height(File* t) {
	int h = 0;
	if (t != NULL) {
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



void AVL_Tree::inorder(File* t) {		//
	if (t == NULL)					//
		return;							//
	inorder(t->left);					//
	cout << t->name << " ";				//
	inorder(t->right);					//
}

//FIX ME [Change to compare NAMES instead of size?] [WHAT IS 'int left', is it height of tree?]
/*void AVL_Tree::Show(File* p, int left) {
	int i;
	if (p != nullptr) {
		Show(p->right, left + 1);
		cout << " ";
		if (p == fl) {
			cout << "Root -> ";
		}
		for (i = 0; i < left && p != fl; i++) {
			cout << " ";
			cout << p->name;                   // Changed from size to name
			Show(p->left, left + 1);
		}
	}
}*/