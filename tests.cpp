// #include <iostream>
// #include "logic.h"
// #include "logic.cpp"

// using std::cout, std::endl, std::string;

// // TODO(student): Write unit tests for the functions in logic.h
// //                You should end up with at least 500 lines of test code

// Player player1; // instance of the Player struct

// void testLoadLevel()
// {
//     // happy paths: things that should run right
//     int maxRow;
//     int maxCol;

    
//     char** test = loadLevel("levels/easy1.txt", maxRow, maxCol, player1);
//     //delete [] test;

//     for(int i = 0; i < 7; i++){
//         for(int j = 0; j < 5; j++){
//             cout << test[i][j] << " ";

//         }
//         cout << endl;
//     }
//     deleteMap(test, maxRow);   

//  }

// void testGetDirection(){

//     // HAPPY PATHS
//     int a; // for nextRow
//     int b; // for nextColumn


//     int c; // to run loadLevel, maxrow
//     int d; // to run loadLevel, maxCol
    
//     /**
//     char** test = loadLevel("zach1.txt", c, d, player1);
    
//     deleteMap(test, c);
//     */

//     getDirection('d', a, b);

    
//     getDirection('a', a, b);

    
//     getDirection('s', a, b);

    
//     getDirection('w', a, b);

    
    

// } // end of testGetDirection

//  void testDeleteMap(){

//     int c; // to run loadLevel, maxrow
//     int d; // to run loadLevel, maxCol
    
//     char** map = loadLevel("zach1.txt", c, d, player1);

//     deleteMap(map, c);

//  }


//  void testResizeMap(){

//     int maxRow;
//     int maxCol;

//     //const int SIZE = 17; 
    
//     //string zachry_dun[SIZE] = {"zach1.txt", "zach2.txt", "zach3.txt", "zach4.txt", "zach5.txt", "zach6.txt", "zach7.txt", "zach8.txt", "zach9.txt", "zach10.txt", "zach11.txt", "zach12.txt", "zach13.txt", "zach14.txt", "zach15.txt", "zach16.txt", "zach17.txt"};
    
//     char** test = loadLevel("levels/zach1.txt", maxRow, maxCol, player1);

//      for(int i = 0; i < 5; i++){
//         for(int j = 0; j < 4; j++){
//             cout << test[i][j] << " ";

//         }
//         cout << endl;
//     }
//     cout << endl;
//     //delete [] test;
    
//     /**
//     char** test2 = resizeMap(test, maxRow, maxCol);

//     deleteMap(test2, maxRow); */

//     test = resizeMap(test, maxRow, maxCol);

//      for(int i = 0; i < 10; i++){
//         for(int j = 0; j < 8; j++){
//             cout << test[i][j] << " ";

//         }
//         cout << endl;
//     }
//     cout << endl;

//     deleteMap(test, maxRow);


          
// }

// void testDoPlayerMove(){
    
//     int maxRow;
//     int maxCol;
//     int nextRow; // for nextRow
//     int nextColumn; // for nextColumn

//     //Player player2;

//     const int SIZE = 17; 
    
//     string zachry_dun[SIZE] = {"zach1.txt", "zach2.txt", "zach3.txt", "zach4.txt", "zach5.txt", "zach6.txt", "zach7.txt", "zach8.txt", "zach9.txt", "zach10.txt", "zach11.txt", "zach12.txt", "zach13.txt", "zach14.txt", "zach15.txt", "zach16.txt", "zach17.txt"};

//     char** test = loadLevel("zach1.txt", maxRow, maxCol, player1);

//     doPlayerMove(test, maxRow, maxCol, player1, nextRow, nextColumn);
//     doPlayerMove(test, maxRow, maxCol, player1, 3, 1);

//     deleteMap(test, maxRow);
//     /**
//     for(int i = 0; i < SIZE; i++){
//         char** test = loadLevel(zachry_dun[i], maxRow, maxCol, player1);
//         //delete [] test;
        
//         doPlayerMove(test, maxRow, maxCol, player1, nextRow, nextColumn);

//         //int b = doPlayerMove(test, maxRow, maxCol, player1, 3, 1);

//         deleteMap(test, maxRow);
//         test = nullptr;
//         //delete [] test;

        
//     }
//     */
    

// }



// void testDoMonsterAttack(){

//     int maxRow;
//     int maxCol;
//     int nextRow; // for nextRow
//     int nextColumn; // for nextColumn

    

//     char** test = loadLevel("levels/zach1.txt", maxRow, maxCol, player1);

//     for(int i = 0; i < 5; i++){
//         for(int j = 0; j < 4; j++){
//             cout << test[i][j] << " ";

//         }
//         cout << endl;
//     }
//     cout << endl;

//     doMonsterAttack(test, maxRow, maxCol, player1);

//     for(int i = 0; i < 5; i++){
//         for(int j = 0; j < 4; j++){
//             cout << test[i][j] << " ";

//         }
//         cout << endl;
//     }
    
//     deleteMap(test, maxRow);

    
// }


// int main() {
    
//    //testResizeMap();
//    testDoMonsterAttack();
    
//     return 0;
// }
