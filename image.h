#ifndef IMAGE_H
#define IMAGE_H

typedef struct imagem Image;

//função que busca as informações da imagem
Image *getInfo(char *filename);

//função que libera imagem
void liberarImagem(Image *imagem);

//Aloca memória para a estrutura nas proporções dadas no arquivo de entrada
Image *create(int rows, int cols, char type[]);

//Carrega a imagem a ser convertida
Image *load_from_ppm(const char *filename);

//cria/altera uma arquivo do qual será escrito o arquivo convertido
void write_to_ppm(Image *image, const char *filename);

//função que converte uma foto colorida em lvl de cinza
void rgb_to_gray(Image *image_rgb, Image *image_gray);
#endif
