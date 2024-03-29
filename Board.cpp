#include "Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "UnplayablePosition.h"
#include "Position.h"

Board::Board()
{
    //ctor
}

Board::~Board()
{
    //dtor
}

void Board::drawBoard()
{
    std::string verticalIndex = "12345678";
    std::cout << "\n\n\ta b c d e f g h\n\n\n";

    short counter = 0;
    for(int i = 0; i < 8; i++)
    {
        while(counter < 8){
            if(counter == 0){std::cout << verticalIndex[i] << '\t';}
            std::cout << boardPositions[counter+(i*8)].getPiece() << ' ';
            counter++;
        }
        counter = 0;
        std::cout << "\n";
    }
}

Board Board::load()
{
    std::string inputFileName;
    std::cout << "Input save file name (example_save.txt) ";
    std::cin >> inputFileName;

    //std::ifstream inputFile;
    //inputFile.open(inputFileName);
    std::ifstream boardFile(inputFileName);
    std::ostringstream ss;
    //ss << inputFile.rdbuf();
    //std::string inputFileString = ss.str();

    int current_line = 0;
    std::string line;
    std::ostringstream ssBoard;
    while(!boardFile.eof())
    {
        current_line++;
        getline(boardFile, line);
        ssBoard << line;
        ssBoard << "\n";

    }

    std::string boardString = ssBoard.str();

    Board importedSave(boardString);
    return importedSave;
}

Board::Board(Player p1, Player p2, int start)
{
    first = p1;
    second = p2;
    /**
    std::cout << "TEST OF NAME: " << first.getName() << first.getName() << first.getName();
    std::string test;
    std::cin >> test;
    */
    if(start == 1){
        current = p1;
    }else if(start == 2){
        current = p2;
    }
}

Board::Board(std::string save_file)
{
    short counter = 0;
    std::ostringstream ssFirst;
    std::ostringstream ssSecond;
    std::ostringstream ssCurrent;
    std::ostringstream ssBoard;
    for(int i = 0; i < save_file.length(); i++)
    {
        if(counter < 3){
            //get players
            if(counter == 0 && save_file[i] != '\n')
            {
                ssFirst << save_file[i];
            }else if(counter == 0 && save_file[i] == '\n')
            {
                //std::cout << "\nfirst name is: " << ssFirst.str();
                counter++;
            }else if(counter == 1 && save_file[i] != '\n')
            {
                ssSecond << save_file[i];
            }else if(counter == 1 && save_file[i] == '\n')
            {
                //std::cout << "\nsecond name is: " << ssSecond.str();
                counter++;
            }else if(counter == 2 && save_file[i] != '\n')
            {
                ssCurrent << save_file[i];
            }else if(counter == 2 && save_file[i] == '\n')
            {
                //std::cout << "\ncurrent name is: " << ssCurrent.str();
                counter++;
            }
        }else
        {//gets board
            if(save_file[i] != '\n')
            {
                ssBoard << save_file[i];
            }
        }
    }
    //std::cout << "\nBoard str is : " << ssBoard.str();


    Player firsti(ssFirst.str());
    first = firsti;
    Player secondi(ssSecond.str());
    second = secondi;
    Player currenti(ssCurrent.str());
    current = currenti;
    setBoardPositions(ssBoard.str());
}

