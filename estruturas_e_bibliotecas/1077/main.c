#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    char *list;
    int size;
} Stack;

Stack *newStack(int size)
{
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->list = (char *) malloc(sizeof(char) * size);
    stack->size = 0;
    return stack;
}

Stack *delStack(Stack *stack)
{
    free(stack->list);
    free(stack);
    return NULL;
}

void stackPush(Stack *stack, char item)
{
    stack->list[stack->size] = item;
    stack->size++;
}

char stackPop(Stack *stack)
{
    if (stack->size == 0)
        return 0;
    stack->size--;
    return stack->list[stack->size];
}

char stackPeek(Stack *stack)
{
    if (stack->size == 0)
        return 0;
    return stack->list[stack->size - 1];
}

int stackIsEmpty(Stack *stack)
{
    return stack->size == 0;
}

int stackSize(Stack *stack)
{
    return stack->size;
}

int getPriority(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
    return 0;
}

int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void convertToPostfix(char *expression)
{
    Stack *stack = newStack(300);
    for (int i = 0; expression[i] != 0; i++)
    {
        if (isOperator(expression[i]))
        {
            while (!stackIsEmpty(stack) && getPriority(stackPeek(stack)) >= getPriority(expression[i]))
            {
                printf("%c", stackPop(stack));
            }
            stackPush(stack, expression[i]);
        }
        else if (expression[i] == '(')
            stackPush(stack, expression[i]);
        else if (expression[i] == ')')
        {
            while (stackPeek(stack) != '(')
            {
                printf("%c", stackPop(stack));
            }
            stackPop(stack);
        }
        else
            printf("%c", expression[i]);
    }

    while (!stackIsEmpty(stack))
    {
        printf("%c", stackPop(stack));
    }
    printf("\n");
    stack = delStack(stack);
}

int main()
{
    char expression[301];
    int n;
    scanf("%i", &n);
    while (n > 0)
    {
        scanf("%s", expression);
        convertToPostfix(expression);
        n--;
    }

    return 0;
}