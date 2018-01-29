#include <stdio.h>
#include <stdlib.h>


int main(){

    int i=0,j=4,columns=393,rows=257,size=(columns*3)+1;
    float sf;
    FILE *image1open,*image2open,*image3open;

    //                                  STEP 1
    struct Bitmapfileheader {
        unsigned char bfh[14];
    };

    struct Bitmapinfoheader {
         unsigned char bih[40];
    };

    //                                  STEP 2
    typedef struct Bitmapheader {
        struct Bitmapfileheader file;
        struct Bitmapinfoheader info;
    }bh;

    //                                  STEP 3
    bh bmph1, bmph2, bmph3;

    //                                  STEP 4
    image1open = fopen("image1_393x257.bmp","rb");
    image2open = fopen("image2_393x257.bmp","rb");

    //                                  STEP 5
    if (image1open == NULL || image2open == NULL){
        printf("\n Error opening images.\n");
    return 0;}

    //                                  STEP 6
    fread(bmph1.file.bfh,1,14,image1open);
    fread(bmph1.info.bih,1,40,image1open);

    fread(bmph2.file.bfh,1,14,image2open);
    fread(bmph2.info.bih,1,40,image2open);


    //                                   STEP 7
    for (i=0;i<14;i++){
        printf("\n bmph1.file.bfh[%d] = %d\n bmph2.file.bfh[%d] = %d",i,bmph1.file.bfh[i],i,bmph2.file.bfh[i]);
        bmph3.file.bfh[i] = bmph1.file.bfh[i];
    }
    for (i=0;i<40;i++){
        printf("\n bmph1.info.bih[%d] = %d\n bmph2.info.bih[%d] = %d",i,bmph1.info.bih[i],i,bmph2.info.bih[i]);
        bmph3.info.bih[i] = bmph1.info.bih[i];
    }

    printf("\nsizeof(bmph1) = %lu\nsizeof(bmph1) = %lu",sizeof(bmph1),sizeof(bmph2));

    //                                   STEP 8
    // width is 4-7 (bytes 5-8), height is 8-11 (bytes 9-12)

    for(j=4;j<12;j++){

        if (bmph1.info.bih[i] != bmph2.info.bih[i]){
        printf("\nHorizontal and/or vertical dimensions do not match.\n");
            return 0;}// end if statement
    }

    //                                    STEP 9
    printf("\nInput a floating point scale factor sf where 0.0 < sf < 1.0. \n");
    scanf("%f",&sf);

    //                                   STEP 10

    image3open = fopen("image3_393x257.bmp","wb");
    fwrite(&bmph3,sizeof(bh),1,image3open);


    unsigned char *i1 = (unsigned char*)malloc(size);
    unsigned char *i2 = (unsigned char*)malloc(size);
    unsigned char *i3 = (unsigned char*)malloc(size);

    fseek(image1open,44,SEEK_SET);
    fseek(image2open,44,SEEK_SET);
    fseek(image3open,44,SEEK_SET);

    for(i=0;i<rows;i++){
    fread(i1,sizeof(unsigned char),size,image1open);
    fread(i2,sizeof(unsigned char),size,image2open);

        for(j=0;j<size;j++){
            i3[j]=(unsigned char)(((float)i1[j])*sf+((float)i2[j]*(1.0-sf)));
        }

        fwrite(i3,sizeof(char),size,image3open);
    }


    return EXIT_SUCCESS;

}
