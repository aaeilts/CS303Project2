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
	fl = FileSystem.AddFile(fl, "documents/programming/data_struct", "assignment1", 10);
	fl = FileSystem.AddFile(fl, "documents/programming/data_struct", "assignment2", 15);
	//FileSystem.inorder(fl);
	cout << endl;

	wanted = FileSystem.GetFile(fl, "documents/programming/data_struct", "assignment1");
	//cout << wanted.name << endl;
	FileSystem.DeleteFile(fl, "documents/programming/data_struct", "assignment2");
	files = FileSystem.GetFiles(files, fl, "documents /programming/data_struct", "assi");
	for (auto v : files) {							//These two lines are just for printing
		std::cout << v.name << "\n";				//out the list of files
	}
	
	







	return 0;
}