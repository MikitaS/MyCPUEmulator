#include "../enum.h"



const int Prog_Size = 100000, Pointer_Lines = 50000;

bool    CheckFloat          (char *str);
void    ReadProgram         (char program[]);
int     ChangeSpaceNull     (char program[],char* pointer[]);
void    FirstCompile        (char* pointer[], int label[], int pi);
void    SecondCompile       (char* pointer[], int label[], int pi);
void    SignatureWrite      (FILE *textfile);
void    WriteAll            (char* pointer[], int pi);

void WriteAll(char* pointer[], int pi)
{
    assert(pointer);
    assert(pi);

    for(int i = 0; i < pi; i++)
        printf("%s\n", pointer[i]);
}

bool CheckFloat(char *str)
{
    assert(str);

    int i = 0, punkt = 0;

    if(str[0] == '-')
        ++i;

    if(isdigit(str[i]))
        ++i;
    else
        return false;

    while(str[i] != '\0')
    {
        if(str[i] == '.')
        {
            i++;
            punkt++;
        }

        if(isdigit(str[i]))
            i++;
        else
            return false;
    }
    if(punkt > 1)
        return false;

    return true;
}

void ReadProgram(char program[])
{
    assert(program);

    FILE *textfile = 0;
    textfile = fopen("Program.txt" , "r");
    assert(textfile);

    fread(program, Prog_Size, sizeof(char), textfile);

    fclose(textfile);
}

int ChangeSpaceNull(char program[],char* pointer[])
{
    assert(program);
    assert(pointer);

    int i = 0, pi = 1;
    pointer[0] = program;

    while(program[i] != '\0')
    {
        if(isspace(program[i]))
        {
            if(!isspace(program[i+1]))
            {
                pointer[pi] = program + i + 1;
                pi++;
            }
            program[i] = '\0';
        }
        i++;
    }
    return pi;
}

void FirstCompile(char* pointer[], int label[], int pi)
{
    assert(pointer);
    assert(label);
    assert(pi);

    int LabelCount = 0;

    for(int i = 0; i < pi; i++)
    {
        if(*pointer[i] == ':')
        {
            LabelCount++;

            if(isdigit(*(pointer[i] + 1)))
            {
                label[*(pointer[i] + 1) - '0'] = i - LabelCount + 1;
            }
            else
            {
                printf("ERROR\nExpected digit after ':' on the %d -th position\n", i);
                exit(0);
            }
        }
    }
}

void SecondCompile(char* pointer[], int label[], int pi)
{
    FILE *textfile = fopen("ResultOfCompile.txt" , "w");
    assert(textfile);
    SignatureWrite(textfile);

    for(int i = 0; i < pi; i++)
    {
        #define command(name, code_compile, code_CPU) \
        code_compile
        if(*pointer[i] == ':')
            ;

        #include "defines.h"

        #undef command(name, code_compile, code_CPU)
        else
        {
            //printf("ERROR\nUnknown command %s on the %d -th position\n", pointer[i], i + 1);
            exit(0);
        }
    }
    fclose(textfile);
}

void SignatureWrite(FILE *textfile)
{
    assert(textfile);

    fprintf(textfile, "%s\n", signature);
}

int main()
{
    char program[Prog_Size] = {0};
    char* pointer[Pointer_Lines] = {0};
    int label[10] = {0};

    ReadProgram(program);
    int pi = ChangeSpaceNull(program, pointer);
    FirstCompile(pointer, label, pi);
    //WriteAll(pointer, pi);
    SecondCompile(pointer, label, pi);

    return 0;
}
