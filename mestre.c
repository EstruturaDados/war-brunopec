#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[20];
    int tropas;
};

struct Territorio territorios[5] = {
    {"América", "Verde", 5},
    {"Europa", "Azul", 3},
    {"Ásia", "Vermelho", 2},
    {"África", "Amarelo", 4},
    {"Oceania", "Branco", 1}
};

// Funções
void mapa();
int menu();
void faseataque(int *atacante, int *defensor);
void sortearMissao(int *missao);
void cumprirmissao(int *missao);

int main() {
    int escolha, atacante, defensor, missao;
    int dado_atacante, dado_defensor;
    
    srand(time(NULL));
    sortearMissao(&missao);
    

    do {
        mapa();
        printf("\nMissão atual: Destruir o exército %s\n", territorios[missao].cor);
        escolha = menu();

        switch (escolha) {
            case 1:
                faseataque(&atacante, &defensor);

                printf("\n--- RESULTADO DA BATALHA ---\n");

                dado_atacante = rand() % 6 + 1;
                dado_defensor = rand() % 6 + 1;

                printf("Ataque (%s): %d | Defesa (%s): %d\n",
                       territorios[atacante-1].nome, dado_atacante,
                       territorios[defensor-1].nome, dado_defensor);

                if (dado_atacante <= dado_defensor) {
                    printf("VITÓRIA DA DEFESA! O atacante perdeu 1 tropa\n\n");
                    territorios[atacante-1].tropas--;
                    territorios[defensor-1].tropas++;
                } else {
                    printf("VITÓRIA DO ATAQUE! O defensor perdeu 1 tropa\n\n");
                    territorios[defensor-1].tropas--;
                    territorios[atacante-1].tropas++;
                }
                break;

            case 2:
                printf("\nMissão atual: Destruir o exército %s\n\n", territorios[missao].cor);
                cumprirmissao(&missao);
                break;

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n\n");
                break;
        }

    } while (escolha != 0);

    return 0;
}

// Exibe o mapa com os territórios e tropas
void mapa() {
    printf("\n================ MAPA DO MUNDO ================\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s      (Exército: %s Tropas: %d)\n",
               i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    printf("==============================================\n");
}

// Menu principal
int menu() {
    int escolha;
    printf("\n--- MENU DE AÇÕES ---\n");
    printf("1. Atacar\n");
    printf("2. Verificar Missão\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);
    return escolha;
}

// Fase de ataque
void faseataque(int *atacante, int *defensor) {
    do {
        printf("Escolha o território atacante (1-5): ");
        scanf("%d", atacante);
    } while (*atacante < 1 || *atacante > 5 || territorios[*atacante-1].tropas < 2);

    do {
        printf("Escolha o território defensor (1-5): ");
        scanf("%d", defensor);
    } while (*defensor < 1 || *defensor > 5 || *defensor == *atacante);
    while (*atacante == *defensor)
    {
        printf("O território defensor deve ser diferente do atacante.\n");
        printf("Escolha o território defensor (1-5): ");
        scanf("%d", defensor);
    }
    
}

// Sorteia uma missão
void sortearMissao(int *missao) {
    *missao = rand() % 5; 
    printf("\nSua missão: Destruir o exército %s\n", territorios[*missao].cor);
}

// Verifica se a missão foi cumprida
void cumprirmissao(int *missao) {
    if (territorios[*missao].tropas <= 0) {
        printf("Parabéns! Você cumpriu sua missão de destruir o exército %s!\n", territorios[*missao].cor);
        sortearMissao(missao); // sorteia nova missão
    } else {
        printf("Missão não cumprida ainda. Continue tentando!\n");
    }
}
