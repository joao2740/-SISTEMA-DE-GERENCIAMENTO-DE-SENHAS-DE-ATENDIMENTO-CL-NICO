/*
 * Sistema simples de gerenciamento de senhas de uma clínica.
 * Projeto didático para alunos iniciantes em C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PACIENTES 100
#define TAM_NOME 50

/* Categorias do atendimento */
typedef enum {
    NORMAL = 0,
    PREFERENCIAL = 1,
    URGENTE = 2
} Categoria;

/* Dados de um paciente */
typedef struct {
    char nome[TAM_NOME];
    char genero;
    int idade;
    int gestante;
    int lactante;
    int necessidadeEspecial;
    int obesidade;
    Categoria categoria;
    char senha[10];
} Paciente;

/* Vetores usados como filas. O índice 0 é o início da fila. */
Paciente filas[3][MAX_PACIENTES];
int tamanhosFilas[3] = {0, 0, 0};

int contadoresSenhas[3] = {0, 0, 0};
Paciente pacienteEmAtendimento;
int atendimentoAtivo = 0;

/* Pergunta ao usuário se a resposta é 1 (sim) ou 0 (não). */
int lerSimNao(const char *pergunta) {
    int resposta;

    while (1) {
        printf("%s (1-Sim / 0-Nao): ", pergunta);

        if (scanf("%d", &resposta) != 1) {
            printf("Entrada invalida. Digite 1 ou 0.\n\n");
            while (getchar() != '\n');
            continue;
        }

        if (resposta == 0 || resposta == 1) {
            while (getchar() != '\n');
            return resposta;
        }

        printf("Entrada invalida. Digite 1 ou 0.\n\n");
    }
}

