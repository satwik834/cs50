#include <cs50.h>
#include <stdio.h>
#include<ctype.h>
#include<string.h>


string encrypt(string plaintext, string Key);
int check_dupe(string Key);

int main(int argc, string argv[])
{
    if (argc > 1 && (strlen(argv[1]) < 26 || strlen(argv[1]) > 26))
    {
        printf("fuck you\n");
        return 1;
    }

    if (argc == 1 || argc == 3)
    {
        return 1;
    }
    string key = argv[1];

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return 1;
        }
    }

    if (check_dupe(key))
    {
        return 1;
    }



    string plaintext = get_string("plaintext:");
    string ciphertext = encrypt(plaintext, key);
    printf("ciphertext:%s\n", ciphertext);


}



string encrypt(string plaintext, string Key)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        int index = toupper(plaintext[i]);
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                plaintext[i] = toupper(Key[index - 65]);
            }
            if (islower(plaintext[i]))
            {
                plaintext[i] = tolower(Key[index - 65]);
            }

        }

    }
    return plaintext;
}


int check_dupe(string Key)
{
    int p;
    for (int i = 0; i < strlen(Key); i++)
    {
        int let = toupper(Key[i]);
        for (int k = i + 1; k < strlen(Key); k++)
        {
            if (let == toupper(Key[k]))
            {
                p = 1;
                break;
            }
        }
    }
    return p;

}