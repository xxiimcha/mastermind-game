#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROUNDS 10
#define CODE_LENGTH 4
#define NUM_COLORS 6

const char COLORS[NUM_COLORS] = {'R', 'Y', 'G', 'B', 'C', 'P'}; // Red, Yellow, Green, Blue, Cyan, Purple

void generateRandomCode(char *c1, char *c2, char *c3, char *c4);
void getUserGuess(char *g1, char *g2, char *g3, char *g4);
void evaluateGuess(char c1, char c2, char c3, char c4, char g1, char g2, char g3, char g4, int *correctPos, int *correctColor);
void displayMenu();
void playGame(int rounds, int customMode, char customC1, char customC2, char customC3, char customC4);

int main() {
    int choice;
    int rounds = 10;
    int customMode = 0;
    char customC1, customC2, customC3, customC4;

    srand(time(0));

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                playGame(rounds, customMode, customC1, customC2, customC3, customC4);
                break;
            case 2:
                printf("Select number of rounds (1-10): ");
                scanf("%d", &rounds);
                if (rounds < 1 || rounds > 10) rounds = 10;
                printf("Enable custom code mode? (1-Yes, 0-No): ");
                scanf("%d", &customMode);
                if (customMode) {
                    printf("Enter custom secret code (%d colors R/Y/G/B/C/P): ", CODE_LENGTH);
                    scanf(" %c %c %c %c", &customC1, &customC2, &customC3, &customC4);
                }
                break;
            case 3:
                printf("Exiting game...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void displayMenu() {
    printf("\n==== MASTERMIND GAME ====\n");
    printf("1. Start New Game\n");
    printf("2. Options\n");
    printf("3. Quit\n");
}

void generateRandomCode(char *c1, char *c2, char *c3, char *c4) {
    *c1 = COLORS[rand() % NUM_COLORS];
    *c2 = COLORS[rand() % NUM_COLORS];
    *c3 = COLORS[rand() % NUM_COLORS];
    *c4 = COLORS[rand() % NUM_COLORS];
}

void getUserGuess(char *g1, char *g2, char *g3, char *g4) {
    printf("Enter your guess (%d colors R/Y/G/B/C/P): ", CODE_LENGTH);
    scanf(" %c %c %c %c", g1, g2, g3, g4);
}

void evaluateGuess(char c1, char c2, char c3, char c4, char g1, char g2, char g3, char g4, int *correctPos, int *correctColor) {
    *correctPos = 0;
    *correctColor = 0;

    if (g1 == c1) (*correctPos)++;
    if (g2 == c2) (*correctPos)++;
    if (g3 == c3) (*correctPos)++;
    if (g4 == c4) (*correctPos)++;

    if (g1 == c2 || g1 == c3 || g1 == c4) (*correctColor)++;
    if (g2 == c1 || g2 == c3 || g2 == c4) (*correctColor)++;
    if (g3 == c1 || g3 == c2 || g3 == c4) (*correctColor)++;
    if (g4 == c1 || g4 == c2 || g4 == c3) (*correctColor)++;
}

void playGame(int rounds, int customMode, char customC1, char customC2, char customC3, char customC4) {
    char secretC1, secretC2, secretC3, secretC4;
    if (customMode) {
        secretC1 = customC1;
        secretC2 = customC2;
        secretC3 = customC3;
        secretC4 = customC4;
    } else {
        generateRandomCode(&secretC1, &secretC2, &secretC3, &secretC4);
    }

    printf("\nSecret Code Generated! Start Guessing.\n");
    char g1, g2, g3, g4;
    int correctPos, correctColor;

    for (int round = 1; round <= rounds; round++) {
        getUserGuess(&g1, &g2, &g3, &g4);
        evaluateGuess(secretC1, secretC2, secretC3, secretC4, g1, g2, g3, g4, &correctPos, &correctColor);
        printf("Round %d - Correct Position: %d, Correct Color Wrong Position: %d\n", round, correctPos, correctColor);

        if (correctPos == CODE_LENGTH) {
            printf("Congratulations! You cracked the code in %d rounds!\n", round);
            return;
        }
    }

    printf("Game Over! The secret code was: %c%c%c%c\n", secretC1, secretC2, secretC3, secretC4);
}
