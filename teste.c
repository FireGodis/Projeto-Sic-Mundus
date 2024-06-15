#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define cabecTexto "################################################################################################"

void comprovante_funcao(char nome[], float renda, float renda_dif, int opcao);

// Função de debug para checar se os dados estão corretos
void debug(char nome[], char nome_usuario[], char senha[], char senha_usuario[], float renda, float renda_dif, int D_ou_S) {
    printf(cabecTexto);
    printf("\n\n# Nome: %s\n", nome);
    printf("# Renda: %.2f\n", renda);
    printf("# Senha: %s\n", senha);
    printf("# Nome de usuário: %s\n", nome_usuario);
    printf("# Senha de usuário: %s\n", senha_usuario);
    printf("# Renda Diferenca: %.2f\n", renda_dif);
    printf("# Deposito ou Saque: %d", D_ou_S);
    
    printf("\n" cabecTexto);
}

// Função de cadastro
float cadastro(char nome[], char senha[], float renda) {
    
    bool senha_correta = false;
    
    printf("# Digite seu nome completo: \n\n");
    printf("--> ");
    scanf(" %[^\n]", nome);  // Leitura do nome completo, incluindo espaços
    system("cls");
    printf("\n# Digite seu salário: \n\n");
    printf("--> ");
    scanf("%f", &renda);  // Leitura da renda
    system("cls");
    while(senha_correta == false){
        printf("\n# Digite a sua senha (até 8 caracteres): \n\n");
        printf("--> ");
        scanf("%8s", senha);  // Leitura da senha com no máximo 8 caracteres
        
        if(strlen(senha) > 8) {
            printf("\n\a• A senha não pode ter mais de 8 caracteres. Tente novamente.\n\n");
        } else {
            senha_correta = true;
        }
    }
    system("cls");
    printf("\n\a• Cadastro realizado com sucesso!\n\n");
   
    return renda;
}

// Função de login
void logar(int comparacao, char nome[], char nome_usuario[], char senha[], char senha_usuario[], int *opcao, float *renda, float *renda_dif) {
    int fechar, comprovante = 0;
    fechar = 0;
    int tentativas = 4;

    system("cls");
    printf("\n# Para fazer seu login, digite seu nome: \n\n");
    printf("--> ");
    scanf(" %[^\n]", nome_usuario);
    system("cls");
    comparacao = strcmp(nome_usuario, nome);

    if (comparacao == 0) {
        printf("\a\n• Nome correto.\n\n");
        printf("# Digite a senha: \n");
        while (tentativas > 0 && fechar == 0) {
            printf("\n--> ");
            scanf(" %[^\n]", senha_usuario);
            system("cls");
            comparacao = strcmp(senha_usuario, senha);
            if (comparacao == 0) {
                printf("\a\n» Senha correta!\n\n");
                printf(cabecTexto);
                printf("\n\n• Deseja depositar ou sacar dinheiro?\n\n");
                printf("1. Depositar\n2. Sacar\n");
                printf("\n--> ");
                scanf("%d", &*opcao);
                
                system("cls");

                switch (*opcao) {
                    case 1:
                        printf("\nQuanto deseja depositar?\n");
                        printf("\n--> ");
                        scanf("%f", renda_dif);
                        system("cls");
                        *renda += *renda_dif;
                        printf("\n\a• Depósito concluído com sucesso!\n\n");
                      
                        printf("\nDeseja imprimir o comprovante?\n");
                        printf("\n 1 - sim\n 2 - não\n");
                        printf("\n--> ");
                        scanf("%d", &comprovante);
                        if(comprovante == 1){
                            comprovante_funcao(nome, *renda, *renda_dif, *opcao);
                            
                        }else if(comprovante == 2){
                            printf("\nOk, Obrigado por utilizar nosso Banco!");
                        }else{
                            printf("\nOpção invalida!\n");
                        
                        
                }
                
                        fechar = 1;
                        break;
                    case 2:
                        printf("\n• Quanto deseja sacar?\n");
                        printf("\n--> ");
                        scanf("%f", renda_dif);
                        system("cls");
                        if (*renda < *renda_dif) {
                            printf("Renda insuficiente, digite a senha novamente!\n");
                        } else {
                            *renda -= *renda_dif;
                            printf("\n\a• Saque concluído com sucesso!\n\n");
                            
                            printf("\nDeseja imprimir o comprovante?\n");
                            printf("\n 1 - sim\n 2 - não\n");
                            printf("\n--> ");
                            scanf("%d", &comprovante);
                            if(comprovante == 1){
                              comprovante_funcao(nome, *renda, *renda_dif, *opcao);
                            
                            }else if(comprovante == 2){
                              printf("\nOk, Obrigado por utilizar nosso Banco!");
                            }else{
                              printf("\nOpção invalida!\n");
                              fechar = 1;
                            }
                        }
                        fechar = 1;
                        break;
                    default:
                        printf("\a» Opção inválida!\n");
                        printf("\nDigite a senha novamente: \n");
                        break;
                }
            } else {
                tentativas--;
                system("cls");
                printf("\a\n» Senha incorreta! %d tentativas restantes...\n", tentativas);
            }
        }
        if (tentativas == 0) {
            system("cls");
            printf("\a\a\a\n»» Conta bloqueada. Entre em contato com um gerente.\n");
        }
    } else {
        system("cls");
        printf("\a\n» Login incorreto!\n");
    }
}

