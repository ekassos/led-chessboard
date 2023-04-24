#include <FastLED.h>

//Defining all LED-related constants
#define LED_PIN     5
#define NUM_LEDS    150
#define BRIGHTNESS  30
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 2
CRGB leds[NUM_LEDS];

// Defining all piece identifiers
#define P1_ROOK_LEFT 1
#define P1_ROOK_RIGHT 8
#define P1_KNIGHT_LEFT 2
#define P1_KNIGHT_RIGHT 7
#define P1_BISHOP_LEFT 3
#define P1_BISHOP_RIGHT 6
#define P1_QUEEN 4
#define P1_KING 5
#define P1_PAWN_1 9
#define P1_PAWN_2 10
#define P1_PAWN_3 11
#define P1_PAWN_4 12
#define P1_PAWN_5 13
#define P1_PAWN_6 14
#define P1_PAWN_7 15
#define P1_PAWN_8 16
#define P2_ROOK_LEFT 25
#define P2_ROOK_RIGHT 32
#define P2_KNIGHT_LEFT 26
#define P2_KNIGHT_RIGHT 31
#define P2_BISHOP_LEFT 27
#define P2_BISHOP_RIGHT 30
#define P2_QUEEN 28
#define P2_KING 29
#define P2_PAWN_1 17
#define P2_PAWN_2 18
#define P2_PAWN_3 19
#define P2_PAWN_4 20
#define P2_PAWN_5 21
#define P2_PAWN_6 22
#define P2_PAWN_7 23
#define P2_PAWN_8 24

int picked[2] = {};
String pieces[] = {"  (P1) Left Rook  ", " (P1) Left Knight ", " (P1) Left Bishop ", "    (P1) Queen    ", 
                   "    (P1) King     ", " (P1) Right Bishop", " (P1) Right Knight", "  (P1) Right Rook ", 
                   "   (P1) Pawn 1    ", "   (P1) Pawn 2    ", "   (P1) Pawn 3    ", "   (P1) Pawn 4    ", 
                   "   (P1) Pawn 5    ", "   (P1) Pawn 6    ", "   (P1) Pawn 7    ", "   (P1) Pawn 8    ",
                   "   (P2) Pawn 1    ", "   (P2) Pawn 2    ", "   (P2) Pawn 3    ", "   (P2) Pawn 4    ", 
                   "   (P2) Pawn 5    ", "   (P2) Pawn 6    ", "   (P2) Pawn 7    ", "   (P2) Pawn 8    ",
                   "  (P2) Left Rook  ", " (P2) Left Knight ", " (P2) Left Bishop ", "    (P2) Queen    ", 
                   "    (P2) King     ", " (P2) Right Bishop", " (P2) Right Knight", "  (P2) Right Rook "};

// Defining piece starting positions and intializing board
int currentBoard[8][8] = {{P1_ROOK_LEFT, P1_KNIGHT_LEFT, P1_BISHOP_LEFT, P1_QUEEN, P1_KING, P1_BISHOP_RIGHT, P1_KNIGHT_RIGHT, P1_ROOK_RIGHT},     // ROW 8
                          {P1_PAWN_1, P1_PAWN_2, P1_PAWN_3, P1_PAWN_4, P1_PAWN_5, P1_PAWN_6, P1_PAWN_7, P1_PAWN_8},                               // ROW 7
                          {},                                                                                                                     // ROW 6
                          {},                                                                                                                     // ROW 5
                          {},                                                                                                                     // ROW 4
                          {},                                                                                                                     // ROW 3
                          {P2_PAWN_1, P2_PAWN_2, P2_PAWN_3, P2_PAWN_4, P2_PAWN_5, P2_PAWN_6, P2_PAWN_7, P2_PAWN_8},                               // ROW 2
                          {P2_ROOK_LEFT, P2_KNIGHT_LEFT, P2_BISHOP_LEFT, P2_QUEEN, P2_KING, P2_BISHOP_RIGHT, P2_KNIGHT_RIGHT, P2_ROOK_RIGHT}      // ROW 1
                          };

int moves[64] = {};
int kills[64] = {};

int P1_taken_out[16] = {};
int P1_taken_out_index = 0;
int P2_taken_out[16] = {};
int P2_taken_out_index = 0;

