#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

int gameOver;
int score;
int highScore = 0;
FILE *fp;

int x, y;
int fruitX, fruitY;

int tailX[500];
int tailY[500];
int tailLength;
int speed;

enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum Direction dir;

void setup();
void draw();
void hideCursor();
void color(int c);
void loading();
void menu();
void input();
void logic();
void help();
void gotoxy(int x, int y);
void gameOverScreen();
void loadHighScore();
void saveHighScore();
void chooseDifficulty();

void setup()
{
    gameOver = 0;

    dir = RIGHT;

    x = WIDTH / 2;
    y = HEIGHT / 2;

    do
    {
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    }
    while(fruitX == x && fruitY == y);

    score = 0;

    tailLength = 0;
}

void draw()
{
    gotoxy(0,0);

    int i, j, k;

    color(11);

    // Top Border
    for(i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\n");

    for(i = 0; i < HEIGHT; i++)
    {
        for(j = 0; j <= WIDTH; j++)
        {
            if(j == 0)
                printf("#");

            if(i == y && j == x)
            {
                color(10);
                printf("O");     // Snake Head
                color(11);
            }

            else if(i == fruitY && j == fruitX)
            {
                color(12);
                printf("*");     // Food
                color(11);
            }

            else
            {
                int print = 0;

                for(k = 0; k < tailLength; k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        color(2);
                        printf("o");     // Tail
                        color(11);
                        print = 1;
                    }
                }

                if(!print)
                    printf(" ");
            }

            if(j == WIDTH)
                printf("#");
        }

        printf("\n");
    }

    for(i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\n\n");

    printf("Score : %d\n", score);
    printf("High Score : %d\n", highScore);
}

void hideCursor()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursor;

    cursor.dwSize = 100;
    cursor.bVisible = FALSE;

    SetConsoleCursorInfo(console, &cursor);
}

void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void loading()
{
    int i;

    printf("\nLoading");

    for(i=0;i<30;i++)
    {
        printf("%c",219);
        Sleep(50);
    }

    printf("\n");
}

void chooseDifficulty()
{
    int ch;

    system("cls");

    printf("=================================\n");
    printf("       SELECT DIFFICULTY\n");
    printf("=================================\n\n");

    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");

    printf("\nChoose : ");
    scanf("%d",&ch);

    switch(ch)
    {
        case 1:
            speed = 150;
            break;

        case 2:
            speed = 100;
            break;

        case 3:
            speed = 60;
            break;

        default:
            speed = 100;
    }
}

void menu()
{
    system("cls");

    color(11);

    printf("=================================\n");
    printf("        SNAKE GAME\n");
    printf("=================================\n\n");

    printf("1. Play Game\n");
    printf("2. Help\n");
    printf("3. Exit\n");

    printf("\nChoose : ");
}

void input()
{
    if(kbhit())
    {
        switch(getch())
        {
            case 'a':
            case 'A':
                if(dir != RIGHT)
                    dir = LEFT;
                break;

            case 'd':
            case 'D':
                if(dir != LEFT)
                    dir = RIGHT;
            break;

            case 'w':
            case 'W':
                if(dir != DOWN)
                    dir = UP;
            break;

            case 's':
            case 'S':
                if(dir != UP)
                    dir = DOWN;
            break;

            case 'p':
            case 'P':
                printf("\n\nGame Paused...");
                getch();
                break;

            case 'x':
            case 'X':
                gameOver = 1;
                break;
        }
    }
}

void logic()
{
    int i;

    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for(i = 1; i < tailLength; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {
        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;

        default:
            break;
    }

    // Wall Collision
    if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;

    // Food
    if(x == fruitX && y == fruitY)
    {
        score += 10;

        do
        {
            fruitX = rand() % WIDTH;
            fruitY = rand() % HEIGHT;
        }
        while(fruitX == x && fruitY == y);

        if(tailLength < 499)
        tailLength++;
    }

    // Self Collision
    for(i = 0; i < tailLength; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }
}

void loadHighScore()
{
    fp = fopen("highscore.txt","r");

    if(fp == NULL)
    {
        highScore = 0;
        return;
    }

    fscanf(fp,"%d",&highScore);

    fclose(fp);
}

void saveHighScore()
{
    if(score > highScore)
    {
        highScore = score;

        fp = fopen("highscore.txt","w");

        fprintf(fp,"%d",highScore);

        fclose(fp);
    }
}

void gameOverScreen()
{
    system("cls");

    printf("\n\n");
    printf("=================================\n");
    printf("         GAME OVER\n");
    printf("=================================\n\n");

    printf("Final Score : %d\n", score);

    printf("\nPress any key...");
    getch();
}

void help()
{
    system("cls");

    printf("Controls\n\n");

    printf("W = UP\n");
    printf("S = DOWN\n");
    printf("A = LEFT\n");
    printf("D = RIGHT\n");

    printf("\nP = Pause");
    printf("\nX = Exit Game");

    printf("\n\nPress any key...");
    getch();
}

int main()
{
    int choice;

    srand(time(NULL));

    hideCursor();
    loadHighScore();
    loading();

    while(1)
    {
        menu();

        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                setup();
                chooseDifficulty();
                while(!gameOver)
                {
                draw();
                input();
                logic();
                Sleep(100);
                }
                saveHighScore();
                gameOverScreen();
                break;

            case 2:
                help();
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid Choice");
                Sleep(1000);
        }
    }

    return 0;
}