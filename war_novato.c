/*
 * =====================================================================
 * JOGO WAR - NÍVEL NOVATO
 * Sistema de Cadastro de Territórios
 * =====================================================================
 * Descrição: Este programa implementa um sistema básico de cadastro
 * de territórios para o jogo War utilizando structs em C.
 * 
 * Autor: [Seu Nome]
 * Data: Novembro/2025
 * Disciplina: Análise e Desenvolvimento de Sistemas
 * =====================================================================
 */

// ==================== BIBLIOTECAS ====================
#include <stdio.h>   // Biblioteca para entrada e saída (printf, scanf)
#include <string.h>  // Biblioteca para manipulação de strings

// ==================== DEFINIÇÃO DA STRUCT ====================
/*
 * Struct Territorio:
 * Estrutura de dados que armazena as informações de cada território
 * - nome: nome do território (máximo 30 caracteres)
 * - cor: cor do exército que controla o território (máximo 10 caracteres)
 * - tropas: quantidade de tropas presentes no território
 */
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

// ==================== CONSTANTES ====================
#define TOTAL_TERRITORIOS 5  // Número total de territórios a serem cadastrados

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    // Declaração do vetor de structs para armazenar os territórios
    Territorio territorios[TOTAL_TERRITORIOS];
    
    // Variável auxiliar para controle de loops
    int i;
    
    // ==================== CABEÇALHO DO PROGRAMA ====================
    printf("=====================================================\n");
    printf("       JOGO WAR - CADASTRO DE TERRITORIOS\n");
    printf("=====================================================\n");
    printf("Sistema de cadastro de territorios do jogo War\n");
    printf("Cadastre %d territorios com suas informacoes\n", TOTAL_TERRITORIOS);
    printf("=====================================================\n\n");
    
    // ==================== ENTRADA DE DADOS ====================
    /*
     * Loop para cadastrar cada um dos 5 territórios
     * Para cada território, solicitamos:
     * 1. Nome do território
     * 2. Cor do exército
     * 3. Quantidade de tropas
     */
    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("\n--- CADASTRO DO TERRITORIO %d ---\n", i + 1);
        
        // Limpeza do buffer de entrada (importante após scanf numérico)
        if (i > 0) {
            while(getchar() != '\n');  // Limpa o buffer
        }
        
        // Entrada do nome do território
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        // Remove o '\n' do final da string capturada pelo fgets
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        // Entrada da cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        // Remove o '\n' do final da string
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        // Validação básica: tropas não podem ser negativas
        while (territorios[i].tropas < 0) {
            printf("ERRO: Quantidade de tropas nao pode ser negativa!\n");
            printf("Digite novamente a quantidade de tropas: ");
            scanf("%d", &territorios[i].tropas);
        }
        
        printf("Territorio cadastrado com sucesso!\n");
    }
    
    // ==================== EXIBIÇÃO DOS DADOS ====================
    /*
     * Após o cadastro de todos os territórios, exibimos
     * as informações cadastradas em formato de tabela
     */
    printf("\n\n=====================================================\n");
    printf("         TERRITORIOS CADASTRADOS\n");
    printf("=====================================================\n\n");
    
    // Loop para percorrer e exibir cada território cadastrado
    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("TERRITORIO %d:\n", i + 1);
        printf("  Nome........: %s\n", territorios[i].nome);
        printf("  Cor.........: %s\n", territorios[i].cor);
        printf("  Tropas......: %d\n", territorios[i].tropas);
        printf("-----------------------------------------------------\n");
    }
    
    // ==================== FINALIZAÇÃO ====================
    printf("\n=====================================================\n");
    printf("Sistema finalizado com sucesso!\n");
    printf("Total de territorios cadastrados: %d\n", TOTAL_TERRITORIOS);
    printf("=====================================================\n");
    
    return 0;  // Retorna 0 indicando execução bem-sucedida
}

/*
  * =====================================================================
 * EXPLICACOES TECNICAS:
 * =====================================================================
 * 
 * 1. STRUCT TERRITORIO:
 *    - Agrupa dados relacionados (nome, cor, tropas) em uma unica estrutura
 *    - Facilita a organizacao e manipulacao dos dados
 *    - typedef permite usar "Territorio" diretamente sem "struct"
 * 
 * 2. VETOR DE STRUCTS:
 *    - territorios[TOTAL_TERRITORIOS] cria 5 posicoes na memoria
 *    - Cada posicao armazena um Territorio completo
 *    - Acesso aos dados: territorios[i].nome, territorios[i].cor, etc.
 * 
 * 3. ENTRADA DE DADOS:
 *    - fgets() e usado para strings (mais seguro que scanf para strings)
 *    - scanf() e usado para inteiros
 *    - strcspn() remove o '\n' que fgets captura
 * 
 * 4. VALIDACAO:
 *    - Verifica se tropas >= 0 para evitar dados inconsistentes
 * 
 * 5. COMPLEXIDADE:
 *    - Tempo: O(n) onde n e o numero de territorios
 *    - Espaco: O(n) para armazenar os territorios
 * =====================================================================
 */