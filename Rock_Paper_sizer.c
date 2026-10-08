//gcc Rock_Paper_sizer.c -o game
//.\Rock_Paper_sizer

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define RED 12
#define GREEN 10
#define YELLOW 14
#define CYAN 11
#define WHITE 15

void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main()
{
    srand(time(0));

    char player_name[50];
    int player_choice, computer_choice;
    int player_wins = 0;
    int computer_wins = 0;
    int ties = 0;
    int total_games = 0;
    int mode, wins_needed;

    char *choices[] =
    {
        "Rock",
        "Paper",
        "Scissors"
    };

    color(CYAN);
    printf("=====================================\n");
    printf("     ROCK PAPER SCISSORS GAME\n");
    printf("=====================================\n\n");

    color(WHITE);
    printf("Enter Your Name: ");
    scanf("%s", player_name);

    printf("\nChoose Game Mode:\n");
    printf("1. Best of 3\n");
    printf("2. Best of 5\n");
    printf("Enter Choice: ");
    scanf("%d", &mode);

    if(mode == 1)
        wins_needed = 2;
    else
        wins_needed = 3;

    while(player_wins < wins_needed &&
          computer_wins < wins_needed)
    {
        color(YELLOW);

        printf("\n-------------------------------------\n");
        printf("0 = Rock\n");
        printf("1 = Paper\n");
        printf("2 = Scissors\n");
        printf("-------------------------------------\n");

        printf("%s, Enter Your Choice: ", player_name);
        scanf("%d", &player_choice);

        if(player_choice < 0 || player_choice > 2)
        {
            color(RED);
            printf("Invalid Choice! Try Again.\n");
            continue;
        }

        computer_choice = rand() % 3;

        printf("\n%s Chose : %s\n",
               player_name,
               choices[player_choice]);

        printf("Computer Chose : %s\n",
               choices[computer_choice]);

        total_games++;

        if(player_choice == computer_choice)
        {
            color(YELLOW);
            printf("\nIt's a Tie!\n");
            ties++;
        }
        else if((player_choice == 0 && computer_choice == 2) ||
                (player_choice == 1 && computer_choice == 0) ||
                (player_choice == 2 && computer_choice == 1))
        {
            color(GREEN);
            printf("\n%s Wins This Round!\n",
                   player_name);

            player_wins++;
        }
        else
        {
            color(RED);
            printf("\nComputer Wins This Round!\n");

            computer_wins++;
        }

        color(CYAN);

        printf("\n========== SCOREBOARD ==========\n");
        printf("%s Wins : %d\n",
               player_name,
               player_wins);

        printf("Computer Wins : %d\n",
               computer_wins);

        printf("Ties : %d\n",
               ties);

        printf("================================\n");
    }

    color(CYAN);

    printf("\n\n=====================================\n");
    printf("           MATCH SUMMARY\n");
    printf("=====================================\n");

    printf("Player Name        : %s\n",
           player_name);

    printf("Total Games Played : %d\n",
           total_games);

    printf("%s Wins           : %d\n",
           player_name,
           player_wins);

    printf("Computer Wins      : %d\n",
           computer_wins);

    printf("Ties               : %d\n",
           ties);

    printf("=====================================\n");

    if(player_wins > computer_wins)
    {
        color(GREEN);

        printf("\n🏆 CONGRATULATIONS %s!\n",
               player_name);

        printf("YOU WON THE MATCH!\n");
    }
    else
    {
        color(RED);

        printf("\n🤖 COMPUTER WON THE MATCH!\n");
    }

    color(WHITE);

    printf("\n\nThank You For Playing!\n");

    return 0;
}