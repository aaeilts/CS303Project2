#include "AVL_Tree.h"
using namespace std;

int main() {
	AVL_Tree FileSystem;
	File wanted;
	list<File> files;

	//documents/programming/data_struct/project

	fl = FileSystem.AddFolder(fl, "", "documents");
	fl = FileSystem.AddFolder(fl, "documents", "programming");
	fl = FileSystem.AddFolder(fl, "documents/programming", "data_struct");
	fl = FileSystem.AddFolder(fl, "documents/programming/data_struct", "project");
	fl = FileSystem.AddFile(fl, "documents/programming/data_struct", "assignment", 10);
	//FileSystem.inorder(fl);
	cout << endl;
	wanted = FileSystem.GetFile(fl, "documents / programming / data_struct", "assignment");
	//cout << wanted.name << endl;
	files = FileSystem.GetFiles(files, fl, "documents / programming / data_struct", "d");
	for (auto v : files)
		std::cout << v.name << "\n";
	
	//FileSystem.Show(fl, 2); //Testing??
	







	return 0;
}