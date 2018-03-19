#include <stdio.h>
#include <stdlib.h>

#define STACK_OVERFLOW 100
#define STACK_UNDERFLOW 200
#define OUT_OF_MEMORY 300
#define CANT_OPEN_FILE 400

typedef struct Stack {
    int * data; // pointer to dynamic array
    size_t size; // max size of stack
    size_t top; // index of top element
} stack_type;

/**
 * write parameter value to the top element of stack and increment index of top
 */
void push(stack_type *stack, const int value) {
    if (stack->top >= stack->size) {
        exit(STACK_OVERFLOW);
    }
    stack->data[stack->top] = value;
    stack->top++;
}

/**
 * decrement index of top
 * @return value of the top element of stack
 */
int pop(stack_type *stack) {
    if (stack->top == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->top--;
    return stack->data[stack->top];
}

/**
 * create struct stack and create there dynamic array with max_size
 * @return pointer to the created stack
 */
stack_type* createStack(size_t max_size) {
    stack_type *stack = NULL;
    stack = (stack_type*) malloc (sizeof(stack_type));
    if (stack == NULL) {
        exit(OUT_OF_MEMORY);
    }
    stack->size = max_size;
    stack->data = (int*) malloc (stack->size * sizeof(int));
    if (stack->data == NULL) {
        free(stack);
        exit(OUT_OF_MEMORY);
    }
    stack->top = 0;
    return stack;
}


/*
 * clear memory
 */
void deleteStack(stack_type *stack) {
    free(stack->data);
    free(stack);
    stack = NULL;
}

int main() {

    FILE *Fin = NULL, *Fout = NULL; // open file to read
    Fin = fopen("stack.in", "r");
    if (Fin == NULL){
        exit(CANT_OPEN_FILE);
    }

    size_t M;
    fscanf(Fin, "%d\n", &M); // scan size of stack and create stack
    stack_type * stack;
    stack = createStack(M);

    int value = 0; // variable to read value
    char sign = 0; // variable to read - or +
    int i; // counter

    Fout = fopen("stack.out", "w"); // open file to write
    if (Fout == NULL){
        exit(CANT_OPEN_FILE);
    }

    for(i = 0; i < M; i++){
        fscanf(Fin, "%c ", &sign); // read sign
        if(sign == '-'){
            fprintf(Fout, "%d\n", pop(stack)); // if - then write top number to the output file
        }
        if(sign=='+'){ // if + then read value from input file and add it to the top
            fscanf(Fin, "%d\n", &value);
            push(stack, value);
        }
    }

    fclose(Fin); // close files and clear memory
    fclose(Fout);
    deleteStack(stack);

    return 0;
}