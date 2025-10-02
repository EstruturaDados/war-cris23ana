// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
//int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    //return 0;
//}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.


//--------------------------------------------------------------------------------------------------------------------------------------

//DESAFIO NIVEL INTERMEDIARIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//--constantes globais
#define MAX_TERRITORIO 5
#define TAM_NOME 30
#define TAM_COR 10

//--numeros aleatorios para os dados
int Dados()
{
    int dado = rand() % 6 + 1; // dado de 1 a 6
    return dado;
}

//--definição da estrutura (struct)
typedef struct
{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

//--função para limpar o buffer de entrada
void limparBuffer()
{
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF)
        ;
}
/*
getchar() lê caractere por caractere
Continua lendo até achar \n (ENTER) ou EOF
Isso "limpa" o restante da linha que o scanf deixou no buffer */

//--funcao ataque
void Atacar(Territorio *atacante, Territorio *defensor)
{
    int dadoAtacante = Dados();
    int dadoDefensor = Dados();

    printf("\nO Atacante %s rolou %d\n", (*atacante).nome, dadoAtacante);
    printf("O Defensor %s rolou %d\n", (*defensor).nome, dadoDefensor);
    //--exibindo resultado
    printf("-------------------------------------\n");
    printf("        Resultado da Batalha       \n");
    printf("-------------------------------------\n");

    if (dadoAtacante > dadoDefensor)
    {
        printf("O Atacante venceu! O Defensor perde 1 tropa.\n");
        (*defensor).tropas--; // defensor perde uma tropa
        (*atacante).tropas++; // atacante ganha 1 tropa
    }
    else if (dadoAtacante == dadoDefensor)
    {
        printf("Deu empate! Ninguem perde tropas.\n");
    }
    else
    {
        printf("O Defensor venceu! O Atacante perde 1 tropa.\n");
        (*atacante).tropas--; // atacante perde uma tropa
        (*defensor).tropas++; // defensor ganha uma tropa
    }

    if ((*atacante).tropas == 0)
    {
        strcpy((*atacante).cor, (*defensor).cor); // muda cor do atacante
    }
    else if ((*defensor).tropas == 0)
    {
        strcpy((*defensor).cor, (*atacante).cor); // muda cor do defensor
    }

    printf("\nPressione Enter para jogar a próxima rodada...");
    getchar();
}

//--função main
int main()
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    int totalTerritorio = 0;
    int opcaoAtacante;
    int opcaoDefensor;

    //--alocaçao de memoria
    Territorio *terr = (Territorio *)calloc(MAX_TERRITORIO, sizeof(Territorio));

    if (terr == NULL)
    {//--teste de erro caso a alocaçao de memoria nao tenha funcionado
        printf("Erro: Falha ao alocar memória.\n");
        return 1;
    }

    // loop
    printf("=====================================\n");
    printf("============ PROJETO WAR ============\n");
    printf("=====================================\n");

    printf("\n-------------------------------------\n");
    printf("        Cadastro de Territórios       \n");
    printf("-------------------------------------\n\n");

    //--loop
    for (int i = 0; i < MAX_TERRITORIO; i++)
    {
        printf("        TERRITÓRIO %d      \n\n", i + 1);
        printf("Digite o nome do território: ");
        fgets((terr[i]).nome, TAM_NOME, stdin);

        printf("Digite a cor do exército: ");
        fgets((terr[i]).cor, TAM_COR, stdin);

        (terr[i]).nome[strcspn(terr[i].nome, "\n")] = '\0';
        //substitui o '\n' por '\0' que significa 'fim de string'
        (terr[i]).cor[strcspn(terr[i].cor, "\n")] = '\0';
        //substitui o '\n' por '\0' que significa 'fim de string'

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &terr[i].tropas);
        limparBuffer(); //limpa o '/n' deixado pelo scanf

        totalTerritorio++;

        printf("\n-------------------------------------\n");
        printf(" Território cadastrado com sucesso!\n");
        printf("-------------------------------------\n\n");
    }

    do
    {
        //--impressao do mapa
        printf("======================================\n");
        printf("                 MAPA         \n");
        printf("======================================\n");

        for (int i = 0; i < MAX_TERRITORIO; i++)
        {
            printf("%d - %s (Exercito %s, Tropas: %d)\n", i + 1,
                   terr[i].nome, terr[i].cor, terr[i].tropas);
        }

        //--area de ataque

        printf("\n=====================================\n");
        printf("                ATAQUE         \n");
        printf("======================================\n");

        printf("Escolha o território atacante (entre 1 e 5) ou 0 para Sair: ");
        scanf("%d", &opcaoAtacante);
        limparBuffer();

        if (opcaoAtacante == 0)
        {
            printf("Saindo...\n");
            break;
        }
        if (terr[opcaoAtacante - 1].tropas <= 0)
        {
            printf("O Território escolhido para Ataque não possui tropas.\n");
            continue;
        }

        printf("Escolha o território defensor (entre 1 e 5): ");
        scanf("%d", &opcaoDefensor);
        limparBuffer();

        if (terr[opcaoDefensor - 1].tropas <= 0)
        {
            printf("O Território escolhido para Defesa não possui tropas.\n");
            continue;
        }

        Atacar(&terr[opcaoAtacante - 1], &terr[opcaoDefensor - 1]);

    } while (opcaoAtacante || opcaoDefensor != 0);

    free(terr); //--libera a memoria
    return 0; // fim do programa
}
