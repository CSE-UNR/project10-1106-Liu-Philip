//Name: Philip Liu
//File: wordup.c
//Date: 05/06/2025
//Class: CS135.1001

#include<stdio.h>
#include<stdbool.h>

#define GUESSMAX 6
#define STR_CAP 5

int lengthOf(const char *s) 
{
    int l = 0;

    while (s[l] != '\0') 
    {
        l++;
    }

    return l;
}

void copy(char *dest, const char *s) 
{
    int i = 0;

    while (s[i] != '\0') 
    {
        dest[i] = s[i];
        i++;
    }
    
    dest[i] = '\0';
}

int newline(const char *s) 
{
    int i = 0;

    while (s[i] != '\0') 
    {
        if (s[i] == '\n') 
        {
            return i;
        }

        i++;
    }

    return -1;
}

char lowerCase(char c) 
{
    if ((c >= 'A') && (c <= 'Z')) 
    {
        return c + ('a' - 'A');
    }

    return c;
}

char upperCase(char c) 
{
    if (c >= 'a' && c <= 'z') 
    {
        return c - ('a' - 'A');
    }

    return c;
}

int main()
{
    char mystery[STR_CAP + 1];
    FILE *fp;

    fp = fopen("mystery.txt", "r");

    if(fp == NULL)
    {
        printf("\nFile is null\n");

        return 0;
    }
    else
    {
        fscanf(fp, "%5s", mystery);

        fclose(fp);
    }

    char guesses[GUESSMAX][STR_CAP + 1];
    int i = 0, win = 0;

    do
    {
        if(i > 0)
        {
            win = 1;

            for(int c = 0; c < STR_CAP; c++)
            {
                if(guesses[i-1][c] != mystery[c])
                {
                    win = 0;
                }
            }

            if(win == 1)
            {
                printf("================================\n");
                break;
            }

            for(int r = 0; r < i; r++)
            {
                for(int c = 0; c < STR_CAP; c++)
                {
                    if(lowerCase(guesses[r][c]) == lowerCase(mystery[c]))
                    {
                        printf("%c", upperCase(guesses[r][c]));
                    }
                    else
                    {
                        printf("%c", guesses[r][c]);
                    }
                }

                printf("\n");

                bool matched[STR_CAP] = {false};

                for (int c = 0; c < STR_CAP; c++) 
                {
                    if (lowerCase(guesses[r][c]) == mystery[c]) 
                    {
                        matched[c] = true;
                    }
                }

                for (int c = 0; c < STR_CAP; c++) 
                {
                    if (lowerCase(guesses[r][c]) == mystery[c])
                        continue;

                    for (int p = 0; p < STR_CAP; p++) 
                    {
                        if (!matched[p] && lowerCase(guesses[r][c]) == mystery[p] && c != p) 
                        {
                            matched[p] = true;

                            for (int t = 0; t < c; t++)
                            {
                                printf(" ");
                            }

                            printf("^");

                            break; 
                        }
                    }
                }

                printf("\n");
            }
        }
        
        char buffer[100];

        while (1) 
        {
            printf("GUESS %d! Enter your guess: ", i + 1);
            fgets(buffer, sizeof(buffer), stdin);

            int index = newline(buffer);

            if (index != -1) 
            {
                buffer[index] = '\0';
            }

            if (lengthOf(buffer) != STR_CAP) {
                printf("Your guess must be 5 letters long. Please try again.\n");
                continue;
            }

            copy(guesses[i], buffer);
            break;
        }

        printf("================================\n");

        i++;
    } while(i < GUESSMAX);

    if(win == 1)
    {
        printf("                ");

        for(int c = 0; c < STR_CAP; c++)
        {
            printf("%c", upperCase(mystery[c]));
        }

        if(i == 1)
        {
            printf("\n        You won in %d guesses!\n", i + 1);
            printf("                GOATED!\n");
        } 
        else if((i == 2) || (i == 3))
        {
            printf("\n        You won in %d guesses!\n", i + 1);
            printf("                Amazing!\n");
        }
        else if((i == 4) || (i == 5))
        {
            printf("\n        You won in %d guesses!\n", i + 1);
            printf("                Nice!\n");
        }
        else
        {
            printf("\n        You won in %d guesses!\n", i + 1);
        }
    }
    else
    {
        printf("You lost, better luck next time!\n");
    }
    
    return 0;
}