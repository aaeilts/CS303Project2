#include "AVL_Tree.h"
using namespace std;

int main() {
	AVL_Tree FileSystem;
	File wanted;
	list<File> files;

	//documents/programming/data_struct/project/assignment1

	fl = FileSystem.AddFolder(fl, "", "documents");
	fl = FileSystem.AddFolder(fl, "documents", "programming");
	fl = FileSystem.AddFolder(fl, "documents/programming", "data_struct");
	fl = FileSystem.AddFolder(fl, "documents/programming/data_struct", "project");
	fl = FileSystem.AddFile(fl, "documents/programming/data_struct/project", "assignment1", 10);
	fl = FileSystem.AddFile(fl, "documents/programming/data_struct/project", "assignment2", 15);
	//FileSystem.inorder(fl); //shows that the tree is built and balanced
	cout << endl;

	wanted = FileSystem.GetFile(fl, "documents/programming/data_struct", "assignment1");
	cout << "Filename: " << wanted.name << endl <<"Filesize: " << wanted.size << endl;  //shows that the search requiremnet works

	FileSystem.DeleteFile(fl, "documents/programming/data_struct", "assignment2");
	files = FileSystem.GetFiles(files, fl, "documents /programming/data_struct", "assi");
	for (auto v : files) {							//These two lines are just for printing
		cout << v.name << "\n";						//out the list of files
	}
	
	
	







	return 0;
}