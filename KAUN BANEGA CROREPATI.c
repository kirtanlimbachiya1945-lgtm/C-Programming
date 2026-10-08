#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#include<time.h>

#define TOTAL_QUESTIONS 15
#pragma comment(lib, "winmm.lib")

typedef struct
{
    char difficulty[20];
    char question[200];
    char optionA[100];
    char optionB[100];
    char optionC[100];
    char optionD[100];
    char correctAnswer;

} Question;

Question questions[TOTAL_QUESTIONS];


char playerName[50];
int score = 0;
int categoryChoice;

int prizeMoney[15] = {
    1000,
    2000,
    5000,
    10000,
    20000,
    40000,
    80000,
    160000,
    320000,
    640000,
    1250000,
    2500000,
    5000000,
    10000000,
    70000000
};


void showMenu();
void showRules();
void startGame();
void showPrizeLadder();
void askQuestion();
void loadQuestions();
void startTimer(int seconds);
void displayQuestion();
void checkAnswer();
int getTimeLimit(int questionNo);
void useFiftyFifty(int currentQuestion);
void useAudiencePoll(int currentQuestion);
void usePhoneAFriend(int currentQuestion);
int useSkipQuestion();
void useLifeline();
void saveHighScore();
void showLeaderboard();
void showLifelines();
void startQuiz();

int safeLevel1 = 4;   // Question 5
int safeLevel2 = 9;   // Question 10

int fiftyFifty = 1;
int audiencePoll = 1;
int phoneAFriend = 1;
int skipQuestion = 1;


int main()
{

    int choice;

    while (1)
    {

        printf("\n==================================");
        printf("\n🎮 KAUN BANEGA CROREPATI 🎮");
        printf("\n==================================");

        printf("\n1. Start Game");
        printf("\n2. Rules");
        printf("\n3. Leaderboard");
        printf("\n4. Exit");

        printf("\n\nEnter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1 :
                startGame();
                break;
            case 2 :
                showRules();
                break;
                case 3:
                showLeaderboard();
                break;
            case 4 :
                printf("\nThank You For Playing...Hope You Enjoy The Game!!! ");
                exit(0);
            default :
                printf("\nInvalid Choice!!!!!");
        } 
    }
    return 0;
}

void startGame()
{
    fiftyFifty = 1;
    audiencePoll = 1;
    phoneAFriend = 1;
    skipQuestion = 1;

    printf("\nEnter Player Name :");
    scanf("%s",playerName);

    printf("\nSelect Category");
    printf("\n1. Programming");
    printf("\n2. Sports");
    printf("\n3. History");
    printf("\n4. Science");
    printf("\n5. General Knowledge");

    printf("\nEnter Choice: ");
    scanf("%d",&categoryChoice);

    showPrizeLadder();

    printf("\nWelcome %s!",playerName);

    printf("\n\nGame Starting Soon....\n");

    PlaySound(TEXT("start.mp3"), NULL, SND_ASYNC);

    loadQuestions();
    startQuiz();

}

void showRules()
{
    printf("\n\n========== RULES ==========");

    printf("\n1. Each question has 4 options.");
    printf("\n2. Only one option is correct.");
    printf("\n3. Correct answer wins money.");
    printf("\n4. Wrong answer ends the game.");
    printf("\n5. Lifelines will be added later.");

    printf("\n===========================\n");
}

void showPrizeLadder()
{
    printf("\n\n================================");
    printf("\n🏆 KBC PRIZE LADDER 🏆");
    printf("\n================================");

    for(int i = 14; i >= 0; i--)
    {
        printf("\nQ%-2d -> Rs %d", i + 1, prizeMoney[i]);
    }

    printf("\n================================\n");
}

