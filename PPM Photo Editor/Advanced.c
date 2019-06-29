#include "Advanced.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

/* Adjust the brightness of an image */
IMAGE *Brightness(IMAGE *image, int brightness) {
    int RBright = 0, GBright = 0, BBright = 0;
    for (int i = 0; i < ImageWidth(image); i++){
        for (int j = 0; j < ImageHeight(image); j++){
            RBright = GetPixelR(image, i, j) + brightness;
            if (RBright > 255){
                SetPixelR(image, i, j, 255);
            }
            else if(RBright < 0){
                SetPixelR(image, i, j, 0);
            }
            else{
                SetPixelR(image, i, j, RBright);
            }

            GBright = GetPixelG(image, i, j) + brightness;
            if (GBright > 255){
                SetPixelG(image, i, j, 255);
            }
            else if(GBright < 0){
                SetPixelG(image, i, j, 0);
            }
            else{
                SetPixelG(image, i, j, GBright);
            }

            BBright = GetPixelB(image, i, j) + brightness;
            if (BBright > 255){
                SetPixelB(image, i, j, 255);
            }
            else if(BBright < 0){
                SetPixelB(image, i, j, 0);
            }
            else{
                SetPixelB(image, i, j, BBright);
            }
        }
    }
    return image;
}

/* Mirror an image horizontally */
IMAGE *HMirror(IMAGE *image) {

    int x, y;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image) / 2; x++) {
            SetPixelR(image, ImageWidth(image) - 1 - x, y, GetPixelR(image, x, y));
            SetPixelG(image, ImageWidth(image) - 1 - x, y, GetPixelG(image, x, y));
            SetPixelB(image, ImageWidth(image) - 1 - x, y, GetPixelB(image, x, y));
        }
    }
    return image;
}

void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3])
{
    /* Memory for result */
    float result[3] = {0, 0, 0};

    /* Perform multiplication */
    result[0] = matrix[0][0]*vector[0] + matrix[0][1]*vector[1] + matrix[0][2]*vector[2];
    result[1] = matrix[1][0]*vector[0] + matrix[1][1]*vector[1] + matrix[1][2]*vector[2];
    result[2] = matrix[2][0]*vector[0] + matrix[2][1]*vector[1] + matrix[2][2]*vector[2];

    /* Copy result into other stack's memory */
    vector[0] = result[0];
    vector[1] = result[1];
    vector[2] = result[2];
}

IMAGE *HueRotate(IMAGE *image, float angle)
{
    /* Matrix to transform normalized
    // RGB color vector from the RGB
    // color space to the YIQ color space */
    static const float RGBtoYIQMatrix[3][3] = {{0.299,  0.587,  0.114},
                                                {0.596, -0.274, -0.321},
                                                {0.211, -0.523,  0.311}};

    /* Matrix to transform normalized
    // YIQ color vector from the YIQ
    // color space to the RGB color space */
    static const float YIQtoRGBMatrix[3][3] = {{1.000,  0.956,  0.621},
                                                {1.000, -0.272, -0.647},
                                                {1.000, -1.107,  1.705}};

    const float cs = cos(angle), ss = sin(angle);

    /* Matrix to perform a hue
    // rotation on a normalized
    // YIQ color vector*/
    const float XYPlaneVectorRotateMatrix[3][3] = {{1.000, 0.000, 0.000},
                                                     {0.000, cs, -ss},
                                                     {0.000, ss, cs}};

    /* Image variables */
    float temp[3];

    for(unsigned int i = 0; i < ImageWidth(image); i++){
        for(unsigned int j = 0; j < ImageHeight(image); j++){
            /* Create a normalized RGB color
            // vector fro the current pixel
            // in the image */
            temp[0] = (float)GetPixelR(image, i, j)/255;
            temp[1] = (float)GetPixelG(image, i, j)/255;
            temp[2] = (float)GetPixelB(image, i, j)/255;

            /* Transform the RGB vector
            // to a YIQ vector */
            matrix_3_3multiplyVector_3(temp, RGBtoYIQMatrix);

            /* Perform the DIP */
            matrix_3_3multiplyVector_3(temp, XYPlaneVectorRotateMatrix);

            /* Transform back to RGB */
            matrix_3_3multiplyVector_3(temp, YIQtoRGBMatrix);

            /* Denormalize and store back into the image */
            temp[0] = temp[0] * 255;
            temp[0] = temp[0] < 0 ? 0 : temp[0];
            temp[0] = temp[0] > 255 ? 255 : temp[0];
            temp[1] = temp[1] * 255;
            temp[1] = temp[1] < 0 ? 0 : temp[1];
            temp[1] = temp[1] > 255 ? 255 : temp[1];
            temp[2] = temp[2] * 255;
            temp[2] = temp[2] < 0 ? 0 : temp[2];
            temp[2] = temp[2] > 255 ? 255 : temp[2];

            SetPixelR(image, i, j, (unsigned char)temp[0]);
            SetPixelG(image, i, j, (unsigned char)temp[1]);
            SetPixelB(image, i, j, (unsigned char)temp[2]);
        }
    }
    return image;
}