int light_coresponding[64][6] = {{},              //CELL 11, INDEX 0
                                 {},              //CELL 12, INDEX 1
                                 {},              //CELL 13, INDEX 2
                                 {},              //CELL 14, INDEX 3
                                 {},              //CELL 15, INDEX 4
                                 {},              //CELL 16, INDEX 5
                                 {},              //CELL 17, INDEX 6
                                 {},              //CELL 18, INDEX 7
                                 {},              //CELL 21, INDEX 8
                                 {},              //CELL 22, INDEX 9
                                 {},              //CELL 23, INDEX 10
                                 {},              //CELL 24, INDEX 11
                                 {},              //CELL 25, INDEX 12
                                 {},              //CELL 26, INDEX 13
                                 {},              //CELL 27, INDEX 14
                                 {},              //CELL 28, INDEX 15
                                 {107, 108, 109, 110, 111, 112},              //CELL 31, INDEX 16
                                 {},              //CELL 32, INDEX 17
                                 {},              //CELL 33, INDEX 18
                                 {},              //CELL 34, INDEX 19
                                 {},              //CELL 35, INDEX 20
                                 {},              //CELL 36, INDEX 21
                                 {},              //CELL 37, INDEX 22
                                 {},              //CELL 38, INDEX 23
                                 {},              //CELL 41, INDEX 24
                                 {},              //CELL 42, INDEX 25
                                 {},              //CELL 43, INDEX 26
                                 {},              //CELL 44, INDEX 27
                                 {},              //CELL 45, INDEX 28
                                 {},              //CELL 46, INDEX 29
                                 {},              //CELL 47, INDEX 30
                                 {},              //CELL 48, INDEX 31
                                 {},              //CELL 51, INDEX 32
                                 {},              //CELL 52, INDEX 33
                                 {},              //CELL 53, INDEX 34
                                 {},              //CELL 54, INDEX 35
                                 {},              //CELL 55, INDEX 36
                                 {},              //CELL 56, INDEX 37
                                 {},              //CELL 57, INDEX 38
                                 {},              //CELL 58, INDEX 39
                                 {},              //CELL 61, INDEX 40
                                 {},              //CELL 62, INDEX 41
                                 {},              //CELL 63, INDEX 42
                                 {},              //CELL 64, INDEX 43
                                 {},              //CELL 65, INDEX 44
                                 {},              //CELL 66, INDEX 45
                                 {},              //CELL 67, INDEX 46
                                 {},              //CELL 68, INDEX 47
                                 {},              //CELL 71, INDEX 48
                                 {},              //CELL 72, INDEX 49
                                 {},              //CELL 73, INDEX 50
                                 {},              //CELL 74, INDEX 51
                                 {},              //CELL 75, INDEX 52
                                 {},              //CELL 76, INDEX 53
                                 {},              //CELL 77, INDEX 54
                                 {},              //CELL 78, INDEX 55
                                 {},              //CELL 81, INDEX 56
                                 {},              //CELL 82, INDEX 57
                                 {},              //CELL 83, INDEX 58
                                 {},              //CELL 84, INDEX 59
                                 {},              //CELL 85, INDEX 60
                                 {},              //CELL 86, INDEX 61
                                 {},              //CELL 87, INDEX 62
                                 {},              //CELL 88, INDEX 63
};

void setup() {
  Serial.begin(9600);
   // while the serial stream is not open, do nothing:
  while (!Serial);
  Serial.println();
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS); 
  FastLED.setBrightness(BRIGHTNESS);
  printBoard();
  // while (Serial.available() == 0) {
    // Wait for User to Input Data
  // }
  // int input = Serial.parseInt();
  // Serial.print(input);
  // Serial.println();
  // printBoard();
}

void loop() { 
  Serial.print("Select the position of the piece to pick up: ");
  while (Serial.available() == 0) {
    // Wait for User to Input Data
  }
  String input = Serial.readString();
  Serial.print(input);
  if (input.length() == 3){
    input.toLowerCase();
    char array[] = {};
    input.toCharArray(array, input.length());
    if ((array[0] == 'a' || array[0] == 'b' || array[0] == 'c' || array[0] == 'd' || array[0] == 'e' || array[0] == 'f' || array[0] == 'g' || array[0] == 'h') && array[1] > 48 && array[1] < 57){
      int initialPosition = positionToNumbers (array[0], array[1] - 48);
      Serial.println(initialPosition);
      Serial.println();
      Serial.println("Available positions you can move to are shown below:");
      int piecePicked = currentBoard[8 - (initialPosition / 10)][initialPosition % 10 - 1];
      possibleMoves(piecePicked, initialPosition);
      movesBoard();
      bool legalMove = false;
      while (legalMove == false) {
        Serial.print("Indicate where you want to place your piece: ");
        while (Serial.available() == 0) {
          // Wait for User to Input Data
        }        
        String toPlace = Serial.readString();
        Serial.print(toPlace);
        if (toPlace.length() == 3){
          toPlace.toLowerCase();
          char toPlace_array[] = {};
          toPlace.toCharArray(toPlace_array, toPlace.length());
          if ((toPlace_array[0] == 'a' || toPlace_array[0] == 'b' || toPlace_array[0] == 'c' || toPlace_array[0] == 'd' || toPlace_array[0] == 'e' || toPlace_array[0] == 'f' || toPlace_array[0] == 'g' || toPlace_array[0] == 'h') && toPlace_array[1] > 48 && toPlace_array[1] < 57){
            int movePosition = positionToNumbers (toPlace_array[0], toPlace_array[1] - 48);
            Serial.print(movePosition);
            for (int i = 0; i < 64; i++) {
              if (moves[i] == movePosition || kills[i] == movePosition || movePosition == initialPosition) {
                legalMove = true;
              }
            }
            if (legalMove) {
              refreshBoard (initialPosition, movePosition);
              Serial.println("Move registered, here's the new board:");
              Serial.println();
              printBoard();
            }
          }
        }
      }
    }
    else {
      Serial.println("You entered illegal characters. Characters allowed: (column) a-e, (row) 1-8");
      Serial.println();
    }
  }
  else {
    Serial.println("Please enter a position in the following two chracter format, without the parentheses: (letter/column)(number/row).");
    Serial.println();
  }
}

