#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include<stdlib.h>

string cipher(string, int);
int key_su(int);
int get_key(char[1000]);


int main(int argc, string argv[])
{
    // checks for valid input for key
    if (argc == 1 || (get_key(argv[1]) == 1) || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // encrypts if valid input is given
    if (argc == 2)
    {

        if (get_key(argv[1]) == 0)
        {
            int key = atoi(argv[1]);
            string inp = get_string("plaintext:  ");

            // get encryped text from function
            string ciphertext = cipher(inp, key);
            printf("ciphertext: %s\n", ciphertext);


        }
    }




}



//function for checking if input is an int
int get_key(char key[1000])
{
    int k = 0;

    //len of key
    int len_key =  strlen(key);

    // checking if input is an int using isdigit()
    for (int i = 0; i < strlen(key); i++)
    {
        if (isdigit(key[i]) == 0)
        {
            k = 1;

        }
    }
    int keyo = atoi(key);

    return k;
}




// function for encrypting the text, a big one at tha
string cipher(string inp, int key)
{
    int str_len = strlen(inp);

    // starting looping throught the input
    for (int i = 0; i < str_len; i++)
    {
        //check if the character is lowercase
        if (islower(inp[i]))
        {
            if (inp[i] + key > 122)
            {
                if ((inp[i] + key - 122) + 96 > 122)
                {
                    int m;
                    int ret = 123;
                    int p = 0 ;
                    while (ret + 96 > 122)
                    {
                        ret = 0;
                        m = (inp[i] + key - 122) + 96;
                        ret = m - 122;
                        p++;
                        if (p > 1)
                        {
                            ret = ret + 96 - 122;
                        }
                    }
                    inp[i] = 96 + ret;
                }
                else
                {
                    inp[i] = (inp[i] + key - 122) + 96;
                }
            }
            else
            {
                inp[i] = inp[i] + key;
            }
        }
        // checking if character is uppercase
        if (isupper(inp[i]))
        {
            if (inp[i] + key > 90)
            {
                if ((inp[i] + key - 90) + 64 > 90)
                {
                    int m;
                    int ret = 123;
                    int p = 0 ;
                    while (ret + 64 > 90)
                    {
                        ret = 0;
                        m = (inp[i]  + key - 90) + 64;
                        ret = m - 90;
                        p++;
                        if (p > 1)
                        {
                            ret = ret + 64 - 90;
                        }
                    }
                    inp[i] = 64 + ret;
                }
                else
                {
                    inp[i] = (inp[i] + key - 90) + 64;
                }
            }
            else
            {
                inp[i] = inp[i] + key;
            }
        }
        if (isalpha(inp[i]) == 0)
        {
            inp[i] = inp[i];
        }
    }

    return inp;
}


