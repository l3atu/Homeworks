#include <fstream>
#include <iostream>
#include <sstream>
#include "BlockFall.h"

BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}

void BlockFall::read_blocks(const string &input_file) {

    ifstream file(input_file);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << input_file << std::endl;
        return;
    }

    string line;
    bool isBlockStart = false;
    Block* previous= nullptr;
    Block* current= nullptr;
    vector<vector<bool>> currentBlock;

    while (getline(file, line)) {

        if (line.find('[') != std::string::npos) {
            // New block starts
            currentBlock.clear();
            isBlockStart = true;
        }

        if (isBlockStart) {

            std::vector<bool> row;
            for (char ch : line) {
                if (ch == '0') {
                    row.push_back(false);
                } else if (ch == '1') {
                    row.push_back(true);
                }
            }
            currentBlock.push_back(row);


            if (line.find(']') != std::string::npos) {
                isBlockStart = false;


                Block* newBlock = new Block();
                newBlock->shape = currentBlock;

                if(currentBlock==rotateRight(currentBlock)){
                    newBlock->right_rotation=newBlock;
                    newBlock->left_rotation=newBlock;


                }else if(currentBlock== rotateRight(rotateRight(currentBlock))){
                    Block* rightBlock1= new Block();
                    rightBlock1->shape= rotateRight(currentBlock);
                    newBlock->right_rotation=rightBlock1;
                    rightBlock1->left_rotation=newBlock;
                    rightBlock1->right_rotation=newBlock;
                    newBlock->left_rotation=rightBlock1;


                }else if(currentBlock== rotateRight(rotateRight(rotateRight(rotateRight(currentBlock))))){
                    Block* rightBlock1= new Block();
                    Block* rightBlock2= new Block();
                    Block* rightBlock3= new Block();

                    rightBlock1->shape= rotateRight(currentBlock);
                    rightBlock2->shape= rotateRight(rightBlock1->shape);
                    rightBlock3->shape= rotateRight(rightBlock2->shape);

                    newBlock->right_rotation=rightBlock1;
                    rightBlock1->left_rotation=newBlock;
                    rightBlock1->right_rotation=rightBlock2;
                    rightBlock2->left_rotation=rightBlock1;
                    rightBlock2->right_rotation=rightBlock3;
                    rightBlock3->left_rotation=rightBlock2;
                    rightBlock3->right_rotation=newBlock;
                    newBlock->left_rotation=rightBlock3;
                }

                if (!initial_block) {
                    active_rotation=newBlock;
                    initial_block = newBlock;
                } else {
                    current = initial_block;
                    active_rotation=initial_block;
                    while (current->next_block) {
                        previous=current;
                        current = current->next_block;
                    }
                    if (current->right_rotation==current){
                        current->next_block = newBlock;
                    }
                    if (current->right_rotation->right_rotation==current){
                        current->right_rotation->next_block = newBlock;
                        current->next_block = newBlock;
                    }
                    if (current->right_rotation->right_rotation->right_rotation->right_rotation==current){
                        current->right_rotation->next_block = newBlock;
                        current->right_rotation->right_rotation->next_block = newBlock;
                        current->left_rotation->next_block = newBlock;
                        current->next_block = newBlock;
                    }
                }
            }
        }
    }
    power_up=current->next_block->shape;
    delete current->next_block;
    previous->next_block->next_block= nullptr;

    file.close();
    // TODO: Read the blocks from the input file and initialize "initial_block" and "active_rotation" member variables
    // TODO: For every block, generate its rotations and properly implement the multilevel linked list structure
    //       that represents the game blocks, as explained in the PA instructions.
    // TODO: Initialize the "power_up" member variable as the last block from the input file (do not add it to the linked list!)
}

void BlockFall::initialize_grid(const string &input_file) {
    std::ifstream file(input_file);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << input_file << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int num;
        std::vector<int> tempRow;

        while (iss >> num) {
            tempRow.push_back(num);
        }

        grid.push_back(tempRow);
    }

    rows = grid.size();
    cols = (rows > 0) ? grid[0].size() : 0;

    file.close();

    // TODO: Initialize "rows" and "cols" member variables
    // TODO: Initialize "grid" member variable using the command-line argument 1 in main*/
}


BlockFall::~BlockFall() {
    Block* current = initial_block;
    while (current!= nullptr) {
        if(current->right_rotation->shape!=current->shape){
            if (current->right_rotation->right_rotation->shape!=current->shape){
                Block* next = current->next_block;
                delete current->left_rotation;
                current->left_rotation= nullptr;
                delete current->right_rotation->right_rotation;
                delete current->right_rotation;
                current->right_rotation = nullptr;
                delete current;
                current = next;
            }
            else{
                Block* next = current->next_block;
                delete current->right_rotation;
                current->left_rotation= nullptr;
                current->right_rotation = nullptr;
                delete current;
                current = next;
            }
        }
        else{
            Block* next = current->next_block;
            current->right_rotation = nullptr;
            current->left_rotation = nullptr;
            delete current;
            current = next;
        }

    }


    // TODO: Free dynamically allocated memory used for storing game blocks
}


std::vector<std::vector<bool>> BlockFall::rotateRight( vector<std::vector<bool>> original) {
    std::vector<std::vector<bool>> rotated(original[0].size(), std::vector<bool>(original.size()));

    for (int i = 0; i < original.size(); i++) {
        for (int j = 0; j < original[0].size(); j++) {
            rotated[j][original.size()- 1 - i] = original[i][j];
        }
    }

    return rotated;
}