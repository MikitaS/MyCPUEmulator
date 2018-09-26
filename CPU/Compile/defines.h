///PUSHR AX из регистра в стек
///
///
///
///
///
///

#define Simple_Command_Compile(COMMAND)                                 \
else\
    if(strcmp(pointer[i], #COMMAND) == 0)                       \
    {                                                           \
        fprintf (textfile, "%d\n", COMMAND);                    \
    }

#define Register_Command(COMMAND)                                 \
else\
    if(strcmp(pointer[i], #COMMAND) == 0)                       \
    {                                                           \
        fprintf (textfile, "%d\n", COMMAND);                    \
        i++;\
        if(strcmp(pointer[i], "AX") == 0)\
            fprintf (textfile, "%d\n", AX);\
        else\
        if(strcmp(pointer[i], "BX") == 0)\
            fprintf (textfile, "%d\n", BX);\
        else\
        if(strcmp(pointer[i], "CX") == 0)\
            fprintf (textfile, "%d\n", CX);\
        else\
        if(strcmp(pointer[i], "DX") == 0)\
            fprintf (textfile, "%d\n", DX);\
    }

#define Jump_Command(COMMAND) \
else\
    if(strcmp(pointer[i], #COMMAND) == 0)     \
        {           \
            i++;        \
            if(isdigit(*pointer[i]))\
                fprintf (textfile, "%d %d\n", COMMAND, label[*pointer[i] - '0']);\
            else\
            {\
                printf("ERROR\nExpected digit after JUMP on the %d -th position\n", i);\
                exit(0);\
            }\
        }

#define RAM_Command(COMMAND)\
else \
    if(strcmp(pointer[i], #COMMAND) == 0) \
    { \
        i++; \
        int a = 0;\
        sscanf(pointer[i], "[%d]", &a);\
        fprintf (textfile, "%d %d\n", COMMAND, a);\
    }

#define CmdPush \
else\
    if(strcmp(pointer[i], "PUSH") == 0)\
        {\
            i++;\
            if(CheckFloat(pointer[i]))\
            {\
                fprintf (textfile, "%d %s\n", PUSH, pointer[i]);\
            }\
            else\
            {\
                printf("ERROR\nExpected float after PUSH on the %d -th position\n", i);\
                exit(0);\
            }\
        }

#define CPUPush \
        case PUSH: \
            StackPush(&StCPU->Stack, program[++i]); \
            break;

#define CPUOut \
        case OUT: \
            printf("%lg\n", StackPop(&StCPU->Stack)); \
            break;

#define CPUAdd \
        case ADD: \
            StackPush(&StCPU->Stack, StackPop(&StCPU->Stack) + StackPop(&StCPU->Stack)); \
            break;

#define CPUSub \
        case SUB: \
            num = StackPop(&StCPU->Stack);\
            StackPush(&StCPU->Stack,  StackPop(&StCPU->Stack) - num; \
            break;

#define CPUMul \
        case MUL:\
            StackPush(&StCPU->Stack, StackPop(&StCPU->Stack) * StackPop(&StCPU->Stack));\
            break;

#define CPUDiv \
        case DIV:\
            num = StackPop(&StCPU->Stack);\
            StackPush(&StCPU->Stack, StackPop(&StCPU->Stack) / num);\
            break;

#define CPUPopr \
        case POPR: \
            switch((int)program[i + 1])\
            { \
            case AX: \
                StCPU->ax = StackPop(&StCPU->Stack); \
                break;\
            case BX: \
                StCPU->bx = StackPop(&StCPU->Stack); \
                break;\
            case CX: \
                StCPU->cx = StackPop(&StCPU->Stack); \
                break;\
            case DX: \
                StCPU->dx = StackPop(&StCPU->Stack);\
                break;\
            }\
            i++;\
            break;


#define CPUPushr \
        case PUSHR: \
            switch((int)program[i + 1])\
            { \
            case AX: \
                StackPush(&StCPU->Stack, StCPU->ax); \
                break;\
            case BX: \
                StackPush(&StCPU->Stack, StCPU->bx); \
                break;\
            case CX: \
                StackPush(&StCPU->Stack, StCPU->cx); \
                break;\
            case DX: \
                StackPush(&StCPU->Stack, StCPU->dx);\
                break;\
            }\
            i++;\
            break;


#define CPUJump \
        case JUMP:\
            i = program[i + 1] - 1;\
            break;\


#define CPUJe \
        case JE:\
            if(StackPop(&StCPU->Stack) == StackPop(&StCPU->Stack))\
                ;\
            else\
                i++;\
            break;

#define CPUJne \
        case JNE:\
            if(StackPop(&StCPU->Stack) != StackPop(&StCPU->Stack))\
                ;\
            else \
                i++;\
            break;

#define CPUJa \
        case JA:\
            if(StackPop(&StCPU->Stack) > StackPop(&StCPU->Stack))\
                ;\
            else \
                i++; \
            break;

#define CPUJae \
        case JAE: \
            if(StackPop(&StCPU->Stack) >= StackPop(&StCPU->Stack))\
                ;\
            else \
                i++; \
            break;

#define CPUJb \
        case JB: \
            if(StackPop(&StCPU->Stack) < StackPop(&StCPU->Stack))\
                ;\
            else \
                i++;\
            break;

#define CPUJbe \
        case JBE: \
            if(StackPop(&StCPU->Stack) <= StackPop(&StCPU->Stack))\
                ;\
            else \
                i++;\
            break;

#define CPUSqrt \
        case SQRT:\
            StackPush(&StCPU->Stack, sqrt(StackPop(&StCPU->Stack)));\
            break;

#define CPUCat \
        case CAT: \
            printf("Meow\tmeow\n");\
            break;

#define CPUEnd \
        case END:\
            exit(0);\
            break;

#define CPUCall \
        case CALL: \
            StackPush(&StCPU->Calls, (float)(i + 1));\
            i = program[i + 1] - 1;\
            break;

#define CPURet \
        case RET:\
            i = (int)StackPop(&StCPU->Calls);\
            break;

#define CPUDog \
        case DOG: \
            printf("Gaw\tGaw\n");\
            break;

#define CPUParet \
        case PARET: \
            printf("Kyrlik\tKyrlik\n");\
            break;

#define CPUPushp\
        case PUSHP: \
            i++; \
            StackPush(&StCPU->Stack, RAM[(int)program[i]]); \
            break;

#define CPUPopp\
        case POPP: \
            i++; \
            RAM[(int)program[i]] = StackPop(&StCPU->Stack);\
            break;


command     (PUSH,      CmdPush,                            CPUPush)
command     (OUT,       Simple_Command_Compile(OUT),        CPUOut)
command     (ADD,       Simple_Command_Compile(ADD),        CPUAdd)
command     (SUB,       Simple_Command_Compile(SUB),        CPUSub)
command     (MUL,       Simple_Command_Compile(MUL),        CPUMul)
command     (DIV,       Simple_Command_Compile(DIV),        CPUDiv)
command     (PUSHR,     Register_Command(PUSHR),            CPUPushr)
command     (POPR,      Register_Command(POPR),             CPUPopr)
command     (JUMP,      Jump_Command(JUMP),                 CPUJump)
command     (JE,        Simple_Command_Compile(JE),         CPUJe)
command     (JNE,       Simple_Command_Compile(JNE),        CPUJne)
command     (JA,        Simple_Command_Compile(JA),         CPUJa)
command     (JAE,       Simple_Command_Compile(JAE),        CPUJae)
command     (JB,        Simple_Command_Compile(JB),         CPUJb)
command     (JBE,       Simple_Command_Compile(JBE),        CPUJbe)
command     (SQRT,      Simple_Command_Compile(SQRT),       CPUSqrt)
command     (CAT,       Simple_Command_Compile(CAT),        CPUCat)
command     (END,       Simple_Command_Compile(END),        CPUEnd)
command     (CALL,      Jump_Command(CALL),                 CPUCall)
command     (RET,       Simple_Command_Compile(RET),        CPURet)
command     (DOG,       Simple_Command_Compile(DOG),        CPUDog)
command     (PARET,     Simple_Command_Compile(PARET),      CPUParet)
command     (PUSHP,     RAM_Command(PUSHP),                 CPUPushp)
command     (POPP,      RAM_Command(POPP),                  CPUPopp)
