#include <algorithm>					//Assumptions:
#include <iostream>						//Assume no more than two matching files when searching
#include <sstream>						//Assumption of passing the tree with function
#include <list>							//Assumption that folders were built sequentially one at a time
#include <vector>						//
#include <string>						//

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
	File(string parent, string name, int size);
	
}*fl;
bool operator==(File& file1, File& file2) { //Comparison overload for comparing names
	return (file1.name == file2.name);
}
File::File() {
	size = 0;
	left = NULL;
	right = NULL;
};

File::File(string name, string parent = "", int size=0) {
	this->parentFolder = parent;
	this->name = name;
	this->size = size;
	this->left = NULL;
	this->right = NULL;
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
	void inorder(File*);
	File* AddFolder(File* t, string path, string folderName);										//DONE 
	void DeleteFolder(string path, string folderName);												//Required //Come back
	File* AddFile(File* t, string path, string fileName, int size);									//Add changing size functions
	File GetFile(File* t, string path, string fileName);											//DONE
	list<File> GetFiles(list<File> files, File* t, string path, string fileName);					//DONE 
	void DeleteFile(File* t, string path, string fileName);											//Come back

	string ParsePath(string path);
	void ChangeSize(); //Goes in add file function, 
};

void AVL_Tree::DeleteFile(File* t, string path, string fileName) {
	if (t == NULL) {
		cout << "File not found";
	}
	if (fileName < t->name) {
		DeleteFile(t->left, path, fileName);
	}
	else if (fileName > t->name) {
		DeleteFile(t->right, path, fileName);
	}
	else {
		if ((t->left == NULL) || (t->right == NULL)) { //Node with only one child or no child
			if ((t->left == NULL) && (t->right == NULL)) {
				t = NULL;
			}
			else {
				File* temp;
				temp = NULL;
				if (t->left == NULL) {
					temp = NULL;
				}
				else if (t->left != NULL) {
					temp = t->left;
				}
				if (t->right == NULL) {
					t->left = NULL;
				}
				else if (t->right != NULL) {
					t->left = t->right;
				}
				if (temp == NULL) { //No child case?
					temp = t;
					t = NULL;
				}
				else {
					*t = *temp;
				}
				free(temp);
			}
		}
		else {
			File* temp = t->right;
			t->name = temp->name;
			DeleteFile(t->right, path, temp->name);

		}
	}
}

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

list<File> AVL_Tree::GetFiles(list<File> files, File* t, string path, string fileName) {  
	if (t->left != NULL && t->right != NULL) {
		if ((t->left->name.substr(0, fileName.size()) == fileName) && (t->right->name.substr(0, fileName.size()) == fileName)) {
			File r;
			r = *t->left;				//ABOVE IF STATEMENT ONLY EXECUTES WHEN BOTH LEFT AND RIGHT CHILDREN MATCH SEARCH
			files.push_back(r);
			r = *t->right;
			files.push_back(r);
			return files;
		}
	}
	if (t->name.substr(0, fileName.size()) == fileName) {
		File r;
		r = *t;
		files.push_back(r);
	}
	if (t->left == NULL && t->right == NULL) {   //If a leaf
		return files;
	}
	else if (fileName < t->name.substr(0, fileName.size())) {  //If less than search term
		 return GetFiles(files, t->left, path, fileName);
	}
	else if (fileName > t->name.substr(0, fileName.size())) {  //Greater than search term
		return GetFiles(files, t->right, path, fileName);
	}
	else {
		if (t->left->name < t->name) {								//For when the search term is too short to compare file names
			return GetFiles(files, t->left, path, fileName);		//the function enters this else suite to keep transcending
		}
		else {
			return GetFiles(files, t->right, path, fileName);
		}
	}
}

File AVL_Tree::GetFile(File* t, string path, string fileName) {		
	string parentName;
	File r;
	parentName = ParsePath(path);
	if (t->name == fileName) {
		r = *t;
		return r;
	}
	else if (fileName < t->name) {
		r = GetFile(t->left, parentName, fileName);
	}
	else if (fileName >= t->name){
		r = GetFile(t->right, parentName, fileName);
	}
	return r;
}
 
File* AVL_Tree::AddFile(File* r, string path, string fileName, int size=0) {
	string filePath;
	filePath = ParsePath(path);
	if (r == NULL) {			//Base Case
		r = new File;
		r->size = size;
		r->parentFolder = filePath;
		r->name = fileName;
		r->left = NULL;
		r->right = NULL;
		return r;
	}
	else if (fileName < r->name) {
		r->left = AddFolder(r->left, filePath, fileName);
		r = Balance(r);
	}
	else if (fileName >= r->name) {
		r->right = AddFolder(r->right, filePath, fileName);
		r = Balance(r);
	}
	return r;
}

//Adds a folder given the path
File* AVL_Tree::AddFolder(File* t, string path, string folderName) {      
	string filePath;
	filePath = ParsePath(path);
	if (t == NULL) {			
		t = new File;
		t->parentFolder = filePath;
		t->name = folderName;
		t->left = NULL;
		t->right = NULL;
		return t;
	}
	else if (folderName < t->name) {
		t->left = AddFolder(t->left, filePath, folderName);
		t = Balance(t);
	}
	else if (folderName >= t->name) {
		t->right = AddFolder(t->right, filePath, folderName);
		t = Balance(t);
	}
	return t;
}

File* AVL_Tree::Insert(File* t, string name, int size = 0) {
	if (t == NULL) {
		t = new File;
		t->parentFolder = "";
		t->size = size;
		t->name = name;
		t->left = NULL;
		t->right = NULL;
		return t;
	}
	else if (name < t->name) {
		t->left = Insert(t->left, name, size);
		t = Balance(t);
	}
	else if (name >= t->name) {
		t->right = Insert(t->right, name, size);
		t = Balance(t);
	}
	return t;
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

void AVL_Tree::inorder(File* t) {
	if (t == NULL)						
		return;							
	inorder(t->left);					
	cout << t->name << " ";				
	inorder(t->right);					
}