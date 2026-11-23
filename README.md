# Sistema de Gerenciamento de Senhas de Atendimento Clínico

Este é um projeto simples em linguagem C. Ele usa funções, estruturas e menus para organizar a fila de pacientes de uma clínica.

## Objetivo

O programa permite cadastrar pacientes, escolher a categoria da senha e chamar os pacientes na ordem correta.

A classificação foi criada apenas para fins didáticos. Ela não substitui avaliação médica.

## Categorias

### Urgente

A senha começa com `U`, por exemplo: `U001`, `U002`.

É urgente quando o paciente tem idade maior que 80 anos.

### Preferencial

A senha começa com `P`, por exemplo: `P001`, `P002`.

É preferencial quando:

- o paciente é uma mulher com 60 anos ou mais;
- o paciente é um homem com 65 anos ou mais;
- o paciente está gestante;
- o paciente é lactante;
- o paciente possui necessidade especial;
- o paciente possui obesidade.

### Normal

A senha começa com `N`, por exemplo: `N001`, `N002`.

É normal quando o paciente não está em nenhuma das condições anteriores.

## Ordem de atendimento

O programa chama primeiro:

1. Urgente;
2. Preferencial;
3. Normal.

Dentro de cada categoria, o primeiro paciente cadastrado é chamado primeiro.

## Menu do programa

```text
1 - Cadastrar paciente
2 - Consultar próxima senha
3 - Chamar próximo paciente
4 - Finalizar atendimento
5 - Mostrar painel
0 - Sair
```

## Requisitos

Você precisa de:

- um computador;
- um compilador C, como o GCC;
- o terminal ou prompt de comando.

## Como compilar no Linux ou no terminal do VS Code

No terminal, entre na pasta do projeto e execute:

```bash
gcc main.c -o sistema_senhas
./sistema_senhas
```

No Windows, pode ser usado:

```bash
gcc main.c -o sistema_senhas.exe
sistema_senhas.exe
```

## Como compilar com Make

Se o `make` estiver instalado:

```bash
make
./sistema_senhas
```

Para remover o programa compilado:

```bash
make clean
```

## Exemplo de uso

### Cadastrar uma paciente preferencial

```text
Nome: Ana
Gênero: F
Idade: 34
Está gestante: 1
É lactante: 0
Possui necessidade especial: 0
Possui obesidade: 0
```

O programa mostrará:

```text
Senha emitida: P001 - Categoria: Preferencial
```

### Cadastrar um paciente normal

```text
Nome: Bruno
Gênero: M
Idade: 40
Possui necessidade especial: 0
Possui obesidade: 0
```

O programa mostrará:

```text
Senha emitida: N001 - Categoria: Normal
```

### Cadastrar um paciente urgente

```text
Nome: Carla
Gênero: F
Idade: 82
Está gestante: 0
É lactante: 0
Possui necessidade especial: 0
Possui obesidade: 0
```

O programa mostrará:

```text
Senha emitida: U001 - Categoria: Urgente
```

Mesmo que `N001` tenha sido criado antes, o paciente urgente será chamado primeiro.

## Principais funções

- `lerSimNao`: lê uma resposta 1 para sim ou 0 para não.
- `lerIdade`: lê e valida a idade.
- `classificarPaciente`: decide se o paciente é normal, preferencial ou urgente.
- `gerarSenha`: cria uma senha como `N001`, `P001` ou `U001`.
- `adicionarFila`: coloca o paciente no final da fila da categoria.
- `procurarProximaCategoria`: decide qual fila deve ser atendida primeiro.
- `consultarProxima`: mostra a próxima senha sem chamá-la.
- `chamarProximo`: chama o próximo paciente.
- `finalizarAtendimento`: termina o atendimento atual.
- `mostrarPainel`: mostra o painel de chamadas.
- `mostrarMenu`: mostra as opções disponíveis.
- `main`: controla o menu principal.

## Observação

Os dados são guardados enquanto o programa está aberto. Ao fechar o programa, os cadastros são apagados da memória.
