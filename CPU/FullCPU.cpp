#include "Stack/MyStack.h"
#include "enum.h"

int     Password    (char password[]);
int     Read        (float program[]);
void    CPU         (float program[], struct cpu* StCPU);

struct cpu
{
    struct Stack Stack;
    struct Stack Calls;
    float ax, bx, cx, dx;
};

const short int Password_Lenth = 15;
const int Prog_Size = 5000, RAM_SIZE = 1024;

int Password(char password[])
{
    assert(password);

    if(strcmp(password, signature) == 0)
    {
        printf("Password correct\n");
        return 1;
    }
    else
    {
        printf("ERROR:\nPassword incorrect\n");
        return 0;
    }

}

int Read(float program[])
{
    FILE *CPUFile = fopen("Compile/ResultOfCompile.txt", "r");
    assert(CPUFile);

    char password[Password_Lenth] = {};
    int ScanfStatus = 1;

    fscanf(CPUFile, "%s", password);
    int PasswordStatus = Password(password);
    if(PasswordStatus == 0)
        return -1;

    for(int i = 0; ScanfStatus == 1; i++)
    {
        ScanfStatus = fscanf(CPUFile, "%f", &program[i]);
    }

    fclose(CPUFile);
    return 1;
}

void CPU(float program[], struct cpu* StCPU)
{
    assert(program);
    assert(StCPU);

    int i = 0;
    float num = 0;
    float RAM[RAM_SIZE] = { 0 };
    while(program[i] != 0)
    {
        switch((int)program[i])
        {
        #define command(name, compile_code, CPU_code)\
            CPU_code

        #include "Compile/defines.h"

        #undef command(name, compile_code, CPU_code)
        default:
            assert(program[i]);
            printf("ERROR");
            break;
        }
        i++;
    }
}

int main()
{
    float program[Prog_Size] = {};
    struct cpu StCPU = {};

    StackConstruct(&StCPU.Stack);
    StackConstruct(&StCPU.Calls);
    int ReadStatus = Read(program);
    if(ReadStatus == -1)
        return -1;
    CPU(program, &StCPU);
    //DumpStack(StCPU.Stack);
    StackDestruct(&StCPU.Stack);
    StackDestruct(&StCPU.Calls);

    return 0;
}