IMAGE *Rotate(IMAGE *image, int option) {
    int x, y, a, b;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);

    IMAGE *temp = NULL;

    if (option == 1) { /* Horizontal Flip*/
        temp = CreateImage(WIDTH, HEIGHT);
        for (y = 0; y < ImageHeight(image); y++) { 
        for (x = 0; x < ImageWidth(image); x++) {
            SetPixelR(temp, WIDTH-1-x, y, GetPixelR(image, x, y));
            SetPixelG(temp, WIDTH-1-x, y, GetPixelG(image, x, y));
            SetPixelB(temp, WIDTH-1-x, y, GetPixelB(image, x, y));
        }
        }
    }
    if (option == 2) { /*Vertical Flip*/
        temp = CreateImage(WIDTH, HEIGHT);
        for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            SetPixelR(temp, x, WIDTH-1-y, GetPixelR(image, x, y));
            SetPixelG(temp, x, WIDTH-1-y, GetPixelG(image, x, y));
            SetPixelB(temp, x, WIDTH-1-y, GetPixelB(image, x, y));
        }
        }

    }
    if (option == 3) { /*Rotate Right*/
        temp = CreateImage(HEIGHT, WIDTH);
        for (y = 0, b = HEIGHT-1; y < HEIGHT; y++, b--) {
        for (x = 0, a = 0; x < WIDTH; x++, a++) {
            SetPixelR(temp, y, x, GetPixelR(image, a, b));
            SetPixelG(temp, y, x, GetPixelG(image, a, b));
            SetPixelB(temp, y, x, GetPixelB(image, a, b));
        }
        }

    }
    if (option == 4) { /*Rotate Left*/
        temp = CreateImage(HEIGHT, WIDTH);
        for (y = 0, b = 0; y < HEIGHT; y++, b++) {
        for (x = 0, a = WIDTH-1; x < WIDTH; x++, a--) {
            SetPixelR(temp, y, x, GetPixelR(image, a, b));
            SetPixelG(temp, y, x, GetPixelG(image, a, b));
            SetPixelB(temp, y, x, GetPixelB(image, a, b));
        }
        }

    }
    return temp;
}

