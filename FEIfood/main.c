#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


void inicio();
void cadastro();
void login();
void menu();
void busca_alimento();
void cadastrar_pedido();
void editar_pedido();
void avaliacao_pedido(int id);
void listar_pedidos();
void listar_avaliacoes();

char username[255], senha[255];
int ids_usados[99] = {0};


//função de início do programa
void inicio(){
    int x;
    while (1)
    {
    printf("-------- BEM-VINDO! --------\n");
    printf("1 - Cadastre-se\n");
    printf("2 - Login\n");
    printf("0 - Sair\n");
    printf("----------------------------\n");
    printf("Opção: ");
    scanf("%d", &x);
    
    if (x == 1){
        cadastro();
        menu();
    }

    else if(x == 2){
        login();
       
    }


    else if (x == 0){
        break;
    }

    else{
        printf("Opção inválida!\n");
    }
    }

}

void menu(){
    int x;
    while(1){
    printf("----------- MENU -----------\n");
    printf("1 - Buscar alimento\n");
    printf("2 - Cadastrar pedido\n");
    printf("3 - Editar pedido\n");
    printf("4 - Ver pedidos\n");
    printf("5 - Ver avaliações\n");
    printf("0 - Voltar\n");
    printf("----------------------------\n");
    printf("Opção: ");
    scanf("%d", &x);

    if(x == 1){
        busca_alimento();

    }

    else if(x == 2){
        cadastrar_pedido();
    }

    else if(x == 3){
        editar_pedido();
    }

    else if(x == 4){
        listar_pedidos();
    }

    else if(x == 5){
        listar_avaliacoes();
    }

    else if(x == 0){
        break;
    }

    else{
        printf("Opção inválida!\n");
    }
}   
}

