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
	File();
	File(string parent, string name, int size);
}*fl;

File::File() {
	size = 0;
	left = NULL;
	right = NULL;
};

File::File(string name, string parent = "", int size = 0) {
	this->parentFolder = parent;
	this->name = name;
	this->size = size;
	this->left = NULL;
	this->right = NULL;
}

class AVL_Tree {
public:
	vector<string> folderNames, allFolderNames;
	int Height(File*);
	int Difference(File*);
	File* RR_Rotate(File*);
	File* LL_Rotate(File*);
	File* LR_Rotate(File*);
	File* RL_Rotate(File*);
	File* Balance(File*);
	File* Insert(File*, string, int);
	void inorder(File*);

	File* AddFolder(File* t, string path, string folderName);										 
	void DeleteFolder(File* t, string path, string folderName);										
	File* AddFile(File* t, string path, string fileName, int size);									
	File GetFile(File* t, string path, string fileName);											
	list<File> GetFiles(list<File> files, File* t, string path, string fileName);					
	void DeleteFile(File* t, string path, string fileName);											

	//void UpdateSizesPlus(File* t, string path, string searchName);
	File* GetFile2(File* t, string path, string fileName);
	vector<string> ParsePath(string path);
};

//Finds and removes the specified Folder passed to it
void AVL_Tree::DeleteFolder(File* t, string path, string folderName) {
	if (t == NULL) {
		cout << "File not found";
	}
	if (folderName < t->name) {
		DeleteFolder(t->left, path, folderName);
	}
	else if (folderName > t->name) {
		DeleteFolder(t->right, path, folderName);
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
				if (temp == NULL) { //No child case
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
			DeleteFolder(t->right, path, temp->name);

		}
	}
}

//Finds and removes the specified File passed to it
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
				if (temp == NULL) { //No child case
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
			t = Balance(t);
			DeleteFile(t->right, path, temp->name);

		}
	}
}

//Returns vector of folder names
vector<string> AVL_Tree::ParsePath(string path) {
	stringstream ss(path);
	while (ss.good()) {
		string substring;
		getline(ss, substring, '/');
		folderNames.push_back(substring);
	}
	return folderNames;
}

//Returns the file passed in if found
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

//Returns the file object passed in if available
File AVL_Tree::GetFile(File* t, string path, string fileName) {		
	string parentName;
	File r;
	parentName = ParsePath(path).back();
	if (t->name == fileName) {
		r = *t;
		return r;
	}
	else if (fileName < t->name) {
		r = GetFile(t->left, parentName, fileName);
	}
	else if (fileName >= t->name) {
		r = GetFile(t->right, parentName, fileName);
	}
	return r;
}

//Get file that returns pointer to file object
File* AVL_Tree::GetFile2(File* t, string path, string fileName) { 
	string parentName, nodeName;
	File r;
	parentName = ParsePath(path).back();
	if (t->name == parentName) {               
		return t;
	}
	else if (fileName < t->name) {
		t = GetFile2(t->left, parentName, fileName);
	}
	else if (fileName >= t->name) {
		t = GetFile2(t->right, parentName, fileName);
	}
	return t;
}

//Adds file to binary search tree
File* AVL_Tree::AddFile(File* t, string path, string fileName, int size = 0) {
	folderNames.clear();
	folderNames = ParsePath(path);
	if (t == NULL) {			//Base Case
		t = new File;
		t->size = size;
		t->parentFolder = folderNames.back();
		t->name = fileName;
		t->left = NULL;
		t->right = NULL;
		folderNames.pop_back();
		return t;
	}
	else if (fileName < t->name) {
		string path2;
		for (int i = 0; i < folderNames.size() - 1; i++) {
			path2 += folderNames.at(i) + "/";  //Add a slash
		}
		path2 += folderNames.back();
		t->left = AddFile(t->left, path2, fileName, size);
		t = Balance(t);
	}
	else if (fileName >= t->name) {
		string path2;
		for (int i = 0; i < folderNames.size() - 1; i++) {
			path2 += folderNames.at(i) + "/";  //Add a slash
		}
		path2 += folderNames.back();
		t->right = AddFile(t->right, path2, fileName, size);
		t = Balance(t);
	}
	return t;
}

