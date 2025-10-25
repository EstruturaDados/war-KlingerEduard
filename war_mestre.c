#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Prototipação das funções
void inicializarTerritorios(Territorio *t, int n);
void exibirMapa(const Territorio *t, int n);
void atacar(Territorio *t, int atacante, int defensor);
int verificarMissao(const Territorio *t, int n, int tipoMissao, const char *corMissao);

// Função principal
int main() {
    srand(time(NULL));
    int n = 5;
    Territorio *territorios = (Territorio *)calloc(n, sizeof(Territorio));

    printf("=== WAR ESTRUTURADO - NÍVEL MESTRE ===\n\n");

    // Inicializa territórios automaticamente
    inicializarTerritorios(territorios, n);

    // Missão aleatória
    int tipoMissao = rand() % 2; // 0 = destruir cor, 1 = conquistar 3 territórios
    char corMissao[10] = "Verde";

    printf("SUA MISSÃO: ");
    if (tipoMissao == 0)
        printf("Destruir o exército %s\n", corMissao);
    else
        printf("Conquistar 3 territórios\n");

    int opcao, atk, def;
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                exibirMapa(territorios, n);
                printf("Escolha o território atacante (1-%d): ", n);
                scanf("%d", &atk);
                printf("Escolha o território defensor (1-%d): ", n);
                scanf("%d", &def);
                getchar();

                if (atk == def || atk < 1 || atk > n || def < 1 || def > n) {
                    printf("Escolha inválida!\n");
                    break;
                }
                atacar(territorios, atk - 1, def - 1);
                break;

            case 2:
                if (verificarMissao(territorios, n, tipoMissao, corMissao)) {
                    printf("\nMISSÃO CUMPRIDA! Você venceu o jogo!\n");
                    opcao = 0;
                } else {
                    printf("\nMissão ainda não concluída.\n");
                }
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    free(territorios);
    return 0;
}

// ---------------- Funções ---------------- //

void inicializarTerritorios(Territorio *t, int n) {
    const char *nomes[] = {"Brasil", "Argentina", "Chile", "México", "Canadá"};
    const char *cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Roxo"};
    const int tropasIniciais[] = {10, 8, 6, 7, 9};

    for (int i = 0; i < n; i++) {
        strcpy(t[i].nome, nomes[i]);
        strcpy(t[i].cor, cores[i]);
        t[i].tropas = tropasIniciais[i];
    }
}

void exibirMapa(const Territorio *t, int n) {
    printf("\n--- ESTADO ATUAL DO MAPA ---\n");
    for (int i = 0; i < n; i++) {
        printf("(%d) %-10s | Cor: %-8s | Tropas: %d\n", i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
    printf("------------------------------\n");
}

void atacar(Territorio *t, int atacante, int defensor) {
    if (t[atacante].tropas <= 1) {
        printf("%s não tem tropas suficientes para atacar!\n", t[atacante].nome);
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("%s (Ataque: %d) x %s (Defesa: %d)\n",
           t[atacante].nome, dadoAtaque, t[defensor].nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        t[defensor].tropas--;
        printf("Ataque bem-sucedido! %s perdeu 1 tropa.\n", t[defensor].nome);
        if (t[defensor].tropas <= 0) {
            printf("%s conquistou o território %s!\n", t[atacante].nome, t[defensor].nome);
            t[defensor].tropas = t[atacante].tropas / 2;
            strcpy(t[defensor].cor, t[atacante].cor);
        }
    } else {
        t[atacante].tropas--;
        printf("Defesa bem-sucedida! %s perdeu 1 tropa.\n", t[atacante].nome);
    }
}

int verificarMissao(const Territorio *t, int n, int tipoMissao, const char *corMissao) {
    if (tipoMissao == 0) {
        // Missão: destruir exército da cor
        for (int i = 0; i < n; i++) {
            if (strcmp(t[i].cor, corMissao) == 0) {
                return 0; // ainda existe território dessa cor
            }
        }
        return 1; // missão cumprida
    } else {
        // Missão: conquistar 3 territórios de uma mesma cor
        int contagem[5] = {0};
        const char *cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Roxo"};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 5; j++) {
                if (strcmp(t[i].cor, cores[j]) == 0)
                    contagem[j]++;
            }
        }
        for (int j = 0; j < 5; j++) {
            if (contagem[j] >= 3)
                return 1;
        }
        return 0;
    }
}
