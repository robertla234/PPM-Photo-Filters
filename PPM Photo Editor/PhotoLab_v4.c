/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/* Modified: Mihnea Chirila for F18, 10/30/18                                                          */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"

#ifdef DEBUG
#include "Test.h"
#endif

/*** function declarations ***/

/* print a menu */
void PrintMenu();

#ifdef DEBUG
#else
/* Test all functions */
void AutoTest(void);
#endif

int main()
{
    int rc ;
    IMAGE *image = malloc(sizeof(image));
#ifdef DEBUG
    AutoTest();
    rc = 0;
#else

    int option;			/* user input option */
    char fname[SLEN];		/* input file name */
    int brightness = -256;
    float angle;
    int rotate;
    int percentage = 501;
    float percent;

    rc = 1 ;
    PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);

    while (option != EXIT) {
    if (option == 1) {
        printf("Please input the file name to load: ");
        scanf("%s", fname);
        image = LoadImage(fname);
        rc = 0;
    }

    /* menu item 2 - 8 requires image is loaded first */
    else if (option >= 2 && option <= 11) {
        if (rc != SUCCESS){
            printf("No image is read.\n");
        }
        /* now image is loaded */
        else {
            switch (option) {
                case 2:
                    printf("Please input the file name to save: ");
                    scanf("%s", fname);
                    SaveImage(fname, image);
                    break;
                case 3:
                    image = BlackNWhite(image);
                    printf("\"Black & White\" operation is done!\n");
                    break;
                case 4:
                    image = Edge(image);
                    printf("\"Edge\" operation is done!\n");
                    break;
                case 5:
                    image = Shuffle(image);
                    printf("\"Shuffle\" operation is done!\n");
                    break;
                case 6:
                    while(brightness > 255 || brightness < -255){
                        printf("Enter brightness value (between -255 and 255):");
                        scanf("%d", &brightness);
                    }
                    image = Brightness(image, brightness);
                    printf("\"brightness\" operation is done!\n");
                    break;
                case 7:
                    image = HMirror(image);
                    printf("\"Horizontally Mirror\" operation is done!\n");
                    break;
                case 8:
                    printf("Enter hue rotation angle:");
                    scanf("%f", &angle);
                    image = HueRotate(image, angle);
                    printf("\"HueRotate\" operation is done!\n");
                    break;
                case 9:
                    printf("Enter for rotation:\n"
                    "(1) - Horizontal Flip\n"
                    "(2) - Vertical Flip\n"
                    "(3) - Rotate Right\n"
                    "(4) - Rotate Left\n\n  ");
                    scanf("%d", &rotate);
                    image = Rotate(image, rotate);
                    printf("\"Rotate\" operation is done!\n");
                    break;
                case 10:
                    while(percentage < 1 || percentage > 500){
                        printf("Enter the resize percentage (between 1 - 500):");
                        scanf("%d", &percentage);
                    }
                    image = Resize(image, percentage);
                    printf("\"Resize\" operation is done!\n");
                    break;
                case 11:
                    printf("Enter the saturation percentage:");
                    scanf("%f", &percent);
                    image = Saturate(image, percent);
                    printf("\"Saturate\" operation is done!\n");
                    break;
                default:
                    break;

            }
        }
    }

    else if (option == 12) {
        AutoTest();
        rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
    }
    else if (option == 13) {
        printf("Goodbye!\n");
        break;
    }
    else {
        printf("Invalid selection!\n");
    }

    /* Process finished, waiting for another input */
    PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);
    }
    if (image != NULL) {
        DeleteImage(image);
    }
    image = NULL;
    printf("You exit the program.\n");
#endif

    return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Sketch the edge of an image\n");
    printf(" 5: Shuffle an image\n");
    printf(" 6: Adjust the brightness of an image\n");
    printf(" 7: Mirror an image horizontally\n");
    printf(" 8: Adjust the hue of an image\n");
    printf(" 9: Rotate or flip the image\n");
    printf(" 10: Resize the image\n");
    printf(" 11: Saturate the image\n");
    printf(" 12: Test all functions\n");
    printf(" 13: Exit\n");
}


/* auto test*/
#ifdef DEBUG
#else
void AutoTest(void) {
    char fname[SLEN] = "HSSOE";
    int brightness = 200;
    float angle = -1.5;
    int rotate = 3;
    
    IMAGE *image= NULL;

    image = LoadImage(fname);
    image = BlackNWhite(image);
    SaveImage("bw", image);
    printf("Black & White tested!\n\n");
    DeleteImage(image);
    image = NULL;
                    
    image = LoadImage(fname);
    image = Edge(image);
    SaveImage("edge", image);
    printf("Edge Detection tested!\n\n");
    DeleteImage(image);
    image = NULL;
    
    image = LoadImage(fname);
    image = Shuffle(image);
    SaveImage("shuffle", image);
    printf("Shuffle tested!\n\n");
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    image = Brightness(image, brightness);
    SaveImage("brightness", image);
    printf("Brightness tested!\n\n");
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    image = HMirror(image);
    SaveImage("hmirror", image);
    printf("HMirror tested!\n\n");
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    image = HueRotate (image, angle);
    SaveImage("hue", image);
    printf("HueRotate tested!\n\n");
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    image = Rotate(image, rotate);
    SaveImage("rotate", image);
    printf("Rotate tested!\n\n");
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    image = Resize(image, 60);
    SaveImage("smallresize", image);
    DeleteImage(image);
    image = NULL;
    image = LoadImage(fname);
    image = Resize(image, 170);
    SaveImage("bigresize", image);
    printf("Resize tested!\n\n");
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    image = Saturate(image, 90);
    SaveImage("saturate", image);
    printf("Saturate tested!\n\n");
    DeleteImage(image);
    image = NULL;

// continue
}
#endif
/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
