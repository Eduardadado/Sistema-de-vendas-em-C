#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cliente {
  char nome[50];
  int idade;
  char sexo;
};

typedef struct cliente cli;

struct compra {
  cli cliente;
  int numItens;
  float valorTotalCompra;
};

typedef struct compra compra;

float Calcmed(float somaValores, float contMedia);

int main(void) {
  // var
  compra compras;
  int cadastrou = 0, menu = 0, i = 0, qtdLetrasNome = 0, confirmaMedia = 0, contqtd1 = 0,
      contM = 0, qtdLinha = 0, qtditens = 0, menorIdade = 1000, tamNome = 0;
  float somaValores = 0, contMedia = 0, valComparacao = 0,
                      valorTm = 0, mediaC = 0, mediaT = 0, valorTgeral = 0;
  compra *arrey_compras, InfoMaiorNome, infoMenorIdade;
  char procuraNome[200], linha[200], continua, maiorNome[50];

  FILE *arq = fopen("registros.txt", "a");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo");
    exit(1);
  }

  // ini
  while (menu != 4) {
    printf("*********** SISTEMA DE COMPRAS **************\n");
    printf("*");
    printf("\n* 1- Cadastrar novas compras.\n*\n* 2- Ver informações de uma compra específica, baseado no nome do cliente.\n*\n* 3- Ver informações de todas as compras.\n*\n* 4- Encerrar o programa.\n*\n* Escolha uma das seguintes opções:");
    
    scanf("%d", &menu);
     printf("\n*");

    switch (menu) {
    case 1:

      cadastrou++;

      printf("Qual a quantidade de compras que deseja cadastrar?: ");
      scanf("%d", &qtdLinha);

      arrey_compras = (compra *)malloc(qtdLinha * sizeof(compra));

      if (arrey_compras == NULL) {
        printf("Erro de alocação de memória");
        exit(1);
      }

      for (i = 0; i < qtdLinha; i++) {
        printf("Digite o nome do cliente: ");
        getchar();
        scanf("%[^\n]", compras.cliente.nome);
        qtdLetrasNome = strlen(compras.cliente.nome);

        while (qtdLetrasNome < 3) {
          printf("Erro ao cadastrar compra!\nNome muito curto.\n\n");
          getchar();
          printf("Digite o nome do cliente: ");
          scanf("%[^\n]", compras.cliente.nome);
          qtdLetrasNome = strlen(compras.cliente.nome);
        }

        printf("Digite a idade do cliente: ");
        scanf("%d", &compras.cliente.idade);

        while(compras.cliente.idade <= 0){ 
          printf("Erro ao cadastrar compra!\nIdade inválida.\n\n");
        printf("Digite a idade do cliente: ");
        scanf("%d", &compras.cliente.idade);
        }
        printf("Digite o sexo do cliente: ");
        getchar();
        scanf(" %c", &compras.cliente.sexo);
        compras.cliente.sexo = toupper(compras.cliente.sexo);
        while (compras.cliente.sexo != 'M' && compras.cliente.sexo != 'F') {
          printf("Erro ao cadastrar compra!\nSexo invalido.\n\n");
          printf("Digite o sexo do cliente: ");
          getchar();
          scanf(" %c", &compras.cliente.sexo);
          compras.cliente.sexo = toupper(compras.cliente.sexo);
        }
        printf("Digite a quantidade de itens da compra: ");
        scanf("%d", &compras.numItens);
        while (compras.numItens <= 0) {
          printf("Valor de itens tem que ser maior que 0\n");
          printf("Digite a quantidade de itens da compra: ");
          getchar();
          scanf("%d", &compras.numItens);
        }
        printf("Qual o valor total da compra?: ");
        scanf("%f", &compras.valorTotalCompra);
        while (compras.valorTotalCompra <= 0) {
          printf("Valor e número de itens tem que ser maior que 0\n");
          printf("Digite a quantidade de itens da compra: ");
          getchar();
          scanf("%f", &compras.valorTotalCompra);
        }

        arq = fopen("registros.txt", "a");
        if (arq == NULL) {
          printf("Erro ao abrir o arquivo");
          exit(1);
        }

        fprintf(arq, "%s %d %c %d %.2f\n", compras.cliente.nome,
                compras.cliente.idade, compras.cliente.sexo, compras.numItens,
                compras.valorTotalCompra);

        printf("Compra cadastrada com sucesso!\n\n");

        fclose(arq);
      }

      free(arrey_compras);

      break;

    case 2:
      do {
        confirmaMedia = 0;
        printf("Digite o nome do cliente que procura: ");
        getchar();
        scanf("%s", procuraNome);

        arq = fopen("registros.txt", "r");
        if (arq == NULL) {
          printf("Erro ao abrir o arquivo");
          exit(1);
        }

        while (fscanf(arq, "%s %d %c %d %f", compras.cliente.nome,
                      &compras.cliente.idade, &compras.cliente.sexo,
                      &compras.numItens, &compras.valorTotalCompra) != EOF) {
          if (strcmp(compras.cliente.nome, procuraNome) == 0) {
            printf("\n\nQuantidade de produtos: %d\nValor total da compra: %.2f\n\n", compras.numItens, compras.valorTotalCompra);
            somaValores += compras.valorTotalCompra;
            contMedia++;
            confirmaMedia = 1;
          }
        }

        if (confirmaMedia == 1) {

          float medpc = 0;

          medpc = Calcmed(somaValores, contMedia);

          contMedia = 0;
          somaValores = 0;

          printf("A média dos valores das compras de %s é: %.2f\n\n", procuraNome, medpc);
        } else {
          printf("Cliente não encontrado!\n\n");
        }

        printf("Deseja continuar procurando? (S/N) ");
        scanf(" %c", &continua);

        fclose(arq);

      } while (toupper(continua) == 'S');
      break;
    case 3:

      // primeiro
      printf("Digite o valor que deseja comparar: ");
      scanf("%f", &valComparacao);

      arq = fopen("registros.txt", "r");
      if (arq == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
      }

      while (fscanf(arq, "%s %d %c %d %f", compras.cliente.nome,
                    &compras.cliente.idade, &compras.cliente.sexo,
                    &compras.numItens, &compras.valorTotalCompra) != EOF) {
        if (compras.valorTotalCompra > valComparacao) {
          printf("Cliente: %s\nValor total: %.2f\n\n", compras.cliente.nome,
                 compras.valorTotalCompra);
        }

        // segundo
        if (compras.numItens == 1) {
          contqtd1++;
        }
        // terceiro
        if (compras.cliente.sexo == 'M') {
          contM++;
        }
        // quarto
        if (compras.cliente.sexo == 'F') {
          valorTm += compras.valorTotalCompra;
        }
        // quinto
        qtditens += compras.numItens;
        // sexto
        qtdLinha++;
        // setimo
        valorTgeral += compras.valorTotalCompra;
        // oitavo
        mediaT = valorTgeral / qtdLinha;
        // nono
        if (tamNome < strlen(compras.cliente.nome)) {
          tamNome = strlen(compras.cliente.nome);
          InfoMaiorNome = compras;
        }
        // décimo
        if (menorIdade > compras.cliente.idade) {
          menorIdade = compras.cliente.idade;
          infoMenorIdade = compras;
        }
      }
      printf("A quantidade de compras com apenas 1 produto é: %d\n\n",
             contqtd1);

      printf("A quantidade de compradores homens é: %d\n\n", contM);

      printf("O valor total comprado pelas mulheres é: %.2f\n\n", valorTm);

      printf("Quantidade de itens vendidos: %d\n\n", qtditens);

      if(cadastrou > 0){
        printf("Quantidade de compras realizadas: %d\n\n", qtdLinha-1);
      } else {
      printf("Quantidade de compras realizadas: %d\n\n", qtdLinha);
      }

      printf("Valor total das compras realizadas: %.2f\n\n", valorTgeral);

      printf("Informações do cliente de maior nome\nNome: %s\nIdade: %d\nSexo: "
             "%c\nQuantidade de itens: %d\nValor total da compra: %.2f\n\n",
             InfoMaiorNome.cliente.nome, InfoMaiorNome.cliente.idade,
             InfoMaiorNome.cliente.sexo, InfoMaiorNome.numItens,
             InfoMaiorNome.valorTotalCompra);

      printf(
          "Informações do cliente de menor idade\nNome: %s\nIdade: %d\nSexo: "
          "%c\nQuantidade de itens: %d\nValor total da compra: %.2f\n\n",
          infoMenorIdade.cliente.nome, infoMenorIdade.cliente.idade,
          infoMenorIdade.cliente.sexo, infoMenorIdade.numItens,
          infoMenorIdade.valorTotalCompra);

      fclose(arq);
      break;
    case 4:

      printf("Finalizado!");

      break;

    default:
      printf("Escolha entre 1 e 4\n\n");
    }
  }

  return 0;
}

float Calcmed(float somaValores, float contMedia) {
  float mediaValores = 0;

  mediaValores = somaValores / contMedia;

  return mediaValores;
}