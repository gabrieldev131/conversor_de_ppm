#ifndef IMAGE_H
#define IMAGE_H

typedef struct imagem{
  char tipo[3]; 
  int rows;     
  int cols;     
  int max;
  int **pixels;
}Image;

Image *getInfo(char *filename);
void liberarImagem(Image *imagem);
Image *create(int rows, int cols, char type[]);
Image *load_from_ppm(const char *filename);
void write_to_ppm(Image *image, const char *filename);
void rgb_to_gray(Image *image_rgb, Image *image_gray);
#endif
