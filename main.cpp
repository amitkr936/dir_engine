#include <iostream>
//#include <stdc++.h>
#include <vector>
#include<string> // for string class
#include <queue>
using namespace std;
class Files // Single connection to the parent directory, Structure for a File
{
public:
    string name;
    //Node * child;
};
// Structure of a Directory
class Directory
{
public:
    string  key;
    //point to previeous node
    std::vector<Directory *>child_dir;
    std::vector<Files *>child_file;
};


// Generating new Directories
Directory newDir(string key)
{
    Directory *temp = new Directory;
    temp->key = key;
    return temp;
}
Files *newFile(string name)//Creating new Files
{
    Files *temp = new Files;
    temp->name = name;
    return temp;
}

Directory create_dir()
{
    string value;
    std::cout<<"Enter the Directory Value"<<std::endl;
    std::cin>>value;
    Directory &tem = (Directory &) newDir(value);
}
// A static Variable which will point to current directory

int main() {
    Directory dir;
    int choice;
    std::cout << "DD       IIIIIIIII          RRRRRR" << std::endl;
    std::cout << "DD D         II             RR    RRRR" << std::endl;
    std::cout << "DD  DD       II             RR    RRR      EEEEE   NNNN   NN    GGGGGG    IIIIII " << std::endl;
    std::cout << "DD   DDD     II             RRRRRRR        EE      NN NN  NN    GG          II"<< std::endl;
    std::cout << "DD  DDD      II             RR    RR       EEEEE   NN  NN NN    GG  GGGG    II                "<< std::endl;
    std::cout << "DD DD        II             RR      RR     EE      NN   NNNN    GG  GGGG    II               "<< std::endl;
    std::cout << "DD       IIIIIIIII          RR        RR   EEEEE   NN    NN     GGGGGGGG  IIIIII  NE  ___" << std::endl;
    std::cout <<"<<--::-->>Welcome to the DirEngine Console<<--::-->>"<< std::endl;
    do{
        std::cout<<"Enter your Choice:\n 1:Create A directory \n 2: Create File \n 3:Move to upper Level of the tree \n 4: Move to Lower Level  \n 5:Traverse the tree"<<std::endl;
        std::cin>>choice;
        //By default create Root Directory must be created
        switch(choice)
        {
            case 1:
                dir = create_dir();
                //Create a Directory(Node Arbitrary Children)
                break;
            case 2:
                //Create a File (Node without a Child)
                break;
            case 3://Move to Higher level Inside implement the method to traverse the current directory get all the child
                break;
            case 4:// Move to Lower Level Inside implement the method to traverse the current directory get all the child
                break;
            case 5:// traverse the while tree(In-order traversal)
                break;
            default:
                break;
        }
    }while(0);
    return 0;
}
