#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#define SH 1
#define MD 20
#define BG 80

//ESTRUTURAS
typedef struct cadastro {
		char titulo[BG];
		char nomeAutor[BG];
		char editora[MD];
		char isbn[MD];
		char tipo;
		int edicao;
		int quantidade;
		int caixa;
		int ano;
}tipoCD;

//FUNÇÕES
void cadastrar();
int contarInfo(tipoCD info[BG]);
void listaGeral(tipoCD info[BG]);

//VARIÁVEIS GLOBAIS
char op =' ',mais,LR;
int i,x;
tipoCD info[MD];
int tCaixa = 10;

int main() {
unsigned int cp    = 1252;
unsigned int cpin  = GetConsoleCP();
unsigned int cpout = GetConsoleOutputCP();
SetConsoleCP(cp);
SetConsoleOutputCP(cp);

inicio:
	system("cls");
    printf("OPCOES\n");
    printf("[ 1 ] Cadastro \n");
    printf("[ 2 ] Listar Geral \n");
    printf("[ 3 ] VAZIO \n");
    printf("[ 4 ] VAZIO \n");
    printf("[ 0 ] Sair \n");
    printf("\nDigite uma opcao:\n> ");
    fflush(stdin);
	scanf("%c", &op);
	//do{
	    switch (op) {
	        case '1':
	            cadastrar(info);
				system("pause");
				goto inicio;
	            break;
	        case '2':
				listaGeral(info);
				system("pause");
				goto inicio;
	            break;
	        case '3':
				system("pause");
				goto inicio;
	            break;
	        case '0':
	                SetConsoleCP(cpin);
				    SetConsoleOutputCP(cpout);
				    printf("\nSaindo... pressione ENTER para finalizar\n\n");
					system("pause");
				    return EXIT_SUCCESS;
	        default:
	            printf("\nErro: Opcao invalida! [enter] \n\n");
	            system("pause");
	            goto inicio;
	            break;
	    }
   // }while(op!=0);
  return 0;
}
void cadastrar(tipoCD info[BG]){
	int indice = contarInfo(info);
	FILE * arq = fopen("bancoDados.txt", "a+");
	if(arq != NULL){	
	mais = 'S';
		while(mais=='S'){
			x = 1;
			system("cls");
			printf ("Por favor, digite as seguintes informacoes da obra...\n\n");
			printf ("Titulo (letras e numeros): \n");
				fflush (stdin);
			    gets(info[indice].titulo);
		    printf ("\nNome do Autor (letras e numeros):\n");
			    fflush (stdin);
			    gets(info[indice].nomeAutor);
		    printf ("\nNome da Editora: (letras e numeros):\n");
			    fflush (stdin);
			    gets(info[indice].editora);
		    printf ("\nNumero da Edicao: (somente numeros):\n");
			    fflush (stdin);
			    scanf("%d",&info[indice].edicao);
		    printf ("\nCodigo ISBN: (letras e numeros)\n");
			    fflush (stdin);
			    gets(info[indice].isbn);
			printf ("\nAno de publicacao (somente numeros):\n");
			    fflush (stdin);
			    scanf("%d",&info[indice].ano);
			printf ("[L]ivro ou [R]evista? Digite L ou R  \n");
				fflush (stdin);
				info[indice].tipo = toupper(getchar());
				while(info[indice].tipo != 'L' && info[indice].tipo != 'R' ){
                        printf("\nEscolha o tipo correto: [L]IVRO ou [R]EVISTA: ");
                        fflush(stdin);
                        info[indice].tipo = toupper(getchar());
                }
				system("cls");
				printf ("\nDigite as seguintes informacoes sobre o armazenamento...\n\n");
		    printf ("\nQuantidade de exemplar (somente numeros):\n");
			    fflush (stdin);
			    scanf("%d",&info[indice].quantidade);
		    printf ("Em qual caixa esta sendo armazenada (somente numeros):\n");
			    fflush (stdin);
			    scanf("%d",&info[indice].caixa);
		    	while(info[indice].caixa < 0 || info[indice].caixa > tCaixa ){
			    	printf("\nEsta caixa nao existe! Digite outro valor.\n");
			    	fflush (stdin);
			    	scanf("%d",&info[indice].caixa);
				}
		    printf ("\n");
		    fwrite(&info[indice], sizeof(tipoCD), 1, arq);
		    printf("Deseja cadastrar outra obra? [S] para Sim ou outra tecla para sair\n> ");
		    fflush(stdin);
		    mais = toupper(getchar());
	    }
    	fclose(arq);
	}
	else{
		printf("\nErro ao abrir o arquivo!\n");
		exit(1);
	}
}
int contarInfo(tipoCD info[BG]){
int contInfo = 0;
	FILE *arq = fopen("bancoDados.txt", "r");
        if(arq == NULL){
            printf("O arquivo nao pode ser aberto.");
            getchar();
            exit(1);
        }
	
		while(1){
			tipoCD p;
			int recebeP = fread(&p, sizeof(tipoCD), 1, arq);

			if(recebeP < 1) break;
			else
				info[contInfo] = p;
			contInfo++;
		}
		fclose(arq);
		return contInfo;
}
void listaGeral(tipoCD info[BG]){	
	int totalInfo = contarInfo(info),i;
	
	printf("\nObras Cadastradas: %d\n", totalInfo);
	printf("\n");
	for(i = 0; i < totalInfo; i++){
		printf("\n[%d] Titulo: %s\nAutor: %s\nEditora: %s\nEdicao: %d\nAno: %d\nTIPO: %c\n ISBN: %s\nCaixa: %d\nQuantidade: %d\n", i+1, info[i].titulo, info[i].nomeAutor, info[i].editora, info[i].edicao, info[i].ano,info[i].tipo, info[i].isbn, info[i].caixa, info[i].quantidade);	
	}
}

