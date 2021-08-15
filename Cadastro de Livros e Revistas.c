#include <stdio.h> 								/*standard input and output*/
#include <stdlib.h> 							/*standard library*/
#include <string.h> 							/*strcpy function*/
#include <locale.h> 							/*pt-br (portuguese language)*/
#include <ctype.h> 								/*toupper function*/
#define caixaMax 5 								/*maximum number of box*/
#define qtMax 10   								/*maximum space available in each box*/
#define cadMax caixaMax * qtMax 				/*maximum number of records*/

/*Struct_________________*/
typedef struct cad_struct{
        char nome[80]; 							//name (book/magazine)
        char autor[80]; 						//author
        char editora[40]; 						//publishing company
        char catg; 								//category
        char isbn[20]; 							//international standard book number
        int ano; 								//year of publication
        int edicao; 							//issue number
        int quant; 								//number of copies
        int caixa; 								//number of copies of each book or magazine
}CAD;
/*_________________Struct*/

/*Funções/Functions________________________*/
    void menu(); 								/*to display program start options*/
    void cadastro(CAD registro[cadMax]);		/*to register book or magazine*/
    void salvarTmps(CAD registro[cadMax]);		/*for temporary records to be effectively saved*/
    void listar();								/*a simple registry preview*/
    void tipo();								/*for print details only*/
    void sobre();								/*program author information*/
    void listarLivros(CAD registro[cadMax]);	/*display all saved books*/
    void listarRevistas(CAD registro[cadMax]);	/*display all saved magazines*/
    void listarCaixas(CAD registro[cadMax]);	/*display all the contents of the boxes*/
    void repChar (char caract , int qtde); 		/*simple function to make code cleaner and train logic*/
    void qLinha (int qtde);						/*for print details only*/
    int lerArquivo(CAD registro[cadMax]);		/*to read the cad_bd.txt file, where the records will be saved*/
    void atualizarCaixa(CAD registro[cadMax]);	/*to update the number of books/magazines in the box*/
    void pesquisa(CAD registro[cadMax]);		/*search for a book or magazine by name (including partial name) or box number*/
    void status(CAD registro[cadMax]);			/*display available spaces in the box*/
/*__________________________________Funções*/

/*Variáveis Globais____________*/
    CAD registro[cadMax];
    CAD tmps;
    char big,sn;
    int cont,opt,i,j,realCaixa;
    int vCaixa[caixaMax];
    int atuaLin;
/*____________Variáveis Globais*/

