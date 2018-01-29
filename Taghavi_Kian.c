#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//                                       START MAIN
int main() {
    //                                     PART 1
      struct header {
        char chunkID[4];// RIFF
        unsigned int chunksize;
        char format[4];//WAVE
        char subchunk1ID[4];//fmt
        unsigned int subchunk1size;
        unsigned short int audioformat;
        unsigned short int numchannels;
        unsigned int samplerate;
        unsigned int byterate;
        unsigned short int blockalign;
        unsigned short int bitspersample;
        char subchunk2ID[4];// data
        unsigned int subchunk2size;
    }headerout,*ptr;//                            PART 2

    ptr = &headerout;

//                                           PART 3
    headerout.chunkID[0] = 'R';
    headerout.chunkID[1] = 'I';
    headerout.chunkID[2] = 'F';
    headerout.chunkID[3] = 'F';
    headerout.format[0] = 'W';
    headerout.format[1] = 'A';
    headerout.format[2] = 'V';
    headerout.format[3] = 'E';
    headerout.subchunk1ID[0] = 'f';
    headerout.subchunk1ID[1] = 'm';
    headerout.subchunk1ID[2] = 't';
    headerout.subchunk1ID[3] = ' ';
    headerout.subchunk1size = 16;
    headerout.subchunk2ID[0] = 'd';
    headerout.subchunk2ID[1] = 'a';
    headerout.subchunk2ID[2] = 't';
    headerout.subchunk2ID[3] = 'a';
    headerout.audioformat = 1;
    headerout.samplerate = 44100;
    headerout.numchannels = 1;
    headerout.bitspersample = 16;
    headerout.byterate = (headerout.samplerate)*(headerout.numchannels) * ((headerout.bitspersample)/8);
    headerout.blockalign = (headerout.numchannels)*((headerout.bitspersample)/8);


//                                        PART 4

    short int **data = (short int**)malloc(25*sizeof(short int*));;
    int i=0,j=0,row=0,columnbytes = 0;
    long freq = 0.0;
    unsigned short int song[48]={3,3,10,10,12,12,10,24,8,8,7,7,5,5,3,0,10,10,8,8,7,7,5,0,10,10,8,8,7,7,5,0,3,3,10,10,12,12,10,24,8,8,7,7,5,5,3,0};
    FILE *write;
    write = fopen("song.wav","wb");

    if (write == NULL){
        printf("File was not opened successfully");
        return 0;}

    for(i=0;i<25;i++){// declaring how many columns of data to make available.
        data[i] = (short int*)malloc(14700*sizeof(short int));
    }

    for(i=0;i<25;i++){
    for(j=0;j<14700;j++){
        if (i == 0)
            freq = 440.0;
        else if (i == 1)
            freq = 466.16;
        else if (i == 2)
            freq = 493.88;
        else if (i == 3)
            freq = 523.25;
        else if (i == 4)
            freq = 554.37;
        else if (i == 5)
            freq = 587.33;
        else if (i == 6)
            freq = 622.25;
        else if (i == 7)
            freq = 659.25;
        else if (i == 8)
            freq = 698.46;
        else if (i == 9)
            freq = 739.99;
        else if (i == 10)
            freq = 783.99;
        else if (i == 11)
            freq = 830.61;
        else if (i == 12)
            freq = 880.0;
        else if (i == 13)
            freq = 932.33;
        else if (i == 14)
            freq = 987.77;
        else if (i == 15)
            freq = 1046.50;
        else if (i == 16)
            freq = 1109.73;
        else if (i == 17)
            freq = 1174.66;
        else if (i == 18)
            freq = 1244.51;
        else if (i == 19)
            freq = 1318.51;
        else if (i == 20)
            freq = 1396.91;
        else if (i == 21)
            freq = 1479.98;
        else if (i == 22)
            freq = 1567.98;
        else if (i == 23)
            freq = 1661.22;
        else if (i == 24)
            freq = 0.0;

        data[i][j] = (short int)(32700*sin(2.0*M_PI*j*freq/44100));
    }}


    fwrite(&headerout,sizeof(headerout),1,write);





    fseek(write,44,SEEK_SET);
    for(i=0;i<48;i++){
        row = song[i];
        columnbytes += (int)fwrite(data[row],sizeof(short int),14700,write);
    }

    headerout.subchunk2size = (int)(columnbytes)*(headerout.numchannels)*((headerout.bitspersample)/8);
     fseek(write,40,SEEK_SET);
    fwrite(&headerout.subchunk2size,sizeof(int),1,write);

    headerout.chunksize = 36 + (headerout.subchunk2size);
     fseek(write,4,SEEK_SET);
    fwrite(&headerout.chunksize,sizeof(int),1,write);


    fclose(write);
    free(data);



    return 0;
}
