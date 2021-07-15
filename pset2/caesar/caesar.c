#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool decimal_digit(string s);
string ciphertext(string t);

int k;

int main (int argc, char *argv[])
{
    k = atoi(argv[1]);
    if (argc == 2 && decimal_digit(argv[1]) == 1)
    {
        printf ("success\n");
        printf ("%i\n", atoi(argv[1]));
    }
    else
    {
      printf ("Usage: ./caesar key\n");
      return 1;
    }
    string plaintext = get_string("Plain text:");
    printf ("ciphertext:%s", ciphertext(plaintext));

    printf("\n");
}

bool decimal_digit(string s)
{
    for (int i = 0, n = strlen(s); i<n; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
string ciphertext(string t)
{
    int key=k;
    string c=t;
    for (int i = 0, n = strlen(t); i < n;i++)
    {

        if (islower(t[i]))
        {
        c[i] = (((t[i]-97) + key) % 26) + 97;

        }
        else if (isupper(t[i]))
        {
        c[i] = (((t[i]-65) + key) % 26) + 65;

        }
        else
        c[i] = t[i];
    }
    return c;
}