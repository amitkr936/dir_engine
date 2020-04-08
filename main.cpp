#include <iostream> //for std input/output
#include <vector> //dynamically allocated list
#include<string> // for string class
#include <queue>

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
    auto *root = new Directory(nullptr, "/");
    //TODO: Main function implementation
    return 0;
}