int main(){
    setlocale(LC_ALL, "Portuguese");

    for(;;) {
        system("cls");
        menu(); /*2 - Possuir um menu de opção.*/
        printf("\nDigite uma opção: ");
        scanf("%d", &opt);
        switch(opt){
            case 1:
                    cadastro(registro);/*2.1 - Incluir o registro das obras.*/
                    break;
            case 2:
                    listarLivros(registro);/*2.2 - Listar todos os livros.*/
                    break;
            case 3:
                    listarRevistas(registro);/*2.3 - Listar todas as revistas.*/
                    break;
            case 4:
                    listarCaixas(registro);/*2.4- Listar as obras por caixa.*/
                    break;
            case 5:
                    pesquisa(registro);/*função extra*/
                    break;
            case 6:
                    sobre(); /*1 - Possuir a sua identificação (RA-Nome-Curso)*/
                    break;
            case 0:
                    exit(0);
            default:
                    printf("\aOpção inválida!\n");
                    getchar();
                    getchar();
                    break;
        }
    }
return 0;
}
   void menu(void){
        int i,total = 10;
        char titulos[7][30]= {  "[ CADASTRO         ]",
                                "[ Listar LIVROS    ]",
                                "[ Listar REVISTAS  ]",
                                "[ Listar CAIXAS    ]",
                                "[ PESQUISA/STATUS  ]",
                                "[ SOBRE            ]",
                                "[ FECHAR           ]"};
        system("cls");
        qLinha(2);
        repChar('_', 2);
        printf("digite");
        repChar('_', 51); 
        printf("para ir...");repChar('_', 10);
        qLinha(3);
        for (i = 0; i < 6; i++){
            printf("[   %d   ]",i+1);
            repChar('_', 50);
            printf("%-*s\n\n", total, titulos[i]);
        }
            printf("[   0   ]");
            repChar('_', 50);
            printf("%-*s", total, titulos[6]);
            qLinha(3);
    }
    void cadastro(CAD registro[cadMax]){
    atuaLin = lerArquivo(registro);
	FILE *arq = fopen("cad_bd.txt", "a+");
    system("cls");
    int working = 1;
        while(working){
            if (lerArquivo(registro) > cadMax){
                printf("LIMITE DE CADASTROS ATINGIDOS!\a\n");
                working = 0;
                break;
            }
            else{
                system("cls");
                printf("\nNOME do LIVRO ou REVISTA (evite acentuação): ");
                fflush(stdin);
                strupr(fgets(tmps.nome, 80, stdin)); /*strupr: records in capital letters, making the search easier and to avoid errors*/
                printf("\nTIPO da obra, [L] para LIVRO e [R] para REVISTA: ");
                fflush(stdin);
                tmps.catg = toupper(getchar());
                    while(tmps.catg != 'L' && tmps.catg != 'R' ){
                        printf("\nImportante! [L] para LIVRO ou [R] para REVISTA: ");
                        fflush(stdin);
                        tmps.catg = toupper(getchar());
                    }
            }
                printf("\nNOME do AUTOR da obra: ");
                fflush(stdin);
                strupr(fgets(tmps.autor, 80, stdin));
                printf("\nNOME da EDITORA: ");
                fflush(stdin);
                strupr(fgets(tmps.editora, 40, stdin));
                printf("\nNÚMERO da EDIÇÃO(ed.), somente números! (ex: 21) : ");
                scanf("%d", &tmps.edicao);
                printf("\nANO desta edição/reimpressão, somente ano/números (ex: 2020) : ");
                scanf("%d", &tmps.ano);
                printf("\nISBN/ASIN (números/letras/caracteres especiais): ");
                fflush(stdin);
                strupr(fgets(tmps.isbn, 20, stdin));
                printf("\nCAIXA onde será armazenada (de 1 a %d) ou ZERO para visualizar STATUS: ", caixaMax);
                scanf("%d", &tmps.caixa);
                if(tmps.caixa <= 0)status(registro);
                printf("\nDigite a caixa selecionada: ");
				scanf("%d", &tmps.caixa);
				while(tmps.caixa < 1 || tmps.caixa > caixaMax){
                    printf("\nSelecione uma das caixas disponíveis >> 1 a %d,", caixaMax);
                    printf("\nDigite o número correto da caixa: ");
                    scanf("%d", &tmps.caixa);
                }
                realCaixa = tmps.caixa-1;
                atualizarCaixa(registro);
                if(vCaixa[realCaixa] == qtMax){
                    printf("\nCaixa cheia! Tentar outra? Digite uma caixa diferente ou ZERO para cancelar: \a\n");
                    while((vCaixa[realCaixa] == qtMax && realCaixa >= 0)||(realCaixa > caixaMax-1)){
                    printf("\nDigite o número da caixa: ");
                    scanf("%d", &tmps.caixa);
                    realCaixa = tmps.caixa-1;
                    	if(vCaixa[realCaixa] == qtMax)printf("\nEsta caixa também cheia!\a\n");
						if(realCaixa > caixaMax-1)printf("\n\aSelecione uma das caixas disponíveis: 1 a %d. Ou ZERO para cancelar: ", caixaMax);
						if(realCaixa < 0){
                    		printf("\n\aRegistro cancelado!\n");
                    		goto outra; 
                    		system("pause");
						}
                	}
                }
                else{
                    system("cls");
					printf("\nQUANTIDADE desta obra armazenada na caixa # %d, resta(m) %d espaço(s): ", tmps.caixa, (qtMax - vCaixa[realCaixa]));
                    scanf("%d", &tmps.quant);
                    if(tmps.quant+vCaixa[realCaixa]>qtMax){
                        printf("Esta caixa tem somente %d espaço(s) disponível(is)!\a\n",qtMax-vCaixa[realCaixa]);
                            printf("Deseja armazenar parcialmente? Digite (S) para Sim ou qualquer outra tecla para sair: \a");
                            getchar();
                            sn = toupper(getchar());
                            if(sn=='S'){
                                registro[atuaLin].quant = qtMax - vCaixa[realCaixa];
                                salvarTmps(registro);
                                system("cls");
                                printf("\nREGISTRO PARCIAL realizado com SUCESSO!\n");
                                fclose(arq);
                                getchar();
                                listar();
                                atuaLin++;
                            }
                    }
                    else{
                        registro[atuaLin].quant = tmps.quant;
                        salvarTmps(registro);
                        system("cls");
                        printf("\nREGISTRO realizado com SUCESSO!\n");
                        fclose(arq);
                        getchar();
                        listar();
                        atuaLin++;
                    }
                }
               outra:
			   printf("\n Digite (S) para cadastrar outra obra ou <enter> para sair: ");
                getchar();
                big = toupper(getchar());
                    if (big!='S'){
                        working = 0;
                    }
            }
        }
    void salvarTmps(CAD registro[cadMax]){
    FILE *arq;
    arq = fopen("cad_bd.txt", "a+");
        if(arq != NULL){
            strcpy(registro[atuaLin].nome,tmps.nome);
            strcpy(registro[atuaLin].autor,tmps.autor);
            strcpy(registro[atuaLin].editora,tmps.editora);
            strcpy(registro[atuaLin].isbn,tmps.isbn);
            registro[atuaLin].ano = tmps.ano;
            registro[atuaLin].edicao = tmps.edicao;
            registro[atuaLin].caixa = realCaixa;
            registro[atuaLin].catg = tmps.catg;
            memset(&tmps, 0, sizeof(tmps));
            fwrite(&registro[atuaLin], sizeof(CAD), 1, arq);
            fclose(arq);
        }
            else{
                printf("\nErro ao abrir o arquivo para leitura! \a\n");
                exit(1);
            }
        }
    int lerArquivo(CAD registro[cadMax]){
    FILE *arq = fopen("cad_bd.txt", "r");
        if(arq != NULL){
            int i = 0;
            while(1){
                CAD p;
                size_t r = fread(&p, sizeof(CAD), 1,arq);
                if(r < 1)
                    break;
                else
                    registro[i++] = p;
            }
            fclose(arq);
            return i;
        }
        else{
           printf("\nErro ao abrir o arquivo para leitura! \a\n");
            exit(1);
    }
}
    void atualizarCaixa(CAD registro[cadMax]){
    int len_vet = lerArquivo(registro);
        for (j=0;j<caixaMax;j++)vCaixa[j]=0;
        for(i=0; i<caixaMax; i++){
            for(j=0; j<len_vet; j++){
                    if(((registro[j].catg == 'R')||(registro[j].catg == 'L'))&&(registro[j].caixa == i)){
                        vCaixa[i]+=registro[j].quant;
                    }
            }
        }
}
    void listarLivros(CAD registro[cadMax]){
    int len_vet = lerArquivo(registro);
        int j = 0,x,m=-1,p = 0;
        char textos[8][200]= {  "Nome do Livro:",
                                "Nome do Autor:",
                                "Nome da Editora:",
                                "ISBN/ASIN:",
                                "Ano:",
                                "Edição:",
                                "Armazenado na caixa:",
                                "Quantidade:"};
        char info[8][200];
        for (i = 0; i < 8; i++){
            x = strlen(textos[i]);
            if (x > m)
               m = x;
        }
        m = m + 10;
        system("cls");
        printf("\n\n");
        for(i = 0; i < len_vet; i++){
            if(registro[i].catg == 'L'){
                cont = cont + 1;
            }
        }
        if(cont==0){
            printf("%d\n\n",cont);
            printf("Não há livros cadastrados!\n\n");
            getchar();
            system("pause");
        }else{
            for(i = 0; i < len_vet; i++){
                if(registro[i].catg == 'L'){
                    p++;
                    system("cls");
                    printf("\n[LIVROS]");
                    qLinha(4);
                    printf("Item # %d",p);repChar('_', 71);
                    for (j=0; j < 8; j++){
                        switch(j){ /*I chose Switch, even though I know it's not the best way to do it, but just for logic training and fun*/
                        case 0: strcpy(info[j],registro[i].nome);
                                printf("\n%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 1: strcpy(info[j],registro[i].autor);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 2: strcpy(info[j],registro[i].editora);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 3: strcpy(info[j],registro[i].isbn);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 4: sprintf(info[j],"%d",registro[i].ano);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 5: sprintf(info[j],"%d",registro[i].edicao);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 6: sprintf(info[j],"%d",registro[i].caixa+1);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 7: sprintf(info[j],"%d",registro[i].quant);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        }
                    }
                    repChar('_', 79);
                    printf("\n\n");
                    getchar();
                    system("pause");
                }
            }
        }
    }
    void listarRevistas(CAD registro[cadMax]){
    int len_vet = lerArquivo(registro);
        int j = 0,x,m=-1,p = 0;
        char textos[8][200]= {  "Nome da Revista:",
                                "Nome do Autor:",
                                "Nome da Editora:",
                                "ISBN/ASIN:",
                                "Ano:",
                                "Edição:",
                                "Armazenado na caixa:",
                                "Quantidade:"};
        char info[8][200];
        for (i = 0; i < 8; i++){
            x = strlen(textos[i]);
            if (x > m)
               m = x;
        }
        m = m + 10;
        system("cls");
        printf("\n\n");
        for(i = 0; i < len_vet; i++){
            if(registro[i].catg == 'R'){
                cont = cont + 1;
            }
        }
        if(cont==0){
            printf("%d\n\n",cont);
            printf("Não há revistas cadastradas! \n\n");
            getchar();
            system("pause");
        }else{
            for(i = 0; i < len_vet; i++){
                if(registro[i].catg == 'R'){
                    p++;
                    system("cls");
                    printf("\n[REVISTAS]");
                    qLinha(4);
                    printf("Item # %d",p);repChar('_', 71);
                    for (j=0; j < 8; j++){
                        switch(j){ /*again... just for logic training and fun*/
                        case 0: strcpy(info[j],registro[i].nome);
                                printf("\n%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 1: strcpy(info[j],registro[i].autor);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 2: strcpy(info[j],registro[i].editora);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 3: strcpy(info[j],registro[i].isbn);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 4: sprintf(info[j],"%d",registro[i].ano);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 5: sprintf(info[j],"%d",registro[i].edicao);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 6: sprintf(info[j],"%d",registro[i].caixa+1);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        case 7: sprintf(info[j],"%d",registro[i].quant);
                                printf("%-*s %s\n", m, textos[j],info[j]);
                                break;
                        }
                    }
                    repChar('_', 79);
                    printf("\n\n");
                    getchar();
                    system("pause");
                }
            }
        }
    }
    void listarCaixas(CAD registro[cadMax]){
    int len_vet = lerArquivo(registro);
    atualizarCaixa(registro);
        for(i=0;i<caixaMax;i++){
            if(vCaixa[i]>0){
                for(j=0;j<len_vet;j++){
                    if(registro[j].caixa == i){
                        system("cls");
                        printf("\nCAIXA # %d",i+1);
                        repChar('_', 69);
                        if (registro[j].catg == 'R'){
                            printf("\n");
                            printf("\n\tTítulo da [REVISTA]: %s",registro[j].nome);
                        }
                        else{
                            printf("\n");
                            printf("\n\tTítulo do [LIVRO]: %s",registro[j].nome);
                        }
                            printf("\n\tAUTOR: %s",registro[j].autor);
                            printf("\n\tEDITORA: %s",registro[j].editora);
                            printf("\n\tISBN/ASIN:  %s",registro[j].isbn);
                            printf("\n\tANO:  %d",registro[j].ano);
                            printf("\n\tEDIÇÂO: %d\n",registro[j].edicao);
                            printf("\n\tQUANTIDADE: %d\n",registro[j].quant);
                            repChar('_', 78);
                            printf("\n");
                            getchar();
                            printf("\nPressione <enter> para continuar...\n");
                            getchar();
                            getchar();
                    }
                }
            }
            else{
                system("cls");
                printf("\nCaixa #%d não contêm registros <enter> para continuar...\n",i+1);
                getchar();
                getchar();
            }
        }
    }
    void listar(void){
    printf("\nDeseja visualizar a obra registrada? (S) para Sim ou outra tecla para sair: ");
    fflush(stdin);
    sn = toupper(getchar()); /*toupper: only uppercase letters to avoid errors*/
        if(sn=='S'){
            system("cls");
            tipo();
            printf("\n* Editora %s\n* Edição: %d",registro[atuaLin].editora,registro[atuaLin].edicao);
            printf("\n* ISBN/ASIN: %s\n* Ano: %d",registro[atuaLin].isbn,registro[atuaLin].ano);
            printf("\n* Total de %d Exemplares, armazenados na caixa nº: %d\n",registro[atuaLin].quant,realCaixa+1);
            printf("\n");
            repChar('_', 79);
            printf("\n\n");
        }
    }
    void pesquisa(CAD registro[cadMax]){
    char chave[30];
    int p,zero = 0,cx,rCx,j;
        do{
        system("cls");
        qLinha(3);
        printf("\n\t[1] pesquisar por NOME\n\n");
        printf("\n\t[2] pesquisar por CAIXA\n\n");
        printf("\n\t[3] STATUS das caixas\n\n");
        printf("\n\t[0] Voltar para o MENU");
        qLinha(4);
        printf("\nEscolha uma opção: ");
        fflush(stdin);
        scanf("%d", &opt);
        switch(opt){
            case 1:
                j = 0;
                system("cls");
                qLinha(2);
                sn='S';
                while(sn=='S'){
                system("cls");
                qLinha(6);
                printf("Nesta opção você poderá pesquisar por PARTE do NOME da Revista ou Livro.");
                qLinha(5);
                printf("Digite uma palavra-chave (não utilize acentos): ");
                fflush(stdin);
                strupr(gets(chave));
                system("cls");
                printf("\n\tA palavra-chave digitada foi: %s\n\n",chave);
                for(p=0;p<cadMax;p++){
                    if(strstr(registro[p].nome, chave) != NULL) { /*strstr: allows you to search for excerpts of the name*/
                        j++;
                        repChar('_', 79);
                        qLinha(2);
                        registro[p].catg == 'L'?printf("#%d [LIVRO] %s\n",j,registro[p].nome):printf("#%d [REVISTA] %s\n",j,registro[p].nome);
                        printf("\n\tArmanezado(a) na caixa nº %d",registro[p].caixa+1);
                        qLinha(3);
                    }else{
                    zero++;
                    }
                }
                    if(zero == cadMax){
                        system("cls");
                        qLinha(3);
                        printf("\nA palavra-chave < %s > não foi encontrada! <tecle enter>",chave);
                        getchar();
                        qLinha(2);
                    }
                printf("\n\nRealizar uma nova busca?[S] para Sim ou outra tecla para sair: ");
                fflush(stdin);
                sn = toupper(getchar());
            }
            break;
            case 2:
                system("cls");
                qLinha(2);
                sn='S';
                while(sn=='S'){
                    system("cls");
                    qLinha(6);
                    printf("Nesta opção você poderá pesquisar pelo número das caixas disponíveis: 1 a %d\n",caixaMax);
                    qLinha(5);
                    printf("Digite o número da caixa (somente números): ");
                    fflush(stdin);
                    scanf("%d", &cx);
                    rCx = cx-1;
                    while(rCx < 0 || rCx > caixaMax-1){
                    printf("\n\aCaixa inexistente! Selecione uma das caixas disponíveis: 1 a %d, ", caixaMax);
                    printf("\ndigite o número correto da caixa: ");
                    scanf("%d", &cx);
                    rCx = cx-1;
                    }
                    system("cls");
                    printf("\n\tA CAIXA escolhida foi [ %d ]\n\n",cx);
                    j = 0;
                    for(p=0;p<cadMax;p++){
                        if(((registro[p].catg == 'R')||(registro[p].catg == 'L'))&&(registro[p].caixa == rCx)){
                            j++;
                            qLinha(1);
                            registro[p].catg == 'L'?printf("#%d [LIVRO] %s",j,registro[p].nome):printf("#%d [REVISTA] %s",j,registro[p].nome);
                            qLinha(1);
                        }else{
                        zero++;
                        }
                    }
                        if(zero == cadMax){
                            system("cls");
                            qLinha(3);
                            printf("\nA Caixa nº < %d > não contêm registros! <tecle enter>",cx);
                            getchar();
                            qLinha(2);
                        }
                    printf("\n\nRealizar uma nova busca?[S] para Sim ou outra tecla para sair: ");
                    fflush(stdin);
                    sn = toupper(getchar());
                }
                    break;
            case 3:
            	status(registro);
			case 0:
				printf("\nVoltando ao menu");
                break;
            default:
            	printf("\n\aOpção inválida!");
                getchar();
                getchar();
                break;
        }
        }while(opt!=0);
    }
    void status(CAD registro[cadMax]){
    lerArquivo(registro);
	atualizarCaixa(registro);
    system("cls");
	repChar('_', 78);
	printf("\n");
	printf("CAIXA:\n");
        for(i=0;i<caixaMax;i++){
            printf("\n#%d :: ",i+1);
			if(vCaixa[i] == qtMax){
				printf("STATUS >> Caixa cheia!\n");
			}else{
				printf("STATUS >> %d espaço(s).\n",(qtMax - vCaixa[i]));
			}
        }
	printf("\n");
	repChar('_', 78);
	printf("\n<pressione enter>");
	getchar();
	getchar();
    }
	void tipo(void){
        if (registro[atuaLin].catg == 'R'){
            repChar('_', 79);
            printf("\n");
            printf("\n* Título da [REVISTA]: %s\n* Autor: %s",registro[atuaLin].nome,registro[atuaLin].autor);
        }
        else{
            repChar('_', 79);
            printf("\n");
            printf("\n* Título do [LIVRO]: %s\n* Autor: %s",registro[atuaLin].nome,registro[atuaLin].autor);
        }
    }
    void repChar (char caract, int qtde){
    int i;
        for (i=0; i != qtde; i++ ){
            printf("%c", caract);
        }
    }
    void qLinha (int qtde){
    int i;
        for (i=0; i != qtde; i++ ){
            printf("\n");
        }
    }
    void sobre(void){
        int total = 80;
        int i, m, x;
        char sobreInfos[4][200]= {"Anderson Rodrigues de Moraes",
                                  "RA nº 20076413-5",
                                  "Engenharia de Software",
                                  "UNICESUMAR"};
        system("cls");
        printf("\n\n");
        printf("Humildemente, desenvolvido por: ");
        qLinha(6);
        for (i = 0; i < 4; i++){
        x = strlen(sobreInfos[i]);
        m = (total - x)/2;
            printf("%*s\n", m+strlen(sobreInfos[i]), sobreInfos[i]);
            printf("\n");
        }
        printf("\n");
        getchar();
        getchar();
    }
