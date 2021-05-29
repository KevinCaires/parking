#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define clean_screen system("clear");

#define true 1
#define false 0
typedef int bool;

typedef struct{
    char *model;
    char *color;
    char *plate;
} Car;

typedef struct CarElement{
    Car car;
    struct CarElement *next;
} Element;

typedef struct{
    Element *top;
} Stack;

// Inicializa a pilha.
void initialize(Stack *stack){
    stack->top = NULL;
}

// Insere um item no topo da pilha.
bool push(Stack *stack, Car car){
    Element *element = (Element*)malloc(sizeof(Element));
    
    if(element == NULL)
        return false;
    
    element->car = car;
    element->next = stack->top;
    stack->top = element;

    return true;
}

// Retira um elemento do topo da pilha.
bool pop(Stack *stack){
    if(stack->top == NULL)
        return false;
    
    Element *element = stack->top;
    stack->top = stack->top->next;
    free(element);

    return true;
}

// Mostra elementos da pilha.
void show_stack(Stack *stack){
    Element *element = stack->top;
    int position = 0;
    while(element != NULL){
        position++;
        printf("\n[%d]\tPlaca:[%s]-Modelo:[%s]-Cor:[%s]",
            position, element->car.plate, element->car.model, element->car.color);
    }
}

// Pausa o sistema.
void pause(void){
    printf("\nPressione enter para continuar...");
    getchar();
}

// Main.
void main(void){
    int option;
    Car car;
    Stack *stack = (Stack*)malloc(sizeof(Stack));

    while(true){
        clean_screen;
        printf("Estacionamento:\n");
        printf("[1] Adicionar carro.\n"
               "[2] Retirar carro.\n"
               "[3] Mostrar estacionamento.\n"
               "[0] Sair\n");
        switch(option){
            case 1:
                printf("Modelo: ");
                scanf("%s", car.model);
                getchar();
                break;
        }
    }
}
