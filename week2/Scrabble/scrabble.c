#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/*

SCRABBLE GAME
1. Prompt for the user for two words
2. Compute the score of each word
3. Print the winner

*/
// Use global constant for arrays to avoid data change
const int EachCharScore[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                               1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int compute_score(string word);
int main(void)
{
    // Prompt the user for two words
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // Compute score for both players
    int Player1Score = compute_score(player1);
    int Player2Score = compute_score(player2);

    if (Player1Score > Player2Score)
    {
        printf("Player 1 Wins! \n");
    }
    else if (Player2Score > Player1Score)
    {
        printf("Player 2 Wins! \n");
    }
    else
    {
        printf("Tie! \n");
    }
}
// Function to compute the score of a given word
int compute_score(string word)
{
    int score = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]))
        {
            score += EachCharScore[toupper(word[i]) - 'A'];
        }
    }
    return score;
}
