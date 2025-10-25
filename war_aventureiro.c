#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void exibirMapa(Territorio *t, int n) {
    printf("\n--- ESTADO ATUAL DO MAPA ---\n");
    for (int i = 0; i < n; i++) {
        printf("(%d) %s - Cor: %s - Tropas: %d\n", i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
    printf("------------------------------\n");
}

void atacar(Territorio *t, int atacante, int defensor) {
    if (t[atacante].tropas <= 1) {
        printf("\n%s não tem tropas suficientes para atacar!\n", t[atacante].nome);
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n%s (Ataque: %d) x %s (Defesa: %d)\n",
           t[atacante].nome, dadoAtaque, t[defensor].nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        t[defensor].tropas--;
        printf("Ataque bem-sucedido! %s perdeu 1 tropa.\n", t[defensor].nome);
        if (t[defensor].tropas <= 0) {
            printf("%s conquistou o território %s!\n",
                   t[atacante].nome, t[defensor].nome);
            t[defensor].tropas = t[atacante].tropas / 2;
            strcpy(t[defensor].cor, t[atacante].cor);
        }
    } else {
        t[atacante].tropas--;
        printf("Defesa bem-sucedida! %s perdeu 1 tropa.\n", t[atacante].nome);
    }
}

int main() {
    srand(time(NULL));
    int n = 5;
    Territorio *territorios = (Territorio *)calloc(n, sizeof(Territorio));

    printf("=== WAR ESTRUTURADO - NÍVEL AVENTUREIRO ===\n\n");

    for (int i = 0; i < n; i++) {
        printf("Cadastro do território %d:\n", i + 1);
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar();
        printf("\n");
    }

    int opcao, atk, def;

    do {
        exibirMapa(territorios, n);
        printf("\nEscolha o território atacante (1-%d, 0 para sair): ", n);
        scanf("%d", &atk);
        if (atk == 0) break;
        printf("Escolha o território defensor (1-%d): ", n);
        scanf("%d", &def);
        getchar();

        if (atk == def || atk < 1 || atk > n || def < 1 || def > n) {
            printf("Escolha inválida!\n");
            continue;
        }

        atacar(territorios, atk - 1, def - 1);

    } while (1);

    free(territorios);
    printf("\nFim do jogo!\n");
    return 0;
}
