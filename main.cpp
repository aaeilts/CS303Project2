#include "AVL_Tree.h"
using namespace std;

int main() {
	AVL_Tree FileSystem;

	//documents/programming/data_struct/project

	fl = FileSystem.AddFolder(fl, "", "documents");
	//FileSystem.inorder(fl);
	fl = FileSystem.AddFolder(fl, "documents", "programming");
	//FileSystem.inorder(fl);
	fl = FileSystem.AddFolder(fl, "documents/programming", "data_struct");
	//FileSystem.inorder(fl);
	fl = FileSystem.AddFolder(fl, "documents/programming/data_struct", "project");
	fl = FileSystem.AddFile(fl, "documents/programming/data_struct", "assignment", 10);
	FileSystem.inorder(fl);
	
	
	//FileSystem.Show(fl, 2); //Testing??
	







	return 0;
}