void Board::play()
{
    system("CLS");
    { //win condition checker
        int temp;
        int counter = 64;
        int whiteCounter = 0;
        int blackCounter = 0;
        for(int i = 0; i < 64; i++){
            if(boardPositions[i].getPiece() == Position::EMPTY){counter--;}
            if(boardPositions[i].getPiece() == Position::BLACK){blackCounter++;}
            if(boardPositions[i].getPiece() == Position::WHITE){whiteCounter++;}
            //std::cout << "blackCounter: " << blackCounter << "\nwhiteCounter: " << whiteCounter;
            //std::cin >> temp;
        }

        if(counter == 0 || blackCounter == 0 || whiteCounter == 0){ //all positions are full
            //count for winner
            int counterB = 0;
            int counterW = 0;

            for(int i = 0; i < 64; i++){
                if(boardPositions[i].getPiece() == Position::BLACK){
                    counterB++;
                }

                if(boardPositions[i].getPiece() == Position::WHITE){
                    counterW++;
                }
            }
            char saveDecision;
            if(counterB > counterW){
                std::cout << "\nBLACK IS THE WINNER.\n\n ";
                drawBoard();
                std::cout << "\nWould you like to save the game? (y/n): ";
                std::cin >> saveDecision;
                if(saveDecision == 'y'){save();}
                exit(0);

            }else if(counterW > counterB){
                std::cout << "\nWHITE IS THE WINNER.\n\n ";
                drawBoard();
                std::cout << "\nWould you like to save the game? (y/n): ";
                std::cin >> saveDecision;
                if(saveDecision == 'y'){save();}
                exit(0);
            }else if(counterW == counterB) {
                std::cout << "THE GAME IS A DRAW.\n ";
                drawBoard();
                std::cout << "\nWould you like to save the game? (y/n): ";
                std::cin >> saveDecision;
                if(saveDecision == 'y'){save();}
                exit(0);
            }
        }
    }

    //prompt user options
    Board::drawBoard();

    int emptyValue;
    int input;
    std::cout << "\n\nIt is " << current.getName() << "'s turn.";
    if(current.getName() == first.getName()){std::cout << "\nPlace a BLACK (B) token. ";}
    else if(current.getName() == second.getName()){std::cout << "\nPlace a WHITE (W) token. ";}

    bool again = true;
    while(again){
        { //win condition checker MAKE FUNCTION
        int temp;
        int counter = 64;
        int whiteCounter = 0;
        int blackCounter = 0;
        for(int i = 0; i < 64; i++){
            if(boardPositions[i].getPiece() == Position::EMPTY){counter--;}
            if(boardPositions[i].getPiece() == Position::BLACK){blackCounter++;}
            if(boardPositions[i].getPiece() == Position::WHITE){whiteCounter++;}
            //std::cout << "blackCounter: " << blackCounter << "\nwhiteCounter: " << whiteCounter;
            //std::cin >> temp;
        }

        if(counter == 0 || blackCounter == 0 || whiteCounter == 0){ //all positions are full
            //count for winner
            int counterB = 0;
            int counterW = 0;

            for(int i = 0; i < 64; i++){
                if(boardPositions[i].getPiece() == Position::BLACK){
                    counterB++;
                }

                if(boardPositions[i].getPiece() == Position::WHITE){
                    counterW++;
                }
            }
            char saveDecision;
            if(counterB > counterW){
                std::cout << "\nBLACK IS THE WINNER.\n\n ";
                drawBoard();
                std::cout << "\nWould you like to save the game? (y/n): ";
                std::cin >> saveDecision;
                if(saveDecision == 'y'){save();}
                exit(0);

            }else if(counterW > counterB){
                std::cout << "\nWHITE IS THE WINNER.\n\n ";
                drawBoard();
                std::cout << "\nWould you like to save the game? (y/n): ";
                std::cin >> saveDecision;
                if(saveDecision == 'y'){save();}
                exit(0);
            }else if(counterW == counterB) {
                std::cout << "THE GAME IS A DRAW.\n ";
                drawBoard();
                std::cout << "\nWould you like to save the game? (y/n): ";
                std::cin >> saveDecision;
                if(saveDecision == 'y'){save();}
                exit(0);
            }
        }
    }
    std::cout << "\n\t1. Move\n\t2. Save\n\t3. Concede the game (loser)\n\t4. Forfeit your turn\n";
    std::cin >> input;
        switch(input){
            case 1:{ //1. Move
                //rewrite board with playable positions
                system("CLS");
                for(int i = 0; i < 64; i++){
                    if(boardPositions[i].getPiece() != Position::WHITE && boardPositions[i].getPiece() != Position::BLACK){
                        if(checkMove(i) == false){
                            boardPositions[i].setPiece('*');
                        }
                    }
                }
                system("CLS");
                drawBoard();

                std::cout << "\n\nIt is " << current.getName() << "'s turn.";
                if(current.getName() == first.getName()){std::cout << "\nPlace a BLACK (B) token. ";}
                else if(current.getName() == second.getName()){std::cout << "\nPlace a WHITE (W) token. ";}
                std::cout << "\n\t1. Move\n\t2. Save\n\t3. Concede the game (loser)\n\t4. Forfeit your turn\n";

                for(int i = 0; i < 64; i++){
                    if(boardPositions[i].getPiece() == UnplayablePosition::UNPLAYABLE){
                        boardPositions[i].setPiece(Position::EMPTY);
                    }
                }

                again = false;
                int indexY;
                char indexX;
                int indexFinal = 100;
                int flag;

                do{
                    flag = 0;
                    indexY = 0;
                    indexX = 0;
                    std::cout << "\nEnter your move (horizontal index, vertical index): ";
                    std::cin >> indexX;
                    std::cin >> indexY;
                    indexX = indexX - 48;

                    //convert indexes to 1d array
                    int indexXint = (int)(indexX - 48) - 1;
                    indexY = indexY - 1;
                    indexY = indexY * 8;
                    indexFinal = indexY + indexXint;

                    //illegal conditions
                    if(indexFinal > 63){flag = 1;}
                    if(indexFinal < 0){flag = 2;}
                    if(boardPositions[indexFinal].canPlayOld() == false){flag = 3;}
                    //std::cout << "Dies on checkMove() ";
                    if(checkMove(indexFinal) == false) {flag = 4;}
                    //std::cout << "Doesn't die on checkMove() ";

                }while(flag != 0);

                boardPositions[indexFinal].setPiece(Position::BLACK);

                makeMove(indexFinal);

                takeTurn();
                break;
            }
            case 2:{ //2. Save
                again = true;
                save();
                break;
            }
            case 3:{ //3. Concede the game
                again = false;
                std::string str1 = first.getName();
                std::string str2 = second.getName();
                std::string strCurrent = current.getName();

                if(strCurrent == str1)
                {
                    std::cout << str2 << " IS THE WINNER.\n";
                }else if(strCurrent == str2)
                {
                    std::cout << str1 << " IS THE WINNER.\n";
                }
                char n;
                std::cout << "\nSave the game? (y/n): ";
                std::cin >> n;
                if(n == 'y'){
                    save();
                }
                exit(0);
                break;
            }
            case 4:{ //4. Forfeit their turn
                again = false;
                takeTurn();
                break;
            }
        }
    }
}

