// war.c
// Projeto WAR Estruturado - Gestão de Territórios e Missões
// Autor: Klinger
// Data: 2025
// Descrição: Implementa o fluxo principal do jogo utilizando funções especializadas.

// Bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// Constantes globais
#define NUM_TERRITORIOS 5
#define MAX_TAM_NOME 30
#define MAX_TAM_COR 10
#define NUM_MISSOES 2

// Estrutura para território
typedef struct {
    char nome[MAX_TAM_NOME];
    char cor[MAX_TAM_COR];
    int tropas;
} Territorio;

// Protótipos das funções

// Setup e gerenciamento
Territorio* alocarMapa(int quantidade);
void inicializarTerritorios(Territorio* mapa, int quantidade);
void liberarMemoria(Territorio* mapa);

// Interface Usuário
void exibirMenuPrincipal(void);
void exibirMapa(const Territorio* mapa, int quantidade);
void exibirMissao(int missaoId);

// Lógica do jogo
void faseDeAtaque(Territorio* mapa, int quantidade);
void simularAtaque(Territorio* origem, Territorio* destino);
int sortearMissao(void);
int verificarVitoria(const Territorio* mapa, int quantidade, int missaoId, const char* corJogador);

// Utilitários
void limparBufferEntrada(void);

// Função principal
int main() {
    setlocale(LC_ALL, "");               // Configurar idioma Português
    srand(time(NULL));                   // Inicializa gerador de números aleatórios
    Territorio* mapa = alocarMapa(NUM_TERRITORIOS);
    if (!mapa) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    inicializarTerritorios(mapa, NUM_TERRITORIOS);
    const char corJogador[MAX_TAM_COR] = "Vermelho";
    int missaoId = sortearMissao();
    int opcao, venceu = 0;

    do {
        exibirMapa(mapa, NUM_TERRITORIOS);
        exibirMissao(missaoId);
        exibirMenuPrincipal();

        printf("Escolha sua ação: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 0:
                printf("Saindo do jogo...\n");
                break;
            case 1:
                faseDeAtaque(mapa, NUM_TERRITORIOS);
                break;
            case 2:
                venceu = verificarVitoria(mapa, NUM_TERRITORIOS, missaoId, corJogador);
                if (venceu)
                    printf("Parabéns! Você cumpriu sua missão!\n");
                else
                    printf("Missão ainda não cumprida. Continue jogando.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        printf("\nPressione Enter para continuar...");
        getchar();
    } while (!venceu && opcao != 0);

    liberarMemoria(mapa);
    return 0;
}