void cadastro(){
    FILE *usuarios = fopen("dados_usuarios.txt", "a");
    
    if (usuarios == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    //lê as informacoes inseridas pelo usuario
    printf("Crie seu username: ");
    scanf("%s", username);
    printf("Crie sua senha: ");
    scanf("%s", senha);
    fprintf(usuarios, "%s %s\n", username, senha);

    printf("Cadastro realizado com sucesso, %s!\n", username);

    

}

void login(){
    FILE *usuarios = fopen("dados_usuarios.txt", "r");

    if (usuarios == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char user_correto[255], senha_correta[5];
    int encontrado = 0;

    printf("Digite seu username: ");
    scanf("%s", username);
    printf("Digite sua senha: ");
    scanf("%s", senha);

    //le as linhas dos arquivos e compara as strings para checar se o username a senha batem com oq esta escrito
    while (fscanf(usuarios, "%s %s", user_correto, senha_correta) == 2) {
        if (!strcmp(username, user_correto) && !strcmp(senha, senha_correta)) {
            printf("Login realizado com sucesso! Bem-vindo, %s!\n", username);
            encontrado = 1;
            break;
        }
    }

    fclose(usuarios);

    if (encontrado) {
        menu();
    } else {
        printf("Usuário ou senha incorretos.\n");
    }

    fclose(usuarios);
    

}

void busca_alimento(){
    FILE *alimentos = fopen("alimentos.txt", "r");

    if (alimentos == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char nome_alimento[255];
    char linha[255];
    char linha_print[255];
    int encontrado = 0;

    while (fgets(linha_print, sizeof(linha_print), alimentos) != NULL) {
        char nome_print[100];
        sscanf(linha_print, "%[^;]\n", nome_print);
        printf("%s\n", nome_print);
    }

    rewind(alimentos);

    printf("Digite o alimento que deseja as informações: ");
    scanf("%s", nome_alimento);

    //le a linha e a guarda dentro da string linha
    while (fgets(linha, sizeof(linha), alimentos) != NULL) {
        char nome[100], calorias[20], descricao[200]; //variaveis para guardar as informacoes

        sscanf(linha, "%[^;];%[^;];%[^\n]", nome, descricao, calorias);

        if (strcmp(nome_alimento, nome) == 0) { // compara as strings nome_alimento e nome
            printf("Alimento encontrado: %s\n", nome); 
            printf("Informações: %s, %s\n", descricao, calorias);
            encontrado = 1; // encontrado TRUE
            break;
        }
    }
    

    if(!encontrado){
        printf("Alimento não encontrado :(\n"); //caso alimento nao seja encontrado
    } 

    fclose(alimentos); // fecha arquivo
}

void cadastrar_pedido(){
    FILE *alimentos = fopen("alimentos.txt", "r");

    if (alimentos == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    FILE *pedidos = fopen("pedidos.txt", "a");

    if (pedidos == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    srand(time(NULL));
    char nome_alimento[255];
    char linha[255];
    char itens_pedidos[255][255];
    int qtd_itens = 0;
    int encontrado = 0;
    int fez_pedido = 0;
    int id;

    //gera um ID novo a cada pedido
    do {
        id = rand() % 99;
    } while (ids_usados[id]);

    ids_usados[id] = 1;

    printf("-- Digite 0 para finalizar seu pedido! --\n");
    fprintf(pedidos, "%d, %s: ",id , username);

    while(1){
        printf("Digite seu pedido: ");
        scanf("%s", nome_alimento);

        if(strcmp(nome_alimento, "0") == 0){
            if (fez_pedido) {
                fprintf(pedidos, "\n");
            }
            break;
        }

        //volta para o arquivo toda vez que uma informaçao é lida
        rewind(alimentos);
        encontrado = 0;
    
        //le a linha e a guarda dentro da string "linha"
        while (fgets(linha, sizeof(linha), alimentos) != NULL) {
            char nome_ag[100];

            sscanf(linha, "%[^;]", nome_ag);

            if (strcmp(nome_alimento, nome_ag) == 0) {
                printf("%s adicionado ao pedido!\n", nome_ag);
                fprintf(pedidos, "%s ", nome_ag);
                strcpy(itens_pedidos[qtd_itens], nome_ag);
                qtd_itens++;
                fez_pedido = 1;
                encontrado = 1;
            }

        }

    

        if(!encontrado){
            printf("Alimento não encontrado :(\n");
        } 

    }
    
    if(fez_pedido){
        printf("\n--- Pedido Finalizado ---\n");
        printf("ID do Pedido: %d\n", id);
        printf("Cliente: %s\n", username);
        printf("Itens:\n");
        for (int i = 0; i < qtd_itens; i++) {
            printf("- %s\n", itens_pedidos[i]);
        }  
        avaliacao_pedido(id);

    }

    fclose(pedidos);
}

void listar_pedidos() {
    FILE *pedidos = fopen("pedidos.txt", "r");
    if (pedidos == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char linha[255];
    int encontrou = 0;

    printf("\n--- Seus pedidos ---\n");

    while (fgets(linha, sizeof(linha), pedidos) != NULL) { //le as linhas que contem os pedidos
        int id;
        char nome[100];
        char itens[200];


        if (sscanf(linha, "%d, %[^:]: %[^\n]", &id, nome, itens) == 3) { //checa para ver se tudo esta certo na linha (id, nome e itens) do pedido
            if (strcmp(nome, username) == 0) { //checa para ver se no nome do usuario que fez o pedido bate com o username
                printf("ID: %d, Itens: %s\n", id, itens);
                encontrou = 1;
            }
        }
    }

    if (!encontrou){
        printf("Nenhum pedido encontrado para o usuário '%s'.\n", username);
    }

    fclose(pedidos);
}


void editar_pedido(){
    FILE *pedidos = fopen("pedidos.txt", "r");
    if (pedidos == NULL) {
        printf("Erro ao abrir arquivo de pedidos!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(pedidos);
        return;
    }

    listar_pedidos();

    int id_busca, id;
    char user[100], itens[300], linha[512];
    int encontrado = 0;
    int alimento_encontrado = 0;

    printf("Digite o ID do pedido que deseja editar: ");
    scanf("%d", &id_busca);
    getchar(); 

    while (fgets(linha, sizeof(linha), pedidos)) {
        sscanf(linha, "%d, %[^:]: %[^\n]", &id, user, itens);

        if (id == id_busca && strcmp(user, username) == 0) {
            encontrado = 1;
            printf("\nItens atuais: %s\n", itens);

            // separa os itens
            char *itens_sep[50];
            int qtd = 0;
            for (char *tok = strtok(itens, " "); tok; tok = strtok(NULL, " "))
                itens_sep[qtd++] = tok;

            for (int i = 0; i < qtd; i++)
                printf("%d - %s\n", i + 1, itens_sep[i]);

            int escolha;
            printf("\nNúmero do item para alterar/remover: ");
            scanf("%d", &escolha);
            getchar();

            if (escolha < 1 || escolha > qtd) {
                printf("Item inválido!\n");
                fclose(pedidos);
                fclose(temp);
                remove("temp.txt");
                return;
            }

            char novo[100];
            printf("Novo item (ou 0 para remover): ");
            fgets(novo, sizeof(novo), stdin);
            novo[strcspn(novo, "\n")] = 0;

            //checar se alimento existe
            int alimento_existe = 0;
            if (strcmp(novo, "0") != 0) { 
                FILE *alimentos = fopen("alimentos.txt", "r");
                if (alimentos == NULL) {
                    printf("Erro ao abrir arquivo de alimentos!\n");
                } else {
                    char linha_alimento[255], nome_ag[100];
                    while (fgets(linha_alimento, sizeof(linha_alimento), alimentos) != NULL) {
                        sscanf(linha_alimento, "%[^;]", nome_ag);
                        if (strcmp(novo, nome_ag) == 0) {
                            alimento_existe = 1;
                            break;
                        }
                    }
                    fclose(alimentos);
                }

                if (!alimento_existe) {
                    printf("Alimento não encontrado na lista. Tente novamente\n");
                    fclose(pedidos);
                    fclose(temp);
                    remove("temp.txt");
                    return;
                }
            }

            // Grava pedido atualizado
            fprintf(temp, "%d, %s: ", id, user);
            for (int i = 0; i < qtd; i++) {
                if (i == escolha - 1 && strcmp(novo, "0") == 0)
                    continue; // remove
                else if (i == escolha - 1)
                    fprintf(temp, "%s ", novo); // substitui
                else
                    fprintf(temp, "%s ", itens_sep[i]);
            }
            fprintf(temp, "\n");

            printf("Pedido atualizado!\n");
        } else {
            fputs(linha, temp);
        }
    }

    fclose(pedidos);
    fclose(temp);
    
    if (encontrado) {
        remove("pedidos.txt");
        rename("temp.txt", "pedidos.txt");
    } else {
        printf("Nenhum pedido encontrado com ID %d para %s.\n", id_busca, username);
        remove("temp.txt");
    }
}


void avaliacao_pedido(int id){
    FILE *avaliados = fopen("pedidos_avaliados.txt", "a");

    if (avaliados == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char nota[6];

    printf("\n--- AVALIAÇÃO DO PEDIDO ---\n");
    printf("Dê uma nota geral para o seu pedido (1 a 5 estrelas(*)): \n");
    scanf("%s", nota);

    fprintf(avaliados, "%d, %s; Nota(*): %s\n", id, username, nota);
    printf("Obrigado!\n");

    

}

void listar_avaliacoes(){
    FILE *avaliacoes = fopen("pedidos_avaliados.txt", "r");
    if (avaliacoes == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char linha[255];
    int encontrou = 0;

    printf("\n--- Suas avaliações ---\n");

    while (fgets(linha, sizeof(linha), avaliacoes) != NULL) { //le as linhas que contem os pedidos
        int id;
        char nome[100];
        char nota[6];


        if (sscanf(linha, "%d, %[^;]; Nota(*): %[^\n]", &id, nome, nota) == 3) { //checa para ver se tudo esta certo na linha (id, nome e nota) da avaliacao
            if (strcmp(nome, username) == 0) { //checa para ver se no nome do usuario que fez a avaliacao bate com o username
                printf("Pedido: %d, Nota: %s\n", id, nota);
                encontrou = 1;
            }
        }
    }

    if (!encontrou){
        printf("Nenhum pedido encontrado para o usuário '%s'.\n", username);
    }

    fclose(avaliacoes);
}


int main(){
    inicio();
    srand(time(NULL));
    return 0;
}