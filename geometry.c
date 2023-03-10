#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ERROR_1 "Error reading from file\n"
#define ERROR_2 "Enter the object\n"
#define ERROR_3 "Expected '('\n"
#define ERROR_4 "Object data is expected to be entered\n"


int check_object(char* str)
{
    int i=0;
    char c=str[i];
    int n = strlen(str);

    while(c!='(' && i!=n)
    {
        c=str[i];

        i++;
    }
    if(c=='(' && i==n)
        return 4;
    if(i==0)
        return 2;
    if(i==n)
        return 3;
    return 0;
}


int check(char* str)
{
    int n = check_object(str);
    return n;
}


int check_and_output(FILE* file)
{
    int n=1000;
    char* str1, *str = malloc(n * sizeof(char));
    while(1)
    {
        str1 = fgets(str,n,file);
        if(str1==NULL)
        {
            if(feof(file) != 0)
            {
                return 0;
            }
            else
            {
                printf("\n");
                printf(ERROR_1);
                return -1;
            }
        }
        int err = check(str);
        int n = strlen(str);
        if(str[n-1]=='\n')
            str[n-1]='\0';
        if(err == 2)
        {
            puts(str);
            printf("^\n");
            printf(ERROR_2);
            return -1;
        }
        if(err == 3)
        {
            puts(str);
            char c=' ';
            for(int i=0;i<strlen(str);i++)
                printf("%c",c);
            printf("^\n");
            printf(ERROR_3);
            return -1;
        }
        if(err == 4)
        {
            puts(str);
            char c=' ';
            for(int i=0;i<strlen(str);i++)
                printf("%c",c);
            printf("^\n");
            printf(ERROR_4);
            return -1;
        }
        puts(str);
    }
    free(str);
}


int main()
{
    FILE* file = fopen("geometry_test","r");
    int Error = check_and_output(file);
    if(Error==0)
        return 0;
    if(Error==-1)  
        return -1;
}