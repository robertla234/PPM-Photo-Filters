//Robert La 20873000
//EECS22 Assignment 4
//Image.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Image.h"

/* Allocate the memory space for the image structure */
/* and the memory spaces for the color intensity values. */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height) {
    IMAGE *p;
    p = malloc(sizeof(IMAGE));
    p->W = Width;
    p->H = Height;
    p->R = malloc(sizeof(unsigned char)*Width*Height);
    p->G = malloc(sizeof(unsigned char)*Width*Height);
    p->B = malloc(sizeof(unsigned char)*Width*Height);
    if (p == NULL){
        perror("Image not found");
        return NULL;
    }
    return p;
}

//TEMP *CreateTemp(unsigned int Width, unsigned int Height) {
//    TEMP *s;
//    s = malloc(sizeof(TEMP));
//    s->tempR = malloc(sizeof(unsigned char)*Width*Height);
 //   s->tempG = malloc(sizeof(unsigned char)*Width*Height);
//    s->tempB = malloc(sizeof(unsigned char)*Width*Height);
    //if (s == NULL){
  //      perror("Image not found");
//        return NULL;
 //   }
 //   return s;
//}
//
//void DeleteTemp(TEMP *s) {
//    assert(s);
//    free(s->tempB);
//    free(s->tempG);
//    free(s->tempR);
//    free(s);
//}
//
//unsigned char GetPixelTempR(const TEMP *s, unsigned int x, unsigned int y, unsigned int W){
//    return s -> tempR[x + y * W];
//}
//unsigned char GetPixelTempG(const TEMP *s, unsigned int x, unsigned int y, unsigned int W){
//    return s -> tempG[x + y * W];
//}
//unsigned char GetPixelTempB(const TEMP *s, unsigned int x, unsigned int y, unsigned int W){
//    return s -> tempB[x + y * W];
//}

/* Release the memory spaces for the pixel color intensity values */
/* Deallocate all the memory spaces for the image */
/* Set R/G/B pointers to NULL */
void DeleteImage(IMAGE *image) {
    assert(image);
    free(image->B);
    free(image->G);
    free(image->R);
    free(image);
}

unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y){   
    return image -> R[x + y * (ImageWidth(image))];
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y){
    return image -> G[x + y * (ImageWidth(image))];
   // image -> G [ x + y * (Image - > W)]
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y){
    return image -> B[x + y * (ImageWidth(image))];
}

void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r){
    image -> R[x + y * (ImageWidth(image))] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g){
    image -> G[x + y * (ImageWidth(image))] = g;
    // image -> G [ x + y * (Image - > W)] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b){
    image -> B[x + y * (ImageWidth(image))] = b;
}

unsigned int ImageWidth(const IMAGE *image){
    return image->W;
} 

unsigned int ImageHeight(const IMAGE *image){
   return image->H;
}

//EOF Image.c
