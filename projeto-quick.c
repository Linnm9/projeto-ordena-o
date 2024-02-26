#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void clean() {
    printf("\n");
    system("pause");
    system("cls");
}

void clean_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu(int *option, int *count) {
    printf("1 - Ordenação de números inteiros em ordem crescente\n");
    printf("2 - Ordenação de números inteiros em ordem decrescente\n");
    printf("3 - Ordenação de letras embaralhadas\n");
    printf("4 - Sair\n");
    scanf("%d", option);

    if(*option == 2) {
        *count = 1;
    }
}

void show_array(int array[], int tam) {
    for (int i = 0; i < tam; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void fill(int **array, int *tamanho) {
    printf("Digite o tamanho da array que você deseja ordenar: ");
    scanf("%d", tamanho);
    printf("-----------------------------------------------------\n");

    *array = malloc(*tamanho * sizeof(int));

    if(*array == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    } 

    for (int i = 0; i < *tamanho; i++){
        printf("Preencha com o valor desejado: ");
        scanf("%d", &(*array)[i]);
    }

    clean();
    printf("Array original: ");
    show_array(*array, *tamanho);
}

void switch_places(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition (int arranjo[], int inicio, int fim, int count) {
    int pivo = arranjo[fim];
    int i = inicio - 1;

    for(int j = inicio; j <= fim - 1; j++) {
        if(count == 1) {
            if(arranjo[j] >= pivo) {
                i++;
                switch_places(&arranjo[i], &arranjo[j]);
            }
        } else {
            if(arranjo[j] <= pivo) {
                i++;
                switch_places(&arranjo[i], &arranjo[j]);
            }
        }
    }
    switch_places(&arranjo[i + 1], &arranjo[fim]);
    return i + 1;
}

void quicksort(int arranjo[], int inicio, int fim, int count) {
    if(inicio < fim) {

        int p = partition(arranjo, inicio, fim, count);

        quicksort(arranjo, inicio, p - 1, count);
        quicksort(arranjo, p + 1, fim, count);
    }
}

void show_string(char *letra) {
    printf("%s", letra);
}

int compare(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

void receive(char **letra) {
    int tam;

    printf("Digite o tamanho da array: ");
    scanf("%d", &tam);
    clean_buffer();

    *letra = malloc((tam + 1)  * sizeof(char));

    if (*letra == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    printf("Digite a array: ");
    fgets(*letra, tam + 1, stdin);

    if((*letra)[strlen(*letra) - 1] == '\n') {
        (*letra)[strlen(*letra) - 1] = '\0';
    }
    
    qsort(*letra, strlen(*letra), sizeof(char), compare);
}

int main(){
    int opc;
    int count;
    int *array;
    char *letras;
    int tam;

    setlocale(LC_ALL, "");

    count = 0;
    do {
        menu(&opc, &count);
        system("cls");

        if(opc == 1 || opc == 2) {
            fill(&array, &tam);
        }
        
        switch(opc) {
            case 1 : {
                quicksort(array, 0, tam - 1, count);
                printf("Array ordenada em ordem crescente: ");
                show_array(array, tam);
                clean();
                free(array);
                break;
            }
            case 2 : {
                quicksort(array, 0, tam - 1, count);
                printf("Array ordenada em ordem decrescente: ");
                show_array(array, tam);
                clean();
                free(array);
                break;
            }
            case 3 : {
                receive(&letras);
                printf("Ordenada alfabeticamente: ");
                show_string(letras);
                clean();
                free(letras);
                break;
            }
            case 4 : {
                printf("Saindo...\n");
                clean();
                break;
            }
            default : {
                printf("Opção inválida!\n");
                clean();
                break;
            }   
        }
    } while(!(opc == 4));
    return 0;
}
