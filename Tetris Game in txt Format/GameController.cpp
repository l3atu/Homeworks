#include <fstream>
#include <sstream>
#include <iostream>
#include "GameController.h"

bool GameController::play(BlockFall& game, const string& commands_file){
    ifstream infile(commands_file);
    Block* currentBlock = game.initial_block;
    time_t lastPlayed = time(nullptr);
    string line;
    int right=0;
    while (getline(infile, line)) {


        istringstream iss(line);
        string command;
        iss >> command;



        if (command == "PRINT_GRID") {
            for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                    if (game.active_rotation->shape[i][j]) {
                        game.grid[i][j+right] = 1;
                    }
                }
            }


            cout << "Score: " << game.current_score <<endl;
            cout << "High Score: "<<game.leaderboard.head_leaderboard_entry->score<< endl;



            for (int i = 0; i < game.rows; i++) {
                for (int j = 0; j < game.cols; j++) {
                    if (game.grid[i][j] == 0) {
                        cout << unoccupiedCellChar;
                    } else {
                        cout << occupiedCellChar;
                    }
                }
                cout << "\n";
            }
            cout << "\n\n";

        } else if (command == "DROP") {
            for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                    if (game.active_rotation->shape[i][j]) {
                        game.grid[0 + i][right+ j] = 0;
                    }
                }
            }

            int filledCells=0;
            int distance=game.grid.size();
            if(!game.gravity_mode_on){
                for (int j = 0; j < game.active_rotation->shape[0].size(); ++j) {
                    for (int i = game.active_rotation->shape.size()-1; i >=0 ; --i) {
                        if(!game.active_rotation->shape[i][j]){
                            continue;
                        }
                        for (int k = i+1; k < game.grid.size(); ++k) {
                            if (game.grid[k][j+right]==1){
                                if (distance>k-(i+1)){
                                    distance=k-(i+1);
                                }
                            } else if(game.grid[k][j+right]==0 && k==game.grid.size()-1){
                                if (distance>k-(i)){
                                    distance=k-(i);
                                }
                            }
                        }
                    }
                }
                for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                    for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                        if (game.active_rotation->shape[i][j]) {
                            game.grid[distance+ i][ j+right] = 1;
                            filledCells++;
                        }
                    }
                }
            }
            else{
                for (int j = 0; j < game.active_rotation->shape[0].size(); ++j) {
                    for (int i = game.active_rotation->shape.size()-1; i >=0 ; --i) {
                        if(!game.active_rotation->shape[i][j]){
                            continue;
                        }
                        for (int k = i+1; k < game.grid.size(); ++k) {
                            if (game.grid[k][j+right]==1){
                                if (distance>k-(i+1)){
                                    distance=k-(i+1);
                                }
                            } else if(game.grid[k][j+right]==0 && k==game.grid.size()-1){
                                if (distance>k-(i)){
                                    distance=k-(i);
                                }
                            }
                        }
                    }
                }
                for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                    for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                        if (game.active_rotation->shape[i][j]) {
                            game.grid[distance+ i][ j+right] = 1;
                            filledCells++;
                        }
                    }
                }

                for (int j = 0; j <game.grid[0].size(); ++j) {
                    int numberOfOne=0;
                    for (int i = 0; i < game.grid.size(); ++i) {
                        if (game.grid[i][j]==1){
                            numberOfOne++;
                            game.grid[i][j]=0;
                        }
                    }
                    for (int k = game.grid.size()-1; k >=game.grid.size()-numberOfOne ; --k) {
                        game.grid[k][j]=1;
                    }
                }
            }

            if (checkPowerUp(game)){
                cout << "Before clearing:" << endl;
                for (int a = 0; a < game.rows; a++) {
                    for (int b = 0; b < game.cols; b++) {
                        if (game.grid[a][b] == 0) {
                            cout << unoccupiedCellChar;
                        } else {
                            cout << occupiedCellChar;
                        }
                    }
                    cout << "\n";
                }
                cout << "\n\n";

                int clearedCells=0;

                for (int i = 0; i < game.grid.size(); ++i) {
                    for (int j = 0; j < game.grid[0].size() ; ++j) {
                        if (game.grid[i][j]==1){
                           clearedCells++;
                           game.grid[i][j]=0;
                        }
                    }
                }
                game.current_score+=1000;
                game.current_score+=clearedCells;
            }

            int clearedRows = 0;
            bool beforeClearing= false;

            for (size_t i = 0; i < game.grid.size(); ++i) {
                bool checkRow=true;
                for (int j = 0; j < game.grid[0].size() ; ++j) {
                    if(game.grid[i][j]==0){
                        checkRow= false;
                        break;
                    }
                }
                if(checkRow){
                    if(!beforeClearing) {
                        beforeClearing= true;

                        cout << "Before clearing:" << endl;
                        for (int a = 0; a < game.rows; a++) {
                            for (int b = 0; b < game.cols; b++) {
                                if (game.grid[a][b] == 0) {
                                    cout << unoccupiedCellChar;
                                } else {
                                    cout << occupiedCellChar;
                                }
                            }
                            cout << "\n";
                        }
                        cout << "\n\n";
                    }
                    game.grid.erase(game.grid.begin() + i);
                    game.grid.insert(game.grid.begin(), vector<int>(game.grid[0].size(), 0));
                    clearedRows++;

                }
            }

            game.current_score+=clearedRows*game.grid[0].size();
            game.current_score+=filledCells*distance;

            right=0;

            if (currentBlock->next_block!= nullptr){
                currentBlock=currentBlock->next_block;
                game.active_rotation=currentBlock;
            }else{
                LeaderboardEntry* new_entry=new LeaderboardEntry(game.current_score,lastPlayed,game.player_name);
                game.leaderboard.insert_new_entry(new_entry);
                cout<<"YOU WIN!"<<endl;
                cout<<"No more blocks."<<endl;
                cout<<"Final grid and score:\n"<<endl;
                cout << "Score: " << game.current_score <<endl;
                cout << "High Score: "<<game.leaderboard.head_leaderboard_entry->score <<endl;

                for (int i = 0; i < game.rows; i++) {
                    for (int j = 0; j < game.cols; j++) {
                        if (game.grid[i][j] == 0) {
                            cout << unoccupiedCellChar;
                        } else {
                            cout << occupiedCellChar;
                        }
                    }
                    cout << "\n";
                }
                cout<<"\n"<<endl;
                game.leaderboard.print_leaderboard();
                game.leaderboard.write_to_file(game.leaderboard_file_name);
                return true;
            }
            for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                    if (game.active_rotation->shape[i][j]) {
                        if(game.grid[i][j]==1){
                            LeaderboardEntry* new_entry=new LeaderboardEntry(game.current_score,lastPlayed,game.player_name);
                            game.leaderboard.insert_new_entry(new_entry);
                            cout<<"GAME OVER!"<<endl;
                            cout<<"Next block that couldn't fit:"<<endl;
                            for (size_t x = 0; x < game.active_rotation->shape.size(); ++x) {
                                for (size_t y = 0; y < game.active_rotation->shape[x].size(); ++y) {
                                    if (game.active_rotation->shape[x][y]){
                                        cout << occupiedCellChar;
                                    }
                                }
                            }
                            cout<<"\n\n";
                            cout<<"Final grid and score:\n"<<endl;
                            cout << "Score: " << game.current_score <<endl;
                            cout << "High Score: "<<game.leaderboard.head_leaderboard_entry->score <<endl;

                            for (int a = 0; a < game.rows; a++) {
                                for (int b = 0; b < game.cols; b++) {
                                    if (game.grid[a][b] == 0) {
                                        cout << unoccupiedCellChar;
                                    } else {
                                        cout << occupiedCellChar;
                                    }
                                }
                                cout << "\n";
                            }
                            cout<<"\n"<<endl;
                            game.leaderboard.print_leaderboard();
                            game.leaderboard.write_to_file(game.leaderboard_file_name);

                            return false;
                        }
                    }
                }
            }
        } else if (command == "ROTATE_RIGHT") {
            for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                    if (game.active_rotation->shape[i][j]) {
                        game.grid[i][right + j] = 0;
                    }
                }
            }
            game.active_rotation=game.active_rotation->right_rotation;

            int distance=game.grid[0].size();

            for (int i = 0; i <game.active_rotation->shape.size() ; ++i) {
                for ( int j = game.active_rotation->shape[0].size()-1; j >=0 ; --j) {
                    if(!game.active_rotation->shape[i][j]){
                        continue;
                    }
                    for (int k = j+1; k < game.grid[0].size(); ++k) {
                        if (game.grid[i][k]==1){
                            if (distance>k-(j+1)){
                                distance=k-(j+1);
                            }
                        } else if(game.grid[i][k]==0 && k==game.grid[0].size()-1){
                            if (distance>k-(j)){
                                distance=k-(j);
                            }
                        }
                    }
                }
            }
            if(right>distance){
                game.active_rotation=game.active_rotation->left_rotation;
            }
            else {
                game.active_rotation = game.active_rotation;
            }

        } else if (command == "ROTATE_LEFT") {
            for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                    if (game.active_rotation->shape[i][j]) {
                        game.grid[0 + i][right+ j] = 0;
                    }
                }
            }
            game.active_rotation=game.active_rotation->left_rotation;

            int distance=game.grid[0].size();

            for (int i = 0; i <game.active_rotation->shape.size() ; ++i) {
                for ( int j = game.active_rotation->shape[0].size()-1; j >=0 ; --j) {
                    if(!game.active_rotation->shape[i][j]){
                        continue;
                    }
                    for (int k = j+1; k < game.grid[0].size(); ++k) {
                        if (game.grid[i][k]==1){
                            if (distance>k-(j+1)){
                                distance=k-(j+1);
                            }
                        } else if(game.grid[i][k]==0 && k==game.grid[0].size()-1){
                            if (distance>k-(j)){
                                distance=k-(j);
                            }
                        }
                    }
                }
            }
            if(right>distance){
                game.active_rotation=game.active_rotation->right_rotation;
            } else{
                game.active_rotation=game.active_rotation;
            }

        } else if (command == "MOVE_RIGHT") {
            for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                    if (game.active_rotation->shape[i][j]) {
                        game.grid[i][right+j] = 0;
                    }
                }
            }

            right++;
            int distance=game.grid[0].size();

            for (int i = 0; i <game.active_rotation->shape.size() ; ++i) {
                for ( int j = game.active_rotation->shape[0].size()-1; j >=0 ; --j) {
                    if(!game.active_rotation->shape[i][j]){
                        continue;
                    }
                    for (int k = j+1; k < game.grid[0].size(); ++k) {
                        if (game.grid[i][k]==1){
                            if (distance>k-(j+1)){
                                distance=k-(j+1);
                            }
                        }
                        else if(game.grid[i][k]==0 && k==game.grid[0].size()-1){
                            if (distance>k-(j)){
                                distance=k-(j);
                            }
                        }
                    }
                }
            }

            if (distance<=right){
                right=distance;
                for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                    for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                        if (game.active_rotation->shape[i][j]) {
                            game.grid[i][distance+j] = 1;
                        }
                    }
                }
            }
            else {
                for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                    for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                        if (game.active_rotation->shape[i][j]) {
                            game.grid[ i][right+j] = 1;
                        }
                    }
                }
            }




        } else if (command == "MOVE_LEFT") {

            for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                    if (game.active_rotation->shape[i][j]) {
                        game.grid[i][right+j] = 0;
                    }
                }
            }
            right--;
            int distance=game.grid[0].size();

            for (int i = 0; i <game.active_rotation->shape.size() ; ++i) {
                for ( int j = game.active_rotation->shape[0].size()-1; j >=0 ; --j) {
                    if(!game.active_rotation->shape[i][j]){
                        break;
                    }
                    for (int k = right+j; k >=0; --k) {
                         if(k==0){
                            if (distance>right+1+j){
                                distance=right+1+j;
                            }
                        }
                    }
                }
            }

            if (distance>right && right>0){
                for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                    for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                        if (game.active_rotation->shape[i][j]) {
                            game.grid[ i][right+j] = 1;
                        }
                    }
                }
            }

            else if (right<0){
                right=0;
            }


        }else if (command == "GRAVITY_SWITCH"){
            if(!game.gravity_mode_on){
                for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                    for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                        if (game.active_rotation->shape[i][j]) {
                            game.grid[0 + i][right+ j] = 0;
                        }
                    }
                }
                game.gravity_mode_on=true;

                for (int j = 0; j <game.grid[0].size(); ++j) {
                    int numberOfone=0;
                    for (int i =0; i < game.grid.size(); ++i) {
                         if (game.grid[i][j]==1){
                            numberOfone++;
                            game.grid[i][j]=0;
                        }
                    }
                    for (int k = game.grid.size()-1; k >=game.grid.size()-numberOfone ; --k) {
                        game.grid[k][j]=1;
                    }
                }


                int clearedRows = 0;
                for (size_t i = 0; i < game.grid.size(); ++i) {
                    bool checkRow=true;
                    for (int j = 0; j < game.grid[0].size() ; ++j) {
                        if(game.grid[i][j]==0){
                            checkRow= false;
                            break;
                        }
                    }
                    if(checkRow){
                        game.grid.erase(game.grid.begin() + i);
                        game.grid.insert(game.grid.begin(), vector<int>(game.grid[0].size(), 0));
                        clearedRows++;
                        i--;
                    }
                }
                game.current_score+=clearedRows*game.grid[0].size();

                for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
                    for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
                        if (game.active_rotation->shape[i][j]) {
                            game.grid[0 + i][right+ j] = 1;
                        }
                    }
                }

            } else{
                game.gravity_mode_on=false;
            }
        }

        // TODO: Implement the gameplay here while reading the commands from the input file given as the 3rd command-line
        //       argument. The return value represents if the gameplay was successful or not: false if game over,
        //       true otherwise.
    }
    for (size_t i = 0; i < game.active_rotation->shape.size(); ++i) {
        for (size_t j = 0; j < game.active_rotation->shape[i].size(); ++j) {
            if (game.active_rotation->shape[i][j]) {
                game.grid[0 + i][right+ j] = 0;
            }
        }
    }
    LeaderboardEntry* new_entry=new LeaderboardEntry(game.current_score,lastPlayed,game.player_name);
    game.leaderboard.insert_new_entry(new_entry);
    cout<<"GAME FINISHED!"<<endl;
    cout<<"No more commands."<<endl;
    cout<<"Final grid and score:\n"<<endl;
    cout << "Score: " << game.current_score <<endl;
    cout << "High Score: "<<game.leaderboard.head_leaderboard_entry->score << endl;

    for (int i = 0; i < game.rows; i++) {
        for (int j = 0; j < game.cols; j++) {
            if (game.grid[i][j] == 0) {
                cout << unoccupiedCellChar;
            } else {
                cout << occupiedCellChar;
            }
        }
        cout << "\n";
    }
    cout<<"\n"<<endl;
    game.leaderboard.print_leaderboard();
    game.leaderboard.write_to_file(game.leaderboard_file_name);


    return true;
}

bool GameController::checkPowerUp(BlockFall& game){

    for (int k = 0; k < (game.grid.size()-game.power_up.size())+1; ++k) {
        bool check=true;
        for (int l = 0; l < (game.grid[0].size()-game.power_up[0].size())+1; ++l) {
            check=true;
            for (int i = 0; i < game.power_up.size(); ++i) {
                for (int j = 0; j < game.power_up[0].size(); ++j) {
                    if (game.grid[i+k][j+l]!=game.power_up[i][j]){
                        check=false;
                    }

                }
            }
            if(check){
                break;
            }
        }
        if(check){
            return true;
        }
    }
    return false;

}



