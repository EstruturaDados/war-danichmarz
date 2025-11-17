/*
 * =====================================================================
 * JOGO WAR - NIVEL MESTRE
 * Sistema Completo com Missoes Estrategicas
 * =====================================================================
 * Descricao: Implementacao completa do jogo War com sistema de missoes,
 * verificacao de vitoria, modularizacao total e uso avancado de ponteiros.
 * 
 * Autor: [Seu Nome]
 * Data: Novembro/2025
 * Disciplina: Analise e Desenvolvimento de Sistemas
 * =====================================================================
 */

// ==================== BIBLIOTECAS ====================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== CONSTANTES ====================
#define NUM_TERRITORIOS 5
#define MAX_MISSOES 5
#define TAM_STRING 100

// ==================== ESTRUTURA DE DADOS ====================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ==================== PROTOTIPOS DAS FUNCOES ====================
// Funcoes de setup e gerenciamento de memoria
Territorio* alocarMapa(int quantidade);
void inicializarTerritorios(Territorio* mapa, int quantidade);
void liberarMemoria(Territorio* mapa);

// Funcoes de interface com o usuario
void exibirMenuPrincipal();
void exibirMapa(const Territorio* mapa, int quantidade);
void exibirMissao(const char* missao);

// Funcoes de logica principal do jogo
void faseDeAtaque(Territorio* mapa, int quantidade);
void simularAtaque(Territorio* atacante, Territorio* defensor);
int sortearMissao();
int verificarVitoria(const char* missao, const Territorio* mapa, int quantidade, const char* corJogador);

// Funcao utilitaria
void limparBufferEntrada();

// ==================== FUNCAO PRINCIPAL ====================
int main() {
    // Variaveis principais
    Territorio* mapa = NULL;
    char* missaoJogador = NULL;
    char corJogador[10];
    int opcao;
    int jogoAtivo = 1;
    int missaoId;
    
    // Vetor de missoes disponiveis
    char* missoes[MAX_MISSOES] = {
        "Destruir completamente o exercito Verde",
        "Conquistar pelo menos 3 territorios",
        "Dominar todos os territorios do mapa",
        "Reduzir o exercito Azul a menos de 5 tropas totais",
        "Controlar territorios com pelo menos 20 tropas no total"
    };
    
    // ==================== CONFIGURACAO INICIAL ====================
    // Inicializa gerador de numeros aleatorios
    srand(time(NULL));
    
    // Cabecalho
    printf("=====================================================\n");
    printf("         JOGO WAR - SISTEMA COMPLETO (MESTRE)\n");
    printf("=====================================================\n");
    printf("    Conquiste territorios e cumpra sua missao!\n");
    printf("=====================================================\n\n");
    
    // Aloca memoria para o mapa
    mapa = alocarMapa(NUM_TERRITORIOS);
    if (mapa == NULL) {
        printf("ERRO: Falha ao alocar memoria para o mapa!\n");
        return 1;
    }
    
    // Inicializa territorios automaticamente
    inicializarTerritorios(mapa, NUM_TERRITORIOS);
    
    // Define cor do jogador
    printf("Digite a cor do seu exercito: ");
    fgets(corJogador, sizeof(corJogador), stdin);
    corJogador[strcspn(corJogador, "\n")] = '\0';
    
    // Aloca memoria para missao do jogador
    missaoJogador = (char*) malloc(TAM_STRING * sizeof(char));
    if (missaoJogador == NULL) {
        printf("ERRO: Falha ao alocar memoria para a missao!\n");
        liberarMemoria(mapa);
        return 1;
    }
    
    // Sorteia e atribui missao
    missaoId = sortearMissao();
    strcpy(missaoJogador, missoes[missaoId]);
    
    printf("\n=====================================================\n");
    printf("           SUA MISSAO SECRETA FOI ATRIBUIDA\n");
    printf("=====================================================\n");
    exibirMissao(missaoJogador);
    printf("\n=====================================================\n");
    
    printf("\nPressione ENTER para comecar o jogo...");
    getchar();
    
    // ==================== LOOP PRINCIPAL DO JOGO ====================
    do {
        // Exibe estado atual
        exibirMapa(mapa, NUM_TERRITORIOS);
        exibirMissao(missaoJogador);
        exibirMenuPrincipal();
        
        // Le opcao do jogador
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        
        // Processa opcao escolhida
        switch (opcao) {
            case 1:
                // Fase de ataque
                faseDeAtaque(mapa, NUM_TERRITORIOS);
                break;
                
            case 2:
                // Verificar se cumpriu missao
                if (verificarVitoria(missaoJogador, mapa, NUM_TERRITORIOS, corJogador)) {
                    printf("\n");
                    printf("*************************************************\n");
                    printf("*                                               *\n");
                    printf("*           PARABENS! VOCE VENCEU!              *\n");
                    printf("*                                               *\n");
                    printf("*         Missao cumprida com sucesso!          *\n");
                    printf("*                                               *\n");
                    printf("*************************************************\n");
                    jogoAtivo = 0;
                } else {
                    printf("\n>>> Missao ainda nao foi cumprida. Continue jogando!\n");
                }
                break;
                
            case 0:
                // Sair do jogo
                printf("\nEncerrando o jogo...\n");
                jogoAtivo = 0;
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
        // Pausa para leitura
        if (jogoAtivo && opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
        
    } while (jogoAtivo);
    
    // ==================== LIMPEZA ====================
    liberarMemoria(mapa);
    free(missaoJogador);
    
    printf("\n=====================================================\n");
    printf("Obrigado por jogar WAR Estruturado!\n");
    printf("Memoria liberada com sucesso.\n");
    printf("=====================================================\n\n");
    
    return 0;
}

// ==================== IMPLEMENTACAO DAS FUNCOES ====================

/*
 * alocarMapa()
 * Aloca dinamicamente memoria para o vetor de territorios
 */
Territorio* alocarMapa(int quantidade) {
    Territorio* mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));
    return mapa;
}

