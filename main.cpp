#include <iostream> //for std input/output
#include <utility>
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
    File *next;
    File *prev;

    File(Directory *parent, string name) {
        this->parent = parent;
        this->name = std::move(name);
        this->next = nullptr;
        this->prev = nullptr;
    }

    static void deleteFile(File *file) {
        file->parent = nullptr;
        file->prev = nullptr;
        file->next = nullptr;

        delete file;
    }

    static File *createFile(Directory *parent, string name) {
        return new File(parent, std::move(name));
    }
};

// Structure of a Directory
class Directory {
public:
    string name;
    Directory *parent;

    //List of child directories and files
    Directory *child_dir;
    Directory *next_dir;
    Directory *pre_dir;

    File **child_file;

    Directory(Directory *parent, string name) {
        this->parent = parent;
        this->name = name;
        cout<<"Created dir with name"<<this->name<<endl;
        this->child_dir = nullptr;
        this->child_file = nullptr;
        this->next_dir = nullptr;
        this->pre_dir = nullptr;
    }

    static void list(Directory *dir)
    {
        //TODO: Print all child dir and files
//        string child_name = ((dir->child_dir))->name;
//        cout<<child_name<<endl;
        if(dir->child_dir)
        {
            Directory* dir = dir->child_dir;
            cout<<"Sub-directories"<<endl;
            while(dir)
            {
                string dir_name = dir->name;
                cout << dir_name << endl;
                dir = dir->next_dir;
            }
        }
        if(dir->child_file)
        {
            cout<<"Files"<<endl;
            File* file = *(dir->child_file);
            while(file)
            {
                string file_name = file->name;
                cout<< file_name << endl;
                dir = dir->next_dir;
            }
        }
    }

    static void createDirectory(Directory *parent, Directory *newDir) {
        //TODO: Insert into linked list
        parent->child_dir = newDir;

        cout<<"Creating dir under "<<parent->name<<" Directory name "<<((parent->child_dir))->name<<endl;
    }

    static void deleteDirectory(Directory *dir)//function to delete Directory
    {
        //TODO:
//        if (dir->child_dir.size() > 0) {
//            for (vector<Directory *>::iterator i = dir->child_dir.begin(); i != dir->child_dir.end(); ++i) {
//                deleteDirectory(*i);
//            }
//        }
//
//        if (dir->child_file.size() > 0) {
//            for (vector<File *>::iterator i = dir->child_file.begin(); i != dir->child_file.end(); ++i) {
//                File::deleteFile(*i);
//            }
//        }
//        dir->parent = nullptr;
//        delete dir;
        if(dir->child_dir)
        {
            deleteDirectory(dir->child_dir);
        }

        if(dir->child_file)
        {
            File* file = *(dir->child_file), *temp_file;
            while (file)
            {
                temp_file = file->next;
                File::deleteFile(file);
                file = temp_file;
            }
        }
        dir->parent = nullptr;
        dir->next_dir = nullptr;
        dir->pre_dir = nullptr;
        delete dir;
    }
};

Directory *root = new Directory(nullptr, "/");
Directory *current_dir = root;

int identifyCommand(string ch) {
    string argument;
    if (ch == "mkdir") {
        cin >> argument;
        auto *newDir = new Directory(current_dir, argument);
        Directory::createDirectory(current_dir, newDir);

        return 1;
    } else if (ch == "ls") {
        cout << "list " << endl;
        Directory::list(current_dir);
        return 1;
    } else if (ch == "cd") {
        cout << "Cd command" << endl;
        cin >> argument;
        return 1;
    } else if (ch == "exit") {
        return 0;
    } else {
        cout << "<Please Enter Valid Command>" << endl;
        return 1;
    }
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"


int main() {

    //Creating root directory with parent as null
    string command;

    while (true) {
        fflush(stdin);

        cout << "Enter the Command >";
        cin >> command;
        cout << command << endl;
        int signal = identifyCommand(command);
        if (signal == 0)//checks if the command is valid or not
        {
            break;
        }
    }
    return 0;
}

#pragma clang diagnostic pop

/** ls
 * cd <path />
 *  cd ..
 *  mkdir <dir-name>
 *  rmdir <dir-name>
 *  rm <file>
 *  mkfile <file-name> / touch <file-name>*/