void Board::save()
{
    std::string saveNameInput;
    std::cout << "\nEnter name of save file: ";
    std::cin >> saveNameInput;

    std::ofstream outputSave(saveNameInput);
    std::ostringstream ss;
    ss << first.getName() << "\n" << second.getName() << "\n" << current.getName();
    ss << "\n";
    for(int i = 0; i < 64; i++){
        ss << boardPositions[i].getPiece();
        if((i + 1)%8 == 0){ ss << "\n";}
    }
    std::string boardString = ss.str();

    outputSave << ss.str();
    outputSave.close();
}

void Board::takeTurn()
{
    //toggles current

    std::string str1 = first.getName();
    std::string str2 = second.getName();
    std::string strCurrent = current.getName();

    std::cout << "\n" << current.getName() << "'s turn is now over. ";
    if(strCurrent == str1)
    {
        //std::cout << "current == first" ;
        current = second;
        //std::cout << "the current name is now " << current.getName();
    }else if(strCurrent == str2)
    {
        //std::cout << "current == second";
        current = first;
    }

}

void Board::setBoardPositions(std::string s)
{

    for(int i = 0; i < s.length(); i++)
    {
        Board::boardPositions[i].setPiece(s[i]);
    }
    for(int i = 2; i < 6; i++){
        Board::boardPositions[i].setPiece(UnplayablePosition::UNPLAYABLE);
    }

}

