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

    string getPath() {
        if (parent == nullptr) return name;
        else {
            return parent->getPath() + name + "/";
        }
    }

    static void list(Directory *dir) {
        if (dir->child_dir) {
            Directory *dirHead = dir->child_dir;
            cout << "Sub-directories" << endl;
            while (dirHead) {
                string dir_name = dirHead->name;
                cout << "\t" << dir_name << endl;
                dirHead = dirHead->next_dir;
            }
        }
        if (dir->child_file) {
            cout << "Files" << endl;
            File *file = (dir->child_file);
            while (file) {
                string file_name = file->name;
                cout << "\t" << file_name << endl;
                file = file->next;
            }
        }
    }

    static void createDirectory(Directory *parent, string directoryName) {
        Directory *head = parent->child_dir;
        if (head == nullptr) {
            parent->child_dir = new Directory(parent, std::move(directoryName));
            return;
        }
        Directory *previous = head;
        head = head->next_dir;
        while (head != nullptr) {
            if (head->name == directoryName) {
                cout << "The directory " << directoryName << " already exists!" << endl;
                return;
            }
            previous = head;
            head = head->next_dir;
        }
        head = new Directory(parent, directoryName);
        previous->next_dir = head;
        head->pre_dir = previous;
    }

    static void deleteDirectory(Directory *dir)//function to delete Directory
    {
        if (dir->child_dir) {
            Directory *dirHead = (dir->child_dir), *temp_dir;
            while (dirHead) {
                temp_dir = dirHead->next_dir;
                deleteDirectory(dirHead);
                dirHead = temp_dir;
            }
        }

        if (dir->child_file) {
            File *file = (dir->child_file), *temp_file;
            while (file) {
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
}

void removeFile(string fileName) {
    File *head = current_dir->child_file;
    if (head != nullptr && head->name == fileName) {
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

void removeDirectory(string directoryName) {
    Directory *head = current_dir->child_dir;
    if (head != nullptr && head->name == directoryName) {
        current_dir->child_dir = head->next_dir;
        Directory::deleteDirectory(head);
        return;
    }
    while (head != nullptr) {
        if (head->name == directoryName) {
            if (head->next_dir != nullptr) {
                head->next_dir->pre_dir = head->pre_dir;
            }
            if (head->pre_dir != nullptr) {
                head->pre_dir->next_dir = head->next_dir;
            }
            Directory::deleteDirectory(head);
            return;
        }
        head = head->next_dir;
    }
    cout << "Directory with name " << directoryName << " not found!" << endl;
}

void createFile(string fileName) {
    File *head = current_dir->child_file;
    if (head == nullptr) {
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
        Directory::createDirectory(current_dir, argument);
        return 1;
    } else if (ch == "rmdir") {
        cin >> argument;
        removeDirectory(argument);
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

        cout << current_dir->getPath() << " >";
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