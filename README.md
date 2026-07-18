# Sistemas Operacionais

Repositório contendo exercícios e implementações desenvolvidos durante a disciplina de **Sistemas Operacionais**, utilizando a linguagem **C** para explorar conceitos fundamentais da interação entre software e sistema operacional.

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![GCC](https://img.shields.io/badge/GCC-444444?style=for-the-badge&logo=gnu&logoColor=white)

## Objetivo

Este repositório reúne exercícios práticos desenvolvidos ao longo da disciplina de **Sistemas Operacionais**, com foco na compreensão do funcionamento interno dos sistemas computacionais através da programação em linguagem C.

Os exemplos exploram desde conceitos básicos da linguagem até recursos fornecidos pelo sistema operacional, permitindo compreender como aplicações interagem diretamente com o kernel.

# Conteúdo

O projeto está organizado em módulos sequenciais, cada um abordando um conjunto específico de conceitos.

```
.
├── f0
├── f1
├── f2
├── f3
├── f4
├── f5
├── f6
└── f7
```

## Módulos

### f0 — Introdução

Primeiros programas em C.

Principais tópicos:

- Compilação
- Execução de programas
- Assembly gerado pelo compilador
- Estrutura básica de um programa em C

Arquivos de destaque:

- `hello.c`
- `hello.s`

### f1 — Ponteiros e Memória

Estudo da organização da memória e manipulação de ponteiros.

Conceitos abordados:

- Ponteiros
- Passagem por valor
- Passagem por referência
- Vetores
- Strings
- Acesso à memória
- Erros comuns envolvendo ponteiros

Arquivos de destaque:

- `bad_pointer.c`
- `good_pointer.c`
- `call_by_value.c`
- `call_by_reference.c`
- `char_array.c`
- `int_array.c`

### f2 — Bibliotecas em C

Implementação de uma biblioteca para operações com números complexos.

Conceitos estudados:

- Modularização
- Arquivos Header (`.h`)
- Bibliotecas estáticas
- Separação entre interface e implementação
- Compilação modular

Operações implementadas:

- Soma
- Subtração
- Multiplicação
- Divisão
- Conjugado
- Argumento
- Módulo
- Parte real
- Parte imaginária

### f3 — Manipulação de Arquivos

Exercícios utilizando arquivos no sistema operacional.

Conceitos abordados:

- Leitura de arquivos
- Escrita
- Processamento de texto
- Contagem de caracteres
- Busca de palavras
- Conversão para letras minúsculas

### f4 — Chamadas de Sistema

Introdução ao uso das chamadas de sistema fornecidas pelo sistema operacional.

Conceitos:

- Interface entre aplicação e kernel
- Execução de programas
- Recursos do sistema operacional

### f5 — Processos

Implementações envolvendo criação e gerenciamento de processos.

Possíveis conceitos explorados:

- `fork()`
- `wait()`
- Processos pai e filho
- Execução concorrente
- Sincronização básica

### f6 — Processos Avançados

Continuação dos estudos sobre processos.

Conceitos:

- Comunicação entre processos
- Execução concorrente
- Controle de processos
- Chamadas de sistema

### f7 — Exercícios Complementares

Exercícios finais consolidando os conceitos estudados durante a disciplina.

# Tecnologias

- Linguagem C
- GCC
- Linux
- Terminal
- Make (quando aplicável)

# Como compilar

Compile qualquer exercício utilizando o GCC.

```bash
gcc arquivo.c -o programa
```

Exemplo:

```bash
gcc hello.c -o hello
```

# Executando

```bash
./hello
```

# Conceitos estudados

Ao longo do projeto são explorados diversos temas fundamentais de Sistemas Operacionais, incluindo:

- Organização da memória
- Ponteiros
- Pilha e Heap
- Manipulação de arquivos
- Bibliotecas em C
- Compilação
- Assembly
- Chamadas de sistema
- Processos
- Comunicação entre processos
- Gerenciamento de memória
- Programação de baixo nível

# Competências desenvolvidas

Durante o desenvolvimento deste projeto foram praticadas habilidades como:

- Programação em C
- Resolução de problemas
- Depuração (Debug)
- Organização modular de código
- Utilização do GCC
- Desenvolvimento em ambiente Linux
- Compreensão da interação entre software e sistema operacional
