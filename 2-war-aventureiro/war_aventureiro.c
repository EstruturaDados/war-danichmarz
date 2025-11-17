/*
 * =====================================================================
 * JOGO WAR - NIVEL AVENTUREIRO
 * Sistema de Cadastro e Batalhas entre Territorios
 * =====================================================================
 * Descricao: Este programa implementa um sistema de cadastro de
 * territorios com alocacao dinamica de memoria e simulacao de batalhas
 * utilizando ponteiros e numeros aleatorios.
 * 
 * Autor: [Seu Nome]
 * Data: Novembro/2025
 * Disciplina: Analise e Desenvolvimento de Sistemas
 * =====================================================================
 */

// ==================== BIBLIOTECAS ====================
#include <stdio.h>   // Entrada e saida padrao
#include <stdlib.h>  // Funcoes de alocacao de memoria (malloc, calloc, free)
#include <string.h>  // Manipulacao de strings
#include <time.h>    // Funcoes de tempo (para srand)

// ==================== DEFINICAO DA STRUCT ====================
/*
 * Struct Territorio:
 * Armazena as informacoes de cada territorio do jogo
 */
typedef struct {
    char nome[30];   // Nome do territorio
    char cor[10];    // Cor do exercito que controla
    int tropas;      // Quantidade de tropas presentes
} Territorio;

// ==================== PROTOTIPOS DAS FUNCOES ====================
Territorio* alocarTerritorios(int quantidade);
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void faseDeAtaque(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
int rolarDado();
void limparBuffer();

// ==================== FUNCAO PRINCIPAL ====================
int main() {
    Territorio* mapa = NULL;  // Ponteiro para o vetor de territorios
    int numTerritorios;
    int opcao;
    
    // Inicializa o gerador de numeros aleatorios
    srand(time(NULL));
    
    // ==================== CABECALHO ====================
    printf("=====================================================\n");
    printf("    JOGO WAR - SISTEMA DE BATALHAS (AVENTUREIRO)\n");
    printf("=====================================================\n\n");
    
    // ==================== ENTRADA DO NUMERO DE TERRITORIOS ====================
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &numTerritorios);
    
    // Validacao: pelo menos 2 territorios para poder atacar
    while (numTerritorios < 2) {
        printf("ERRO: E necessario pelo menos 2 territorios!\n");
        printf("Digite novamente: ");
        scanf("%d", &numTerritorios);
    }
    
    // ==================== ALOCACAO DINAMICA ====================
    mapa = alocarTerritorios(numTerritorios);
    
    // Verifica se a alocacao foi bem-sucedida
    if (mapa == NULL) {
        printf("ERRO: Falha ao alocar memoria!\n");
        return 1;  // Encerra o programa com codigo de erro
    }
    
    printf("\nMemoria alocada com sucesso para %d territorios!\n\n", numTerritorios);
    
    // ==================== CADASTRO DOS TERRITORIOS ====================
    cadastrarTerritorios(mapa, numTerritorios);
    
    // ==================== LOOP PRINCIPAL DO JOGO ====================
    do {
        printf("\n\n=====================================================\n");
        printf("                  MENU PRINCIPAL\n");
        printf("=====================================================\n");
        printf("1 - Exibir Mapa\n");
        printf("2 - Iniciar Fase de Ataque\n");
        printf("0 - Sair do Jogo\n");
        printf("=====================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                exibirMapa(mapa, numTerritorios);
                break;
            case 2:
                faseDeAtaque(mapa, numTerritorios);
                break;
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            limparBuffer();
            getchar();
        }
        
    } while (opcao != 0);
    
    // ==================== LIBERACAO DE MEMORIA ====================
    liberarMemoria(mapa);
    
    printf("\n=====================================================\n");
    printf("Memoria liberada com sucesso!\n");
    printf("Obrigado por jogar WAR Estruturado!\n");
    printf("=====================================================\n\n");
    
    return 0;
}

// ==================== IMPLEMENTACAO DAS FUNCOES ====================

/*
 * alocarTerritorios()
 * Parametros: quantidade de territorios a serem alocados
 * Retorno: ponteiro para o vetor de territorios alocado
 * Descricao: Aloca dinamicamente memoria usando calloc para o vetor
 */
