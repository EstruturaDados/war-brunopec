#include <stdio.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_COR 10

struct Territorio {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
};

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu() {
    printf("================================\n");
    printf("    BEM-VINDO AO WAR \n");
    printf("================================\n");
    printf("    ACESSANDO MENU\n");
    printf("1. INSTRUÇÕES\n");
    printf("2. CADASTRAR TERRITÓRIO\n");
    printf("3. LISTAR TERRITÓRIOS\n");
    printf("0. SAIR\n");
    printf("================================\n");
}

int selecionaropc() {
    int opcao;
    menu();
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    limparBufferEntrada(); // evita problema com fgets
    return opcao;
}

int main() {
    int totalTerritorio = 0;
    struct Territorio territorios[5];
    int opcao;

    do {
        opcao = selecionaropc();
        switch (opcao) {
            case 0:
                printf("Saindo do programa...\n");
                break;

            case 1:
                printf("INSTRUÇÕES\n");
                printf("Selecionando a opção:\n");
                printf("1. CADASTRAR TERRITÓRIO:\nAdicione um novo território ao jogo.\n");
                printf("Deve primeiro informar nome do território, seguido de sua cor e número de tropas.\n");
                printf("2. LISTAR TERRITÓRIOS:\nExiba todos os territórios cadastrados.\n");
                printf("0. SAIR:\nEncerre o programa.\n");
                break;

            case 2:
                if (totalTerritorio >= 5) {
                    printf("Limite de territórios atingido.\n");
                } else {
                    printf("CADASTRAR TERRITÓRIO\n");
                    printf("Digite o nome do território: ");
                    fgets(territorios[totalTerritorio].nome, MAX_NOME, stdin);
                    territorios[totalTerritorio].nome[strcspn(territorios[totalTerritorio].nome, "\n")] = 0;

                    printf("Digite a cor do território: ");
                    fgets(territorios[totalTerritorio].cor, MAX_COR, stdin);
                    territorios[totalTerritorio].cor[strcspn(territorios[totalTerritorio].cor, "\n")] = 0;

                    printf("Digite o número de tropas: ");
                    scanf("%d", &territorios[totalTerritorio].tropas);
                    limparBufferEntrada();

                    totalTerritorio++;
                    printf("Território cadastrado com sucesso!\n");
                }
                break;

            case 3:
                if (totalTerritorio == 0) {
                    printf("Nenhum território cadastrado ainda.\n");
                } else {
                    printf("LISTAR TERRITÓRIOS\n");
                    for (int i = 0; i < totalTerritorio; i++) {
                        printf("Território %d:\n", i + 1);
                        printf("Nome: %s\n", territorios[i].nome);
                        printf("Cor: %s\n", territorios[i].cor);
                        printf("Tropas: %d\n", territorios[i].tropas);
                    }
                }
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
