#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char aStack[20];
int aTop = -1;

//Please implement all the functions
int isEmpty (char stack[], int* pTop) {
    if(*pTop == -1){
        return 1;
    }
    return 0;
}
int isFull (char stack[], int* pTop) {
    if(*pTop == 20-1){
        return 1;
    }
    return 0;
}

//You need to throw exceptions when user try to push more char but the stack is full
char push (char stack[], int* pTop, char c) {
    if(*pTop == 20 - 1){
        printf("stack full");
    }
    *pTop += 1;
    aStack[*pTop] = c;
    return c;
}
//You need to throw exceptions when user try to pop out more char but the stack is empty
char pop (char stack [], int* pTop) {
    if(*pTop == -1){
        printf("stack empty");
    }
    char out;
    out = aStack[*pTop];
    *pTop -= 1;
    return out;
}
//You need to throw exceptions when the stack is empty
char top (char stack [], int* pTop) {
    if(*pTop == -1){
        printf("stack empty");
    }
    char out = aStack[*pTop];
    return out;
}

//you need to reverse the order of the input string(size <= 20)
//the implementation requires using the stack
//e.g. input "Hello World", your program need to print "dlroW olleH"
void reverse(char* string, int size){
    for(int i = 0; i < size; i++){
        push(aStack, &aTop, string[i]);
    }
    for(int i = 0; i < size; i++){
        printf("%c", pop(aStack, &aTop));
    }
}

//you need to check whether the input expression's brackets is balanced
//return 1:true 0:false
//the implementation requires using the stack
//e.g. input "(a+b)*c)" is not balanced and "((a+b)/c)" is balanced
int balancedbrackets(char* string, int size){
    for(int i = 0; i < size; i++){
        if(string[i] == '('){
            push(aStack, &aTop, string[i]);
        }
        else if(string[i] == ')'){
            pop(aStack, &aTop);
        }
        else{
            //do nothing
        }
    }
    if(isEmpty(aStack, &aTop)){
        return 1;
    }
    else{
        return 0;
    }
}

int main () {
    char* string = "Hello World";
    printf("The reverse of %s is ", string);
    reverse(string, strlen(string));

    char* expression = "((a+b)/c)";
    int result = balancedbrackets(expression, strlen(expression));
    printf(". The expression %s is ", expression);
    if(result){
        printf("balanced\n");
    } else {
        printf("not balanced\n");
    }
    return 0;
}


