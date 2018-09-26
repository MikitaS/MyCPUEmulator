#include <stdio.h>
#include <cstdlib>
#include <string.h>
#define DEBUG_AssertOK // if(0)

#define AssertDefDestruct(Stack)                            \
    if(IsStackDestructed(Stack))                            \
        printf("Struct %s is destructed", #Stack);

const int Stack_Size = 1024, Stack_Increase = 512, Max_Stack_Size = 1024 + 20*512;
const int Canary_Num = 1337;

struct Stack
{
    int canary1;
    float* data;
    int Count;
    int Size;
    int canary2;
};

void    StackConstruct      (struct Stack* StackP);
void    StackDestruct       (struct Stack* StackP);
void    StackPush           (struct Stack* StackP, float num);
float   StackPop            (struct Stack* StackP);
void    StackRegPush        (struct Stack* StackP);
void    StackRegPop         (struct Stack* StackP);
void    StackIncrease       (struct Stack* StackP);
void    DumpStack           (struct Stack StackP);
bool    AssertOk            (struct Stack StackP);
bool    IsStackDestructed   (struct Stack StackP);

//!------------------------------------------------------------------------------------------
//!@param [IN] StackP - stack
//!@return [OUT] 1 if stack is destructed
//!@return [OUT] 0 if stack is not destructed
//!------------------------------------------------------------------------------------------
bool IsStackDestructed(struct Stack StackP)
{
    if((StackP.canary1 == 0) && (StackP.canary2 == 0) && (StackP.Size == 0) && (StackP.Count == 0))
        return 1;
    else
        return 0;
}

//!------------------------------------------------------------------------------------------
//!@param [IN] StackP - stack
//!@return [OUT] 1 if stack is normal
//!
//!@note in case of problems with stack abort
//!------------------------------------------------------------------------------------------
bool AssertOk(struct Stack StackP)
{
    if(IsStackDestructed(StackP))
        return 0;
    if((StackP.canary1 != Canary_Num) || (StackP.canary1 != Canary_Num))
    {
        printf("canary was destroyed\n");
        abort();
    }
    if(StackP.Size <= 0)
    {
        printf("problems with the size of stack\n");
        abort();
    }
    if((StackP.Count > StackP.Size) || (StackP.Count < 0))
    {
        printf("problems with the count of stack\n");
        abort();
    }
    return 1;
}

//!------------------------------------------------------------------------------------------
//!@param [IN] StackP - pointer on stack variable
//!
//!@note construct stack
//!------------------------------------------------------------------------------------------
void StackConstruct(struct Stack* StackP)
{
    StackP->canary1 = Canary_Num;
    StackP->canary2 = Canary_Num;
    (*StackP).Size = Stack_Size;
    (*StackP).Count = 0;
    StackP->data = (float *)calloc(StackP->Size, sizeof(float));
}

//!------------------------------------------------------------------------------------------
//!@param [IN] StackP - pointer on stack variable
//!
//!@note destruct stack
//!------------------------------------------------------------------------------------------
void StackDestruct(struct Stack* StackP)
{
    if(!IsStackDestructed(*StackP))
    {
        for( int i = 0; i < StackP->Size; i++)
            StackP->data[i] = 0;
        StackP->Count = 0;
        StackP->Size = 0;
        StackP->canary1 = 0;
        StackP->canary2 = 0;
    }
    free(StackP->data);
}

//!------------------------------------------------------------------------------------------
//!@param [IN] StackP - pointer on stack variable
//!@param [IN] number in stack
//!------------------------------------------------------------------------------------------
void StackPush(struct Stack* StackP, float num)
{
    DEBUG_AssertOK AssertOk(*StackP);
    StackP->data[StackP->Count++] = num;
    if((StackP->Count + 1) == StackP->Size)
        StackIncrease(StackP);
    DEBUG_AssertOK AssertOk(*StackP);
}

//!------------------------------------------------------------------------------------------
//!@param [IN] StackP - pointer on stack variable
//!@return [OUT] last number in stack
//!------------------------------------------------------------------------------------------
float StackPop(struct Stack* StackP)
{
    DEBUG_AssertOK AssertOk(*StackP);
    if(StackP->Count > 0)
    {
        float num = StackP->data[--StackP->Count];
        return num;
    }
    else
        return 0;
}

//!------------------------------------------------------------------------------------------
//!@param [IN] StackP - pointer on stack variable
//!
//!@note increase stack
//!------------------------------------------------------------------------------------------
void StackIncrease(struct Stack* StackP)
{
    DEBUG_AssertOK AssertOk(*StackP);
    if(StackP->Size >= Max_Stack_Size)
        return;
    StackP->Size += Stack_Increase;
    StackP->data = (float*)realloc(StackP->data, StackP->Size);
    DEBUG_AssertOK AssertOk(*StackP);
}

//!------------------------------------------------------------------------------------------
//!@param [IN] StackP -stack
//!
//!@note write all stack's compounds
//!------------------------------------------------------------------------------------------
void DumpStack(struct Stack StackP)
{
    DEBUG_AssertOK AssertOk(StackP);
    int i = 0;
    printf("_________________________________________________________________\n");
    printf("Canary1 = %d, canary2 = %d\n",StackP.canary1,StackP.canary2);
    printf("Stack size is %d\n", StackP.Size);
    printf("Stack count is %d\n", StackP.Count);
    printf("Current elements in stack are\n");
    for(;i < (StackP.Count);i++)
        printf("%lg\n",StackP.data[i]);
    printf("Writting elements of the stack finished\n");
    printf("_________________________________________________________________\n");
}
