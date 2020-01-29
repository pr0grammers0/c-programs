#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int shift(char c);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere key\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isupper(argv[1][i]) || islower(argv[1][i]))
        {
        }
        else
        {
            printf("Usage: ./vigenere key\n");
            return 1;
        }
    }

    string text = get_string("plaintext:  ");
    bool cap;
    int chr;
    int key;
    for (int i = 0, j = 0; i < strlen(text); i++)
    {
        chr = text[i];
        cap = false;
        if (isupper(text[i]))
        {
            cap = true;
            text[i] = tolower(text[i]);
        }
        if (islower(text[i]))
        {

            int rot = j / strlen(argv[1]);
            if (rot > 0)
            {
                key = shift(argv[1][(j % strlen(argv[1]))]);
            }
            else
            {
                key = shift(argv[1][i]);
            }
            int rem;
            chr = text[i] + key;

            if (chr > 122)
            {
                rem = chr - 122;
                text[i] = 96 + rem;
            }
            else
            {
                text[i] = chr;
            }
            if (cap)
            {
                text[i] = toupper(text[i]);
            }
            j++;
        }

    }
    printf("ciphertext: %s\n", text);
}

int shift(char c)
{
    string letters = "abcdefghijklmnopqrstuvwxyz";
    int number;
    for (int j = 0; j < strlen(letters); j++)
    {
        if (tolower(c) == letters[j])
        {
            number = j;
        }
    }
    return number;
}