void comprovante_funcao(char nome[], float renda, float renda_dif, int opcao) {
    system("cls");
    printf("\n" cabecTexto);
    time_t segundos;
    struct tm *data_hora_atual; 
    
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    char data_formatada[100];
    strftime(data_formatada, 100, "%d/%m/%Y %H:%M:%S", data_hora_atual);
        
    printf("\n\n# Nome: %s\n", nome);
    printf("# Renda: %.2f\n", renda);
    if(opcao == 1){
        printf("# Valor Depositado: %.2f\n", renda_dif);
    }else{
        printf("# Valor Sacado: %.2f\n", renda_dif);
    }
    
    printf("# Data e Hora do Deposito: %s\n", data_formatada);
    printf("# Instituição: BCO SIC Mundus (Brasil) S.A\n");
    if(opcao == 1){
        printf("# Tipo de transição: Deposito\n");
    }else{
      printf("# Tipo de transição: Saque\n");    
    }
      
    
    printf("\n" cabecTexto);
}

// Função principal
int main() {
    char nome[30]; 
    char nome_usuario[30];
    char senha[8];
    char senha_usuario[8];
    float renda = 0;
    float renda_dif = 0;
    int escolha, programa = 0, programa2 = 0, programa3 = 0, comparacao = 0;
    int opcao = 0;
    
    char continuar;
    
    while (programa2 == 0) {
        printf(cabecTexto "\n\n");
        printf("\n• Olá usuário, seja bem-vindo ao banco SIC MUNDUS.\n\n");
        
        printf("• Você deseja fazer um cadastro ou já possui uma conta?\n\n");
        printf("1. Cadastro\n\n");
        printf("--> ");
        scanf("%d", &escolha);
        system("cls");

        switch (escolha) {
            case 1:
                renda = cadastro(nome, senha, renda);
                programa2 = 1;
                break;
            default:
                printf("\a\n» Resposta inválida!\n\n");
                break;
        }
    }

    while (programa == 0) {
        programa3 = 0;  // Redefine programa3 para permitir múltiplas iterações
        printf("• Você deseja fazer um cadastro ou já possui uma conta?\n");
        printf("\n1. Logar\n");
        printf("2. Cadastrar\n\n");
        printf("--> ");
        scanf("%d", &escolha);
        system("cls");

        switch (escolha) {
            case 1:
                logar(comparacao, nome, nome_usuario, senha, senha_usuario, &opcao, &renda, &renda_dif);
                break;
            case 2:
                renda = cadastro(nome, senha, renda);
                break;
            default:
                printf("\a\n» Opção inválida!\n\n");
                break;
        }

        //debug(nome, nome_usuario, senha, senha_usuario, renda, renda_dif, opcao);
        
        printf("\n\n# Deseja continuar no programa?\n\n");
        printf("E - para encerrar.\nC - para continuar.\n\n");
        printf("--> ");
        scanf(" %c", &continuar);
        system("cls");
        printf("\n" cabecTexto);
        printf("\n\n\a");

        while (programa3 == 0) {
            if (continuar == 'E' || continuar == 'e') {
                printf("\a\a");
                programa = 1;  // Encerra o programa
                programa3 = 1;
            } else if (continuar == 'C' || continuar == 'c') {
                printf("\a");
                programa = 0;
                programa3 = 1;
            } else {
                printf("\a\nOpção inválida! Reescreva tudo novamente: ");
                printf("\n\n" cabecTexto);
                printf("\n\n\a");
                printf("\n\n# Deseja continuar no programa?\n\n");
                printf("E - para encerrar.\nC - para continuar.\n\n");
                printf("--> ");
                scanf(" %c", &continuar);
                printf("\n" cabecTexto);
                printf("\n\n\a");
            }
        }
    }

    return 0;
}