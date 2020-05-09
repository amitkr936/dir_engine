#include <iostream> //for std input/output
#include <vector> //dynamically allocated list
#include<string> // for string class
#include<iterator>


using namespace std;

string CommandSplit[3];

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

    static void deleteFile(File* file)
    {
        file->parent = NULL;
        free(file);
    }
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

    static void deleteDirectory(Directory* dir)//function to delete Directory
    {
        if(dir->child_dir.size() == 0 && dir->child_file.size() == 0)
        {
            dir->parent = NULL;
            free(dir);
            return;
        }

        if(dir->child_dir.size() > 0)
        {
            for(vector<Directory*>::iterator i = dir->child_dir.begin(); i != dir->child_dir.end(); ++i)
            {
                deleteDirectory(*i);
            }
        }

        if(dir->child_file.size() > 0)
        {
            for(vector<File*>::iterator i = dir->child_file.begin(); i != dir->child_file.end(); ++i)
            {
                File::deleteFile(*i);
            }
        }
    }
};
void setCommand(string ch)
{
    cout << ch << endl;
    if(ch == "kdir")
    {
        cout << "Mkdir" << endl;

    }

}


int main() {
    //Creating root directory with parent as null
    string command;
    auto *root = new Directory(nullptr, "/");
    int choice;

    string Array[3];
    /*
     *  do {
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
    } while (true);*/
    while(true)
    {
        static string ch="";
        cout << "Enter the Command ><$:::$" << endl;

        static int i;

        while (cin.get() != '\n') {
            i = 0;
            cin >> ch;
            cout << "Inp 1" << endl;
            cout << ch << endl;
            setCommand(ch);
            i++;

            if (ch.find(' ')) {
                cin >> ch;
                cout << "Inp 2" << endl;
                cout << ch << endl;
                //    Array[i++] = ch;
                break;
            }
        }
    }


    return 0;
}
