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

//DESAFIO NIVEL AVANÇADO MESTRE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

//--constantes globais
#define MAX_TERRITORIO 5
#define TAM_NOME 30
#define TAM_COR 10
#define MAX_MISSOES 5
#define TAM_MISSAO 100

//--constante aux para verificacao
int vitoriaAtacante = 0;
int vitoriaDefensor = 0;

//--criacao de estruturas (structs)
typedef struct{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

typedef struct{
    char missaoAleatoria[TAM_MISSAO];
    int indice;
} Missao;

//--alocacao de memoria para territorios
Territorio *alocarTerritorios() {
    Territorio *territorio = (Territorio*) calloc(MAX_TERRITORIO, sizeof(Territorio));
    return territorio;
}

//--alocacao de memoria para missoes
Missao *alocarMissoes(){
    Missao *missao = (Missao*) calloc(MAX_MISSOES, sizeof(Missao));
    return missao;
}

//--prototipo das funcoes
int rolagemDados();
void limparBuffer();
//---criacao e exibicao de territorios
void criarTerritorio(Territorio *territorio);
void exibirMenu();
void exibirMapa(Territorio *territorio);
//---atribuicao e exibicao de missoes
void atribuirMissao(Missao *missao, char *missoesDisponiveis[], int totalMissoes);
void exibirMissao(const Missao *missao);
//---verificar missao
void verificarMissao();
//---logica de ataque
void atacarFase(Territorio *territorio);
void atacarSimulacao(Territorio *territorio, int atacante, int defensor);
//---liberacao de memoria
void liberarMemoria(Territorio *territorio, Missao *missao);

//--função main
int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int opcao;

    //--lista de missoes
    const char *missoesDisponiveis[] = {
        "Conquistar 03 territorios como Territorio Atacante",
        "Perder 01 tropa para o Territorio Defensor",
        "Obter 05 vitorias como Territorio Atacante ou Defensor",
        "Vencer 02 vezes como Territorio Atacante e 02 vezes como Territorio Defensor",
        "Conquistar 03 territorios como Territorio Defensor"
    };

    /*
    para calcular o numero de itens, sizeof(missoesDisponiveis) da o tamanho total do array em bytes,
    sizeof(missoesDisponiveis[0]) da o tamanho de um elemento (um ponteiro char*) em bytes,
    assim, a divisao de ambos nos da o numero de elementos
    */

    int totalMissoes = sizeof(missoesDisponiveis) / sizeof(missoesDisponiveis[0]);

    //alocar memoria
    Territorio *territorio = alocarTerritorios(MAX_TERRITORIO);
    Missao *missao = alocarMissoes(MAX_MISSOES);

    //--confere se a alocacao funcionou; se nao, retorna 1 para indicar erro
    if (territorio == NULL || missao == NULL){
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    //preencher territorio
    criarTerritorio(territorio);

    //sorteia missao
    atribuirMissao(missao, missoesDisponiveis, MAX_MISSOES);

    //laco
    do {
        //exibe mapa missao e menu a cada iteracao
        exibirMapa(territorio);
        exibirMissao(missao);

        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao){
            case 1:
            atacarFase(territorio);
            break;

            case 2:
            verificarMissao(missao, territorio);
            break;

            case 0:
            printf("\nSaindo...\n");
            break;

            default:
            printf("\nOpcao invalida. Pressione Enter para tentar novamente.");
            getchar();
            break;
        }

    } while (opcao != 0);

    //limpeza de memoria
    liberarMemoria(territorio, missao);
    printf("Memorias liberadas com sucesso!\n");

    return 0;
}

//--implementacao das funcoes

//---rolagem de dados para decidir o vencedor de cada rodada
int rolagemDados(){
    int dado = rand() % 6 +1; //--dado de 1 a 6
    return dado;
}

//---limpar buffer de entrada para evitar problema de leitura consecutiva de scanf e getchar
void limparBuffer(){
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF);
}

