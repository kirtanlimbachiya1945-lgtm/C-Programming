#include<stdio.h>
#include<math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <string.h>  // Add these headers at the top
 // colored output on Windows

void print_menu() {
    printf("\n======== 🖩🖩 Scientific Calculator Menu 🖩🖩 ========\n");
    printf("1. Addition ➕\n");
    printf("2. Subtraction ➖\n");
    printf("3. Multiplication ✖️\n");
    printf("4. Division ➗\n");
    printf("5. Power 🔼\n");
    printf("6. Square Root √️⃣\n");
    printf("7. Percentage 💯\n");
    printf("8. Factorial ❗\n");
    printf("9. Modulus 🧮\n");
    printf("10. Average ⚖️\n");
    printf("11. Even/Odd Check 🔢\n");
    printf("12. Prime Number Check 🎯\n");
    printf("13. Temperature Converter 🌡️\n");
    printf("14. Sin(x) 🌀\n");
    printf("15. Cos(x) 🌙\n");
    printf("16. Tan(x) 🌊\n");
    printf("17. Sec(x) ☀️\n");
    printf("18. Cosec(x) 🌌\n");
    printf("19. Cot(x) 🌐\n");
    printf("20. Sin Inverse 🌀\n");
    printf("21. Cos Inverse ⚡\n");
    printf("22. Tan Inversen ♾️\n");
    printf("23. Log Base 10 🔮\n");
    printf("24. Natural Log (ln) 🌱\n");
    printf("25. Exponential (e^x) 🔺\n");
    printf("26. Square (x^2) 🛸\n");
    printf("27. Cube (x^3) 🚀\n");
    printf("28.Age Calculator 🎂\n");
    printf("0. Exit 🚪\n");
    
}

void saveHistory(char operation[], double result)
{
    FILE *fp = fopen("history.txt", "a");

    if(fp != NULL)
    {
        fprintf(fp, "%s = %.2lf\n", operation, result);
        fclose(fp);
    }
}


