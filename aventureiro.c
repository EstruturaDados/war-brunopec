#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10

//------Define territorio
struct Territorio {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
};

struct Territorio* territorio;

//-----Função para exibir o layout
void layout(const char* texto){
    printf("===========================================\n");
    printf("    %s\n", texto);
    printf("===========================================\n");
}
void cabecalho (const char* texto){
    printf("--- %s ---\n", texto);
}

//------Cadastro de território 
void cadastro(int i){
    printf("--- Cadastrando Território %d ---\n", i+1);
    printf("Nome do Territorio: ");
    fgets(territorio[i].nome, MAX_NOME, stdin);
    territorio[i].nome[strcspn(territorio[i].nome, "\n")] = 0;  

    printf("Cor do Territorio: ");
    fgets(territorio[i].cor, MAX_COR, stdin);
    territorio[i].cor[strcspn(territorio[i].cor, "\n")] = 0;  

    printf("Numero de tropas: ");
    scanf("%d", &territorio[i].tropas);
    getchar();  
}

//------ESTADO ATUAL
void estado_atual(){
    layout("MAPA DO MUNDO - ESTADO ATUAL");
    for (int i = 0; i < 5; i++) {
       printf("%d. %s (Exercito: %s, Tropas: %d)\n", 
              i + 1, territorio[i].nome, territorio[i].cor, territorio[i].tropas);
    }
}

int main() {
    int qtd = 5;
    int atacante, defensor, dado_atacante, dado_defensor;
    srand(time(NULL)); 

    territorio = (struct Territorio*) calloc(qtd, sizeof(struct Territorio));

    layout("WAR ESTRUTURADO - CADASTRO INICIAL");
    for (int i = 0; i < 5; i++) {
       cadastro(i);  // <-- corrigido para não estourar vetor
    }

    int sair = 0;
    while (!sair) {
        estado_atual();

        cabecalho("FASE DE ATAQUE");
        printf("\nSelecione o território atacante (1 a 5, ou 0 para sair): ");
        scanf("%d", &atacante);

        if (atacante == 0) {
            sair = 1; 
            break;
        } else         
        if (atacante < 1 || atacante > 5) {
            printf("Seleção inválida. Tente novamente.\n");
            printf("\nSelecione o território atacante (1 a 5, ou 0 para sair): ");
            scanf("%d", &atacante);
            continue;
        }

        printf("Selecione o território defensor (1 a 5): ");
        scanf("%d", &defensor);
        if (defensor < 1 || defensor > 5) {
            printf("Seleção inválida. Tente novamente.\n");
            printf("\nSelecione o território defensor (1 a 5): ");
            scanf("%d", &defensor);
            continue;
        } else
        if (defensor == atacante) {
            printf("O território defensor deve ser diferente do atacante.\n");
            printf("Selecione o território defensor (1 a 5): ");
            scanf("%d", &defensor);
            continue;
        }


        //------RESULTADO DO ATAQUE   
        cabecalho("RESULTADO DO ATAQUE");
        printf("\n");

        // Jogando os dados

        dado_atacante = rand() % 6 + 1;
        dado_defensor = rand() % 6 + 1;
        while (dado_atacante == dado_defensor) {
                dado_atacante = rand() % 6 + 1;
                dado_defensor = rand() % 6 + 1;
        }

        printf("O atacante %s rolou um dado e obteve %d.\n", territorio[atacante - 1].nome, dado_atacante);
        printf("O defensor %s rolou um dado e obteve %d.\n", territorio[defensor - 1].nome, dado_defensor);

        if (dado_atacante > dado_defensor) {
            printf("VITORIA DO ATAQUE! O defensor perde 1 tropa.\n");
            territorio[defensor - 1].tropas -= 1;
            //------DEFININDO TROPA
            if (territorio[defensor - 1].tropas <= 0) {
                territorio[defensor - 1].tropas = 1;
                strcpy(territorio[defensor-1].cor, territorio[atacante - 1].cor);
            }
        } else {
            printf("VITORIA DO DEFENSOR! O atacante perde 1 tropa.\n");
            territorio[atacante - 1].tropas -= 1;
            //------DEFININDO TROPA
            if (territorio[atacante - 1].tropas <= 0) {
                territorio[atacante - 1].tropas = 1;
                strcpy(territorio[atacante - 1].cor, territorio[defensor-1].cor);
            }
        }
        

        getchar();
        printf("Pressione Enter para continuar...");
        getchar();

    }

    free(territorio);
    return 0;
}
