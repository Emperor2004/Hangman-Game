#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For rand()
#include <ctype.h>  // For tolower()

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20

// Function to print the current state of the word with guessed letters or underscores
void printWord(char *word, char *guessedLetters)
{
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        int guessed = 0;
        for (int j = 0; j < strlen(guessedLetters); j++)
        {
            if (word[i] == guessedLetters[j])
            {
                guessed = 1;
                break;
            }
        }
        if (guessed)
        {
            printf("%c ", word[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

int main()
{
    char words[][MAX_WORD_LENGTH] = {"hangman", "programming", "computer", "science", "python"};
    int numWords = sizeof(words) / sizeof(words[0]);

    // Seed the random number generator
    srand(time(NULL));

    // random number generator
    int r = rand() % numWords;
    // Pick a random word
    char *secretWord = words[r];
    int wordLength = strlen(secretWord);

    char guessedLetters[MAX_WORD_LENGTH] = {0}; // Initialize with zeros to ensure null-termination
    int numTries = 0;                             // Number of incorrect tries

    printf("Welcome to Hangman!\n");

    while (1)
    {
        printf("\nWord: ");
        printWord(secretWord, guessedLetters);

        // Check if the player has guessed all the letters
        int allGuessed = 1;
        for (int i = 0; i < wordLength; i++)
        {
            if (strchr(guessedLetters, secretWord[i]) == NULL)
            {
                allGuessed = 0;
                break;
            }
        }
        if (allGuessed)
        {
            printf("Congratulations! You guessed the word: %s\n", secretWord);
            break;
        }

        printf("Enter a letter: ");
        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess); // Convert to lowercase

        // Check if the letter has already been guessed
        if (strchr(guessedLetters, guess) != NULL)
        {
            printf("You've already guessed that letter. Try again.\n");
            continue;
        }

        // Store the guessed letter in the guessedLetters array
        guessedLetters[numTries] = guess;
        numTries++;
        guessedLetters[numTries] = '\0'; // Null-terminate the string after all guessed letters

        // Check if the letter is in the word
        if (strchr(secretWord, guess) == NULL)
        {
            printf("Incorrect guess!\n");
            if (++numTries == MAX_TRIES) // Increment numTries and check if it equals MAX_TRIES
            {
                printf("You ran out of tries! The word was: %s\n", secretWord);
                break;
            }
        }
    }

    return 0;
}