int positionToNumbers (char letter, int number){
  if (letter == 'a'){
    Serial.println("a");
    return number * 10 + 1;
  }
  if (letter == 'b'){
    return number * 10 + 2;
  }
  if (letter == 'c'){
    return number * 10 + 3;
  }
  if (letter == 'd'){
    return number * 10 + 4;
  }
  if (letter == 'e'){
    return number * 10 + 5;
  }
  if (letter == 'f'){
    return number * 10 + 6;
  }
  if (letter == 'g'){
    return number * 10 + 7;
  }
  if (letter == 'h'){
    return number * 10 + 8;
  }
}

void printBoard() {
  String empty =  " |             |                    |                    |                    |                    |                    |                    |                    |                    | ";
  String filler = " | ----------- | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ";
     Serial.println();
     Serial.print("               | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ");
     Serial.println();
     Serial.print("               |         a          |         b          |         c          |         d          |         e          |         f          |         g          |         h          | ");
     Serial.println();
     Serial.print(filler);
     Serial.println();
  for(int i = 7; i > -1; i--) {
    Serial.print(empty);
    Serial.println();
    Serial.print(" |      ");
    Serial.print(i + 1);
    Serial.print("      | ");
    for(int j = 0; j < 8; j++) {
      int piece = currentBoard[8 - i - 1][j];
      if (piece == 0){
        Serial.print("                  ");
      }
      else{
        Serial.print(pieces[piece - 1]);
      }
      Serial.print(" | ");
    }
    Serial.println();
    Serial.print(empty);
    Serial.println();
    Serial.print(filler);
    Serial.println();
  }
  Serial.println();
  Serial.println();
}

void movesBoard() {
  String empty =  " |             |                    |                    |                    |                    |                    |                    |                    |                    | ";
  String filler = " | ----------- | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ";
     Serial.println();
     Serial.print("               | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ");
     Serial.println();
     Serial.print("               |         a          |         b          |         c          |         d          |         e          |         f          |         g          |         h          | ");
     Serial.println();
     Serial.print(filler);
     Serial.println();
  for (int i = 7; i > -1; i--) {
    Serial.print(empty);
    Serial.println();
    Serial.print(" |      ");
    Serial.print(i + 1);
    Serial.print("      | ");
    for (int j = 0; j < 8; j++) {
      int piece = currentBoard[8 - i - 1][j];
      int movePosition = (i + 1) * 10 + j + 1;
      bool canAttack = false;
      for (int n = 0; n < 64; n++) {
        if (movePosition == kills[n]){
          canAttack = true;
        }
      }
      if (canAttack) {
        Serial.print(" Can attack here! ");
      }
      else {
        if (picked[0] == i + 1 && picked[1] == j + 1) {
          Serial.print("* Picked up here *");
        }
        else {
          Serial.print("                  ");
        }
        
      }
      Serial.print(" | ");
    }
    Serial.println();
    Serial.print(" |       ");
    Serial.print("      | ");
    for (int j = 0; j < 8; j++) {
      int piece =  currentBoard[8 - i - 1][j];
      int movePosition = (i + 1) *10 + j + 1;
      bool canMove = false;
      for (int n = 0; n < 64; n++) {
        if (movePosition == moves[n]){
          canMove = true;
        }
      }
      if (canMove) {
        Serial.print("  Can move here!  ");
      }
      else {
        if (piece == 0){
          Serial.print("                  ");
        }
        else {
          Serial.print(pieces[piece - 1]);
        }
      }
      Serial.print(" | ");
    }
    Serial.println();
    Serial.print(empty);
    Serial.println();
    Serial.print(filler);
    Serial.println();
  }
  Serial.println();
  Serial.println();
}

void possibleMoves(int piece, int currentPosition) {
  int currentRow = currentPosition / 10;
  int currentColumn = currentPosition % 10;

  picked[0] = currentRow;
  picked[1] = currentColumn;
  
  Serial.print("currentRow: ");
  Serial.print(currentRow);
  Serial.print(",");
  Serial.print("\t");
  Serial.print("currentColumn: ");
  Serial.print(currentColumn);
  Serial.print(".");
  Serial.println();
      
  // clear possible moves 
  for (int i = 0; i < 64; i++){
      moves[i] = 0;
  }

  // clear possible kills 
  for (int i = 0; i < 64; i++){
      kills[i] = 0;
  }
  
  if (piece == P1_ROOK_LEFT || piece == P1_ROOK_RIGHT || piece == P2_ROOK_LEFT || piece == P2_ROOK_RIGHT) {
    rookMoves (piece, currentRow, currentColumn);
  }
  if (piece == P1_KNIGHT_LEFT || piece == P1_KNIGHT_RIGHT || piece == P2_KNIGHT_LEFT || piece == P2_KNIGHT_RIGHT) {
    knightMoves (piece, currentRow, currentColumn);
  }
  if (piece == P1_KING || piece == P2_KING) {
    kingMoves (piece, currentRow, currentColumn);
  }
  if (piece == P1_BISHOP_LEFT || piece == P1_BISHOP_RIGHT || piece == P2_BISHOP_LEFT || piece == P2_BISHOP_RIGHT) {
    bishopsMoves (piece, currentRow, currentColumn);
  }
  if (piece == P1_QUEEN || piece == P2_QUEEN) {
    queenMoves (piece, currentRow, currentColumn);
  }
  if ((piece > 8 && piece < 17) || (piece > 16 && piece < 25)){
    pawnMoves (piece, currentRow, currentColumn);
  }
  refreshLights();
}

