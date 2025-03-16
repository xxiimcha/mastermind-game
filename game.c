#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CODE_LENGTH 4
#define DEFAULT_MAX_ROUNDS 10
#define NUM_COLORS 6

void generateSecretCode(int secretCode[]);
void getPlayerGuess(int playerGuess[]);
void evaluateGuess(int secretCode[], int playerGuess[], int *correctPos, int *correctColor);
void printFeedback(int correctPos, int correctColor);
void displayMenu();
void startGame(int maxRounds, int customMode);
void setOptions(int *maxRounds, int *customMode);

int main() {
    int choice;
    int maxRounds = DEFAULT_MAX_ROUNDS;
    int customMode = 0;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                startGame(maxRounds, customMode);
                break;
            case 2:
                setOptions(&maxRounds, &customMode);
                break;
            case 3:
                printf("Thank you for playing Mastermind! Goodbye.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

void displayMenu() {
    printf("\n=== Mastermind ===\n");
    printf("1. Start a New Game\n");
    printf("2. Options\n");
    printf("3. Quit\n");
    printf("Enter your choice: ");
}

void startGame(int maxRounds, int customMode) {
    int secretCode[CODE_LENGTH];
    int playerGuess[CODE_LENGTH];
    int correctPos, correctColor;
    int round = 0;

    if (customMode) {
        printf("Enter a custom secret code (4 numbers between 1-6): ");
        getPlayerGuess(secretCode);
    } else {
        srand(time(NULL));
        generateSecretCode(secretCode);
    }

    printf("\nWelcome to Mastermind!\n");
    printf("Try to guess the secret code.\n");

    while (round < maxRounds) {
        correctPos = 0;
        correctColor = 0;
        printf("\nRound %d: Enter your guess: ", round + 1);
        getPlayerGuess(playerGuess);
        evaluateGuess(secretCode, playerGuess, &correctPos, &correctColor);
        printFeedback(correctPos, correctColor);

        if (correctPos == CODE_LENGTH) {
            printf("Congratulations! You guessed the secret code in %d rounds!\n", round + 1);
            return;
        }
        round++;
    }

    printf("Game Over! The secret code was: ");
    for (int i = 0; i < CODE_LENGTH; i++) {
        printf("%d ", secretCode[i]);
    }
    printf("\n");
}

void setOptions(int *maxRounds, int *customMode) {
    int choice;
    printf("\n=== Options ===\n");
    printf("1. Set Game Mode (1 - Random, 2 - Custom)\n");
    printf("2. Set Number of Rounds (1-10)\n");
    printf("3. Return to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Select mode (1 - Random, 2 - Custom): ");
            scanf("%d", customMode);
            *customMode = (*customMode == 2) ? 1 : 0;
            break;
        case 2:
            printf("Enter number of rounds (1-10): ");
            scanf("%d", maxRounds);
            if (*maxRounds < 1 || *maxRounds > 10) {
                printf("Invalid input! Setting to default (10).\n");
                *maxRounds = DEFAULT_MAX_ROUNDS;
            }
            break;
        case 3:
            return;
        default:
            printf("Invalid choice. Returning to main menu.\n");
    }
}

void generateSecretCode(int secretCode[]) {
    for (int i = 0; i < CODE_LENGTH; i++) {
        secretCode[i] = (rand() % NUM_COLORS) + 1;
    }
}

void getPlayerGuess(int playerGuess[]) {
    for (int i = 0; i < CODE_LENGTH; i++) {
        scanf("%d", &playerGuess[i]);
        if (playerGuess[i] < 1 || playerGuess[i] > NUM_COLORS) {
            printf("Invalid input! Please enter numbers between 1 and 6.\n");
            i--;
        }
    }
}

void evaluateGuess(int secretCode[], int playerGuess[], int *correctPos, int *correctColor) {
    int secretChecked[CODE_LENGTH] = {0};
    int guessChecked[CODE_LENGTH] = {0};

    for (int i = 0; i < CODE_LENGTH; i++) {
        if (playerGuess[i] == secretCode[i]) {
            (*correctPos)++;
            secretChecked[i] = 1;
            guessChecked[i] = 1;
        }
    }

    for (int i = 0; i < CODE_LENGTH; i++) {
        if (!guessChecked[i]) {
            for (int j = 0; j < CODE_LENGTH; j++) {
                if (!secretChecked[j] && playerGuess[i] == secretCode[j]) {
                    (*correctColor)++;
                    secretChecked[j] = 1;
                    break;
                }
            }
        }
    }
}

void printFeedback(int correctPos, int correctColor) {
    printf("Correct Position: %d | Correct Color but Wrong Position: %d\n", correctPos, correctColor);
}
