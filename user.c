#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX_USERS 1000
#define FILE_NAME "users.dat"

typedef struct {
    char username[50];
    char password[50];
    char email[100];
    char phone[15];
    int age;
    int loginCount;
} User;

User users[MAX_USERS];
int userCount = 0;

/* Function Prototypes */
void loadUsers();
void saveUsers();

void registerUser();
int loginUser();

void searchUser();
void viewUsers();

void inputPassword(char password[]);
void clearInputBuffer();
int usernameExists(char username[]);

void line();

/* ---------------- MAIN ---------------- */

void deleteUser();
void changePassword(int userIndex);
void editProfile(int userIndex);

int isValidEmail(char email[]);
int isValidPhone(char phone[]);
void userDashboard(int userIndex);



int main() {

    int option;

    loadUsers();

    while (1) {

        line();
        printf("      USER MANAGEMENT SYSTEM\n");
        line();

        printf("1. Register User\n");
        printf("2. Login User\n");
        printf("3. Search User\n");
        printf("4. View All Users\n");
        printf("5. Exit\n");

        line();

        printf("Select Option: ");
        scanf("%d", &option);

        switch (option) {

            case 1:
                registerUser();
                break;

            case 2: {
                int userIndex = loginUser();

                if (userIndex != -1) {

                    users[userIndex].loginCount++;
                    saveUsers();

                    printf("\nLogin Successful!\n");
                    printf("Welcome %s\n",
                           users[userIndex].username);

                    printf("Total Logins: %d\n",
                           users[userIndex].loginCount);
                }
                else {
                    printf("\nInvalid Username or Password!\n");
                }

                break;
            }

            case 3:
                searchUser();
                break;

            case 4:
                viewUsers();
                break;

            case 5:
                saveUsers();
                printf("\nData Saved Successfully.\n");
                printf("Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid Option!\n");
        }

        printf("\nPress any key to continue...");
        getch();
        printf("\n\n");
    }

    return 0;
}

/* ---------------- UI ---------------- */

void line() {
    printf("========================================\n");
}

/* ---------------- FILE HANDLING ---------------- */

void loadUsers() {

    FILE *fp;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        return;
    }

    userCount = fread(users,
                      sizeof(User),
                      MAX_USERS,
                      fp);

    fclose(fp);
}

void saveUsers() {

    FILE *fp;

    fp = fopen(FILE_NAME, "wb");

    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    fwrite(users,
           sizeof(User),
           userCount,
           fp);

    fclose(fp);
}

/* ---------------- PASSWORD INPUT ---------------- */

void inputPassword(char password[]) {

    int i = 0;
    char ch;

    while (1) {

        ch = getch();

        if (ch == 13) {

            password[i] = '\0';
            break;
        }

        else if (ch == 8 && i > 0) {

            i--;
            printf("\b \b");
        }

        else if (ch != 8 && i < 49) {

            password[i++] = ch;
            printf("*");
        }
    }

    printf("\n");
}

/* ---------------- REGISTER ---------------- */

void registerUser() {

    User newUser;

    if (userCount >= MAX_USERS) {

        printf("Maximum User Limit Reached!\n");
        return;
    }

    printf("\nEnter Username: ");
    scanf("%49s", newUser.username);

    if (usernameExists(newUser.username)) {

        printf("Username Already Exists!\n");
        return;
    }

    printf("Enter Password: ");
    inputPassword(newUser.password);

    printf("Enter Email: ");
    scanf("%99s", newUser.email);

    printf("Enter Phone: ");
    scanf("%14s", newUser.phone);

    printf("Enter Age: ");
    scanf("%d", &newUser.age);

    newUser.loginCount = 0;

    users[userCount] = newUser;
    userCount++;

    saveUsers();

    printf("\nUser Registered Successfully!\n");
}

/* ---------------- LOGIN ---------------- */