void refreshLights() {
    for (int i = 0; i < 64; i++){
    if (moves[i] != 0){
      int arrayRow = moves[i] / 10;
      int arrayColumn = moves[i] % 10;
      int arayIndex = (arrayRow - 1) * 8 + (arrayColumn - 1);
          Serial.print("going through cell number: ");
          Serial.print(arrayRow);
          Serial.print(arrayColumn);
          Serial.print(", index: ");
          Serial.print(arayIndex);
          Serial.println();
      for (int j = 0; j < 6; j++){
        if (light_coresponding[arayIndex][j] != 0){
          Serial.print("sending command to light up LED: ");
          Serial.print(light_coresponding[arayIndex][j]);
          Serial.println();
          leds[(light_coresponding[arayIndex][j])] = CRGB::Orange; FastLED.show();
        }
      }
      Serial.println();
    }
  }
  Serial.println();
  FastLED.show();
}

bool isOpponent (int yourPiece, int locationRow, int locationColumn){
  int pieceAtTile = currentBoard[locationRow][locationColumn];
  Serial.print("pieceAtTile: ");
  Serial.print(pieces[pieceAtTile - 1]);
  Serial.print(", result: ");
  Serial.print((yourPiece < 17 && pieceAtTile > 16) || (yourPiece > 16 && pieceAtTile < 17));
  Serial.println();
  return ((yourPiece < 17 && pieceAtTile > 16) || (yourPiece > 16 && pieceAtTile < 17));
}

void refreshBoard (int oldPosition, int newPosition){
  int oldRow = 8 - oldPosition / 10;
  int oldColumn = (oldPosition % 10) - 1;
  int newRow = 8 - newPosition / 10;
  int newColumn = (newPosition % 10) - 1;
  int yourPiece = currentBoard[oldRow][oldColumn];
  int currentPiece = currentBoard[newRow][newColumn];
  if (currentPiece != 0 && currentPiece != yourPiece){
    if (currentPiece < 17){
      P1_taken_out[P1_taken_out_index] = currentPiece;
      P1_taken_out_index ++; 
    }
    else {
      P2_taken_out[P2_taken_out_index] = currentPiece;
      P2_taken_out_index ++; 
    }
  }
  currentBoard[oldRow][oldColumn] = 0;
  currentBoard[newRow][newColumn] = yourPiece;
}

void rookMoves (int piece, int currentRow, int currentColumn) {
  int index = 0;
  int kills_index = 0;
  int boardRow = 8 - currentRow;
  int boardColumn = currentColumn - 1;
  
  // check for possible moves on left side of rook
  for (int i = boardColumn; i > 0; i--) {
    if (currentBoard[boardRow][i - 1] == 0) {
      moves[index] = currentRow * 10 + i;
      index++;
    }
    else{
      if (isOpponent(piece, boardRow, i)){
        kills[kills_index] = currentRow * 10 + i;
        kills_index++;
        int arayIndex = (currentRow - 1) * 8 + i + 1;
        Serial.print("going through left opponent cell: ");
        Serial.print(currentRow);
        Serial.print(i);
        Serial.print(", index: ");
        Serial.print(arayIndex);
        Serial.println();
        for (int j = 0; j < 6; j++){
          if (light_coresponding[arayIndex][j] != 0){
            Serial.print("sending command to light up LED: ");
            Serial.print(light_coresponding[arayIndex][j]);
            Serial.println();
            leds[(light_coresponding[arayIndex][j])] = CRGB::Blue;
          }
      }
      Serial.println();
      }
      break;
    }
  }

  // check for possible moves on right side of rook
  for (int i = currentColumn; i < 8; i++) {
    if (currentBoard[boardRow][i] == 0) {
      moves[index] = currentRow * 10 + i + 1;
      index++;
    }
    else{
      if (isOpponent(piece, boardRow, i)){
        kills[kills_index] = currentRow * 10 + i + 1;
        kills_index++;
        int arayIndex = (currentRow - 1) * 8 + i + 1;
        Serial.print("going through right opponent cell: ");
        Serial.print(currentRow);
        Serial.print(i + 1);
        Serial.print(", index: ");
        Serial.print(arayIndex);
        Serial.println();
        for (int j = 0; j < 6; j++){
          if (light_coresponding[arayIndex][j] != 0){
            Serial.print("sending command to light up LED: ");
            Serial.print(light_coresponding[arayIndex][j]);
            Serial.println();
            leds[(light_coresponding[arayIndex][j])] = CRGB::Blue; 
          }
      }
      Serial.println();
      }
      break;
    }
  }

  // check for possible moves on top side of rook
  for (int i = boardRow - 1; i > -1; i--) {
    if (currentBoard[i][boardColumn] == 0) {
      moves[index] = (8 - i) * 10 + currentColumn;
      index++;
    }
    else{
      if (isOpponent(piece, i, boardColumn)){
        kills[kills_index] = (8 - i) * 10 + currentColumn;
        kills_index++;
        int arayIndex = (8 - i) * 8 + boardColumn;
        Serial.println();
        Serial.print("going through bottom opponent cell: ");
        Serial.print(8 - i);
        Serial.print(currentColumn);
        Serial.print(", index: ");
        Serial.print(arayIndex);
        Serial.println();
        for (int j = 0; j < 6; j++){
          if (light_coresponding[arayIndex][j] != 0){
            Serial.print("sending command to light up LED: ");
            Serial.print(light_coresponding[arayIndex][j]);
            Serial.println();
            leds[(light_coresponding[arayIndex][j])] = CRGB::Blue;
          }
      }
      Serial.println();
      }
      break;
    }
  }

  // check for possible moves on bottom side of rook
  for (int i = boardRow + 1; i < 8; i++) {
    if (currentBoard[i][boardColumn] == 0) {
      moves[index] = (8 - i) * 10 + currentColumn;
      index++;
    }
    else{
      if (isOpponent(piece, i, boardColumn)){
        kills[kills_index] = (8 - i) * 10 + currentColumn;
        kills_index++;
        int arayIndex = (8 - i - 1) * 8 + boardColumn;
        Serial.print("going through bottom opponent cell: ");
        Serial.print(8 - i);
        Serial.print(currentColumn);
        Serial.print(", index: ");
        Serial.print(arayIndex);
        Serial.println();
        for (int j = 0; j < 6; j++){
          if (light_coresponding[arayIndex][j] != 0){
            Serial.print("sending command to light up LED: ");
            Serial.print(light_coresponding[arayIndex][j]);
            Serial.println();
            leds[(light_coresponding[arayIndex][j])] = CRGB::White; FastLED.show();
          }
      }
      Serial.println();
      }
      break;
    }
  }
  Serial.println();
  Serial.println("Ran rook");
  Serial.print('\n');
  Serial.print("possible moves for rook: ");
  Serial.print('\n');
  for (int i = 0; i < 64; i++){
    if (moves[i] > 0){
      Serial.print(moves[i]);
      Serial.print(", ");
    }
  }
  Serial.println();
  Serial.println();
}

