#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------
// Definição da struct Sala
// -----------------------------
typedef struct Sala {
    char nome[50];            // Nome do cômodo
    struct Sala *esquerda;    // Caminho para a esquerda
    struct Sala *direita;     // Caminho para a direita
} Sala;

// --------------------------------
// Função para criar uma sala dinamicamente
// --------------------------------
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*)malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ------------------------------------
// Função para explorar as salas interativamente
// ------------------------------------
void explorarSalas(Sala *atual) {
    char escolha;

    // Enquanto existir uma sala atual
    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Se não houver caminhos à esquerda nem à direita
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou ao fim deste caminho. Não há mais portas aqui!\n");
            break;
        }

        // Mostra opções possíveis
        printf("Para onde deseja ir? (e = esquerda, d = direita, s = sair): ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Não há caminho à esquerda!\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Não há caminho à direita!\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("Você decidiu parar a exploração.\n");
            break;
        } else {
            printf("Opção inválida!\n");
        }
    }
}

// -----------------------------
// Função principal (main)
// -----------------------------
int main() {
    // Criando as salas (árvore binária)
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *quarto = criarSala("Quarto Secreto");

    // Montando a estrutura da mansão (ligando nós)
    hall->esquerda = salaEstar;     // Hall -> esquerda = Sala de Estar
    hall->direita = cozinha;        // Hall -> direita = Cozinha

    salaEstar->esquerda = biblioteca; // Sala de Estar -> esquerda = Biblioteca
    salaEstar->direita = jardim;      // Sala de Estar -> direita = Jardim

    cozinha->direita = quarto;        // Cozinha -> direita = Quarto Secreto

    // Início da exploração
    printf("Bem-vindo(a) ao Detective Quest!\n");
    printf("Você começará sua exploração pelo Hall de Entrada.\n");

    explorarSalas(hall);

    // Liberar memória (simples)
    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);
    free(quarto);

    printf("\nExploração finalizada.\n");
    return 0;
}
