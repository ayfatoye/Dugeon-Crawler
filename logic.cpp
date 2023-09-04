#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    ifstream inFS;
    char tempVar;

    bool exitAvailable = false; // to check if there's no exit characters in the file
    
    
    inFS.open(fileName);

    if(!inFS.is_open()){
        return nullptr;
    }

    // fail tests
    inFS >> maxRow;
    if(inFS.fail() || (maxRow <= 0)){ // number three
        return nullptr;
    }
    inFS >> maxCol;
    if(inFS.fail() || (maxCol <= 0)){
        return nullptr;
    }
    if(maxRow > (INT32_MAX/maxCol)){
        return nullptr;
    }
    inFS >> player.row;
    if(inFS.fail() || (player.row < 0) || (player.row >= maxRow)){
        return nullptr;
    }
    inFS>> player.col;
    if(inFS.fail() || (player.col < 0) || (player.col >= maxCol)){
        return nullptr;
    }

    // checking that player.row and player.col make sense (number two)

    char** map = createMap(maxRow, maxCol);

    for(int i = 0; i < maxRow; i++){

        for(int j = 0; j < maxCol; j++){
            inFS >> map[i][j];

            if((map[i][j] == '?') || (map[i][j] == '!')){
                exitAvailable = true;
            }
            // checking for invalid characters (number one)
            if( (inFS.fail()) || ( (map[i][j] != TILE_OPEN) && (map[i][j] != TILE_TREASURE) && (map[i][j] != TILE_AMULET) && (map[i][j] != TILE_MONSTER) && (map[i][j] != TILE_PILLAR) && (map[i][j] != TILE_DOOR) && (map[i][j] != TILE_EXIT)) ){
                deleteMap(map, maxRow); // cause you're returning nullptr after creating a map
                return nullptr;
            }
            else if(map[i][j] == TILE_PLAYER){ // the ap shouldn't originally have a player
                map[i][j] = TILE_OPEN;
            }
        }
    }
    // checking that they have just the right amount of characters
    char temp;
    inFS >> temp;
    if(!inFS.eof()){
        deleteMap(map, maxRow);
        return nullptr;
    }
    map[player.row][player.col] = TILE_PLAYER;

    if(!exitAvailable){
        deleteMap(map, maxRow);
        return nullptr;
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {

    if(input == MOVE_UP){
        nextRow--; 
    }
    else if(input == MOVE_DOWN) {
        nextRow++;
    }
    else if(input == MOVE_LEFT) {
        nextCol--;
    }
    else if(input == MOVE_RIGHT) {
        nextCol++;
    }
    
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    
    if((maxRow < 0) || (maxCol < 0)){
        return nullptr;
    }
    char** map = new char* [maxRow]{};

    for(int y = 0; y < maxRow; y++){
        map[y] = new char[maxCol]{};

        for(int x = 0; x < maxCol; x++){
            map[y][x] = TILE_OPEN;
        }
    }



    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {

    if(map == nullptr) {
        maxRow = 0;
        return;
        }

    for(int y = 0; y < maxRow; y++){

        

        delete [] map[y]; // going through map and deallocating it's individual elements that are also arrays themselves.
                          // remember that making map a dynamically allocated array, makes it's individual elements dynamically allocated, so we
                          // have to deallocate them individually and then deallocate map itself.
    }

    delete [] map;

    map = nullptr;
    maxRow = 0;

    
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {

    if(maxRow < 1 || maxCol < 1){
        return nullptr;
    }
    if(map == nullptr){
        return nullptr;
    }

    maxRow *= 2; // maybe just use maxRow*2 in making map2 instead of updating it like this :)
    maxCol *= 2;
    //cout << maxCol << endl;
        

    char** map2 = createMap((maxRow), (maxCol));
    //char temp;
    for(int i = 0; i < maxRow/2; i++){
        for(int j = 0; j < maxCol/2; j++){
            // cout << i << " " << j << endl;
            //temp = map[i][j];
            map2[i][j] = map[i][j];
            
            map2[i + maxRow/2][j] = map[i][j];
            map2[i][j + maxCol/2] = map[i][j];
            map2[i + maxRow/2][j + maxCol/2] = map[i][j];
        }
    }

    int maxRow2 = maxRow/2;

    deleteMap(map, maxRow2);

    for(int i = 0; i < maxRow; i++){

        for(int j = 0; j < maxCol; j++){

            if((map2[i][j] == TILE_PLAYER) && ((i >= maxRow/2) || (j >= maxCol/2))){
                map2[i][j] = TILE_OPEN;
            }
        }
    }

    
    return map2;
    //return nullptr;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {

    // checking if the next row and col is out of bounds 
    if((nextRow >= maxRow) || (nextCol >= maxCol) || (nextCol < 0) || (nextRow < 0)){ // prompt 3a. i. 1
        nextRow = player.row;
        nextCol = player.col;
        return STATUS_STAY;

    }
    else if((nextRow == player.row) && (nextCol == player.col)){ // prompt 3a. i. 1
        return STATUS_STAY;
    }

    else if((map[nextRow][nextCol] == '+') || (map[nextRow][nextCol] == 'M')){ // prompt 3a. i. 1
        nextRow = player.row;
        nextCol = player.col;

        return STATUS_STAY;
    }
    // checking other cases where the player can't move
    else if(map[nextRow][nextCol] == '?'){

        // are we to update nextRow and nextCol with player's row and col here?
        map[player.row][player.col] = TILE_OPEN;

        
        player.row = nextRow;
        player.col = nextCol;

        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_LEAVE;
    }
    
    else if(map[nextRow][nextCol] == '$'){
        player.treasure++;

        map[player.row][player.col] = TILE_OPEN;

        
        player.row = nextRow;
        player.col = nextCol;

        map[player.row][player.col] = TILE_PLAYER;

        return STATUS_TREASURE;
    }
    else if(map[nextRow][nextCol] == '@'){

        map[player.row][player.col] = TILE_OPEN;

        player.row = nextRow;
        player.col = nextCol;

        map[player.row][player.col] = TILE_PLAYER;

        return STATUS_AMULET;
    }
    else if((map[nextRow][nextCol] == '!') && (player.treasure > 0)){
        
        map[player.row][player.col] = TILE_OPEN;

        player.row = nextRow;
        player.col = nextCol;

        map[player.row][player.col] = TILE_PLAYER; 

        return STATUS_ESCAPE;
    }
    else if((map[nextRow][nextCol] == '!') && (player.treasure <= 0)){
        
        nextRow = player.row;
        nextCol = player.col;
        
        return STATUS_STAY;
    }
    else{
        map[player.row][player.col] = TILE_OPEN;

        player.row = nextRow;
        player.col = nextCol;

        map[player.row][player.col] = TILE_PLAYER;

        return STATUS_MOVE;
    }

    return 0;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {

    /**
     * I'll probably have to make an actual 2D dynamically allocated array/map first
     * Then we'll check straight in all directions of the player's current position till we either see a monster of an obstacle
     * If we see a monster before an obstacle, the monster will move towards the player by one and we'll update the map
     * 
     * 
     */
    bool attack = false; // cause monsters can eat monsters
    

    int i = player.row;
    int j = player.col;

    // checking up for monster

    while(i != 0 ){
        // if(i == 0){
        //     break;
        // }
        i--;
        if(map[i][j] == TILE_MONSTER){

            if(map[i + 1][j] == TILE_PLAYER){
                map[i][j] = TILE_OPEN;
                map[i + 1][j] = TILE_MONSTER;
                attack = true;
               // return true; // the monster ate you!!
            }
        
        map[i][j] = TILE_OPEN;
        map[i + 1][j] = TILE_MONSTER;

        
        
        }
        else if (map[i][j] == TILE_PILLAR){
         break;
        }

    }

    

    // checking down for the player

    i = player.row;
    j = player.col;

    while(i != (maxRow - 1)){
        
        i++;
        if(map[i][j] == TILE_MONSTER){

            if(map[i - 1][j] == TILE_PLAYER){
                map[i][j] = TILE_OPEN;
                map[i - 1][j] = TILE_MONSTER;
                attack = true;
               // return true; // the monster ate you!!
            }
        
        map[i][j] = TILE_OPEN;
        map[i - 1][j] = TILE_MONSTER;
        
     } 
     else if (map[i][j] == TILE_PILLAR){
         break;
     }


    }

    
    // checking for left from the player
    i = player.row;
    j = player.col;

    while(j != 0){
        
        j--;

        if(map[i][j] == TILE_MONSTER){

        if(map[i][j + 1] == TILE_PLAYER){
            
            map[i][j] = TILE_OPEN;
            map[i][j + 1] = TILE_MONSTER;
            attack = true;
            // return true; // the monster ate you!!
        }
        
        map[i][j] = TILE_OPEN;
        map[i][j + 1] = TILE_MONSTER;
    }
    else if (map[i][j] == TILE_PILLAR){
         break;
        }
    


    }

    
    // checking the right of the player
    i = player.row;
    j = player.col;

    while(j != (maxCol - 1)){
        
        j++;

        if(map[i][j] == TILE_MONSTER){

        if(map[i][j - 1] == TILE_PLAYER){
            map[i][j] = TILE_OPEN;
            map[i][j - 1] = TILE_MONSTER;
            attack = true;
            // return true; // the monster ate you!!
        }
        
        map[i][j] = TILE_OPEN;
        map[i][j - 1] = TILE_MONSTER;
        
        }
        else if (map[i][j] == TILE_PILLAR){
         break;
        }

    }

    
    if(attack){
        return true;
    }


    return false;
}