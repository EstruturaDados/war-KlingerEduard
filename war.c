#include <stdio.h>
#include <string.h>

// Definição da estrutura de cada território
typedef struct {
    char nome[30];   // nome do território (máx 29 chars + '\0')
    char cor[10];    // cor do exército (máx 9 chars + '\0')
    int tropas;      // quantidade de tropas no território
} Territorio;

int main() {
    Territorio territorios[5]; // vetor para 5 territórios
    int i;

    // Cadastro dos territórios
    for (i = 0; i < 5; i++) {
        printf("Cadastro do território %d:\n", i+1);
        printf("Nome: ");
        scanf("%29s", territorios[i].nome); // lê nome
        printf("Cor do exército: ");
        scanf("%9s", territorios[i].cor);   // lê cor
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas); // lê número de tropas
    }

    // Exibição dos dados
    printf("\n--- Dados dos Territórios Cadastrados ---\n");
    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i+1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("-------------------------\n");
        }

    return 0;
}
