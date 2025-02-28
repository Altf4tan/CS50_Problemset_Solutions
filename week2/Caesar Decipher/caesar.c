#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*Pseudo-code
1. Validate command-line argument:
   - If no key or multiple arguments provided:
       Print usage message and exit.
   - Check if the key contains only digits.
       If not, print an error message and exit.
   - Convert the key to an integer.

2. Prompt user for plaintext.

3. Encrypt plaintext:
   - Initialize an empty string for ciphertext.
   - For each character in plaintext:
       - If character is uppercase:
           Rotate within 'A'-'Z'.
       - Else if character is lowercase:
           Rotate within 'a'-'z'.
       - Else:
           Keep the character unchanged.
       - Append the transformed character to ciphertext.

4. Print ciphertext.

*/
string Encrypter(string text, int key);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage ./ceasar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    for (int i = 0, length = strlen(argv[1]); i < length; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage ./ceaser key\n");
            return 1;
        }
    }
    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string unencrypted_message = get_string("Please enter a text: ");
    // Encrypt the message
    string encrypted_message = Encrypter(unencrypted_message, key);
    printf("ciphertext: %s\n", encrypted_message);
}

string Encrypter(string text, int key)
{
    // Include space for null-terminator
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        // Rotate the character if it's a letter
        if (isalpha(text[i]))
        {
            // If uppercase add ascii of 'A'
            if (isupper(text[i]))
            {
                text[i] = ((text[i] - 'A' + key) % 26) + 'A';
            }
            // If lowercase add ascii of 'a'
            else if (islower(text[i]))
            {
                text[i] = ((text[i] - 'a' + key) % 26) + 'a';
            }
        }
        // Non-alphabetic characters remain unchanged
    }
    return text;
}