void Board::makeMove(int pos)
{
    bool loop = true;
    bool loop2 = true;
    char selfPiece;
    char oppoPiece;
    if(current.getName() == first.getName()){selfPiece = Position::BLACK; oppoPiece = Position::WHITE;}
    if(current.getName() == second.getName()){selfPiece = Position::WHITE; oppoPiece = Position::BLACK;}

    int posN = pos - 8;
    int posNE = pos - 7;
    int posE = pos + 1;
    int posSE = pos + 9;
    int posS = pos + 8;
    int posSW = pos + 7;
    int posW = pos - 1;
    int posNW = pos - 9;
    short pieceCount = 0;

    if(pos < 0 || pos > 63){std::cout << "\nposition too big, out of range. " ;}

    //place N
    pieceCount = 0;
    loop = true;
    loop2 = true;
    while(loop){
        if(posN < 0 || posN > 63){break;}
        //std::cout << "\n\nChecking N: " << boardPositions[posN].getPiece();

        if(boardPositions[posN].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posN].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posN].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the North\n\n";
            while(loop2){// goes back and changes pieces, up to its original spot
                posN = posN + 8;
                if(boardPositions[posN].getPiece() == oppoPiece){
                    boardPositions[posN].setPiece(selfPiece);
                }else{
                    //boardPositions[posN].setPiece(selfPiece);
                    loop2 = false;
                }
            }

        }
        posN = posN - 8;
    }

    //place NE
    pieceCount = 0;
    loop = true;
    loop2 = true;
    while(loop){
        if(posNE < 0 || posNE > 63){break;}
        //std::cout << "\n\nChecking NE: " << boardPositions[posN].getPiece();
        if(boardPositions[posNE].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posNE].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posNE].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the North East\n\n";
            while(loop2){// goes back and changes pieces, up to its original spot
                posNE = posNE + 7;
                if(boardPositions[posNE].getPiece() == oppoPiece){
                    boardPositions[posNE].setPiece(selfPiece);
                }else{
                    //boardPositions[posNE].setPiece(selfPiece);
                    loop2 = false;
                }
            }
        }
        posNE = posNE - 7;
    }

    //place E
    int initialRowE = (pos+1)/8;
    int newRowE;
    pieceCount = 0;
    loop = true;
    loop2 = true;
    while(loop){
        if(posE < 0 || posE > 63){break;}
        //std::cout << "\n\nChecking NE: " << boardPositions[posN].getPiece();
        if(boardPositions[posE].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posE].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posE].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the East\n\n";
            while(loop2){// goes back and changes pieces, up to its original spot
                posE = posE - 1;
                if(boardPositions[posE].getPiece() == oppoPiece){
                    boardPositions[posE].setPiece(selfPiece);
                }else{
                    //boardPositions[posE].setPiece(selfPiece);
                    loop2 = false;
                }
            }
        }
        posE = posE + 1;
    }

    //place SE
    pieceCount = 0;
    loop = true;
    loop2 = true;
    while(loop){
        if(posSE < 0 || posSE > 63){break;}
        //std::cout << "\n\nChecking NE: " << boardPositions[posN].getPiece();
        if(boardPositions[posSE].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posSE].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posSE].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the South East\n\n";
            while(loop2){// goes back and changes pieces, up to its original spot
                posSE = posSE - 9;
                if(boardPositions[posSE].getPiece() == oppoPiece){
                    boardPositions[posSE].setPiece(selfPiece);
                }else{
                    //boardPositions[posSE].setPiece(selfPiece);
                    loop2 = false;
                }
            }
        }
        posSE = posSE + 9;
    }

    //place S
    pieceCount = 0;
    loop = true;
    loop2 = true;
    while(loop){
        if(posS < 0 || posS > 63){break;}
        //std::cout << "\n\nChecking NE: " << boardPositions[posN].getPiece();
        if(boardPositions[posS].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posS].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posS].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the South East\n\n";
            while(loop2){// goes back and changes pieces, up to its original spot
                posS = posS - 8;
                if(boardPositions[posS].getPiece() == oppoPiece){
                    boardPositions[posS].setPiece(selfPiece);
                }else{
                    //boardPositions[posS].setPiece(selfPiece);
                    loop2 = false;
                }
            }
        }
        posS = posS + 8;
    }

    //place SW
    pieceCount = 0;
    loop = true;
    loop2 = true;
    while(loop){
        if(posSW < 0 || posSW > 63){break;}
        //std::cout << "\n\nChecking NE: " << boardPositions[posN].getPiece();
        if(boardPositions[posSW].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posSW].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posSW].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the South East\n\n";
            while(loop2){// goes back and changes pieces, up to its original spot
                posSW = posSW - 7;
                if(boardPositions[posSW].getPiece() == oppoPiece){
                    boardPositions[posSW].setPiece(selfPiece);
                }else{
                    //boardPositions[posSW].setPiece(selfPiece);
                    loop2 = false;
                }
            }
        }
        posSW = posSW + 7;
    }

    //place W
    pieceCount = 0;
    loop = true;
    loop2 = true;
    while(loop){
        if(posW < 0 || posW > 63){break;}
        //std::cout << "\n\nChecking NE: " << boardPositions[posN].getPiece();
        if(boardPositions[posW].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posW].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posW].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the South East\n\n";
            while(loop2){// goes back and changes pieces, up to its original spot
                posW = posW + 1;
                if(boardPositions[posW].getPiece() == oppoPiece){
                    boardPositions[posW].setPiece(selfPiece);
                }else{
                    //boardPositions[posW].setPiece(selfPiece);
                    loop2 = false;
                }
            }
        }
        posW = posW - 1;
    }

    //place NW
    pieceCount = 0;
    loop = true;
    loop2 = true;
    while(loop){
        if(posNW < 0 || posNW > 63){break;}
        //std::cout << "\n\nChecking NE: " << boardPositions[posN].getPiece();
        if(boardPositions[posNW].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posNW].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posNW].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the South East\n\n";
            while(loop2){// goes back and changes pieces, up to its original spot
                posNW = posNW + 9;
                if(boardPositions[posNW].getPiece() == oppoPiece){
                    boardPositions[posNW].setPiece(selfPiece);
                }else{
                    //boardPositions[posNW].setPiece(selfPiece);
                    loop2 = false;
                }
            }
        }
        posNW = posNW - 9;
    }
}