int loginUser() {

    char username[50];
    char password[50];

    printf("\nEnter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    inputPassword(password);

    for (int i = 0; i < userCount; i++) {

        if (strcmp(users[i].username,
                   username) == 0 &&
            strcmp(users[i].password,
                   password) == 0) {

            return i;
        }
    }

    return -1;
}

/* ---------------- SEARCH USER ---------------- */

void searchUser() {

    char username[50];
    int found = 0;

    printf("\nEnter Username To Search: ");
    scanf("%49s", username);

    for (int i = 0; i < userCount; i++) {

        if (strcmp(users[i].username,
                   username) == 0) {

            line();

            printf("USER FOUND\n");

            line();

            printf("Username    : %s\n",
                   users[i].username);

            printf("Email       : %s\n",
                   users[i].email);

            printf("Phone       : %s\n",
                   users[i].phone);

            printf("Age         : %d\n",
                   users[i].age);

            printf("Login Count : %d\n",
                   users[i].loginCount);

            line();

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User Not Found!\n");
    }
}

/* ---------------- VIEW USERS ---------------- */

void viewUsers() {

    if (userCount == 0) {

        printf("\nNo Users Registered!\n");
        return;
    }

    line();
    printf("REGISTERED USERS\n");
    line();

    for (int i = 0; i < userCount; i++) {

        printf("%d. %s\n",
               i + 1,
               users[i].username);
    }

    line();
    printf("Total Users: %d\n",
           userCount);
}

/* ---------------- UTILITIES ---------------- */

int usernameExists(char username[]) {

    for (int i = 0; i < userCount; i++) {

        if (strcmp(users[i].username,
                   username) == 0) {

            return 1;
        }
    }

    return 0;
}

void clearInputBuffer() {

    while (getchar() != '\n');
}

int isValidEmail(char email[]) {

    int atCount = 0;

    for(int i = 0; email[i] != '\0'; i++) {

        if(email[i] == '@')
            atCount++;
    }

    return (atCount == 1);
}

int isValidPhone(char phone[]) {

    if(strlen(phone) != 10)
        return 0;

    for(int i = 0; i < 10; i++) {

        if(phone[i] < '0' || phone[i] > '9')
            return 0;
    }

    return 1;
}

void deleteUser() {

    char username[50];

    printf("\nEnter Username To Delete: ");
    scanf("%49s", username);

    for(int i = 0; i < userCount; i++) {

        if(strcmp(users[i].username, username) == 0) {

            for(int j = i; j < userCount - 1; j++) {

                users[j] = users[j + 1];
            }

            userCount--;

            saveUsers();

            printf("User Deleted Successfully!\n");
            return;
        }
    }

    printf("User Not Found!\n");
}

void changePassword(int userIndex) {

    char oldPassword[50];
    char newPassword[50];

    printf("\nEnter Current Password: ");
    inputPassword(oldPassword);

    if(strcmp(oldPassword,
              users[userIndex].password) != 0) {

        printf("Wrong Password!\n");
        return;
    }

    printf("Enter New Password: ");
    inputPassword(newPassword);

    strcpy(users[userIndex].password,
           newPassword);

    saveUsers();

    printf("Password Changed Successfully!\n");
}

void editProfile(int userIndex) {

    printf("\nCurrent Email: %s\n",
           users[userIndex].email);

    printf("Current Phone: %s\n",
           users[userIndex].phone);

    do {

        printf("New Email: ");
        scanf("%49s",
              users[userIndex].email);

    } while(!isValidEmail(users[userIndex].email));

    do {

        printf("New Phone: ");
        scanf("%14s",
              users[userIndex].phone);

    } while(!isValidPhone(users[userIndex].phone));

    saveUsers();

    printf("Profile Updated Successfully!\n");
}

void userDashboard(int userIndex) {

    int choice;

    while(1) {

        line();

        printf("USER DASHBOARD\n");

        line();

        printf("1. View Profile\n");
        printf("2. Change Password\n");
        printf("3. Edit Profile\n");
        printf("4. Logout\n");

        line();

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:

                printf("\nUsername : %s\n",
                       users[userIndex].username);

                printf("Email    : %s\n",
                       users[userIndex].email);

                printf("Phone    : %s\n",
                       users[userIndex].phone);

                printf("Age      : %d\n",
                       users[userIndex].age);

                printf("Logins   : %d\n",
                       users[userIndex].loginCount);

                break;

            case 2:
                changePassword(userIndex);
                break;

            case 3:
                editProfile(userIndex);
                break;

            case 4:
                return;

            case 5:
                deleteUser();
                break;

            case 6:
                saveUsers();
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }
}