void loadQuestions()
{
    char filename[30];

switch(categoryChoice)
{
    case 1:
        strcpy(filename,"programming.txt");
        break;

    case 2:
        strcpy(filename,"sports.txt");
        break;

    case 3:
        strcpy(filename,"history.txt");
        break;

    case 4:
        strcpy(filename,"science.txt");
        break;

    case 5:
        strcpy(filename,"gk.txt");
        break;
    default:
    printf("\nInvalid Category!");
    return;
}

FILE *fp = fopen(filename,"r");

    if(fp == NULL)
    {
    printf("\nError opening file: %s", filename);
    return;
    }

    for(int i=0;i<TOTAL_QUESTIONS;i++)
    {
        fgets(questions[i].difficulty,20,fp);
        questions[i].difficulty[strcspn(questions[i].difficulty,"\n")] = '\0';


        fgets(questions[i].question,200,fp);
        fgets(questions[i].optionA,100,fp);
        fgets(questions[i].optionB,100,fp);
        fgets(questions[i].optionC,100,fp);
        fgets(questions[i].optionD,100,fp);

        fscanf(fp," %c",&questions[i].correctAnswer);

        char temp[10];
        fgets(temp,sizeof(temp),fp);
        fgets(temp,sizeof(temp),fp);  
    }

    fclose(fp);
}

int getTimeLimit(int questionNo)
{
    if(questionNo <= 5)
        return 15;

    if(questionNo <= 10)
        return 30;

    return 60;
}

void startQuiz()
{
    score = 0;
    char answer;

    for(int i=0;i<TOTAL_QUESTIONS;i++)
    {
        printf("\n\n================================");
        printf("\nQuestion %d / %d", i+1, TOTAL_QUESTIONS);
        printf("\nPrize Money : Rs %d", prizeMoney[i]);
        printf("\nTime Limit : %d Seconds", getTimeLimit(i+1));
        printf("\nDifficulty : %s", questions[i].difficulty);
        printf("\n================================");

        printf("\n%s",questions[i].question);

        printf("A. %s",questions[i].optionA);
        printf("B. %s",questions[i].optionB);
        printf("C. %s",questions[i].optionC);
        printf("D. %s",questions[i].optionD);

        //startTimer(getTimeLimit(i+1));

        printf("\nL. Use Lifeline");

        printf("\nAnswer: ");
        scanf(" %c",&answer);

        answer = toupper(answer);

    if(answer == 'L')
{
    showLifelines();

    int lifeChoice;

    printf("\nChoose Lifeline: ");
    scanf("%d",&lifeChoice);

    if(lifeChoice == 1)
    {
    useFiftyFifty(i);
    }
    else if(lifeChoice == 2)
    {
    useAudiencePoll(i);
    }
    else if(lifeChoice == 3)
    {
    usePhoneAFriend(i);
    }
    else if(lifeChoice == 4)
    {
    if(useSkipQuestion())
    {
        continue;
    }
    }
    i--;
    continue;
}

        if(answer == questions[i].correctAnswer)
        {
            PlaySound(TEXT("correct.mp3"), NULL, SND_ASYNC);

            printf("\nCorrect!");


            score = prizeMoney[i];

            printf("\nWon Rs %d\n",
                   prizeMoney[i]);
        }
        else
        {
        printf("\nWrong Answer!");

        PlaySound(TEXT("wrong.wav"), NULL, SND_ASYNC);

    if(i >= safeLevel2)
    {
    score = prizeMoney[safeLevel2];
    printf("\n🏆 Safe Level 2 Reached!");
    }
    else if(i >= safeLevel1)
    {
    score = prizeMoney[safeLevel1];
    printf("\n🏆 Safe Level 1 Reached!");
    }
    else
    {
    score = 0;
    }      
        break;
    }
}

    printf("\n\n========================");
    printf("\n\nGame Over");
    printf("\nFINAL SCOREBOARD");
    printf("\n========================");
    printf("\nPlayer : %s", playerName);
    printf("\nWinning : Rs %d", score);
    printf("\n========================");

    saveHighScore();
    
}

void startTimer(int seconds)
{
    while(seconds > 0)
    {
        printf("\rTime Left: %d ",seconds);
        fflush(stdout);
        sleep(1);
        seconds--;
    }

    printf("\nTime Up!");
}