//getters and setters
bool Board::checkMove(int pos)
{
    /**
    This currently returns true if just one direction will outflank pieces.
    This saves time as it will not go through all 8 directions, instead just go until it finds one possibility
    In make move it will need to view all 8 directions, cannot skip any.
        could possible take the results from this method and pass it into the makeMove() method so reduce the
        amount of computations.

    !!!BUG!!!: currently the while(true) loops do not check if the indexes are part of the array. If a garbage
                happens to be '.' 'B' or 'W', it can lead to false results.
    */

    int flag = 0;
    bool loop = true;
    char selfPiece;
    char oppoPiece;
    if(current.getName() == first.getName()){selfPiece = Position::BLACK; oppoPiece = Position::WHITE;}
    if(current.getName() == second.getName()){selfPiece = Position::WHITE; oppoPiece = Position::BLACK;}

    int posN = pos - 8;
    int posNE = pos - 7;
    int posE = pos + 1;
    int posSE = pos + 9;
    int posS = pos + 8;
    int posSW = pos + 7;
    int posW = pos - 1;
    int posNW = pos - 9;
    short pieceCount = 0;

    //check N
    //std::cout << "\nDies on north";
    pieceCount = 0;
    loop = true;
    while(loop){
        //std::cout << "\n\nChecking N: " << boardPositions[posN].getPiece();
        if(posN < 0 || posN > 63){loop = false; break;}
        if(boardPositions[posN].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posN].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posN].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the North\n\n";
            return true;
        }
        posN = posN - 8;
    }

    //std::cout << "\nDies on north east";
    //check NE
    int initialRowNE = (pos)/8;
    int newRowNE = (posNE)/8;
    int diffNE = 0;
    pieceCount = 0;
    loop = true;
    while(loop){
        diffNE = initialRowNE - newRowNE;
        if(posNE < 0 || posNE > 63){break;}
        if(diffNE != -1){loop = false; break;}
        //std::cout << "\n\nChecking NE: " << boardPositions[posNE].getPiece();
        if(boardPositions[posNE].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posNE].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posNE].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece North East";
            return true;
        }
        posNE = posNE - 7;
        newRowNE = (posNE)/8;
    }

    //std::cout << "\nDies on east";
    //check E
    int initialRowE = (pos)/8;
    int newRowE = (posE)/8;
    pieceCount = 0;
    loop = true;
    while(loop){
        //system("pause");
        if(posE < 0 || posE > 63){break;}
        if(initialRowE != newRowE){loop = false; break;}
        //std::cout << "\n\nChecking E: " << boardPositions[posE].getPiece();
        if(boardPositions[posE].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posE].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posE].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the East";
            return true;
        }
        posE = posE + 1;
        newRowE = (posE)/8;
    }

    //std::cout << "\nDies on south east";
    //check SE
    int initialRowSE = (pos)/8;
    int newRowSE = (posSE)/8;
    int diffSE = 0;
    pieceCount = 0;
    loop = true;
    while(loop){
        diffSE = initialRowSE - newRowSE;
        if(posSE < 0 || posSE > 63){break;}
        if(diffSE != 1){loop = false; break;}
        //std::cout << "\n\nChecking SE: " << boardPositions[posSE].getPiece();
        if(boardPositions[posSE].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posSE].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posSE].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the South East";
            return true;
        }
        posSE = posSE + 9;
        newRowSE = (posSE)/8;
    }

    //std::cout << "\nDies on south";
    //check S
    pieceCount = 0;
    loop = true;
    while(loop){
        if(posS < 0 || posS > 63){break;}
        //std::cout << "\n\nChecking S: " << boardPositions[posS].getPiece();
        if(boardPositions[posS].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posS].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posS].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the south";
            return true;
        }
        posS = posS + 8;
    }

    //std::cout << "\nDies on south west";
    //check SW
    int initialRowSW = (pos)/8;
    int newRowSW = (posSW)/8;
    int diffSW = 0;
    pieceCount = 0;
    loop = true;
    while(loop){
        diffSW = initialRowSW - newRowSW;
        if(posSW < 0 || posSW > 63){break;}
        if(diffSW != 1){loop = false; break;}
        //std::cout << "\n\nChecking SW: " << boardPositions[posSW].getPiece();
        if(boardPositions[posSW].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posSW].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posSW].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the south west";
            return true;
        }
        posSW = posSW + 7;
        newRowSW = (posSW)/8;
    }

    //check W
    int initialRowW = (pos)/8;
    int newRowW = (posW)/8;
    pieceCount = 0;
    loop = true;
    while(loop){
        if(posW < 0 || posW > 63){break;}
        if(initialRowW != newRowW){loop = false; break;}
        //std::cout << "\n\nChecking W: " << boardPositions[posW].getPiece();
        if(boardPositions[posW].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posW].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posW].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the west";
            return true;
        }
        posW = posW - 1;
        newRowW = (posW)/8;
    }

    //std::cout << "\nDies on north west";
    //check NW
    int initialRowNW = (pos)/8;
    int newRowNW = (posNW)/8;
    int diffNW = 0;
    pieceCount = 0;
    loop = true;
    while(loop){
        diffNW = initialRowNW - newRowNW;
        //std::cout << "\n\nChecking NW: " << boardPositions[posNW].getPiece();
        if(posNW < 0 || posNW > 63){break;}
        if(diffNW != -1){loop = false; break;}
        if(boardPositions[posNW].getPiece() == Position::EMPTY){loop = false;}
        if(boardPositions[posNW].getPiece() == oppoPiece){pieceCount++;}
        if(boardPositions[posNW].getPiece() == selfPiece && pieceCount > 0){
            //std::cout << "\n\nfound the flanking piece in the North West";
            return true;
        }
        posNW = posNW - 9;
        newRowNW = (posNW)/8;
    }
    //if no loops catch a flank, return false.
    return false;
}

void Board::setPlayerOne(Player p)
{
    first = p;
}

void Board::setPlayerTwo(Player p)
{
    second = p;
}

void Board::setPlayerCurrent(Player p)
{
    current = p;
}

Player Board::getPlayerOne()
{
    return first;
}

Player Board::getPlayerTwo()
{
    return second;
}

Player Board::getPlayerCurrent()
{
    return current;
}
