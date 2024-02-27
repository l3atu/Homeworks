#include "SpaceSectorLLRBT.h"
#include "stack"

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
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
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison criteria based on the sector coordinates.
}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    deleteTree(root);
    root= nullptr;
    // TODO: Free any dynamically allocated memory in this class.
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    root = insert(root, x, y, z);
    root->color = BLACK;
    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.
}

void SpaceSectorLLRBT::displaySectorsInOrder() {
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

        if (current_sector->color){
            cout <<"RED sector: "<< current_sector->sector_code << endl;
        } else{
            cout <<"BLACK sector: "<< current_sector->sector_code << endl;
        }

        current_sector = current_sector->right;
    }
    cout<<endl;
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
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

        if (current_sector->color){
            cout <<"RED sector: "<< current_sector->sector_code << endl;
        } else{
            cout <<"BLACK sector: "<< current_sector->sector_code << endl;
        }

        if (current_sector->right != nullptr) {
            nodeStack.push(current_sector->right);
        }

        if (current_sector->left != nullptr) {
            nodeStack.push(current_sector->left);
        }
    }
    cout<<endl;
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
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

            if (current_sector->color){
                cout <<"RED sector: "<< current_sector->sector_code << endl;
            } else{
                cout <<"BLACK sector: "<< current_sector->sector_code << endl;
            }

            nodeStack.pop();
            lastVisited = current_sector;
            current_sector = nullptr;
        } else {
            current_sector = current_sector->right;
        }
    }
    cout<<endl;
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    std::vector<Sector*> path2;
    std::vector<Sector*> path3;
    auto *earth=sectorHashMap["0SSS"];
    auto *elara =sectorHashMap[sector_code];

    while (earth!= nullptr){
        path2.push_back(earth);
        earth=earth->parent;
    }
    while (elara!= nullptr){
        path3.push_back(elara);
        elara=elara->parent;
    }

    if (!path2.empty() && !path3.empty()){
        bool control=false;
        for (int i = 0; i < path2.size(); ++i) {
            path.push_back(path2[i]);
            for (int j = 0; j < path3.size(); ++j) {
                if (path2[i]->sector_code==path3[j]->sector_code){
                    control= true;
                    for (int k = j-1; k >= 0; --k) {
                        path.push_back(path3[k]);
                    }
                    break;
                }
            }
            if (control){
                break;
            }
        }
    }

    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
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

Sector* SpaceSectorLLRBT::rotateLeft(Sector* sector){
    Sector* x = sector->right;
    sector->right = x->left;

    if (x->left != nullptr) {
        x->left->parent = sector;
    }

    x->left = sector;
    x->color = sector->color;
    sector->color = RED;

    if (sector->parent != nullptr) {
        if (sector == sector->parent->left) {
            sector->parent->left = x;
        } else {
            sector->parent->right = x;
        }
    }

    x->parent = sector->parent;
    sector->parent = x;

    return x;
}

Sector* SpaceSectorLLRBT::rotateRight(Sector* sector){
    Sector* x = sector->left;
    sector->left = x->right;

    if (x->right != nullptr) {
        x->right->parent = sector;
    }

    x->right = sector;
    x->color = sector->color;
    sector->color = RED;

    if (sector->parent != nullptr) {
        if (sector == sector->parent->left) {
            sector->parent->left = x;
        } else {
            sector->parent->right = x;
        }
    }

    x->parent = sector->parent;
    sector->parent = x;

    return x;

}

bool SpaceSectorLLRBT::isRed(Sector* sector) {
    if (sector == nullptr){
        return false;
    }
    return sector->color;
}

void SpaceSectorLLRBT::flipColors(Sector* sector){
    sector->color = RED;
    sector->left->color = BLACK;
    sector->right->color = BLACK;
}

Sector* SpaceSectorLLRBT::insert(Sector* sector, int x, int y, int z) {
    if (sector == nullptr) {
        auto *new_sector = new Sector(x, y, z);
        sectorHashMap[new_sector->sector_code]=new_sector;
        new_sector->color = RED;
        return new_sector;
    }

    if (x < sector->x) {
        sector->left = insert(sector->left, x, y, z);
        sector->left->parent=sector;
    } else if (x > sector->x) {
        sector->right = insert(sector->right, x, y, z);
        sector->right->parent=sector;
    } else {
        if (y < sector->y) {
            sector->left = insert(sector->left, x, y, z);
            sector->left->parent=sector;
        } else if (y > sector->y) {
            sector->right = insert(sector->right, x, y, z);
            sector->right->parent=sector;
        } else {
            if (z < sector->z) {
                sector->left = insert(sector->left, x, y, z);
                sector->left->parent=sector;
            } else if (z > sector->z) {
                sector->right = insert(sector->right, x, y, z);
                sector->right->parent=sector;
            }
        }
    }

    if (isRed(sector->right) && !isRed(sector->left)) {
        sector = rotateLeft(sector);
    }
    if (isRed(sector->left) && isRed(sector->left->left)) {
        sector = rotateRight(sector);
    }
    if (isRed(sector->left) && isRed(sector->right)) {
        flipColors(sector);
    }

    return sector;
}

void SpaceSectorLLRBT::deleteTree(Sector* current_sector) {
    if (current_sector != nullptr) {
        deleteTree(current_sector->left);
        deleteTree(current_sector->right);

        delete current_sector;
    }
}