//---criacao e exibicao de territorios
void criarTerritorio(Territorio *territorio){
    printf("=====================================\n");
    printf("============ PROJETO WAR ============\n");
    printf("=====================================\n");

    printf("\n-------------------------------------\n");
    printf("        Cadastro de Territórios       \n");
    printf("-------------------------------------\n\n");

    //--o usuario cadastra cinco territorios para jogar
    for (int i = 0; i < MAX_TERRITORIO; i++)
    {
        printf("        TERRITÓRIO %d      \n\n", i + 1);
        printf("Digite o nome do território: ");
        fgets(territorio[i].nome, TAM_NOME, stdin);
        territorio[i].nome[strcspn(territorio[i].nome, "\n")] = '\0';

        printf("Digite a cor do exército: ");
        fgets(territorio[i].cor, TAM_COR, stdin);
        territorio[i].cor[strcspn(territorio[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorio[i].tropas);
        limparBuffer();

        printf("\n-------------------------------------\n");
        printf(" Território cadastrado com sucesso!\n");
        printf("-------------------------------------\n\n");
    }
}

//--exibir menu interativo
void exibirMenu(){
    printf("\n--- MENU ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("Escolha a sua proxima acao: ");
}

//--exibir mapa dos 5 territorios cadastrados
void exibirMapa(Territorio *territorio){
    printf("\n======================================\n");
    printf("                 MAPA         \n");
    printf("======================================\n");

    for (int i = 0; i < MAX_TERRITORIO; i++){
        printf("%d - Territorio %s (Exercito %s, Tropas: %d)\n", i + 1,
        territorio[i].nome, territorio[i].cor, territorio[i].tropas);
    }
}

//---atribuicao e exibicao de missoes
void atribuirMissao(Missao *missao, char *missoesDisponiveis[], int totalMissoes){
    int id = rand() % totalMissoes;
    strcpy((*missao).missaoAleatoria, missoesDisponiveis[id]);
    (*missao).indice = id;
}

void exibirMissao(const Missao *missao){
    printf("\n--- SUA MISSAO ---\n");
    printf("Sua missao é %s\n", (*missao).missaoAleatoria);
}
//---verificar missao

void verificarMissao(Missao *missao, Territorio *territorio){

    int sucesso;

    //--MISSAO: 
    if((*missao).indice = 0)//--Conquistar 03 territorios como territorio Atacante
    {
        if(vitoriaAtacante >= 3){
            sucesso = 1;
        }
    } else if((*missao).indice = 1)//--Perder 01 tropa para o territorio Defensor
    {
        if(vitoriaDefensor >= 1){
            sucesso = 1;
        }
    } else if((*missao).indice = 2)//--Obter 05 vitorias como Atacante ou Defensor
    {
        if(vitoriaAtacante == 5 || vitoriaDefensor == 5){
            sucesso = 1;
        }

    } else if((*missao).indice = 3)//--Vencer 02 vezes como Atacante e 02 vezes como Defensor
    {
        if(vitoriaAtacante >= 2 && vitoriaDefensor >= 2){
            sucesso = 1;
        }
    } else//--Conquistar 03 territorios como Territorio Defensor
    {
        if(vitoriaDefensor >= 3){
            sucesso = 1;
        }
    };

    printf("\n--- VERIFICAÇÃO ---\n");
    if (sucesso == 1) {
        printf("Parabens! Voce cumpriu a missao: %s\n", (*missao).missaoAleatoria);
    } else {
        printf("Infelizmente voce ainda nao cumpriu sua missao, %s\n", (*missao).missaoAleatoria);
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

//---logica de ataque
void atacarFase(Territorio *territorio){

    int atacante, defensor;

    printf("\n=====================================\n");
    printf("            FASE DE ATAQUE         \n");
    printf("======================================\n");

    printf("Escolha o território atacante (entre 1 e 5): ");
    scanf("%d", &atacante);
    limparBuffer();

    if (territorio[atacante - 1].tropas <= 0)
    {
        printf("O Território escolhido para Ataque não possui tropas.\n");
        printf("\nPressione Enter para retornar ao Menu...");
        getchar();
        return;
    }

    printf("Escolha o território defensor (entre 1 e 5): ");
    scanf("%d", &defensor);
    limparBuffer();
    
    if (territorio[defensor - 1].tropas <= 0)
    {
        printf("O Território escolhido para Defesa não possui tropas.\n");
        printf("\nPressione Enter para retornar ao Menu...");
        getchar();
        return;
    }

    atacarSimulacao(territorio, atacante - 1, defensor - 1);
}

//----------------------------------------------------------------------------------
void atacarSimulacao(Territorio *territorio, int atacante, int defensor){

    int dadoAtacante = rolagemDados();
    int dadoDefensor = rolagemDados();
        
    printf("\nO Atacante %s rolou %d\n", territorio[atacante].nome, dadoAtacante);
    printf("O defensor %s rolou %d\n", territorio[defensor].nome, dadoDefensor);

    //--exibindo resultado
    printf("-------------------------------------\n");
    printf("        Resultado da Batalha       \n");
    printf("-------------------------------------\n");

    if (dadoAtacante > dadoDefensor){
        territorio[defensor].tropas--; // defensor perde uma tropa
        territorio[atacante].tropas++; // atacante ganha 1 tropa
        printf("O Atacante venceu! O Defensor perde 1 tropa.\n");
        vitoriaAtacante++;

        if(territorio[defensor].tropas == 0){
            strcpy(territorio[defensor].cor, territorio[atacante].cor); //--muda a cor do defensor para a do atacante
            printf("O Defensor %s agora é do Exercito %s\n", territorio[defensor].nome, territorio[atacante].cor);
        }
    } else if (dadoAtacante == dadoDefensor){
        printf("Deu empate! Ninguem perde tropas.\n");
    } else {
        territorio[atacante].tropas--; // atacante perde uma tropa
        printf("O Defensor venceu! O Atacante perde 1 tropa.\n");
        vitoriaDefensor++;
    }

    printf("\nPressione Enter para jogar a próxima rodada...");
    getchar();
}

//---liberacao de memoria
void liberarMemoria(Territorio *territorio, Missao *missao){
    free(territorio);
    free(missao);
}
