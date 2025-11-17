# 🎮 WAR Estruturado - Análise e Desenvolvimento de Sistemas

Projeto completo do jogo WAR implementado em linguagem C, desenvolvido como trabalho prático da disciplina de Estruturas de Dados.

---

## 👨‍💻 Autor
*Daniela Chiavenato Marzagão**  
Curso: Análise e Desenvolvimento de Sistemas  
Data: 16/11/2025

---

## 📂 Estrutura do Projeto

O projeto está organizado em 4 pastas, representando a evolução do desenvolvimento:

### 📁 **0-war/**
Contém a documentação original e template base do projeto.

### 📁 **1-war-novato/**
**Nível Novato - Cadastro de Territórios**
- Implementação de `struct Territorio`
- Vetor estático para armazenar 5 territórios
- Sistema básico de cadastro e exibição
- **Conceitos:** structs, vetores, entrada/saída

### 📁 **2-war-aventureiro/**
**Nível Aventureiro - Sistema de Batalhas**
- Alocação dinâmica de memória (`calloc`, `malloc`, `free`)
- Sistema de ataques entre territórios
- Simulação de batalhas com dados aleatórios
- Conquista e transferência de territórios
- **Conceitos:** ponteiros, alocação dinâmica, números aleatórios

### 📁 **3-war-mestre/**
**Nível Mestre - Missões Estratégicas**
- Sistema completo de missões sorteadas
- Verificação de condição de vitória
- Modularização total do código
- Menu interativo profissional
- Inicialização automática de territórios
- **Conceitos:** modularização, `const correctness`, passagem por referência

---

## 🎯 Funcionalidades Implementadas

### ✅ Nível Novato
- [x] Cadastro de 5 territórios
- [x] Armazenamento com structs
- [x] Exibição formatada dos dados

### ✅ Nível Aventureiro
- [x] Alocação dinâmica de memória
- [x] Sistema de batalhas com dados (1-6)
- [x] Conquista de territórios
- [x] Atualização de tropas e donos
- [x] Validações de ataque

### ✅ Nível Mestre
- [x] 5 missões estratégicas diferentes
- [x] Sorteio aleatório de missões
- [x] Verificação automática de vitória
- [x] Menu interativo completo
- [x] Código totalmente modularizado
- [x] Gerenciamento completo de memória

---

## 🚀 Como Compilar e Executar

### Nível Novato
```bash
cd 1-war-novato
gcc war_novato.c -o war_novato
./war_novato
```

### Nível Aventureiro
```bash
cd 2-war-aventureiro
gcc war_aventureiro.c -o war_aventureiro
./war_aventureiro
```

### Nível Mestre
```bash
cd 3-war-mestre
gcc war_mestre.c -o war_mestre
./war_mestre
```

---

## 📚 Conceitos de Programação Aplicados

- **Estruturas de Dados:** structs, vetores, ponteiros
- **Gerenciamento de Memória:** malloc, calloc, free
- **Modularização:** funções especializadas, separação de responsabilidades
- **Algoritmos:** simulação de batalhas, verificação de condições
- **Boas Práticas:** comentários, const correctness, validações

---

## 📊 Estatísticas do Projeto

- **Linhas de código:** ~1.200+
- **Funções implementadas:** 20+
- **Níveis concluídos:** 3/3
- **Commits:** 3 commits bem documentados
- **Tempo de desenvolvimento:** ~1h30

---

## 🏆 Status do Projeto

**TEMA 1: ESTRUTURAS DE DADOS - ✅ CONCLUÍDO**

---

## 📝 Observações

Este projeto demonstra a evolução gradual de complexidade na implementação de sistemas em C, começando com conceitos básicos e evoluindo para técnicas avançadas de programação estruturada.

---

**Última atualização:** 16/11/2025