void knightMoves (int piece, int currentRow, int currentColumn) {
  int index = 0;
  int kills_index = 0;
  // possible moves to test
  int combinations[8][2] = { {currentRow + 2, currentColumn - 1}, // i + 2, j - 1
                             {currentRow + 2, currentColumn + 1}, // i + 2, j + 1
                             {currentRow + 1, currentColumn - 2}, // i + 1, j - 2
                             {currentRow + 1, currentColumn + 2}, // i + 1, j + 2
                             {currentRow - 2, currentColumn - 1}, // i - 2, j - 1
                             {currentRow - 2, currentColumn + 1}, // i - 2, j + 1
                             {currentRow - 1, currentColumn - 2}, // i - 1, j - 2
                             {currentRow - 1, currentColumn + 2}, // i - 1, j + 2
  };

  for (int i = 0; i < 8; i++){
    // make sure the move coordinates are not out of bounds
    if (combinations[i][0] < 9 && combinations[i][0] > 0 && combinations[i][1] < 9 && combinations[i][1] > 0){

      if (currentBoard[8 - combinations[i][0]][combinations[i][1] - 1] == 0) {
        moves[index] = combinations[i][0] * 10 + combinations[i][1];
        index++;
      }
      else {
        if (isOpponent(piece, 8 - combinations[i][0], combinations[i][1] - 1)){
          kills[kills_index] = combinations[i][0] * 10 + combinations[i][1];
          kills_index++;
          int arayIndex = (combinations[i][0] - 1) * 8 + combinations[i][1] - 1;
          Serial.print("going through opponent cell: ");
          Serial.print(combinations[i][0]);
          Serial.print(combinations[i][1]);
          Serial.print(", index: ");
          Serial.print(arayIndex);
          Serial.println();
          for (int j = 0; j < 6; j++){
            if (light_coresponding[arayIndex][j] != 0){
              Serial.print("sending command to light up LED: ");
              Serial.print(light_coresponding[arayIndex][j]);
              Serial.println();
              leds[(light_coresponding[arayIndex][j])] = CRGB::Blue;
            }
        }
        Serial.println();
        }
      }
    }
  }
  Serial.print("Ran knight");
  Serial.print('\n');
  Serial.print("possible moves for knight: ");
  Serial.print('\n');
  for (int i = 0; i < 64; i++){
    if (moves[i] > 0){
      Serial.print(moves[i]);
      Serial.print(", ");
    }
  }
  Serial.println();
}

