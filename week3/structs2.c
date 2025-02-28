#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int votes;
}candidate;

// Create an array of three candidates
// Populate an array using users input
// Search the array to find the most votes awarded to single candidate

int main(void)
{
    const int num = 3;
    candidate presidents[num];
    for (int i = 0; i < 3; i++)
    {
        presidents[i].name = get_string("Name: ");
        presidents[i].votes = get_int("Votes: ");
    }
    int highest_vote = 0;
    string highest_candidate;
    for (int n = 0; n < 3; n++)
    {
        if (presidents[n].votes > highest_vote)
        {
            highest_vote = presidents[n].votes;
            highest_candidate = presidents[n].name;
        }
    }
    printf("Highest Voted Candidate Name: %s\n", highest_candidate);
    printf("Highest Vote Number: %i\n", highest_vote);
}
