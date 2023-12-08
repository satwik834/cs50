#include <cs50.h>
#include <stdio.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

int get_letters(string sent);
int get_words(string sent);
int get_sentences(string sent);

int main(void)
{
    string sentence = get_string("Text:");

    float letter_count = get_letters(sentence);

    float word_count = get_words(sentence);

    float sentence_count = get_sentences(sentence);


    float k = (letter_count / word_count);
    float p = (sentence_count / word_count);

    float L = k * 100;
    float S = p * 100;



    float grade = (0.0588 * L) - (0.296 * S)  - 15.8;


    int index = round(grade);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    if (index > 1 && index < 16)
    {
        printf("Grade %i\n",  index);

    }

}






int get_letters(string sent)
{
    int letter_count = 0;
    for (int i = 0 ; i < strlen(sent) ; i++)
    {
        if (isalpha(sent[i]))
        {
            letter_count = letter_count + 1;
        }
    }
    return letter_count;
}



int get_words(string sent)
{
    int space_count = 0;
    for (int i = 0 ; i < strlen(sent) ; i++)
    {
        if (sent[i] == 32)
        {
            space_count = space_count + 1;
        }
    }
    return space_count + 1;

}

int get_sentences(string sent)
{
    int char_count = 0;
    for (int i = 0 ; i < strlen(sent) ; i++)
    {
        if (sent[i] == '!' || sent[i] == '.' || sent[i] == '?')
        {
            char_count = char_count + 1;
        }
    }
    return char_count;
}