void kingMoves (int piece, int currentRow, int currentColumn) {
  int index = 0;
  int kills_index = 0;
  // possible moves to test
  int combinations[8][2] = { {currentRow + 1, currentColumn},     // i + 1, j
                             {currentRow + 1, currentColumn - 1}, // i + 1, j - 1
                             {currentRow + 1, currentColumn + 1}, // i + 1, j + 1
                             {currentRow, currentColumn - 1},     // i, j - 1
                             {currentRow, currentColumn + 1},     // i, j + 1
                             {currentRow - 1, currentColumn},     // i - 1, j
                             {currentRow - 1, currentColumn + 1}, // i - 1, j + 1
                             {currentRow - 1, currentColumn - 1}, // i - 1, j - 1
  };

  for (int i = 0; i < 8; i++){
    // make sure the move coordinates are not out of bounds
    if (combinations[i][0] < 9 && combinations[i][0] > 0 && combinations[i][1] < 9 && combinations[i][1] > 0){

      if (currentBoard[8 - combinations[i][0]][combinations[i][1] - 1] == 0) {
        moves[index] = combinations[i][0] * 10 + combinations[i][1];
        index++;
      }
      else {
        if (isOpponent(piece, 8 - combinations[i][0], combinations[i][1] - 1)){
          kills[kills_index] = combinations[i][0] * 10 + combinations[i][1];
          kills_index++;
          int arayIndex = (combinations[i][0] - 1) * 8 + combinations[i][1] - 1;
          Serial.print("going through opponent cell: ");
          Serial.print(combinations[i][0]);
          Serial.print(combinations[i][1]);
          Serial.print(", index: ");
          Serial.print(arayIndex);
          Serial.println();
          for (int j = 0; j < 6; j++){
            if (light_coresponding[arayIndex][j] != 0){
              Serial.print("sending command to light up LED: ");
              Serial.print(light_coresponding[arayIndex][j]);
              Serial.println();
              leds[(light_coresponding[arayIndex][j])] = CRGB::Blue;
            }
        }
        Serial.println();
        }
      }
    }
  }
  Serial.print("Ran king");
  Serial.print('\n');
  Serial.print("possible moves for king: ");
  Serial.print('\n');
  for (int i = 0; i < 64; i++){
    if (moves[i] > 0){
      Serial.print(moves[i]);
      Serial.print(", ");
    }
  }
  Serial.println();
}

void bishopsMoves (int piece, int currentRow, int currentColumn) {
  int index = 0;
  int kills_index = 0;
  // possible moves to test
  int combinations[4][28][2] = { {{currentRow + 1, currentColumn + 1},     // i + 1, j + 1
                              {currentRow + 2, currentColumn + 2},     // i + 2, j + 2
                              {currentRow + 3, currentColumn + 3},     // i + 3, j + 3
                              {currentRow + 4, currentColumn + 4},     // i + 4, j + 4
                              {currentRow + 5, currentColumn + 5},     // i + 5, j + 5
                              {currentRow + 6, currentColumn + 6},     // i + 6, j + 6
                              {currentRow + 7, currentColumn + 7}},    // i + 7, j + 7
                             {{currentRow - 1, currentColumn + 1},     // i - 1, j + 1
                              {currentRow - 2, currentColumn + 2},     // i - 2, j + 2
                              {currentRow - 3, currentColumn + 3},     // i - 3, j + 3
                              {currentRow - 4, currentColumn + 4},     // i - 4, j + 4
                              {currentRow - 5, currentColumn + 5},     // i - 5, j + 5
                              {currentRow - 6, currentColumn + 6},     // i - 6, j + 6
                              {currentRow - 7, currentColumn + 7}},    // i - 7, j + 7
                             {{currentRow - 1, currentColumn - 1},     // i - 1, j - 1
                              {currentRow - 2, currentColumn - 2},     // i - 2, j - 2
                              {currentRow - 3, currentColumn - 3},     // i - 3, j - 3
                              {currentRow - 4, currentColumn - 4},     // i - 4, j - 4
                              {currentRow - 5, currentColumn - 5},     // i - 5, j - 5
                              {currentRow - 6, currentColumn - 6},     // i - 6, j - 6
                              {currentRow - 7, currentColumn - 7}},    // i - 7, j - 7
                             {{currentRow + 1, currentColumn - 1},     // i + 1, j - 1
                              {currentRow + 2, currentColumn - 2},     // i + 2, j - 2
                              {currentRow + 3, currentColumn - 3},     // i + 3, j - 3
                              {currentRow + 4, currentColumn - 4},     // i + 4, j - 4
                              {currentRow + 5, currentColumn - 5},     // i + 5, j - 5
                              {currentRow + 6, currentColumn - 6},     // i + 6, j - 6
                              {currentRow + 7, currentColumn - 7}}     // i + 7, j - 7

  };


  for (int j = 0; j < 4; j++){
  for (int i = 0; i < 28; i++){
    // make sure the move coordinates are not out of bounds
    if (combinations[j][i][0] < 9 && combinations[j][i][0] > 0 && combinations[j][i][1] < 9 && combinations[j][i][1] > 0){

      if (currentBoard[8 - combinations[j][i][0]][combinations[j][i][1] - 1] == 0) {
        moves[index] = combinations[j][i][0] * 10 + combinations[j][i][1];
        index++;
      }
      else {
        if (isOpponent(piece, 8 - combinations[j][i][0], combinations[j][i][1] - 1)){
          kills[kills_index] = combinations[j][i][0] * 10 + combinations[j][i][1];
          kills_index++;
          int arayIndex = (combinations[j][i][0] - 1) * 8 + combinations[j][i][1] - 1;
          Serial.print("going through opponent cell: ");
          Serial.print(combinations[j][i][0]);
          Serial.print(combinations[j][i][1]);
          Serial.print(", index: ");
          Serial.print(arayIndex);
          Serial.println();
          for (int j = 0; j < 6; j++){
            if (light_coresponding[arayIndex][j] != 0){
              Serial.print("sending command to light up LED: ");
              Serial.print(light_coresponding[arayIndex][j]);
              Serial.println();
              leds[(light_coresponding[arayIndex][j])] = CRGB::Blue;
            }
        }
        Serial.println();
        }
        break;
      }
    }
  }}
  Serial.print("Ran bishop");
  Serial.print('\n');
  Serial.print("possible moves for bishop: ");
  Serial.print('\n');
  for (int i = 0; i < 64; i++){
    if (moves[i] > 0){
      Serial.print(moves[i]);
      Serial.print(", ");
    }
  }
  Serial.println();
}