IMAGE *Resize(IMAGE *image, int percentage) { 
    float Widthnew, Widthold, Heightnew, Heightold, p;
    int c, COUNT, X, Y, x, y, w, h, r, g, b, xp, yp;
    Widthold = ImageWidth(image);
    Heightold = ImageHeight(image);

    Widthnew = Widthold * (percentage / 100.00);
    Heightnew = Heightold * (percentage / 100.00);
    IMAGE *temp = NULL;
    temp = CreateImage(Widthnew, Heightnew);
    /* larger resize */
    if (percentage > 100) {
        for (X = 0; X < Widthold; X++) {
            for (Y = 0; Y < Heightold; Y++) {
                x = X * (percentage / 100.00);
                y = Y * (percentage / 100.00);
                r = GetPixelR(image, X, Y);
                g = GetPixelG(image, X, Y);
                b = GetPixelB(image, X, Y);
                SetPixelR(temp, x, y, r);
                SetPixelG(temp, x, y, g);
                SetPixelB(temp, x, y, b);


                w = Widthnew / 2;
                h = Heightnew / 2;
                COUNT = (percentage / 100)^2;
                for (c = 0; c <= COUNT; c++) {
                if (x <= w) {
                    if (y <= h) {
                    SetPixelR(temp, x+c, y, r);
                    SetPixelG(temp, x+c, y, g);
                    SetPixelB(temp, x+c, y, b);
                    SetPixelR(temp, x, y+c, r);
                    SetPixelG(temp, x, y+c, g);
                    SetPixelB(temp, x, y+c, b);
                    SetPixelR(temp, x+c, y+c, r);
                    SetPixelG(temp, x+c, y+c, g);
                    SetPixelB(temp, x+c, y+c, b);
                    }
                    if (y > h) {
                    SetPixelR(temp, x+c, y, r);
                    SetPixelG(temp, x+c, y, g);
                    SetPixelB(temp, x+c, y, b);
                    SetPixelR(temp, x, y-c, r);
                    SetPixelG(temp, x, y-c, g);
                    SetPixelB(temp, x, y-c, b);
                    SetPixelR(temp, x+c, y-c, r);
                    SetPixelG(temp, x+c, y-c, g);
                    SetPixelB(temp, x+c, y-c, b);
                    } 
                }
                if (x > w) {
                    if (y <= h) {
                    SetPixelR(temp, x-c, y, r);
                    SetPixelG(temp, x-c, y, g);
                    SetPixelB(temp, x-c, y, b);
                    SetPixelR(temp, x, y+c, r);
                    SetPixelG(temp, x, y+c, g);
                    SetPixelB(temp, x, y+c, b);
                    SetPixelR(temp, x-c, y+c, r);
                    SetPixelG(temp, x-c, y+c, g);
                    SetPixelB(temp, x-c, y+c, b);
                    }
                    if (y > h) {
                    SetPixelR(temp, x-c, y, r);
                    SetPixelG(temp, x-c, y, g);
                    SetPixelB(temp, x-c, y, b);
                    SetPixelR(temp, x, y-c, r);
                    SetPixelG(temp, x, y-c, g);
                    SetPixelB(temp, x, y-c, b);
                    SetPixelR(temp, x-c, y-c, r);
                    SetPixelG(temp, x-c, y-c, g);
                    SetPixelB(temp, x-c, y-c, b);
                    }
                }
                }
       /*Y*/}
   /*X*/}
        
    }
    /* smaller resize */
    if (percentage < 100) {
        p = 100.00 / percentage;
        for (x = 0; x < Widthnew; x++) {
            for (y = 0; y < Heightnew; y++) {
                xp = x*p;
                yp = y*p;
                
                if (y == 0 && x != 0 && x != Widthnew - 1) {
                    r = (GetPixelR(image, xp, yp) + GetPixelR(image, xp-1, yp) + GetPixelR(image, xp+1, yp) + GetPixelR(image, xp, yp+1) + GetPixelR(image, xp-1, yp+1) + GetPixelR(image, xp+1, yp+1))/6; 
                    g = (GetPixelG(image, xp, yp) + GetPixelG(image, xp-1, yp) + GetPixelG(image, xp+1, yp) + GetPixelG(image, xp, yp+1) + GetPixelG(image, xp-1, yp+1) + GetPixelG(image, xp+1, yp+1))/6; 
                    b = (GetPixelB(image, xp, yp) + GetPixelB(image, xp-1, yp) + GetPixelB(image, xp+1, yp) + GetPixelB(image, xp, yp+1) + GetPixelB(image, xp-1, yp+1) + GetPixelB(image, xp+1, yp+1))/6; 
                }
                else if (y == Heightnew - 1 && x != 0 && x != Widthnew - 1) {
                    r = (GetPixelR(image, xp, yp) + GetPixelR(image, xp-1, yp) + GetPixelR(image, xp+1, yp) + GetPixelR(image, xp, yp-1) + GetPixelR(image, xp-1, yp-1) + GetPixelR(image, xp+1, yp-1))/6;   
                    g = (GetPixelG(image, xp, yp) + GetPixelG(image, xp-1, yp) + GetPixelG(image, xp+1, yp) + GetPixelG(image, xp, yp-1) + GetPixelG(image, xp-1, yp-1) + GetPixelG(image, xp+1, yp-1))/6;
                    b = (GetPixelB(image, xp, yp) + GetPixelB(image, xp-1, yp) + GetPixelB(image, xp+1, yp) + GetPixelB(image, xp, yp-1) + GetPixelB(image, xp-1, yp-1) + GetPixelB(image, xp+1, yp-1))/6;
                }
                else if (x == 0 && y != 0 && y != Heightnew - 1) {
                    r = (GetPixelR(image, xp, yp-1) + GetPixelR(image, xp, yp) + GetPixelR(image, xp, yp+1) + GetPixelR(image, xp+1, yp-1) + GetPixelR(image, xp+1, yp) + GetPixelR(image, xp+1, yp+1))/6;   
                    g = (GetPixelG(image, xp, yp-1) + GetPixelG(image, xp, yp) + GetPixelG(image, xp, yp+1) + GetPixelG(image, xp+1, yp-1) + GetPixelG(image, xp+1, yp) + GetPixelG(image, xp+1, yp+1))/6;
                    b = (GetPixelB(image, xp, yp-1) + GetPixelB(image, xp, yp) + GetPixelB(image, xp, yp+1) + GetPixelB(image, xp+1, yp-1) + GetPixelB(image, xp+1, yp) + GetPixelB(image, xp+1, yp+1))/6;
                }
                else if (x == Widthnew - 1 && y != 0 && y != Heightnew - 1) {
                    r = (GetPixelR(image, xp, yp-1) + GetPixelR(image, xp, yp) + GetPixelR(image, xp, yp+1) + GetPixelR(image, xp-1, yp-1) + GetPixelR(image, xp-1, yp) + GetPixelR(image, xp-1, yp+1))/6;   
                    g = (GetPixelG(image, xp, yp-1) + GetPixelG(image, xp, yp) + GetPixelG(image, xp, yp+1) + GetPixelG(image, xp-1, yp-1) + GetPixelG(image, xp-1, yp) + GetPixelG(image, xp-1, yp+1))/6;
                    b = (GetPixelB(image, xp, yp-1) + GetPixelB(image, xp, yp) + GetPixelB(image, xp, yp+1) + GetPixelB(image, xp-1, yp-1) + GetPixelB(image, xp-1, yp) + GetPixelB(image, xp-1, yp+1))/6;
                }
                else if (x == 0 || y == 0 || x == Widthnew - 1 || y == Heightnew - 1){
                    r = GetPixelR(image, xp, yp);
                    g = GetPixelG(image, xp, yp);
                    b = GetPixelB(image, xp, yp);
                }
                else { 
                    r = (GetPixelR(image, xp, yp-1) + GetPixelR(image, xp, yp) + GetPixelR(image, xp, yp+1) + GetPixelR(image, xp+1, yp-1) + GetPixelR(image, xp+1, yp) + GetPixelR(image, xp+1, yp+1) + GetPixelR(image, xp-1, yp-1) + GetPixelR(image, xp-1, yp) + GetPixelR(image, xp-1, yp+1))/9;
                    g = (GetPixelG(image, xp, yp-1) + GetPixelG(image, xp, yp) + GetPixelG(image, xp, yp+1) + GetPixelG(image, xp+1, yp-1) + GetPixelG(image, xp+1, yp) + GetPixelG(image, xp+1, yp+1) + GetPixelG(image, xp-1, yp-1) + GetPixelG(image, xp-1, yp) + GetPixelG(image, xp-1, yp+1))/9;
                    b = (GetPixelB(image, xp, yp-1) + GetPixelB(image, xp, yp) + GetPixelB(image, xp, yp+1) + GetPixelB(image, xp+1, yp-1) + GetPixelB(image, xp+1, yp) + GetPixelB(image, xp+1, yp+1) + GetPixelB(image, xp-1, yp-1) + GetPixelB(image, xp-1, yp) + GetPixelB(image, xp-1, yp+1))/9;                      
                }
                SetPixelR(temp, x, y, r);
                SetPixelG(temp, x, y, g);
                SetPixelB(temp, x, y, b);
                 
            }
        }
        
        
    }

    return temp;
}

IMAGE *Saturate(IMAGE *image, float percent) {
    int R, G, B, W, H;
    float Rt, Gt, Bt;
    for (W = 0; W < ImageWidth(image); W++) {
        for (H = 0; H < ImageHeight(image); H++) {
            R = GetPixelR(image, W, H);
            G = GetPixelG(image, W, H);
            B = GetPixelB(image, W, H);
            /* Given Saturate Calculations */
            Rt = (R + G + B) / 3;
            Gt = Rt;
            Bt = Rt;

            Rt = R - Rt;
            Gt = G - Gt;
            Bt = B - Bt;

            R = R + (Rt * percent / 100);
            G = G + (Gt * percent / 100);
            B = B + (Bt * percent / 100);

            if (R < 0) {
                R = 0;
            }
            if (G < 0) {
                G = 0;
            }
            if (B < 0) {
                B = 0;
            }
            if (R > 255) {
                R = 0;
            }
            if (G > 255) {
                G = 255;
            }
            if (B > 255) {
                B = 255;
            }

            SetPixelR(image, W, H, R);
            SetPixelG(image, W, H, G);
            SetPixelB(image, W, H, B);
        }
    }
    return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