int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int isPrime(int n) {
    if (n <= 1)
        return 0;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {

    char password[20];

    printf("Enter password to access the calculator: ");
    scanf("%s", password);
    if(strcmp(password, "1945") != 0) {
    printf("Incorrect password. Access denied.\n");
    return 0;
}

    int choice,n,birthYear, age;
    double num1, num2, result,angle;
    float celsius, fahrenheit;


    while (1) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Exiting the calculator. Goodbye! Thank you for using the calculator.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = num1 + num2;
                printf("Result: %.2lf\n", result);
                break;
            case 2:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = num1 - num2;
                printf("Result: %.2lf\n", result);
                break;
            case 3:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = num1 * num2;
                printf("Result: %.2lf\n", result);
                break;
            case 4:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                    if (num2 != 0) {
                    result = num1 / num2;
                    printf("Result: %.2lf\n", result);
                } else {
                    printf("Error: Division by zero is not allowed.\n");
                }
                break;
            case 5:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                        result = pow(num1, num2);
                printf("Result: %.2lf\n", result);
                break;
            case 6:
                printf("Enter THE number: ");
                scanf("%lf", &num1);
                if (num1 >= 0) {
                    result = sqrt(num1);
                    printf("Result: %.2lf\n", result);
                } else {
                    printf("Error: Square root of a negative number is not allowed.\n");
                }
                break;
            case 7:
                printf("Enter two numbers: ");
                 scanf("%lf %lf", &num1, &num2);
                result = (num1 * num2) / 100.0;
                printf("Result: %.2lf\n", result);
                break;
            case 8:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                if (num1 >= 0 && num1 == (int)num1) {
                    result = factorial((int)num1);
                    printf("Result: %.2lf\n", result);
                } else {
                    printf("Error: Factorial is only defined for non-negative integers.\n");
                }
                break;
            case 9:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                if (num2 != 0) {
                    result = fmod(num1, num2);
                    printf("Result: %.2lf\n", result);
                } else {
                    printf("Error: Modulus by zero is not allowed.\n");
                }
                break;
            case 10:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = (num1 + num2) / 2.0;
                printf("Result: %.2lf\n", result);
                break;  
            case 11:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                if ((int)num1 % 2 == 0) {
                    printf("%.2lf is Even\n", num1);
                } else {
                    printf("%.2lf is Odd\n", num1);
                }
                break;
            case 12:
                printf("Enter The Number : ");
                scanf("%d", &n);

                if(isPrime(n)) {
                printf("%d is a Prime Number\n", n);
                } else {
                printf("%d is not a Prime Number\n", n);
                }
                break;
            case 13:
                printf("Enter temperature in Celsius: ");
                scanf("%f", &celsius);
                fahrenheit = (celsius * 9 / 5) + 32;
                printf("Temperature in Fahrenheit: %.2f\n", fahrenheit);
                break;
            case 14:
                printf("Enter angle in degrees: ");
                scanf("%lf", &angle);
                result = sin(angle * M_PI / 180);
                printf("Sin(%.2lf) = %.2lf\n", angle, result);
                break;
            case 15:
                printf("Enter angle in degrees: ");
                scanf("%lf", &angle);
                result = cos(angle * M_PI / 180);
                printf("Cos(%.2lf) = %.2lf\n", angle, result);
                break;
            case 16:
                printf("Enter angle in degrees: ");
                scanf("%lf", &angle);
                result = tan(angle * M_PI / 180);
                printf("Tan(%.2lf) = %.2lf\n", angle, result);
                break;
            case 17:
                printf("Enter angle in degrees: ");
                scanf("%lf", &angle);
                result = 1 / cos(angle * M_PI / 180);
                printf("Sec(%.2lf) = %.2lf\n", angle, result);
                break;
            case 18:
                printf("Enter angle in degrees: ");
                scanf("%lf", &angle);
                result = 1 / sin(angle * M_PI / 180);
                printf("Cosec(%.2lf) = %.2lf\n", angle, result);
                break;
            case 19:
                printf("Enter angle in degrees: ");
                scanf("%lf", &angle);
                result = 1 / tan(angle * M_PI / 180);
                printf("Cot(%.2lf) = %.2lf\n", angle, result);
                break;
            case 20:
                printf("Enter value for Sin Inverse: ");
                scanf("%lf", &num1);
                result = asin(num1) * 180 / M_PI;
                printf("Sin Inverse(%.2lf) = %.2lf degrees\n", num1, result);
                break;
            case 21:
                printf("Enter value for Cos Inverse: ");
                scanf("%lf", &num1);
                result = acos(num1) * 180 / M_PI;
                printf("Cos Inverse(%.2lf) = %.2lf degrees\n", num1, result);
                break;
            case 22:
                printf("Enter value for Tan Inverse: ");
                scanf("%lf", &num1);
                result = atan(num1) * 180 / M_PI;
                printf("Tan Inverse(%.2lf) = %.2lf degrees\n", num1, result);
                break;
            case 23:
                printf("Enter value for Log Base 10: ");
                scanf("%lf", &num1);
                if (num1 > 0) {
                    result = log10(num1);
                    printf("Log Base 10(%.2lf) = %.2lf\n", num1, result);
                } else {
                    printf("Error: Logarithm is only defined for positive numbers.\n");
                }
                break;
            case 24:
                printf("Enter value for Natural Log (ln): ");
                scanf("%lf", &num1);
                if (num1 > 0) {
                    result = log(num1);
                    printf("Natural Log (ln)(%.2lf) = %.2lf\n", num1, result);
                } else {
                    printf("Error: Logarithm is only defined for positive numbers.\n");
                }
                break;
            case 25:
                printf("Enter value for Exponential (e^x): ");
                scanf("%lf", &num1);
                result = exp(num1);
                printf("Exponential (e^%.2lf) = %.2lf\n", num1, result);
                break;
            case 26:
                printf("Enter value for Square (x^2): ");
                scanf("%lf", &num1);
                result = pow(num1, 2);
                printf("Square (%.2lf^2) = %.2lf\n", num1, result);
                break;
            case 27:
                printf("Enter value for Cube (x^3): ");
                scanf("%lf", &num1);
                result = pow(num1, 3);
                printf("Cube (%.2lf^3) = %.2lf\n", num1, result);
                break;
            case 28:
            {
            printf("Enter your birth year: ");
            scanf("%d", &birthYear);
            printf("Your age is %d years.\n", 2026 - birthYear);
            break;
            }

            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("Thank You Sir/Mam For Choosing Our Scientific Calculator...☺️\n");
    }

    return 0;
}