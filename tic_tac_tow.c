#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define BOARD_SIZE 3
#define X 'x'
#define O 'o'

typedef struct{
    int Player_Won;
    int Computer_Won;
    int Draw;
} Scores;

int difficulty;
Scores score = {.Player_Won = 0, .Computer_Won = 0, .Draw = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main(){
    srand(time(0));
    int choice;
    input_difficulty();
    do{
        play_game();
        printf("\n🔄  Do you want to play again? (1  for Yes, 0 for No): ");
        scanf("%d", &choice);
    } while(choice == 1);

    printf("\n🏆 FINAL SCORE BOARD 🏆\n");
    printf("👤 Player Wins   : %d\n", score.Player_Won);
    printf("🤖 Computer Wins : %d\n", score.Computer_Won);
    printf("🤝 Draws         : %d\n", score.Draw);
    
    return 0;
}


void play_game(){
     char board[BOARD_SIZE][BOARD_SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
  };
   char current_player = rand() % 2 == 0 ? X : O;

   print_board(board);
   while(1){
     if (current_player == X) {
      player_move(board);
      print_board(board);
      if (check_win(board, X)) {
        score.Player_Won++;
        print_board(board);
        printf("\n🎉🎉 CONGRATULATIONS! 🎉🎉\n");
        printf("🏆 You Won The Game! 🏆\n");
        break;
      }
      current_player = O;
    } else {
      computer_move(board);
      print_board(board);
      if (check_win(board, O)) {
        score.Computer_Won++;
        print_board(board);
        printf("I won 🥳!!! But you played well...👏🫡");
        break;
      }
      current_player = X;
    }

    if (check_draw(board)) {
      score.Draw++;
      print_board(board);
      printf("\nIt's a draw!");
      break;
    }
  }
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
  return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == ' ';
}

void player_move(char Board[BOARD_SIZE][BOARD_SIZE]){
    int counter = 0,x,y;
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(Board[i][j] == ' '){
                counter++;
                x = i;
                y = j;
            }
        }
    }

if(counter == 1){
    Board[x][y] = X;
    return;
}

    int row, col;
    do{
        printf("\n 🎯 Enter your move (row and column): ");
        scanf("%d %d", &row, &col);
        row--;
        col--;
    } while(!is_valid_move(Board, row, col));
    Board[row][col] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = O;
        if (check_win(board, O)) {
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = X;
        if (check_win(board, X)) {
          board[i][j] = O;
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  // GOD Mode
  if (difficulty == 2) {
    if (board[1][1] == ' ') {
      board[1][1] = O;
      return;
    }

    int corner[4][2] = {
      {0, 0},
      {0, 2},
      {2, 0},
      {2, 2}
    };
    for (int i = 0; i < 4; i++) {
      if (board[corner[i][0]][corner[i][1]] == ' ') {
        board[corner[i][0]][corner[i][1]] = O;
        return;
      }
    }
  }

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = O;
        return;
      }
    }
  }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
      return 1;
    }

    if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
      return 1;
    }
  }

  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
      (board[2][0] == player && board[1][1] == player && board[0][2] == player)) {
    return 1;
  }
  return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        return 0;
      }
    }
  }
  return 1;
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
  clear_screen();
  printf("Score - Player_Won: 👑  %d  👑 , Computer_Won: 🤖  %d  🤖 , Draw: 🤝  %d  🤝 ", score.Player_Won, score.Computer_Won, score.Draw);
  printf("\n 🎮 ================================ 🎮\n");
  printf("      TIC TAC TOE GAME\n");
  printf("🎮 ================================ 🎮\n");

  for (int i = 0 ; i < BOARD_SIZE; i++) {
    printf("\n");
    for (int j = 0; j < BOARD_SIZE; j++) {
      printf(" %c ", board[i][j]);
      if (j < BOARD_SIZE - 1) {
        printf("|");
      }
    }
    if (i < BOARD_SIZE - 1) {
      printf("\n---+---+---");
    }
  }
  printf("\n\n");
}

void input_difficulty() {
  while (1) {
    printf("\n⚙️ Select Difficulty Level:\n");
    printf("1. 🙂 EASY\n");
    printf("2. 👑 HARD \n");
    printf("Enter your choice 😎  : ");
    scanf("%d", &difficulty);

    if (difficulty != 1 && difficulty != 2) {
      printf("\nIncorrect choice enter (1/2)!!🤔");
    } else {
      break;
    }
  };
}

void clear_screen() {
  #ifdef _Win32
    system("cls");
  #else
    system("clear");
  #endif    
}
