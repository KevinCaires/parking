#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define clean_screen system("clear");

#define true 1
#define false 0
typedef int bool;

#define MAX_LEN 10

typedef struct{
    char *model;
    char *color;
    char *plate;
} Car;

typedef struct{
    Car car[MAX_LEN];
    int top;
} Stack;

// Inicializa a pilha.
void initialize(Stack *stack){
    stack->top = -1;
}

// Insere um item no topo da pilha.
bool push(Stack *stack, Car car){
    if(stack->top >= MAX_LEN -1)
        return false;

    stack->top = stack->top + 1;
    stack->car[stack->top] = car;

    return true;
}

// Retira um elemento do topo da pilha.
bool pop(Stack *stack){
    if(stack->top < 0)
        return false;

    printf("[%d]\t[%s | %s | %s] retirado.",
        stack->top + 1,
        stack->car[stack->top].color,
        stack->car[stack->top].model,
        stack->car[stack->top].plate);
    stack->top = stack->top - 1;

    return true;
}

// Mostra elementos da pilha.
void show_stack(Stack *stack){
    for(int i=stack->top; i>=0; i--){
        printf("[%d]\t[%s | %s | %s]\n",
            i+1,
            stack->car[i].color,
            stack->car[i].model,
            stack->car[i].plate);
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

    initialize(stack);

    while(true){
        clean_screen;
        printf("Estacionamento:\n");
        printf("[1] Adicionar carro.\n"
               "[2] Retirar carro.\n"
               "[3] Mostrar estacionamento.\n"
               "[0] Sair\n");
        scanf("%d", &option);
        getchar();

        switch(option){
            case 1:
                clean_screen;
                car.color = (char*)malloc(sizeof(char));
                car.model = (char*)malloc(sizeof(char));
                car.plate = (char*)malloc(sizeof(char));
                printf("Modelo: ");
                scanf("%s", car.model);
                getchar();
                printf("Cor: ");
                scanf("%s", car.color);
                getchar();
                printf("Placa: ");
                scanf("%s", car.plate);
                getchar();
                if(push(stack, car))
                    printf("Carro estacionado!");
                else
                    printf("Não foi possível estacionar o carro!");
                pause();
                break;

            case 2:
                clean_screen;
                if(!pop(stack))
                    printf("Não foi possível retirar o carro!");
                pause();
                break;

            case 3:
                clean_screen;
                show_stack(stack);
                pause();
                break;

            case 0:
                return;

            default:
                printf("Opção inválida, tente novamente!");
                pause();
                break;
        }
    }
}
