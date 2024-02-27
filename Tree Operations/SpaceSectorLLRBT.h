#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <unordered_map>

class SpaceSectorLLRBT {
public:
    Sector* root;
    std::unordered_map<std::string, Sector*> sectorHashMap;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    Sector* rotateLeft(Sector* sector);
    Sector* rotateRight(Sector* sector);
    bool isRed(Sector* sector);
    Sector* insert(Sector* node, int x, int y, int z);
    void flipColors(Sector* sector);
    void deleteTree(Sector* current_sector);
};

#endif // SPACESECTORLLRBT_H