Territorio* alocarTerritorios(int quantidade) {
    // calloc aloca memoria e inicializa com zeros
    Territorio* mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));
    return mapa;
}

/*
 * cadastrarTerritorios()
 * Parametros: ponteiro para o mapa e quantidade de territorios
 * Retorno: void
 * Descricao: Solicita dados de cada territorio e preenche a struct
 */
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    int i;
    
    printf("=====================================================\n");
    printf("           CADASTRO DE TERRITORIOS\n");
    printf("=====================================================\n");
    
    for (i = 0; i < quantidade; i++) {
        printf("\n--- TERRITORIO %d ---\n", i + 1);
        
        limparBuffer();
        
        // Nome do territorio
        printf("Digite o nome do territorio: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        
        // Cor do exercito
        printf("Digite a cor do exercito: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
        
        // Quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        // Validacao de tropas
        while (mapa[i].tropas <= 0) {
            printf("ERRO: Tropas devem ser maior que zero!\n");
            printf("Digite novamente: ");
            scanf("%d", &mapa[i].tropas);
        }
        
        printf("Territorio cadastrado com sucesso!\n");
    }
}

/*
 * exibirMapa()
 * Parametros: ponteiro constante para o mapa e quantidade
 * Retorno: void
 * Descricao: Exibe todos os territorios cadastrados em formato de tabela
 */
void exibirMapa(Territorio* mapa, int quantidade) {
    int i;
    
    printf("\n\n=====================================================\n");
    printf("              MAPA ATUAL DOS TERRITORIOS\n");
    printf("=====================================================\n\n");
    
    for (i = 0; i < quantidade; i++) {
        printf("TERRITORIO %d:\n", i + 1);
        printf("  Nome........: %s\n", mapa[i].nome);
        printf("  Cor.........: %s\n", mapa[i].cor);
        printf("  Tropas......: %d\n", mapa[i].tropas);
        printf("-----------------------------------------------------\n");
    }
}

/*
 * faseDeAtaque()
 * Parametros: ponteiro para o mapa e quantidade de territorios
 * Retorno: void
 * Descricao: Gerencia a fase de ataque, solicitando escolhas do jogador
 */
void faseDeAtaque(Territorio* mapa, int quantidade) {
    int indexAtacante, indexDefensor;
    char continuar;
    
    printf("\n\n=====================================================\n");
    printf("              FASE DE ATAQUE\n");
    printf("=====================================================\n");
    
    do {
        // Exibir territorios disponiveis
        printf("\nTerritorios disponiveis:\n");
        for (int i = 0; i < quantidade; i++) {
            printf("%d - %s (Cor: %s, Tropas: %d)\n", 
                   i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        
        // Escolher atacante
        printf("\nEscolha o territorio ATACANTE (1-%d): ", quantidade);
        scanf("%d", &indexAtacante);
        indexAtacante--;  // Ajusta para indice do vetor (0 a n-1)
        
        // Validacao do atacante
        while (indexAtacante < 0 || indexAtacante >= quantidade || 
               mapa[indexAtacante].tropas < 2) {
            if (mapa[indexAtacante].tropas < 2) {
                printf("ERRO: O atacante precisa de pelo menos 2 tropas!\n");
            } else {
                printf("ERRO: Territorio invalido!\n");
            }
            printf("Escolha novamente: ");
            scanf("%d", &indexAtacante);
            indexAtacante--;
        }
        
        // Escolher defensor
        printf("Escolha o territorio DEFENSOR (1-%d): ", quantidade);
        scanf("%d", &indexDefensor);
        indexDefensor--;  // Ajusta para indice do vetor
        
        // Validacao do defensor
        while (indexDefensor < 0 || indexDefensor >= quantidade || 
               indexDefensor == indexAtacante ||
               strcmp(mapa[indexAtacante].cor, mapa[indexDefensor].cor) == 0) {
            if (indexDefensor == indexAtacante) {
                printf("ERRO: Nao pode atacar o proprio territorio!\n");
            } else if (strcmp(mapa[indexAtacante].cor, mapa[indexDefensor].cor) == 0) {
                printf("ERRO: Nao pode atacar territorio da mesma cor!\n");
            } else {
                printf("ERRO: Territorio invalido!\n");
            }
            printf("Escolha novamente: ");
            scanf("%d", &indexDefensor);
            indexDefensor--;
        }
        
        // Executar ataque
        printf("\n>>> %s (%s) ataca %s (%s)!\n", 
               mapa[indexAtacante].nome, mapa[indexAtacante].cor,
               mapa[indexDefensor].nome, mapa[indexDefensor].cor);
        
        atacar(&mapa[indexAtacante], &mapa[indexDefensor]);
        
        // Perguntar se quer continuar atacando
        limparBuffer();
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf("%c", &continuar);
        
    } while (continuar == 's' || continuar == 'S');
}

/*
 * atacar()
 * Parametros: ponteiros para territorio atacante e defensor
 * Retorno: void
 * Descricao: Simula uma batalha usando dados aleatorios e atualiza territorios
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante, dadoDefensor;
    
    // Rolar dados
    dadoAtacante = rolarDado();
    dadoDefensor = rolarDado();
    
    printf("\n--- ROLAGEM DE DADOS ---\n");
    printf("Atacante rolou: %d\n", dadoAtacante);
    printf("Defensor rolou: %d\n", dadoDefensor);
    
    // Determinar vencedor
    if (dadoAtacante > dadoDefensor) {
        printf("\n*** ATACANTE VENCEU! ***\n");
        
        defensor->tropas--;
        
        // Verifica se o territorio foi conquistado
        if (defensor->tropas == 0) {
            printf("\n!!! TERRITORIO CONQUISTADO !!!\n");
            printf("%s agora pertence ao exercito %s!\n", 
                   defensor->nome, atacante->cor);
            
            // Transfere controle do territorio
            strcpy(defensor->cor, atacante->cor);
            
            // Move 1 tropa do atacante para o territorio conquistado
            defensor->tropas = 1;
            atacante->tropas--;
        } else {
            printf("O defensor perdeu 1 tropa.\n");
        }
    } else {
        printf("\n*** DEFENSOR RESISTIU! ***\n");
        atacante->tropas--;
        printf("O atacante perdeu 1 tropa.\n");
    }
    
    // Exibir estado apos ataque
    printf("\n--- SITUACAO APOS O ATAQUE ---\n");
    printf("%s: %d tropas (%s)\n", atacante->nome, atacante->tropas, atacante->cor);
    printf("%s: %d tropas (%s)\n", defensor->nome, defensor->tropas, defensor->cor);
}

/*
 * rolarDado()
 * Parametros: nenhum
 * Retorno: numero aleatorio entre 1 e 6
 * Descricao: Simula a rolagem de um dado de 6 faces
 */
int rolarDado() {
    return (rand() % 6) + 1;  // Gera numero entre 1 e 6
}

/*
 * liberarMemoria()
 * Parametros: ponteiro para o mapa
 * Retorno: void
 * Descricao: Libera a memoria alocada dinamicamente
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}

/*
 * limparBuffer()
 * Parametros: nenhum
 * Retorno: void
 * Descricao: Limpa o buffer de entrada (stdin)
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * =====================================================================
 * EXPLICACOES TECNICAS:
 * =====================================================================
 * 
 * 1. ALOCACAO DINAMICA:
 *    - calloc(n, tamanho) aloca memoria para n elementos e inicializa com 0
 *    - malloc(tamanho_total) apenas aloca, sem inicializar
 *    - free(ponteiro) libera a memoria alocada
 * 
 * 2. PONTEIROS:
 *    - Territorio* mapa: ponteiro para o primeiro elemento do vetor
 *    - mapa[i] acessa o elemento i do vetor
 *    - &mapa[i] passa o endereco do elemento para funcoes
 * 
 * 3. SISTEMA DE BATALHA:
 *    - Dados aleatorios de 1-6 para atacante e defensor
 *    - Atacante vence se dado > defensor
 *    - Conquista ocorre quando defensor chega a 0 tropas
 * 
 * 4. MODULARIZACAO:
 *    - Cada funcionalidade em uma funcao separada
 *    - Facilita manutencao e compreensao do codigo
 *    - Permite reutilizacao de codigo
 * 
 * 5. VALIDACOES:
 *    - Atacante precisa ter pelo menos 2 tropas
 *    - Nao pode atacar territorio proprio ou da mesma cor
 *    - Todas as entradas sao validadas
 * =====================================================================
 */