#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para representar um território com nome, cor e número de tropas
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para exibir o estado atual do mapa
void exibirMapa(Territorio *t, int n) {
    printf("\n--- ESTADO ATUAL DO MAPA ---\n");
    for (int i = 0; i < n; i++) {
        printf("(%d) %s - Cor: %s - Tropas: %d\n", i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
    printf("------------------------------\n");
}

// Função para simular um ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    // Verifica se os territórios têm a mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nNão é possível atacar um território da mesma cor!\n");
        return;
    }

    // Verifica se o atacante tem tropas suficientes
    if (atacante->tropas <= 1) {
        printf("\n%s precisa de mais de 1 tropa para atacar!\n", atacante->nome);
        return;
    }

    // Gera números aleatórios para simular dados de ataque e defesa
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    // Exibe o resultado dos dados
    printf("\n%s (Ataque: %d) x %s (Defesa: %d)\n",
           atacante->nome, dadoAtaque, defensor->nome, dadoDefesa);

    // Compara os dados: atacante vence se o dado de ataque for maior ou igual
    if (dadoAtaque >= dadoDefesa) {
        defensor->tropas--;
        printf("Ataque bem-sucedido! %s perdeu 1 tropa.\n", defensor->nome);
        // Se o defensor ficar sem tropas, o território é conquistado
        if (defensor->tropas <= 0) {
            printf("%s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);
            defensor->tropas = atacante->tropas / 2;
            strcpy(defensor->cor, atacante->cor);
        }
    } else {
        atacante->tropas--;
        printf("Defesa bem-sucedida! %s perdeu 1 tropa.\n", atacante->nome);
    }
}

// Função para liberar a memória alocada para o vetor de territórios
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    // Inicializa a semente para números aleatórios
    srand(time(NULL));

    // Solicita o número de territórios ao usuário
    int n;
    printf("=== WAR ESTRUTURADO - NÍVEL AVENTUREIRO ===\n\n");
    printf("Digite o número de territórios: ");
    scanf("%d", &n);
    getchar(); // Limpa o buffer do '\n'

    // Verifica se o número de territórios é válido
    if (n <= 0) {
        printf("Número de territórios inválido!\n");
        return 1;
    }

    // Aloca dinamicamente o vetor de territórios
    Territorio *territorios = (Territorio *)calloc(n, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro dos territórios
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
        getchar(); // Limpa o buffer do '\n'
        printf("\n");
    }

    int atk, def;

    // Laço interativo para ataques
    do {
        exibirMapa(territorios, n);
        printf("\nEscolha o território atacante (1-%d, 0 para sair): ", n);
        scanf("%d", &atk);
        if (atk == 0) break;
        printf("Escolha o território defensor (1-%d): ", n);
        scanf("%d", &def);
        getchar(); // Limpa o buffer do '\n'

        // Valida as escolhas do usuário
        if (atk == def || atk < 1 || atk > n || def < 1 || def > n) {
            printf("Escolha inválida!\n");
            continue;
        }

        // Realiza o ataque
        atacar(&territorios[atk - 1], &territorios[def - 1]);

    } while (1);

    // Libera a memória alocada
    liberarMemoria(territorios);
    printf("\nFim do jogo!\n");
    return 0;
}