/* Lê e valida uma idade inteira. */
int lerIdade(void) {
    int idade;

    while (1) {
        printf("Idade: ");

        if (scanf("%d", &idade) != 1) {
            printf("Entrada invalida. Digite um numero.\n\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        if (idade >= 0 && idade <= 120) {
            return idade;
        }

        printf("A idade deve estar entre 0 e 120 anos.\n\n");
    }
}

/* Identifica a categoria conforme as regras didáticas da atividade. */
Categoria classificarPaciente(Paciente paciente) {
    /* A urgente tem prioridade maior. */
    if (paciente.idade > 80) {
        return URGENTE;
    }

    if (paciente.genero == 'F' && paciente.idade >= 60) {
        return PREFERENCIAL;
    }

    if (paciente.genero == 'M' && paciente.idade >= 65) {
        return PREFERENCIAL;
    }

    if (paciente.gestante || paciente.lactante ||
        paciente.necessidadeEspecial || paciente.obesidade) {
        return PREFERENCIAL;
    }

    return NORMAL;
}

/* Gera senha, por exemplo: N001, P001 ou U001. */
void gerarSenha(Paciente *paciente) {
    Categoria categoria = paciente->categoria;

    contadoresSenhas[categoria]++;

    if (categoria == NORMAL) {
        sprintf(paciente->senha, "N%03d", contadoresSenhas[categoria]);
    } else if (categoria == PREFERENCIAL) {
        sprintf(paciente->senha, "P%03d", contadoresSenhas[categoria]);
    } else {
        sprintf(paciente->senha, "U%03d", contadoresSenhas[categoria]);
    }
}

/* Guarda o paciente no final da fila correspondente. */
int adicionarFila(Paciente paciente) {
    Categoria categoria = paciente.categoria;

    if (tamanhosFilas[categoria] >= MAX_PACIENTES) {
        printf("Esta fila esta cheia.\n");
        return 0;
    }

    filas[categoria][tamanhosFilas[categoria]] = paciente;
    tamanhosFilas[categoria]++;
    return 1;
}

/* Cadastra o paciente e cria sua senha. */
void cadastrarPaciente(void) {
    Paciente paciente;
    char nome[TAM_NOME];
    char genero;

    printf("\n--- Cadastro de paciente ---\n");

    while (getchar() != '\n');

    printf("Nome: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    if (strlen(nome) == 0) {
        printf("O nome nao pode ficar vazio.\n");
        return;
    }

    strcpy(paciente.nome, nome);

    while (1) {
        printf("Genero (F-Feminino / M-Masculino / O-Outro): ");

        if (scanf(" %c", &genero) != 1) {
            printf("Entrada invalida.\n");
            while (getchar() != '\n');
            continue;
        }

        if (genero == 'f') genero = 'F';
        if (genero == 'm') genero = 'M';
        if (genero == 'o') genero = 'O';

        if (genero == 'F' || genero == 'M' || genero == 'O') {
            break;
        }

        printf("Digite F, M ou O.\n");
    }

    paciente.genero = genero;
    paciente.idade = lerIdade();
    paciente.gestante = 0;
    paciente.lactante = 0;

    if (paciente.genero == 'F') {
        paciente.gestante = lerSimNao("Esta gestante?");
        paciente.lactante = lerSimNao("E lactante?");
    }

    paciente.necessidadeEspecial = lerSimNao("Possui necessidade especial?");
    paciente.obesidade = lerSimNao("Possui obesidade?");

    paciente.categoria = classificarPaciente(paciente);
    gerarSenha(&paciente);

    if (adicionarFila(paciente)) {
        printf("\nSenha emitida: %s", paciente.senha);

        if (paciente.categoria == URGENTE) {
            printf(" - Categoria: Urgente\n");
        } else if (paciente.categoria == PREFERENCIAL) {
            printf(" - Categoria: Preferencial\n");
        } else {
            printf(" - Categoria: Normal\n");
        }
    }
}

/* Procura a categoria com maior prioridade que possui paciente. */
int procurarProximaCategoria(void) {
    if (tamanhosFilas[URGENTE] > 0) {
        return URGENTE;
    }

    if (tamanhosFilas[PREFERENCIAL] > 0) {
        return PREFERENCIAL;
    }

    if (tamanhosFilas[NORMAL] > 0) {
        return NORMAL;
    }

    return -1;
}

/* Mostra o nome da categoria. */
void mostrarCategoria(Categoria categoria) {
    if (categoria == URGENTE) {
        printf("Urgente");
    } else if (categoria == PREFERENCIAL) {
        printf("Preferencial");
    } else {
        printf("Normal");
    }
}

/* Consulta a próxima senha sem retirá-la da fila. */
void consultarProxima(void) {
    int categoria = procurarProximaCategoria();

    if (categoria == -1) {
        printf("Nao existe paciente aguardando.\n");
        return;
    }

    printf("Proxima senha: %s - ", filas[categoria][0].senha);
    mostrarCategoria((Categoria)categoria);
    printf(" - Paciente: %s\n", filas[categoria][0].nome);
}

/* Remove o primeiro paciente da fila para iniciar o atendimento. */
void chamarProximo(void) {
    int categoria;
    int i;

    if (atendimentoAtivo) {
        printf("Finalize o atendimento atual antes de chamar outra senha.\n");
        return;
    }

    categoria = procurarProximaCategoria();

    if (categoria == -1) {
        printf("Nao existe paciente aguardando.\n");
        return;
    }

    pacienteEmAtendimento = filas[categoria][0];

    for (i = 0; i < tamanhosFilas[categoria] - 1; i++) {
        filas[categoria][i] = filas[categoria][i + 1];
    }

    tamanhosFilas[categoria]--;
    atendimentoAtivo = 1;

    printf("Chamando senha %s - Categoria: ", pacienteEmAtendimento.senha);
    mostrarCategoria(pacienteEmAtendimento.categoria);
    printf(" - Paciente: %s\n", pacienteEmAtendimento.nome);
}

/* Finaliza o atendimento atual. */
void finalizarAtendimento(void) {
    if (!atendimentoAtivo) {
        printf("Nao existe atendimento em andamento.\n");
        return;
    }

    printf("Atendimento da senha %s finalizado.\n",
           pacienteEmAtendimento.senha);

    atendimentoAtivo = 0;
}

/* Mostra o painel atual do sistema. */
void mostrarPainel(void) {
    int categoria;
    int i;
    int quantidadeMostrada = 0;

    printf("\n========== PAINEL DE CHAMADA ==========");

    if (atendimentoAtivo) {
        printf("\nEm atendimento: %s - Categoria: ",
               pacienteEmAtendimento.senha);
        mostrarCategoria(pacienteEmAtendimento.categoria);
        printf(" - Paciente: %s", pacienteEmAtendimento.nome);
    } else {
        printf("\nEm atendimento: nenhum");
    }

    printf("\nProximas senhas:");

    for (categoria = URGENTE; categoria >= NORMAL; categoria--) {
        for (i = 0; i < tamanhosFilas[categoria] && quantidadeMostrada < 5; i++) {
            printf("\n  %s - ", filas[categoria][i].senha);
            mostrarCategoria((Categoria)categoria);
            quantidadeMostrada++;
        }
    }

    if (quantidadeMostrada == 0) {
        printf("\n  Nenhuma senha aguardando.");
    }

    printf("\nPacientes em espera:");
    printf("\n  Urgente: %d", tamanhosFilas[URGENTE]);
    printf("\n  Preferencial: %d", tamanhosFilas[PREFERENCIAL]);
    printf("\n  Normal: %d", tamanhosFilas[NORMAL]);

    printf("\n=======================================\n");
}

/* Exibe as opções do menu. */
void mostrarMenu(void) {
    printf("\n=== SISTEMA DE SENHAS CLINICAS ===\n");
    printf("1 - Cadastrar paciente\n");
    printf("2 - Consultar proxima senha\n");
    printf("3 - Chamar proximo paciente\n");
    printf("4 - Finalizar atendimento\n");
    printf("5 - Mostrar painel\n");
    printf("0 - Sair\n");
}

int main(void) {
    int opcao;

    do {
        mostrarMenu();

        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida. Digite um numero de 0 a 5.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarPaciente();
                break;

            case 2:
                consultarProxima();
                break;

            case 3:
                chamarProximo();
                break;

            case 4:
                finalizarAtendimento();
                break;

            case 5:
                mostrarPainel();
                break;

            case 0:
                printf("Encerrando o sistema.\n");
                break;

            default:
                printf("Opcao invalida. Escolha de 0 a 5.\n");
        }

    } while (opcao != 0);

    return 0;
}
