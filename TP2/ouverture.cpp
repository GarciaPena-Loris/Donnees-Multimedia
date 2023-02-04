// fermeture.cpp :

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut, *ImgTamp;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgTamp, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i = 0; i < nH; i++)
        for (int j = 0; j < nW; j++)
        {
            if (ImgIn[i * nW + j] == 255 || ImgIn[(i - 1) * nW + j] == 255 || ImgIn[(i + 1) * nW + j] == 255 || ImgIn[i * nW + (j - 1)] == 255 || ImgIn[i * nW + (j + 1)] == 255)
            {
                ImgTamp[i * nW + j] = 255;
            }
            else
            {
                ImgTamp[i * nW + j] = 0;
            }
        }

    for (int i = 0; i < nH; i++)
        for (int j = 0; j < nW; j++)
        {
            if (ImgTamp[i * nW + j] == 0 || ImgTamp[(i - 1) * nW + j] == 0 || ImgTamp[(i + 1) * nW + j] == 0 || ImgTamp[i * nW + (j - 1)] == 0 || ImgTamp[i * nW + (j + 1)] == 0)
            {
                ImgOut[i * nW + j] = 0;
            }
            else
            {
                ImgOut[i * nW + j] = 255;
            }
        }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 1;
}
