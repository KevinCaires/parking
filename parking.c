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
bool push(Stack *stack_a, Stack *stack_b, Car car){
    if(stack_a->top >= MAX_LEN -1 && stack_b->top >= MAX_LEN -1)
        return false;

    if(stack_b->top < stack_a->top){
        stack_b->top = stack_b->top + 1;
        stack_b->car[stack_b->top] = car;
    }
    else{
        stack_a->top = stack_a->top + 1;
        stack_a->car[stack_a->top] = car;
    }

    return true;
}

// Retira um elemento do topo da pilha.
bool pop(Stack *stack_a, Stack *stack_b, char side, int index){
    if(stack_a->top < 0 && stack_b->top < 0)
        return false;

    if((side=='a' || side=='A') && index > stack_a->top)
        return false;
    else if((side=='b' || side=='B') && index > stack_b->top)
        return false;

    if(stack_a->top > 4 && stack_b->top > 4)
        return false;

    if(side=='a' || side=='A'){
        for(int i=stack_a->top; i>index; i--){
            stack_b->top += 1;
            stack_b->car[stack_b->top] = stack_a->car[i];
            stack_a->top -= 1;
        }
        printf("[%d]\t[%s | %s | %s] retirado.",
            stack_a->top + 1,
            stack_a->car[index].color,
            stack_a->car[index].model,
            stack_a->car[index].plate);
        stack_a->top = stack_a->top - 1;
    }
    else if(side=='b' || side=='B'){
        for(int i=stack_b->top; i>index; i--){
            stack_a->top += 1;
            stack_a->car[stack_a->top] = stack_b->car[i];
            stack_b->top -= 1;
        }
        printf("[%d]\t[%s | %s | %s] retirado.",
            stack_b->top + 1,
            stack_b->car[index].color,
            stack_b->car[index].model,
            stack_b->car[index].plate);
        stack_b->top = stack_b->top - 1;
    }

    return true;
}

// Mostra elementos da pilha.
void show_stack(Stack *stack_a, Stack *stack_b){
    printf("Lado A:\n");
    for(int i=stack_a->top; i>=0; i--){
        printf("[%d]\t[%s | %s | %s]\n",
            i+1,
            stack_a->car[i].color,
            stack_a->car[i].model,
            stack_a->car[i].plate);
    }

    printf("\nLado B:\n");
    for(int i=stack_b->top; i>=0; i--){
        printf("[%d]\t[%s | %s | %s]\n",
            i+1,
            stack_b->car[i].color,
            stack_b->car[i].model,
            stack_b->car[i].plate);
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
    int index;
    char side;
    Car car;
    Stack *stack_a = (Stack*)malloc(sizeof(Stack));
    Stack *stack_b = (Stack*)malloc(sizeof(Stack));

    initialize(stack_a);
    initialize(stack_b);

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
                if(push(stack_a, stack_b, car))
                    printf("Carro estacionado!");
                else
                    printf("Estacionamento cheio!");
                pause();
                break;

            case 2:
                clean_screen;
                printf("Escolha o lado [A|B]: ");
                scanf("%c", &side);
                getchar();
                printf("Escolha a posição: ");
                scanf("%d", &index);
                index -= 1;
                if(!pop(stack_a, stack_b, side,index))
                    printf("Não foi possível retirar o carro!");
                pause();
                break;

            case 3:
                clean_screen;
                show_stack(stack_a, stack_b);
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
