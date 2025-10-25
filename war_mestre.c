#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para representar um território no jogo
typedef struct {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do jogador controlador
    int tropas;     // Quantidade de tropas
} Territorio;

// Declaração das funções
void inicializarTerritorios(Territorio *mapa, int tamanho);
void exibirMapa(Territorio *mapa, int tamanho);
void atacar(Territorio *atacante, Territorio *defensor);
void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
void exibirMissao(char *missao);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void liberarMemoria(Territorio *mapa, char *missao);

// Função principal
int main() {
    srand(time(NULL)); // Inicializa semente para números aleatórios
    int numTerritorios = 5; // Número de territórios no jogo

    // Aloca vetor de territórios
    Territorio *mapa = (Territorio *)calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa!\n");
        return 1;
    }

    // Vetor com 5 missões estratégicas
    char *missoes[] = {
        "Conquistar 3 territórios consecutivos",
        "Eliminar todas as tropas Vermelhas",
        "Controlar 2 territórios com mais de 5 tropas",
        "Destruir o exército Azul",
        "Conquistar todos os territórios"
    };
    int totalMissoes = 5;

    // Aloca memória para a missão do jogador
    char *missaoJogador = (char *)malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para a missão!\n");
        free(mapa);
        return 1;
    }

    printf("=== JOGO WAR - DESAFIO ESTRUTURADO ===\n\n");

    // Inicializa o mapa com territórios
    inicializarTerritorios(mapa, numTerritorios);

    // Atribui uma missão aleatória ao jogador
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    int opcao, indiceAtacante, indiceDefensor;
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n' do buffer

        if (opcao == 1) {
            exibirMapa(mapa, numTerritorios);
            printf("Digite o número do território atacante (1 a %d): ", numTerritorios);
            scanf("%d", &indiceAtacante);
            printf("Digite o número do território defensor (1 a %d): ", numTerritorios);
            scanf("%d", &indiceDefensor);
            getchar();

            // Valida a entrada
            if (indiceAtacante < 1 || indiceAtacante > numTerritorios ||
                indiceDefensor < 1 || indiceDefensor > numTerritorios ||
                indiceAtacante == indiceDefensor) {
                printf("Escolha inválida! Tente novamente.\n");
                continue;
            }
            // Verifica se o defensor é inimigo
            if (strcmp(mapa[indiceAtacante - 1].cor, mapa[indiceDefensor - 1].cor) == 0) {
                printf("Você não pode atacar um território aliado!\n");
                continue;
            }
            // Verifica se há tropas suficientes
            if (mapa[indiceAtacante - 1].tropas <= 1) {
                printf("O território %s não tem tropas suficientes para atacar!\n", mapa[indiceAtacante - 1].nome);
                continue;
            }
            atacar(&mapa[indiceAtacante - 1], &mapa[indiceDefensor - 1]);

        } else if (opcao == 2) {
            if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
                printf("\nPARABÉNS! Você completou a missão e venceu o jogo!\n");
                opcao = 0; // Encerra o jogo
            } else {
                printf("\nA missão ainda não foi completada.\n");
            }
        } else if (opcao == 0) {
            printf("\nJogo encerrado.\n");
        } else {
            printf("Opção inválida! Escolha 0, 1 ou 2.\n");
        }
    } while (opcao != 0);

    // Libera memória alocada
    liberarMemoria(mapa, missaoJogador);
    return 0;
}

// Inicializa o mapa com territórios, cores e tropas
void inicializarTerritorios(Territorio *mapa, int tamanho) {
    char *nomes[] = {"Brasil", "Argentina", "Chile", "México", "Canadá"};
    char *cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Roxo"};
    int tropas[] = {10, 8, 6, 7, 9};

    for (int i = 0; i < tamanho; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = tropas[i];
    }
}

// Exibe o estado atual do mapa
void exibirMapa(Territorio *mapa, int tamanho) {
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("(%d) %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("------------------\n");
}

// Simula um ataque entre territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1; // Rola dado de 1 a 6
    int dadoDefensor = rand() % 6 + 1;

    printf("%s (Dado: %d) ataca %s (Dado: %d)\n", atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        defensor->tropas--; // Defensor perde uma tropa
        printf("Ataque bem-sucedido! %s perdeu 1 tropa.\n", defensor->nome);
        if (defensor->tropas <= 0) {
            printf("%s conquistou %s!\n", atacante->nome, defensor->nome);
            defensor->tropas = atacante->tropas / 2; // Transfere metade das tropas
            strcpy(defensor->cor, atacante->cor);    // Atualiza a cor
            atacante->tropas -= defensor->tropas;    // Reduz tropas do atacante
        }
    } else {
        atacante->tropas--; // Atacante perde uma tropa
        printf("Defesa bem-sucedida! %s perdeu 1 tropa.\n", atacante->nome);
    }
}

// Atribui uma missão aleatória ao jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes; // Escolhe uma missão aleatoriamente
    strcpy(destino, missoes[indice]);   // Copia a missão para o destino
}

// Exibe a missão do jogador
void exibirMissao(char *missao) {
    printf("Missão do jogador: %s\n", missao);
}

// Verifica se a missão foi cumprida
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    char *corJogador = mapa[0].cor; // Assume que o jogador controla a cor do primeiro território

    if (strcmp(missao, "Conquistar 3 territórios consecutivos") == 0) {
        int consecutivos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                consecutivos++;
                if (consecutivos >= 3) return 1; // Missão cumprida
            } else {
                consecutivos = 0; // Reseta se encontrar território inimigo
            }
        }
        return 0;
    }
    if (strcmp(missao, "Eliminar todas as tropas Vermelhas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0) return 0; // Ainda há territórios vermelhos
        }
        return 1;
    }
    if (strcmp(missao, "Controlar 2 territórios com mais de 5 tropas") == 0) {
        int contagem = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas > 5) {
                contagem++;
            }
        }
        return contagem >= 2;
    }
    if (strcmp(missao, "Destruir o exército Azul") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) return 0; // Ainda há territórios azuis
        }
        return 1;
    }
    if (strcmp(missao, "Conquistar todos os territórios") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0) return 0; // Nem todos são do jogador
        }
        return 1;
    }
    return 0; // Caso a missão não seja reconhecida
}

// Libera a memória alocada
void liberarMemoria(Territorio *mapa, char *missao) {
    free(mapa);       // Libera o vetor de territórios
    free(missao);     // Libera a missão do jogador
}