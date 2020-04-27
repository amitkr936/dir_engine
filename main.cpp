#include <iostream> //for std input/output
#include <vector> //dynamically allocated list
#include<string> // for string class


using namespace std;

//Declaring classes as these have inter-dependency
class File;

class Directory;

//Class for file
class File {
public:
    string name;
    Directory *parent;

    File(Directory *parent, string name) {
        this->parent = parent;
        this->name = name;
    }
    //TODO: Other properties of file
};

// Structure of a Directory
class Directory {
public:
    string name;
    Directory *parent;

    //List of child directories and files
    vector<Directory *> child_dir;
    vector<File *> child_file;

    Directory(Directory *parent, string name) {
        this->parent = parent;
        this->name = name;
    }
};

// A static Variable which will point to current directory

int main() {
    //Creating root directory with parent as null
    string command;
    auto *root = new Directory(nullptr, "/");
    int choice;
   // <vector> string[] results;
    //TODO: Main function implementation
    do {
        std::cout
                << "Enter your Choice:\n 1:Create A directory \n 2: Create File \n 3:Move to upper Level of the tree \n 4: Move to Lower Level  \n 5:Traverse the tree"
                << std::endl;
        std::cin >> choice;
        //By default create Root Directory must be created
        switch (choice) {
            case 1:
               // createdir();
                //TODO: Create a Directory(Node Arbitrary Children)
                break;
            case 2:
                //TODO: Create a File (Node without a Child)
                break;
            case 3:
                //TODO: Move to Higher level Inside implement the method to traverse the current directory get all the child
                break;
            case 4:
                //TODO: Move to Lower Level Inside implement the method to traverse the current directory get all the child
                break;
            case 5:
                //TODO: Traverse the while tree(In-order traversal)
                break;
            default:
                //TODO: Handle otherwise
                exit(0);
                break;
        }
    } while (true);
   /* while(true)
    {

     cout<<"direngin<$>";
     getline(cin,command);
//     removeDupWord

    }*/


}
/*
void removeDupWord(string str)
{
    string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            cout << word << endl;
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
    cout << word << endl;
}*/