/*
 * inicializarTerritorios()
 * Inicializa automaticamente os territorios com dados pre-definidos
 */
void inicializarTerritorios(Territorio* mapa, int quantidade) {
    // Dados pre-definidos dos territorios
    char* nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia"};
    char* cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Roxo"};
    int tropas[] = {10, 8, 12, 6, 9};
    
    printf("\n>>> Inicializando territorios do mapa...\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = tropas[i];
        
        printf("Territorio %d: %s (Cor: %s, Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    
    printf("\n>>> Mapa inicializado com sucesso!\n\n");
}

/*
 * liberarMemoria()
 * Libera a memoria alocada dinamicamente para o mapa
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}

/*
 * exibirMenuPrincipal()
 * Exibe o menu de opcoes para o jogador
 */
void exibirMenuPrincipal() {
    printf("\n=====================================================\n");
    printf("                  MENU PRINCIPAL\n");
    printf("=====================================================\n");
    printf("1 - Iniciar Fase de Ataque\n");
    printf("2 - Verificar se Cumpriu a Missao\n");
    printf("0 - Sair do Jogo\n");
    printf("=====================================================\n");
}

/*
 * exibirMapa()
 * Exibe o estado atual de todos os territorios
 * Usa const para garantir que nao modifica os dados
 */
void exibirMapa(const Territorio* mapa, int quantidade) {
    printf("\n\n=====================================================\n");
    printf("              MAPA ATUAL DOS TERRITORIOS\n");
    printf("=====================================================\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("TERRITORIO %d:\n", i + 1);
        printf("  Nome........: %s\n", mapa[i].nome);
        printf("  Cor.........: %s\n", mapa[i].cor);
        printf("  Tropas......: %d\n", mapa[i].tropas);
        printf("-----------------------------------------------------\n");
    }
}

/*
 * exibirMissao()
 * Exibe a missao atual do jogador
 */
void exibirMissao(const char* missao) {
    printf("\n>>> SUA MISSAO: %s\n", missao);
}

/*
 * faseDeAtaque()
 * Gerencia a fase de ataque entre territorios
 */
void faseDeAtaque(Territorio* mapa, int quantidade) {
    int indexAtacante, indexDefensor;
    char continuar;
    
    printf("\n\n=====================================================\n");
    printf("              FASE DE ATAQUE\n");
    printf("=====================================================\n");
    
    do {
        // Lista territorios disponiveis
        printf("\nTerritorios disponiveis:\n");
        for (int i = 0; i < quantidade; i++) {
            printf("%d - %s (Cor: %s, Tropas: %d)\n",
                   i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        
        // Escolha do atacante
        printf("\nEscolha o territorio ATACANTE (1-%d): ", quantidade);
        scanf("%d", &indexAtacante);
        indexAtacante--;
        
        // Validacao do atacante
        while (indexAtacante < 0 || indexAtacante >= quantidade ||
               mapa[indexAtacante].tropas < 2) {
            if (indexAtacante >= 0 && indexAtacante < quantidade) {
                printf("ERRO: O atacante precisa ter pelo menos 2 tropas!\n");
            } else {
                printf("ERRO: Territorio invalido!\n");
            }
            printf("Escolha novamente: ");
            scanf("%d", &indexAtacante);
            indexAtacante--;
        }
        
        // Escolha do defensor
        printf("Escolha o territorio DEFENSOR (1-%d): ", quantidade);
        scanf("%d", &indexDefensor);
        indexDefensor--;
        
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
        
        // Executa o ataque
        printf("\n>>> %s (%s) ataca %s (%s)!\n",
               mapa[indexAtacante].nome, mapa[indexAtacante].cor,
               mapa[indexDefensor].nome, mapa[indexDefensor].cor);
        
        simularAtaque(&mapa[indexAtacante], &mapa[indexDefensor]);
        
        // Pergunta se quer continuar
        limparBufferEntrada();
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf("%c", &continuar);
        
    } while (continuar == 's' || continuar == 'S');
}

/*
 * simularAtaque()
 * Simula uma batalha entre dois territorios usando dados aleatorios
 */
void simularAtaque(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante, dadoDefensor;
    
    // Rola dados (1-6)
    dadoAtacante = (rand() % 6) + 1;
    dadoDefensor = (rand() % 6) + 1;
    
    printf("\n--- ROLAGEM DE DADOS ---\n");
    printf("Atacante rolou: %d\n", dadoAtacante);
    printf("Defensor rolou: %d\n", dadoDefensor);
    
    // Resolve batalha
    if (dadoAtacante > dadoDefensor) {
        printf("\n*** ATACANTE VENCEU! ***\n");
        defensor->tropas--;
        
        // Verifica conquista
        if (defensor->tropas == 0) {
            printf("\n!!! TERRITORIO CONQUISTADO !!!\n");
            printf("%s agora pertence ao exercito %s!\n",
                   defensor->nome, atacante->cor);
            
            // Transfere controle
            strcpy(defensor->cor, atacante->cor);
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
    
    // Estado apos ataque
    printf("\n--- SITUACAO APOS O ATAQUE ---\n");
    printf("%s: %d tropas (%s)\n", atacante->nome, atacante->tropas, atacante->cor);
    printf("%s: %d tropas (%s)\n", defensor->nome, defensor->tropas, defensor->cor);
}

/*
 * sortearMissao()
 * Sorteia aleatoriamente um ID de missao
 */
int sortearMissao() {
    return rand() % MAX_MISSOES;
}

/*
 * verificarVitoria()
 * Verifica se o jogador cumpriu sua missao
 * Retorna 1 se venceu, 0 caso contrario
 */
int verificarVitoria(const char* missao, const Territorio* mapa, int quantidade, const char* corJogador) {
    // Missao 1: Destruir exercito Verde
    if (strstr(missao, "Verde") != NULL) {
        int existeVerde = 0;
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
                existeVerde = 1;
                break;
            }
        }
        return !existeVerde;
    }
    
    // Missao 2: Conquistar pelo menos 3 territorios
    if (strstr(missao, "3 territorios") != NULL) {
        int contadorTerritorios = 0;
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contadorTerritorios++;
            }
        }
        return contadorTerritorios >= 3;
    }
    
    // Missao 3: Dominar todos os territorios
    if (strstr(missao, "todos os territorios") != NULL) {
        int dominaTotal = 1;
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0) {
                dominaTotal = 0;
                break;
            }
        }
        return dominaTotal;
    }
    
    // Missao 4: Reduzir exercito Azul
    if (strstr(missao, "Azul") != NULL) {
        int totalAzul = 0;
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) {
                totalAzul += mapa[i].tropas;
            }
        }
        return totalAzul < 5;
    }
    
    // Missao 5: Controlar 20+ tropas
    if (strstr(missao, "20 tropas") != NULL) {
        int totalTropas = 0;
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                totalTropas += mapa[i].tropas;
            }
        }
        return totalTropas >= 20;
    }
    
    return 0;
}

