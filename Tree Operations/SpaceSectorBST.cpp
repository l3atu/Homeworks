#include "SpaceSectorBST.h"
#include "stack"

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    deleteTree(root);
    root= nullptr;
    // Free any dynamically allocated memory in this class.
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string firstLine;
    std::getline(file,firstLine);
    std::string line;
    while (std::getline(file,line)){
        std::stringstream iss(line);
        std::string coordinates;
        int x,y,z ;
        char comma;
        if(iss>>x>>comma>>y>>comma>>z){
            insertSectorByCoordinates(x,y,z);
        } else{
            cout<<"Error"<<endl;
        }

    }
    cout << endl;
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    auto *new_sector = new Sector(x, y, z);
    sectorHashMap[new_sector->sector_code] = new_sector;

    if (root == nullptr) {
        root = new_sector;
        return;
    }

    Sector* parent = nullptr;
    Sector* current = root;

    while (current != nullptr) {
        parent = current;

        if (x < current->x || (x == current->x && y < current->y) || (x == current->x && y == current->y && z < current->z)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    new_sector->parent = parent;
    if (x < parent->x || (x == parent->x && y < parent->y) || (x == parent->x && y == parent->y && z < parent->z)) {
        parent->left = new_sector;
    } else {
        parent->right = new_sector;
    }
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    auto iterator = sectorHashMap.find(sector_code);
    if (iterator == sectorHashMap.end()) {
        std::cout << "Error" << std::endl;
        return;
    }

    Sector* current_sector = iterator->second;
    Sector* replace_sector = nullptr;


    if (current_sector->right == nullptr && current_sector->left == nullptr) {
        if (current_sector->parent == nullptr) {
            delete current_sector;
            root = nullptr;

        } else {
            if (current_sector->parent->left == current_sector) {
                current_sector->parent->left = nullptr;

            } else {
                current_sector->parent->right = nullptr;
            }
            delete current_sector;
        }
    } else if (current_sector->right == nullptr && current_sector->left != nullptr) {
        replace_sector = current_sector->left;
        replace_sector->parent = current_sector->parent;

        if (current_sector->parent != nullptr) {
            if (current_sector->parent->left == current_sector) {
                current_sector->parent->left = replace_sector;
            } else {
                current_sector->parent->right = replace_sector;
            }
        } else {
            root = replace_sector;
        }
        delete current_sector;

    } else if (current_sector->right != nullptr && current_sector->left == nullptr) {
        replace_sector = current_sector->right;
        replace_sector->parent = current_sector->parent;

        if (current_sector->parent != nullptr) {
            if (current_sector->parent->left == current_sector) {
                current_sector->parent->left = replace_sector;
            } else {
                current_sector->parent->right = replace_sector;
            }
        } else {
            root = replace_sector;
        }
        delete current_sector;
    } else {
        replace_sector = current_sector->right;
        while (replace_sector->left != nullptr) {
            replace_sector = replace_sector->left;
        }

        current_sector->x = replace_sector->x;
        current_sector->y = replace_sector->y;
        current_sector->z = replace_sector->z;
        current_sector->distance_from_earth = replace_sector->distance_from_earth;
        current_sector->sector_code = replace_sector->sector_code;

        if (replace_sector->parent != current_sector) {
            if (replace_sector->right != nullptr) {
                replace_sector->parent->left=replace_sector->right;
                replace_sector->right->parent = replace_sector->parent;
            } else{
                replace_sector->parent->left= nullptr;
            }
        } else {
            if (replace_sector->right != nullptr) {
                replace_sector->parent->right=replace_sector->right;
                replace_sector->right->parent = replace_sector->parent;
            } else{
                replace_sector->parent->right= nullptr;
            }
        }

        sectorHashMap[current_sector->sector_code] = current_sector;
        delete replace_sector;
    }
}

void SpaceSectorBST::displaySectorsInOrder() {
    cout<<"Space sectors inorder traversal:"<<endl;
    stack<Sector*> nodeStack;
    Sector* current_sector = root;

    while (current_sector != nullptr || !nodeStack.empty()) {
        while (current_sector != nullptr) {
            nodeStack.push(current_sector);
            current_sector = current_sector->left;
        }

        current_sector = nodeStack.top();
        nodeStack.pop();

        cout << current_sector->sector_code << endl;

        current_sector = current_sector->right;
    }
    cout<<endl;
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPreOrder() {
    cout<<"Space sectors preorder traversal:"<<endl;
    if (root == nullptr) {
        cout<<endl;
        return;
    }
    stack<Sector*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Sector* current_sector = nodeStack.top();
        nodeStack.pop();

        cout << current_sector->sector_code << endl;

        if (current_sector->right != nullptr) {
            nodeStack.push(current_sector->right);
        }

        if (current_sector->left != nullptr) {
            nodeStack.push(current_sector->left);
        }
    }
    cout<<endl;
    // TODO: Traverse the space sector BST map in pre-order traversal and print
    // the sectors to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPostOrder() {
    cout << "Space sectors postorder traversal:" << endl;

    stack<Sector*> nodeStack;
    Sector* current_sector = root;
    Sector* lastVisited = nullptr;

    while (current_sector != nullptr || !nodeStack.empty()) {
        while (current_sector != nullptr) {
            nodeStack.push(current_sector);
            current_sector = current_sector->left;
        }

        current_sector = nodeStack.top();

        if (current_sector->right == nullptr || current_sector->right == lastVisited) {
            cout << current_sector->sector_code << endl;
            nodeStack.pop();
            lastVisited = current_sector;
            current_sector = nullptr;
        } else {
            current_sector = current_sector->right;
        }
    }
    cout<<endl;
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    std::stack<Sector*> nodeStack;
    Sector* current_sector = root;

    while (current_sector != nullptr || !nodeStack.empty()) {
        while (current_sector != nullptr) {
            nodeStack.push(current_sector);
            current_sector = current_sector->left;
        }

        current_sector = nodeStack.top();
        nodeStack.pop();
        if (current_sector->sector_code==sector_code){
            path.push_back(current_sector);
            while (current_sector->parent!= nullptr){
                current_sector = current_sector->parent;
                path.push_back(current_sector);
            }
            break;
        }

        current_sector = current_sector->right;
    }
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    std::reverse(path.begin(), path.end());

    return path;
}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    if (path.size()>0){
        cout<<"The stellar path to Dr. Elara: ";
        for (int i = 0; i < path.size() ; ++i) {
            if (i!=path.size()-1){
                cout<<path[i]->sector_code<<"->";
            } else{
                cout<<path[i]->sector_code;
            }

        }
        cout<<endl;
    } else{
        cout<<"A path to Dr. Elara could not be found."<<endl;
    }

    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
}

void SpaceSectorBST::deleteTree(Sector* current_sector) {
    if (current_sector != nullptr) {
        deleteTree(current_sector->left);
        deleteTree(current_sector->right);

        delete current_sector;
    }
}