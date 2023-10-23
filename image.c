#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

struct imagem{
  char tipo[3]; //tipo do cabeçalho da imagem
  int rows;     //dimensões das linhas
  int cols;     //dimensões das colunas
  int max;      //valor máximo do pixel
  int **pixels; //matriz de pixels
};

//função que automatiza a busca das informações para create
Image *getInfo(char *filename){
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
      printf("Erro: não foi possível abrir o arquivo.\n");
      exit(EXIT_FAILURE); //exit_failure é uma macro definida em stdlib.h
  }
  char tipo[3];
  int rows, cols, max, **pixels;
  fscanf(file, "%s", tipo);
  fscanf(file, "%d %d", &rows,&cols);
  fscanf(file, "%d", &max);
  Image *ima = create(rows, cols, tipo);
  fclose(file);
  return ima;  
}
//Função que libera memória
void liberarImagem(Image *imagem){
    for (int i = 0; i < imagem->rows; ++i) {
        free(imagem->pixels[i]);
    }
    free(imagem->pixels);
    free(imagem);
}
//Função que cria e aloca memória para o novo tipo 
Image *create(int rows, int cols, char type[]){
  Image *newImage = (Image*)malloc(sizeof(Image));
    if (newImage == NULL) {
        printf("Erro: falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    newImage->rows = rows;
    newImage->cols = cols;
    newImage->max = 255;          
    strncpy(newImage->tipo, type, sizeof(newImage->tipo)); //função que copia a string e a cola no local indicado
    if (strcmp(type, "P2") == 0) {
        // Aloca memória para matriz de pixels do tipo P2
        newImage->pixels = (int**)malloc(rows * sizeof(int*));
        if (newImage->pixels == NULL) {
            printf("Erro: falha ao alocar memória.\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < rows; i++) {
            newImage->pixels[i] = (int*)malloc(cols * sizeof(int));
            if (newImage->pixels[i] == NULL) {
                printf("Erro: falha ao alocar memória.\n");
                exit(EXIT_FAILURE);
            }
        }
    } 
      // Aloca memória para matriz de pixels do tipo P3
    else if (strcmp(type, "P3") == 0 ) {
        newImage->pixels = (int**)malloc(rows * sizeof(int*));
        if (newImage->pixels == NULL) {
            printf("Erro: falha ao alocar memória.\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < rows; i++) {
            newImage->pixels[i] = (int*)malloc(cols * 3 * sizeof(int));
            if (newImage->pixels[i] == NULL) {
                printf("Erro: falha ao alocar memória.\n");
                exit(EXIT_FAILURE);
            }
        }
    } 
    else {
        printf("Erro: tipo de imagem não suportado.\n");
        exit(EXIT_FAILURE);
    }
    return newImage;
}
//Função que abre o arquivo
Image *load_from_ppm(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro: não foi possível abrir o arquivo aqui %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    char tipo[3];
    int rows, cols, max, **pixels;
    fscanf(file, "%s", tipo);
    if (strcmp(tipo, "P3") != 0){
      printf("Erro: O arquivo %s não é do tipo P3.\n", filename);
      exit(EXIT_FAILURE);
    }
    fscanf(file, "%d %d", &rows,&cols);
    fscanf(file, "%d", &max);
    Image *ima = create(rows, cols, tipo);
    for (int i = 0; i < ima->rows; i++) {
        for (int j = 0; j < ima->cols * 3; j++) {
            fscanf(file, "%d", &ima->pixels[i][j]);
        }
    }
    fclose(file);
    return ima;
  }
//Função que escreve o arquivo
void write_to_ppm(Image *image, const char *filename){
  FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro: não foi possível criar o arquivo %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", image->tipo);
    fprintf(file, "%d %d\n", image->rows, image->cols);
    fprintf(file, "%d\n", image->max);
    if (strcmp(image->tipo, "P2") == 0) {
        for (int i = 0; i < image->rows; i++) {
            for (int j = 0; j < image->cols; j++) {
                fprintf(file, "%d ", image->pixels[i][j]);
            }
            fprintf(file, "\n");
        }
    } 
    else if (strcmp(image->tipo, "P3") == 0) {
        for (int i = 0; i < image->rows; i++) {
            for (int j = 0; j < image->cols * 3; j += 3) {
              fprintf(file, "%d %d %d ", image->pixels[i][j], image->pixels[i][j + 1], image->pixels[i][j + 2]);
            }
            fprintf(file, "\n");
        }
    } else {
        printf("Erro: tipo de imagem não suportado.\n");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}
//Função que converte o arquivo PGM para PPM
void rgb_to_gray(Image *image_rgb, Image *image_gray){
    if (strcmp(image_rgb->tipo, "P3") != 0) {
        printf("Erro: a função rgb_to_gray suporta apenas imagens RGB do tipo P3.\n");
    }
    strcpy(image_gray->tipo, "P2");
    image_gray->rows = image_rgb->rows;
    image_gray->cols = image_rgb->cols;
    image_gray->max = 255;
    for (int i = 0; i < image_rgb->rows; i++) {
        for (int j = 0; j < image_rgb->cols * 3; j += 3) {
          float r = image_rgb->pixels[i][j];
          float g = image_rgb->pixels[i][j + 1];
          float b = image_rgb->pixels[i][j + 2];
          float gray_value = 0.299 * r + 0.587 * g + 0.114 * b; //Usadno float por conta da multiplicação
          image_gray->pixels[i][j / 3] = gray_value; //O valor float é convertido em int automáticamente
        }
    }
}
