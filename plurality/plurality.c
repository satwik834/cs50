#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string to_cap(string name);

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    string NAME = name;

    for(int i = 0;i < candidate_count; i++)
    {
        string cname = candidates[i].name;
        if(strcmp(cname,NAME) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    bool tie = false;
    int winner;
    int maxv = 0;
    for(int i = 0;i < candidate_count; i++)
    {
        if(candidates[i].votes > maxv)
        {
            maxv = candidates[i].votes;
            winner = i;
        }
    }
    for(int i = 0;i < candidate_count; i++)
    {
        if(maxv > 0 && candidates[i].votes == maxv)
        {
            tie = true;
        }
    }

    if(!tie)
    {
        printf("%s\n",candidates[winner].name);
    }
    if(tie)
    {
        for(int i = 0;i < candidate_count; i++)
        {
            if(candidates[i].votes == maxv)
            {
                printf("%s\n",candidates[i].name);
            }
        }
    }
    return;
}

string to_cap(string name)
{
    for(int i = 0; i < strlen(name); i++)
    {
        name[i] = toupper(name[i]);
    }
    return name;
}