#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
/*
Pseudo-code:
1. Prompt the user for some text
2. Count the number of letters, words, and sentences in the text
3. Use Coleman-Liau index to sort out text and sentence length's
    index = 0.0588 * L - 0.296 * S - 15.8
    * L is average number of letters per 100 words
    * S is average number of sentences per 100 words
4. Print grade level
* Be sure to round score to nearest whole number(2.8 -> 3)
* Output should be "Grade X" where X is the grade level
* If output is less than 1, output "Before Grade 1"
* If output is 16 or higher, output "Grade 16+"
*/
int Letter_Counter(string text);
int Word_Counter(string text);
int Sentence_Counter(string text);
void Grader(float index);

int main(void)
{
    // Prompt user for entering a text
    string user_text = get_string("Enter paragraph to be graded: ");
    float average_letter = 0.0;
    float average_sentence = 0.0;
    float index = 0.0;

    // Store counter function results in local variables
    int letters = Letter_Counter(user_text);
    int words = Word_Counter(user_text);
    int sentences = Sentence_Counter(user_text);

    // Compute averages
    average_letter = ((float) letters / words) * 100;
    average_sentence = ((float) sentences / words) * 100;

    // Calculate the Coleman-Liau Index:
    index = (0.0588 * average_letter) - (0.296 * average_sentence) - 15.8;

    // Output the grade level
    Grader(index);
}

// Count every character in given text
int Letter_Counter(string text)
{
    int count_of_letters = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        // Make sure given character is alphabetic(A-Z)(a-z)
        if (isalpha(text[i]))
        {
            count_of_letters++;
        }
    }
    return count_of_letters;
}

int Word_Counter(string text)
{
    // Assume words as 1 for counting the last word
    int count_of_words = 1;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        // When encountered with whitespace('\0') add 1 to counter
        if (text[i] == ' ')
        {
            count_of_words++;
        }
    }
    return count_of_words;
}

int Sentence_Counter(string text)
{
    int count_of_sentence = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        // When encountered with '.', '!' and '?' characters add 1 to counter
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count_of_sentence++;
        }
    }
    return count_of_sentence;
}

void Grader(float index)
{
    // Round the index and store it inside a local variable
    int rounded_index = round(index);
    if (rounded_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rounded_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", rounded_index);
    }
}
