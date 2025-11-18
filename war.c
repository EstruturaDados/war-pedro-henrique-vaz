#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

void exibirMissao(char* missao) {
    printf("\n=== Sua missão: %s ===\n\n", missao);
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Você não pode atacar um território da sua própria cor!\n");
        return;
    }

    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Ataque rolou: %d | Defesa rolou: %d\n", dadoAtq, dadoDef);

    if (dadoAtq > dadoDef) {
        printf("Ataque VITORIOSO!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Ataque FALHOU! Atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    if (strstr(missao, "Conquistar 3 territorios") != NULL) {
        int count = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "Azul") == 0) count++;
        
        if (count >= 3) return 1;
    }

    if (strstr(missao, "Eliminar tropa vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "Vermelho") == 0) return 0;
        return 1;
    }
    
    for (int i = 0; i < tamanho; i++)
        if (mapa[i].tropas >= 10) return 1;

    return 0;
}

void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s | Cor: %s | Tropas: %d\n",
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

int main() {
    srand(time(NULL));

    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar tropa vermelha",
        "Ter 10 tropas em um unico territorio",
        "Conquistar qualquer territorio inimigo",
        "Dominar territorio central"
    };
    int totalMissoes = 5;

    char* missaoJogador = (char*) malloc(200 * sizeof(char));

    atribuirMissao(missaoJogador, missoes, totalMissoes);

    exibirMissao(missaoJogador);

    int tamanhoMapa = 3;
    Territorio* mapa = (Territorio*) calloc(tamanhoMapa, sizeof(Territorio));

    strcpy(mapa[0].nome, "Territorio Norte");
    strcpy(mapa[0].cor, "Azul");
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Territorio Leste");
    strcpy(mapa[1].cor, "Vermelho");
    mapa[1].tropas = 4;

    strcpy(mapa[2].nome, "Territorio Sul");
    strcpy(mapa[2].cor, "Verde");
    mapa[2].tropas = 6;

    int turno = 1;

    while (1) {
        printf("\n===== TURNO %d =====\n", turno);
        exibirMapa(mapa, tamanhoMapa);

        printf("Escolha uma acao:\n");
        printf("1 - Atacar\n");
        printf("2 - Finalizar Turno\n");
        printf("3 - Sair\n> ");

        int opc;
        scanf("%d", &opc);

        if (opc == 1) {
            int a, d;
            printf("Escolha seu território atacante (0 a 2): ");
            scanf("%d", &a);
            printf("Escolha território defensor (0 a 2): ");
            scanf("%d", &d);

            atacar(&mapa[a], &mapa[d]);
        }

        else if (opc == 2) {
            if (verificarMissao(missaoJogador, mapa, tamanhoMapa)) {
                printf("\n===== MISSÃO CUMPRIDA! =====\n");
                printf("Parabéns, você venceu!\n");
                break;
            }
            turno++;
        }

        else if (opc == 3) {
            break;
        }
    }

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