/*
 * limparBufferEntrada()
 * Limpa o buffer de entrada para evitar problemas com scanf
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * =====================================================================
 * EXPLICACOES TECNICAS FINAIS:
 * =====================================================================
 * 
 * 1. MODULARIZACAO COMPLETA:
 *    - Cada funcionalidade em funcao separada
 *    - Main() apenas orquestra o fluxo
 *    - Facil manutencao e expansao
 * 
 * 2. SISTEMA DE MISSOES:
 *    - Vetor de strings com missoes pre-definidas
 *    - Sorteio aleatorio no inicio
 *    - Alocacao dinamica com malloc
 *    - Verificacao condicional inteligente
 * 
 * 3. CONST CORRECTNESS:
 *    - Funcoes de leitura usam const
 *    - Garante que dados nao sejam modificados
 *    - Boa pratica profissional
 * 
 * 4. PASSAGEM POR REFERENCIA E VALOR:
 *    - Ponteiros para modificar dados (atacante/defensor)
 *    - Const para apenas ler (exibirMapa, verificarVitoria)
 * 
 * 5. GERENCIAMENTO DE MEMORIA:
 *    - Alocacao: calloc para mapa, malloc para missao
 *    - Liberacao: free para ambos ao final
 *    - Sem vazamentos de memoria
 * =====================================================================
 */