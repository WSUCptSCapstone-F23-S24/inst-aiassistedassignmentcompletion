#include "TokenFormatter.h"

void removeChar(char *str, char word)
{

    bool IsChar = false;
    char *start, *end;
   
    for(start = end = str; *str != '\0'; start++)
    {

        *end = *start;
      
        if(*end != word)
        {
            IsChar = false;
            end++;
        }
        else
        {
            if(IsChar)
            {
                IsChar = false;
                end++;           
            }
            else
            {
                IsChar = true;
            }
        }
        str++;
    }
    *end = '\0';
}

void UpperCase(char *Letter)
{
    while(*Letter)
    {
        *Letter = toupper((unsigned char) *Letter);
        Letter++;
    }

    return;
}
int getStrLength (char *svalue)
{
    return strlen(svalue)-2;
}