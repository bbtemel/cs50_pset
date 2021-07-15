#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool check_validity(string s);

int main (int argc, char *argv[])
{

    if (argc == 2 && !check_validity(argv[1]))
    {
        printf ("Key must contain 26 characters.\n");
        return 1;
    }
    else if (argc != 2 )
    {
      printf ("Usage: ./substitution key\n");
      return 1;
    }
    string key = argv[1];
    string plaintext = get_string("Plain text:");
    string c = plaintext;

    for (int i = 0, n = strlen(plaintext); i < n;i++)
    {
        char m = 0;

        if (islower(plaintext[i]))
            {
            m = 'a';
            c[i] = key [plaintext[i] - m];
            c[i] = tolower((int)c[i]);
            }
        else if (isupper(plaintext[i]))
            {
                m = 'A';
            c[i] = key [plaintext[i] - m];
            c[i] = toupper((int)c[i]);
            }
        else
            c[i] = plaintext[i];

    }
    printf ("ciphertext:%s\n", c);

return 0;
}

bool check_validity(string s)
{
    int n = strlen(s);
    if (strlen(s) !=26)
    {
        return 0;
    }
    for (int i = 0; i<n; i++)
    {
        if (isalpha(s[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
