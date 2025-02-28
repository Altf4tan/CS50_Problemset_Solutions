#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string phone;
}person;

int main(void)
{
    person people[3];

    people[0].name = "altan";
    people[0].phone = "123";

    people[1].name = "basoglu";
    people[1].phone = "456";

    people[2].name = "Benis Dickson";
    people[2].phone = "69 69 69 69";

    string search_name = get_string("Name to look: ");
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(search_name, people[i].name) == 0)
        {
            printf("found %s\n", search_name);
            return 0;
        }
        else
        {
            printf("didn't found %s\n", search_name);
            return 1;
        }
    }
}