//Function to update filesizes when a file is added 
/*void AVL_Tree::UpdateSizesPlus(File* t, string path, string FileName) {
	File* s;
	string parentName; int fileSize;
	s = GetFile2(t, path, FileName);		//Returns an actual file
	fileSize = s->size;							//Saves size to add
	parentName = s->parentFolder;
	while (parentName != "") {
		File* r;
		r = GetFile2(t, path, parentName);
		r->size += fileSize;
		parentName = t->parentFolder;
	}
}*/
//Function to update filesizes when a file is added
/*void AVL_Tree::UpdateSizesMinus(File* t, string path, string FileName) {
	File* s;
	string parentName; int fileSize;
	s = GetFile2(t, path, FileName);		//Returns an actual file
	fileSize = s->size;							//Saves size to add
	parentName = s->parentFolder;
	while (parentName != "") {
		File* r;
		r = GetFile2(t, path, parentName);
		r->size -= fileSize;
		parentName = t->parentFolder;
	}
}*/

//Adds a folder given the path
File* AVL_Tree::AddFolder(File* t, string path, string folderName) {
	folderNames.clear();
	folderNames = ParsePath(path);
	if (t == NULL) {
		t = new File;
		t->parentFolder = folderNames.back();
		folderNames.pop_back();
		t->name = folderName;
		t->left = NULL;
		t->right = NULL;
		return t;
	}
	else if (folderName < t->name) {
		string path2 = "";
		for (int i = 0; i < folderNames.size() - 1; i++) {
			path2 += folderNames.at(i) + "/";  
		}
		path2 += folderNames.back();
		folderNames.pop_back();
		t->left = AddFolder(t->left, path2, folderName);
		t = Balance(t);
	}
	else if (folderName >= t->name) {
		string path2 = "";
		for (int i = 0; i < folderNames.size() - 1; i++) {
			path2 += folderNames.at(i) + "/"; 
		}
		path2 += folderNames.back();
		folderNames.pop_back();
		t->right = AddFolder(t->right, path2, folderName);
		t = Balance(t);
	}
	return t;
}
//Recursive function to add files
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
//Gets the height of the subtree passed
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
//Calculates the height difference of subtrees
int AVL_Tree::Difference(File* t) {
	int lHeight = Height(t->left);
	int rHeight = Height(t->right);
	int difference = lHeight - rHeight;
	return difference;
}
//Performs Right-Right rotation when rebalancing
File* AVL_Tree::RR_Rotate(File* parent) {
	File* t;
	t = parent->right;
	parent->right = t->left;
	t->left = parent;
	return t;
}
//Performs Left-Left rotation when rebalancing
File* AVL_Tree::LL_Rotate(File* parent) {
	File* t;
	t = parent->left;
	parent->left = t->right;
	t->right = parent;
	return t;
}
//Performs Left-Right rotation when rebalancing
File* AVL_Tree::LR_Rotate(File* parent) {
	File* t;
	t = parent->left;
	parent->left = RR_Rotate(t);
	return LL_Rotate(parent);
}
//Performs Right-Left rotation when rebalancing
File* AVL_Tree::RL_Rotate(File* parent) {
	File* t;
	t = parent->right;
	parent->right = LL_Rotate(t);
	return RR_Rotate(parent);
}
//Runs the correct rotation based on height difference of subtrees
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
//Prints the contents of the tree in order 
void AVL_Tree::inorder(File* t) {
	if (t == NULL)
		return;
	inorder(t->left);
	cout << t->name << " " << t->size << " : ";

	inorder(t->right);
}