void queenMoves (int piece, int currentRow, int currentColumn) {
  int index = 0;
  int kills_index = 0;
  // possible moves to test
  int combinations[8][28][2] = { {{currentRow + 1, currentColumn + 1},     // i + 1, j + 1
                              {currentRow + 2, currentColumn + 2},     // i + 2, j + 2
                              {currentRow + 3, currentColumn + 3},     // i + 3, j + 3
                              {currentRow + 4, currentColumn + 4},     // i + 4, j + 4
                              {currentRow + 5, currentColumn + 5},     // i + 5, j + 5
                              {currentRow + 6, currentColumn + 6},     // i + 6, j + 6
                              {currentRow + 7, currentColumn + 7}},    // i + 7, j + 7
                             {{currentRow - 1, currentColumn + 1},     // i - 1, j + 1
                              {currentRow - 2, currentColumn + 2},     // i - 2, j + 2
                              {currentRow - 3, currentColumn + 3},     // i - 3, j + 3
                              {currentRow - 4, currentColumn + 4},     // i - 4, j + 4
                              {currentRow - 5, currentColumn + 5},     // i - 5, j + 5
                              {currentRow - 6, currentColumn + 6},     // i - 6, j + 6
                              {currentRow - 7, currentColumn + 7}},    // i - 7, j + 7
                             {{currentRow - 1, currentColumn - 1},     // i - 1, j - 1
                              {currentRow - 2, currentColumn - 2},     // i - 2, j - 2
                              {currentRow - 3, currentColumn - 3},     // i - 3, j - 3
                              {currentRow - 4, currentColumn - 4},     // i - 4, j - 4
                              {currentRow - 5, currentColumn - 5},     // i - 5, j - 5
                              {currentRow - 6, currentColumn - 6},     // i - 6, j - 6
                              {currentRow - 7, currentColumn - 7}},    // i - 7, j - 7
                             {{currentRow + 1, currentColumn - 1},     // i + 1, j - 1
                              {currentRow + 2, currentColumn - 2},     // i + 2, j - 2
                              {currentRow + 3, currentColumn - 3},     // i + 3, j - 3
                              {currentRow + 4, currentColumn - 4},     // i + 4, j - 4
                              {currentRow + 5, currentColumn - 5},     // i + 5, j - 5
                              {currentRow + 6, currentColumn - 6},     // i + 6, j - 6
                              {currentRow + 7, currentColumn - 7}},    // i + 7, j - 7
                             {{currentRow, currentColumn - 1},         // i, j - 1
                              {currentRow, currentColumn - 2},         // i, j - 2
                              {currentRow, currentColumn - 3},         // i, j - 3
                              {currentRow, currentColumn - 4},         // i, j - 4
                              {currentRow, currentColumn - 5},         // i, j - 5
                              {currentRow, currentColumn - 6},         // i, j - 6
                              {currentRow, currentColumn - 7}},        // i, j - 7
                             {{currentRow, currentColumn + 1},         // i, j + 1
                              {currentRow, currentColumn + 2},         // i, j + 2
                              {currentRow, currentColumn + 3},         // i, j + 3
                              {currentRow, currentColumn + 4},         // i, j + 4
                              {currentRow, currentColumn + 5},         // i, j + 5
                              {currentRow, currentColumn + 6},         // i, j + 6
                              {currentRow, currentColumn + 7}},        // i, j + 7
                             {{currentRow - 1, currentColumn},         // i - 1, j
                              {currentRow - 2, currentColumn},         // i - 2, j
                              {currentRow - 3, currentColumn},         // i - 3, j
                              {currentRow - 4, currentColumn},         // i - 4, j
                              {currentRow - 5, currentColumn},         // i - 5, j
                              {currentRow - 6, currentColumn},         // i - 6, j
                              {currentRow - 7, currentColumn}},        // i - 7, j
                             {{currentRow + 1, currentColumn},         // i + 1, j
                              {currentRow + 2, currentColumn},         // i + 2, j
                              {currentRow + 3, currentColumn},         // i + 3, j
                              {currentRow + 4, currentColumn},         // i + 4, j
                              {currentRow + 5, currentColumn},         // i + 5, j
                              {currentRow + 6, currentColumn},         // i + 6, j
                              {currentRow + 7, currentColumn}}         // i + 7, j
  };


  for (int j = 0; j < 8; j++){
  for (int i = 0; i < 28; i++){
    // make sure the move coordinates are not out of bounds
    if (combinations[j][i][0] < 9 && combinations[j][i][0] > 0 && combinations[j][i][1] < 9 && combinations[j][i][1] > 0){

      if (currentBoard[8 - combinations[j][i][0]][combinations[j][i][1] - 1] == 0) {
        moves[index] = combinations[j][i][0] * 10 + combinations[j][i][1];
        index++;
      }
      else {
        if (isOpponent(piece, 8 - combinations[j][i][0], combinations[j][i][1] - 1)){
          kills[kills_index] = combinations[j][i][0] * 10 + combinations[j][i][1];
          kills_index++;
          int arayIndex = (combinations[j][i][0] - 1) * 8 + combinations[j][i][1] - 1;
          Serial.print("going through opponent cell: ");
          Serial.print(combinations[j][i][0]);
          Serial.print(combinations[j][i][1]);
          Serial.print(", index: ");
          Serial.print(arayIndex);
          Serial.println();
          for (int j = 0; j < 6; j++){
            if (light_coresponding[arayIndex][j] != 0){
              Serial.print("sending command to light up LED: ");
              Serial.print(light_coresponding[arayIndex][j]);
              Serial.println();
              leds[(light_coresponding[arayIndex][j])] = CRGB::Blue;
            }
        }
        Serial.println();
        }
        break;
      }
    }
  }}
  Serial.print("Ran queen");
  Serial.print('\n');
  Serial.print("possible moves for queen: ");
  Serial.print('\n');
  for (int i = 0; i < 64; i++){
    if (moves[i] > 0){
      Serial.print(moves[i]);
      Serial.print(", ");
    }
  }
  Serial.println();
}