void showLifelines()
{
    printf("\n\n===== LIFELINES =====");

    if(fiftyFifty)
        printf("\n1. 50-50");

    if(audiencePoll)
        printf("\n2. Audience Poll");

    if(phoneAFriend)
        printf("\n3. Phone A Friend");

    if(skipQuestion)
        printf("\n4. Skip Question");

    printf("\n=====================");
}

void saveHighScore()
{
    FILE *fp = fopen("leaderboard.txt","a");

    if(fp != NULL)
    {
        fprintf(fp,"%s %d\n",playerName,score);
        fclose(fp);
    }
}

void useFiftyFifty(int currentQuestion)
{
    if(fiftyFifty == 0)
    {
        printf("\n50-50 already used!");
        return;
    }

    fiftyFifty = 0;

    printf("\n\n***** 50-50 Lifeline Used *****");

    char correct = questions[currentQuestion].correctAnswer;

    printf("\n");

    if(correct == 'A')
    {
        printf("\nA. %s", questions[currentQuestion].optionA);
        printf("\nC. %s", questions[currentQuestion].optionC);
    }
    else if(correct == 'B')
    {
        printf("\nB. %s", questions[currentQuestion].optionB);
        printf("\nD. %s", questions[currentQuestion].optionD);
    }
    else if(correct == 'C')
    {
        printf("\nC. %s", questions[currentQuestion].optionC);
        printf("\nA. %s", questions[currentQuestion].optionA);
    }
    else
    {
        printf("\nD. %s", questions[currentQuestion].optionD);
        printf("\nB. %s", questions[currentQuestion].optionB);
    }

    printf("\n");
}

void useAudiencePoll(int currentQuestion)
{

    if(audiencePoll == 0)
    {

        printf("\nAudience Poll Is Already Used!!!");
        return;
    }

    audiencePoll = 0;

    printf("\n\n===== AUDIENCE POLL =====");

    char correct = questions[currentQuestion].correctAnswer;

    if(correct == 'A')
    {

        printf("\nA : 75%%");
        printf("\nB : 15%%");
        printf("\nC : 7%%");
        printf("\nD : 3%%");

    }

        else if(correct == 'B')
    {

        printf("\nA : 4%%");
        printf("\nB : 78%%");
        printf("\nC : 5%%");
        printf("\nD : 13%%");

    }
    else if(correct == 'C')
    {

        printf("\nA : 15%%");
        printf("\nB : 2%%");
        printf("\nC : 77%%");
        printf("\nD : 6%%");

    }
    else
    {

        printf("\nA : 1%%");
        printf("\nB : 4%%");
        printf("\nC : 3%%");
        printf("\nD : 92%%");

    }

    printf("\n=========================\n");
}
    
void usePhoneAFriend(int currentQuestion)
{
    if(phoneAFriend == 0)
    {
        printf("\nPhone A Friend Is Already Used!!!");
        return;
    }

    phoneAFriend = 0;

    printf("\n\n📞 Calling Friend... 📞");

    int chance = rand() % 100;

    if(chance < 80)
    {
        printf("\nFriend thinks answer is: %c",
               questions[currentQuestion].correctAnswer);
    }
    else
    {
        printf("\nFriend is confused and suggests another option.");
    }

    printf("\n");
}

int useSkipQuestion()
{
    if(skipQuestion == 0)
    {
        printf("\nSkip Question already used!!!");
        return 0;
    }

    skipQuestion = 0;

    printf("\nQuestion Skipped Successfully!");

    return 1;
}

void showLeaderboard()
{
    FILE *fp = fopen("leaderboard.txt","r");

    if(fp == NULL)
    {
        printf("\nNo Leaderboard Data Found!");
        return;
    }

    char name[50];
    int amount;

    printf("\n\n===== LEADERBOARD =====\n");

    while(fscanf(fp,"%s %d",name,&amount)==2)
    {
        printf("%s - Rs %d\n",name,amount);
    }

    fclose(fp);
}