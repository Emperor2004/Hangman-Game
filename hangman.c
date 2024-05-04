#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20
#define MISTAKE 10

void guessWord(char *word, int len);

int main() {
    FILE *fptr = fopen("words.txt", "r");
    if (fptr == NULL) {
        printf("Sorry! Words cannot be loaded");
        return 1;
    }

    int len = 0;
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    while (fscanf(fptr, "%s", words[len]) == 1) {
        len++;
    }
    fclose(fptr);

    srand(time(NULL));

    int rindex = rand() % len;

    char word[MAX_WORD_LENGTH];
    strcpy(word, words[rindex]);
    for (int i = 0; i < strlen(word); i++) {
        word[i] = tolower(word[i]);
    }

    printf("Welcome to Hangman!\n");
    guessWord(word, strlen(word));

    return 0;
}

void guessWord(char *word, int len) {
    int gameloop = 1, letterGuessed = 0, mistake = 0;

    char guessedWord[MAX_WORD_LENGTH];
    for (int i = 0; i < len; i++) {
        guessedWord[i] = '_';
    }
    guessedWord[len] = '\0';

    do {
        printf("\nWord: ");
        for (int j = 0; j < len; j++) {
            printf("%c ", guessedWord[j]);
        }
        printf("\nMistake: %d", mistake);
        printf("\nEnter a letter: ");

        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess);

        int found = 0;
        for (int k = 0; k < len; k++) {
            if (word[k] == guess) {
                guessedWord[k] = guess;
                letterGuessed++;
                found = 1;
            }
        }

        if (!found) {
            printf("Incorrect guess!\n");
            mistake++;
        }

        if (mistake == MISTAKE) {
            printf("You ran out of tries! The word was: %s\n", word);
            gameloop = 0;
        }

        if (letterGuessed == len) {
            printf("\nCongratulations! You guessed the word: %s\n", word);
            gameloop = 0;
        }

    } while (gameloop == 1);
}