void pawnMoves (int piece, int currentRow, int currentColumn) {
  int index = 0;
  int kills_index = 0;

  if (currentRow == 7){
    if (currentBoard[2][currentColumn - 1] == 0){
      moves[index] = 60 + currentColumn;
      index++;
    }
    if (currentBoard[3][currentColumn - 1] == 0){
      moves[index] = 50 + currentColumn;
      index++;
    }    
  }
  else if (currentRow == 2){
    if (currentBoard[5][currentColumn - 1] == 0){
      moves[index] = 30 + currentColumn;
      index++;
    }
    if (currentBoard[4][currentColumn - 1] == 0){
      moves[index] = 40 + currentColumn;
      index++;
    }
  }
  else if (piece < 17){
    if (8 - currentRow + 1 < 8){
      if (currentBoard[8 - currentRow + 1][currentColumn - 1] == 0){
        moves[index] = (currentRow - 1) * 10 + currentColumn;
        index++;
      }
    }
  }
  else {
    if (8 - currentRow - 1 > - 1){
      if (currentBoard[8 - currentRow - 1][currentColumn - 1] == 0){
        moves[index] = (currentRow + 1) * 10 + currentColumn;
        index++;
      }
    }
  }
  
  // possible moves to test for kills
  int combinations[4][2] = { {currentRow - 1, currentColumn + 1},     // i - 1, j + 1
                             {currentRow - 1, currentColumn - 1},     // i - 1, j - 1
                             {currentRow + 1, currentColumn + 1},     // i + 1, j + 1
                             {currentRow + 1, currentColumn - 1},     // i + 1, j - 1
  };

  if (piece < 17) {
    for (int i = 0; i < 2; i++){
      // make sure the move coordinates are not out of bounds
      if (combinations[i][0] < 9 && combinations[i][0] > 0 && combinations[i][1] < 9 && combinations[i][1] > 0){
  
        if (currentBoard[8 - combinations[i][0]][combinations[i][1] - 1] == 0) {
        }
        else {
          if (isOpponent(piece, 8 - combinations[i][0], combinations[i][1] - 1)){
            kills[kills_index] = combinations[i][0] * 10 + combinations[i][1];
            kills_index++;
            int arayIndex = (combinations[i][0] - 1) * 8 + combinations[i][1] - 1;
            Serial.print("going through opponent cell: ");
            Serial.print(combinations[i][0]);
            Serial.print(combinations[i][1]);
            Serial.print(", index: ");
            Serial.print(arayIndex);
            Serial.println();
            for (int j = 0; j < 6; j++){
              if (light_coresponding[arayIndex][j] != 0){
                Serial.print("sending command to light up LED: ");
                Serial.print(light_coresponding[arayIndex][j]);
                Serial.println();
                leds[(light_coresponding[arayIndex][j])] = CRGB::Blue;
              }
          }
          Serial.println();
          }
        }
      }
    }
  }
  else {
    for (int i = 2; i < 4; i++){
      // make sure the move coordinates are not out of bounds
      if (combinations[i][0] < 9 && combinations[i][0] > 0 && combinations[i][1] < 9 && combinations[i][1] > 0){
  
        if (currentBoard[8 - combinations[i][0]][combinations[i][1] - 1] == 0) {
        }
        else {
          if (isOpponent(piece, 8 - combinations[i][0], combinations[i][1] - 1)){
            kills[kills_index] = combinations[i][0] * 10 + combinations[i][1];
            kills_index++;
            int arayIndex = (combinations[i][0] - 1) * 8 + combinations[i][1] - 1;
            Serial.print("going through opponent cell: ");
            Serial.print(combinations[i][0]);
            Serial.print(combinations[i][1]);
            Serial.print(", index: ");
            Serial.print(arayIndex);
            Serial.println();
            for (int j = 0; j < 6; j++){
              if (light_coresponding[arayIndex][j] != 0){
                Serial.print("sending command to light up LED: ");
                Serial.print(light_coresponding[arayIndex][j]);
                Serial.println();
                leds[(light_coresponding[arayIndex][j])] = CRGB::Blue;
              }
          }
          Serial.println();
          }
        }
      }
    }
  }
  Serial.print("Ran pawn");
  Serial.print('\n');
  Serial.print("possible moves for pawn: ");
  Serial.print('\n');
  for (int i = 0; i < 64; i++){
    if (moves[i] > 0){
      Serial.print(moves[i]);
      Serial.print(", ");
    }
  }
  Serial.println();
}