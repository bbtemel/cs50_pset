#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int count_letter(string a);
int count_word(string b);
int count_sentence(string c);
void clindex(string t);

int main(void)
{
    string text = get_string("Text:");
    clindex(text);

}
void clindex(string t)
    {

        float L = (count_letter(t) / (float) count_word(t)) * 100;
        float S = (count_sentence(t) / (float) count_word(t)) * 100;
        int index = round((0.0588 * L) - (0.296 * S) - 15.8 );

        if (index > 1 && index < 16)
        {
            printf("Grade %i\n", index);
        }
        else if (index >= 16)
        {
            printf("Grade 16+\n");
        }
        else if (index < 1)
        {
            printf("Before Grade 1\n");
        }
    }

int count_letter(string a)
    {
        int count = 0;
        for (int i = 0; i < strlen(a) ; i++ )
        {
            if (isalpha(a[i]))
            {
                count++;
            }
        }
    return count;
    }

int count_word(string b)
    {

        int count = 0;
        for(int i = 0; i < strlen(b); i++)
        {
            if (isspace(b[i]))
            {
                count++;
            }
        }
    return count+1;
    }

int count_sentence(string c)
    {
        int count = 0;
        for (int i = 0; i<strlen(c); i++)
        {
            if ((int) c[i] == 33 || (int) c[i] == 46 || (int) c[i] == 63)
            {
                count++;
            }
        }
    return count;
    }