#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
//Funcoes
int menu();
void cadastrar();
void alterar();
void excluir();
void listar();
void limparTela();
void pesquisar();
void escrever_arquivo();
int ler_arquivo();
//Estruturas
typedef struct {
    char nome[50];
    int numero;

}dados;
/*TRABALHO FINAL - DISCIPLINA: PROGRAMACAO ESTRUTURADA*/
/*Desenvolver uma agenda telefonica e guardar as informações em um arquivo. Criar uma
funcao para cada item do menu e listar os contatos em ordem alfabética*/
int main(){
    /*Variaveis. MAX é uma constante com o numero maximo de cadastros, cr = numero
    de cadastros realizados*/
    dados agenda[MAX];
    int cr;
    int opcao;
    cr = ler_arquivo(agenda);
	do{
		
		opcao = menu();
        switch(opcao){
            case 1:
                cadastrar(&agenda,&cr);
                break;
            case 2:
                alterar(&agenda,&cr);
                break;
            case 3:
                excluir(&agenda,&cr);
                break;
            case 4:
                listar(&agenda,&cr);
                break;
            case 5:
                pesquisar(&agenda,&cr);
                break;
            case 6:
            	escrever_arquivo(agenda,&cr);
                printf("Sair\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
        
	}while(opcao != 6);
    return 0;
}


int menu(){
	int opcao;
	char op[2];

        printf("#####################\n");
        printf("# AGENDA TELEFONICA #\n");
        printf("#####################\n");

        printf("ESCOLHA UMA DAS OPCOES ABAIXO\n");
        printf("1 - CADASTRAR\n2 - ALTERAR\n3 - EXCLUIR\n4 - LISTAR CONTATOS\n5 - PESQUISAR CONTATOS\n6 - SAIR E SALVAR\n");
        //Ler a opcao digitada e converte para um int, caso o usuario digite um carectere a funcao atoi retorna zero
		scanf(" %s",op);
        opcao = atoi(op);

        //Verifica se o usuario digitou uma opcao valida
        if(opcao == 0){
            strcpy(op,"6");
        }

	return opcao;
}

void cadastrar(dados *agenda, int *cr){
    if((*cr)<MAX){
	//Variaveis.
    int i,r,j,n;
    char nome[50];
    printf("Digite o nome: ");
    scanf(" %50[^\n]", nome);
    printf("\nDigite o numero: ");
    scanf("%d", &n);

    for(i=0; i<*cr; i++){
        r = strcmp(nome, agenda[i].nome);
        if(r<0){
            for(j=*cr;j>i; j--){

                strcpy(agenda[j+1].nome,agenda[j].nome);
                agenda[j+1].numero = agenda[j].numero;
            }
            break;
        }
    }
    strcpy(agenda[i+1].nome,agenda[i].nome);
    agenda[i+1].numero = agenda[i].numero;
    strcpy(agenda[i].nome,nome);
    agenda[i].numero = n;
    (*cr)++;
    }else
    	printf("Agenda cheia, apague um contato!\n");
    
}
void alterar(dados *agenda, int *cr){
    //Variaveis
    char nome[50];
    int i=0, opcao,j=0;
    //Se no final do while j for zero, siginifica que o contato nao foi encontrado

    printf("Qual contato deseja alterar ? \n");
    scanf(" %50[^\n]",nome);
    while(i<*cr){
        if(strcmp(nome, agenda[i].nome) == 0){
			j=1;
   	        printf("Deseja alterar qual campo.\n1 - Nome\n2 - Numero\n");
   	        scanf("%d", &opcao);
            if(opcao == 1){
                printf("Informe o novo nome:\n");
                scanf(" %50[^\n]",agenda[i].nome);
            }else if(opcao == 2){
                printf("Informe o novo numero:\n");
                scanf("%d",&agenda[i].numero);
            }
            break;
        }
        i++;
    }
    if(j==0)
    	printf("Contato nao encontrado!!!\n");
    	

    //Ordenando
    int x, y,r,auxN,k=(*cr);
    char aux[50];
    for(x=0; x<=k; x++){
        for(y = x+1; y < k; y++){
            r = strcmp(agenda[x].nome,agenda[y].nome);
            if(r > 0){
                strcpy(aux,agenda[x].nome);
                strcpy(agenda[x].nome,agenda[y].nome);
                strcpy(agenda[y].nome,aux);
                auxN = agenda[x].numero;
                agenda[x].numero = agenda[y].numero;
                agenda[y].numero = auxN;
            }
        }
    }

}

void excluir(dados *agenda, int *cr) {
    //Variaveis.
    int i,r;
    char nome[50];
    printf("Digite o nome: ");
    scanf(" %50[^\n]", nome);
    for(i=0; i<*cr; i++){
        r = strcmp(nome, agenda[i].nome);
        if(r==0){
            int j = i;
            while(j<(*cr)){
                strcpy(agenda[j].nome,agenda[j+1].nome);
                agenda[j].numero = agenda[j+1].numero;
                j++;
            }
            (*cr)--;
            break;
        }
    }


}

void listar(dados *agenda, int *cr){
    //Variaveis
    int a=0;

    while(a<(*cr)){
        printf("\n");
        printf("%d\n",a+1);
        printf("Nome: %s\n",agenda[a].nome);
        printf("Numero: %d\n", agenda[a].numero);
        a++;
    }
}

void pesquisar(dados *agenda,int *cr) {
    //Variaveis.
    int i, r;
    char nome[50];
    printf("Digite o nome: ");
    scanf(" %50[^\n]", nome);
    for (i = 0; i < *cr; i++) {
        r = strcmp(nome, agenda[i].nome);
        if (r == 0) {
            printf("\n");
            printf("Nome: %s\n",agenda[i].nome);
            printf("Numero: %d\n", agenda[i].numero);
            break;
        }

    }
    if (i == (*cr)) {
        printf("Contato nao encontrado\n");
    }
}

void escrever_arquivo(dados agenda[], int *cr){
	int i;
	int len_vet = (*cr); // tamanho do vetor
	FILE * arq;

	// abre o arquivo para escrita no modo append (adiciona ao final)
	arq = fopen("dados.bin", "wb");

	if(arq != NULL)
	{
		for(i = 0; i < len_vet; i++)
			// escreve cada elemento do vetor no arquivo
			fwrite(&agenda[i], sizeof(dados), 1, arq);
		fclose(arq); // aborta o programa
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1); // aborta o programa
	}
}
int ler_arquivo(dados agenda[MAX])
{
	// abre o arquivo para leitura
	FILE * arq = fopen("dados.bin", "rb");
	//Cria um arquivo caso ele não exista
	if(arq == NULL){
		arq = fopen("dados.bin", "wb");
		arq = fopen("dados.bin", "rb");
		}
	if(arq != NULL)
	{
		int indice = 0;
		while(1)
		{
			dados p;

			// fread ler os dados
			// retorna a quantidade de elementos lidos com sucesso
			size_t r = fread(&p, sizeof(dados), 1, arq);

			// se retorno for menor que o count, então sai do loop
			if(r < 1)
				break;
			else
				agenda[indice++] = p;
		}
		fclose(arq); // fecha o arquivo
		return indice;
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1); // aborta o programa
	}
}