#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    int votes;
} candidate;

// Max number of candidates
#define MAX 9

// Array of candidates (called globally)
candidate candidates[MAX];
int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc >= 1)
    {
        candidate_count = argc - 1;
        if (candidate_count > MAX)
        {
            printf("Maximum number of candidates is %i\n", MAX);
            return 2;
        }
        else
        {
            // Sorts given names in candidates struct
            for (int i = 0; i < (candidate_count); i++)
            {
                candidates[i].name = argv[i + 1];
                candidates[i].votes = 0;
            }

            // Loop that will execute 'vote' function every time user inputs a name
            int voters = get_int("Number of voters: ");
            string unsorted_vote[voters];
            for (int i = 0; i < voters; i++)
            {
                unsorted_vote[i] = get_string("Vote: ");
                do
                {
                    if (!vote(unsorted_vote[i]))
                    {
                        printf("Invalid vote.\n");
                        return 3;
                    }
                }
                while (vote(unsorted_vote[i]) == false);
            }
            print_winner();
        }
    }
    else
    {
        // Ensures that candidates are inputed
        printf("No candidates entered.\n");
        return 1;
    }
}

// Look for candidate 'name'
// If candidate found, update their vote total and return true.
// If not found, return false.
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // case sensitive!!
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Find who has the most votes and declare the winner(s)
void print_winner(void)
{
    int winner = 0;
    string winners[candidate_count];
    int j = 0;
    for (int i = 1; i < candidate_count; i++)
    {
        // Selection sort
        if (candidates[winner].votes < candidates[i].votes)
        {
            winner = i;
        }
        else if (candidates[winner].votes == candidates[i].votes)
        {
            winners[j] = candidates[i].name;
            j++;
        }
    }

    if (j > 0)
    {
        printf("%s\n", candidates[winner].name);
        for (int i = 0; i < j; i++)
        {
            printf("%s\n", winners[i]);
        }
    }
    else
    {
        printf("%s\n", candidates[winner].name);
    }
    return;
}
