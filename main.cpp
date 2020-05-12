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

    File *child_file;

    Directory(Directory *parent, string name) {
        this->parent = parent;
        this->name = std::move(name);
        this->child_dir = nullptr;
        this->child_file = nullptr;
        this->next_dir = nullptr;
        this->pre_dir = nullptr;
    }

    static void list(Directory *dir) {
        //TODO: Print all child dir and files
        string child_name = ((dir->child_dir))->name;
        cout << child_name << endl;
    }

    static void createDirectory(Directory *parent, Directory *newDir) {
        //TODO: Insert into linked list
        parent->child_dir = newDir;

        cout << "Creating dir under " << parent->name << " Directory name " << ((parent->child_dir))->name << endl;
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
    }
};

Directory *root = new Directory(nullptr, "/");
Directory *current_dir = root;

void changeDirectory(string target) {
    if (target == "..") {
        if (current_dir->name != "/") {
            current_dir = current_dir->parent;
        }
    } else {
        Directory *head = current_dir->child_dir;
        while (head != nullptr) {
            if (head->name == target) {
                current_dir = head;
                return;
            }
            head = head->next_dir;
        }
        cout << "Could not find the directory with name " << target << endl;
    }

void removeFile(string fileName) {
    File *head = current_dir->child_file;
    if(head != nullptr && head->name == fileName){
        current_dir->child_file = head->next;
        File::deleteFile(head);
        return;
    }
    while (head != nullptr) {
        if (head->name == fileName) {
            if (head->next != nullptr) {
                head->next->prev = head->prev;
            }
            if (head->prev != nullptr) {
                head->prev->next = head->next;
            }
            File::deleteFile(head);
            return;
        }
        head = head->next;
    }
    cout << "File with name " << fileName << " not found!" << endl;
}

void createFile(string fileName) {
    File *head = current_dir->child_file;
    if(head == nullptr){
        current_dir->child_file = File::createFile(current_dir, fileName);
        return;
    }
    File *previous = head;
    head = head->next;
    while (head != nullptr) {
        if (head->name == fileName) {
            cout << "The file " << fileName << " already exists!" << endl;
            return;
        }
        previous = head;
        head = head->next;
    }
    head = File::createFile(current_dir, fileName);
    previous->next = head;
    head->prev = previous;

}

int identifyCommand(string ch) {
    string argument;
    if (ch == "mkdir") {
        cin >> argument;
        auto *newDir = new Directory(current_dir, argument);
        Directory::createDirectory(current_dir, newDir);
        return 1;
    } else if (ch == "ls") {
        Directory::list(current_dir);
        return 1;
    } else if (ch == "cd") {
        cin >> argument;
        changeDirectory(argument);
        return 1;
    } else if (ch == "mkfile") {
        cin >> argument;
        createFile(argument);
    } else if (ch == "rm") {
        cin >> argument;
        removeFile(argument);
    } else if (ch == "exit") {
        return 0;
    } else {
        cout << "Invalid command " << ch << "!" << endl;
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
