#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

int main() {
  char escolha;
  char refNome_entrada[100];
  char refNome_saida[100];
  char *nomePPMentrada = refNome_entrada;
  char *nomePPMsaida = refNome_saida;
  Image *ima;

  while (escolha != 's') {
    printf("\n -----------------------------------------------\n");
    printf("\t\t\t\t conversor de PPM");
    printf("\n -----------------------------------------------\n");
    printf("\n Escolha uma opção: \n");
    printf("(a) Converter uma imagem tipo P3 em P2\n");
    printf("(s) Sair\n");
    scanf(" %c", &escolha);

    switch (escolha) {
      case 's': 
          break;

      case 'a':
          printf(" \nConverter uma imagem PPM em PGM\n");
          printf("deseja usar o caminho padrão? (s/n)\n");
          scanf(" %c", &escolha);
          if (escolha == 's') {
            ima = getInfo("vale.ppm");
            nomePPMentrada = "vale.ppm";
          } else if (escolha == 'n') {
            printf("\nQual o nome do arquivo PPM a ser convertido?\n");
            scanf("%s", refNome_entrada);
            ima = getInfo(refNome_entrada);
          } else {
            printf("Opção inválida. Tente novamente.\n");
            break;
          }
          Image *new = create(ima->rows, ima->cols, "P2");
          Image *old = create(ima->rows, ima->cols, ima->tipo);
          old = load_from_ppm(nomePPMentrada);
          rgb_to_gray(old, new);
          printf("deseja nomear o arquivo? (s/n)\n");
          scanf(" %c", &escolha);
          if (escolha == 's') {
            printf("Como nomeará o arquivo?\n");
            scanf("%s", refNome_saida);
            write_to_ppm(new, refNome_saida);
          } 
          else if (escolha == 'n') {
            printf("como o nome ficou indefinido, o arquivo ficou salvo como arquivo.ppm\n");
            write_to_ppm(new, "arquivo.ppm");
          } 
          else {
            printf("erro, tente novamente\n");
          }         
          liberarImagem(new);
          liberarImagem(old);
          liberarImagem(ima);
          printf("\nImagem foi gerada com sucesso!\n");
          escolha = 'n';
          break;

      default:
          printf("Opção inválida. Tente novamente.\n");
          break;
    }
  }
  printf("programa encerrado\n");
  return 0;
}
