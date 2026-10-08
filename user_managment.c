#include<stdio.h>
#include<string.h>

#define MAX_USERS 10000

typedef struct {

    char username[50];
    char password[50];

    char email[100];
    char phone[15];

    int age;

} User;

User users[MAX_USERS];
int userCount = 0;

void registerUser();
int loginUser();
void viewUser();
void searchUser();
void deleteUser();
void statistics();
void saveToFile();
void loadFromFile();

int main() {

    int option;

    loadFromFile(); 

    while (1) {

    printf("Welcome to the User Management System!\n");
    printf("Please select an option:\n");
    printf("1. Register User\n");
    printf("2. Login User\n");
    printf("3. Search User\n");
    printf("4. View All Users\n");
    printf("5. Delete User\n");
    printf("6. Statistics\n");
    printf("7. Exit\n");
    printf("Select an option: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            registerUser();
            printf("Registering user...\n");
            break;
        case 2:{
            printf("Logging in user...\n");
            int userIndex = loginUser();
            if (userIndex != -1) {
                printf("Login successful! Welcome, %s!\n", users[userIndex].username);
                viewUser();
            } else {
                printf("Login failed. Invalid username or password.\n");
            }
            break;
        }

        case 3:

            searchUser();
            break;

        case 4:
            viewUser();
            break;

        case 5:
            deleteUser();
            break;

        case 6:
            statistics();
            break;

        case 7:
            printf("Exiting the system. Goodbye!\n");
            return 0;

        default:
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}


void registerUser(){
    if (userCount >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    printf("Enter Your username: ");
    scanf("%49s", users[userCount].username);

    printf("Enter Your password: ");
    scanf("%49s", users[userCount].password);

    printf("Enter Your Email Adderess: ");
    scanf("%99s", users[userCount].email);

    printf("Enter Your Phone Number: ");
    scanf("%14s", users[userCount].phone);

    printf("Enter Your Age: ");
    scanf("%d", &users[userCount].age);
    

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, users[userCount].username) == 0) {
            printf("Username already exists. Please choose a different username.\n");
            return;
        }
    }

    userCount++;

    printf("User registered successfully!\n");
    saveToFile();

}

int loginUser(){
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i; 
        }
    }

    return -1; 
}

void viewUser() {
    printf("\n----- Registered Users -----\n");

    if (userCount == 0) {
        printf("No users registered.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        printf("\nUser %d\n", i + 1);

        printf("Username : %s\n", users[i].username);
        printf("Email    : %s\n", users[i].email);
        printf("Phone NO.    : %s\n", users[i].phone);
        printf("Age      : %d\n", users[i].age);

        
    }

} 

void searchUser() {

    char username[50];
    int found = 0;

    printf("Enter username to search: ");
    scanf("%49s", username);

    for(int i = 0; i < userCount; i++) {

        if(strcmp(users[i].username, username) == 0) {

            printf("\nUser Found!\n");
            printf("Username: %s\n", users[i].username);

            found = 1;
            break;
        }
    }

    if(!found) {
        printf("User not found!\n");
    }
}

void deleteUser() {

    char username[50];

    printf("Enter username to delete: ");
    scanf("%49s", username);

    for(int i = 0; i < userCount; i++) {

        if(strcmp(users[i].username, username) == 0) {

            for(int j = i; j < userCount - 1; j++) {

                users[j] = users[j + 1];
            }

            userCount--;

            printf("User deleted successfully!\n");
            saveToFile();
            return;
        }
    }

    printf("User not found!\n");
}

void statistics() {

    printf("\nTotal Users: %d\n", userCount);

    if(userCount == 0)
        return;

    int totalAge = 0;

    for(int i = 0; i < userCount; i++) {

        totalAge += users[i].age;
    }

    printf("Average Age: %.2f\n",
           (float)totalAge / userCount);
}

void loadFromFile() {
    FILE *fp = fopen("Users.txt", "r");

    if (fp == NULL) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }

    userCount = 0;

    while (fscanf(fp, "%49s %49s %99s %14s %d",
                  users[userCount].username,
                  users[userCount].password,
                  users[userCount].email,
                  users[userCount].phone,
                  &users[userCount].age) == 5) {
        userCount++;
    }

    fclose(fp);
}

void saveToFile() {
    FILE *fp = fopen("Users.txt", "w");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(fp, "%s %s %s %s %d\n",
                users[i].username,
                users[i].password,
                users[i].email,
                users[i].phone,
                users[i].age);
    }

    fclose(fp);
}