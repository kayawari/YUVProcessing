//
//  main.cpp
//  noise_copy
//
//  Created by 感性情報学研究室 on 2014/12/06.
//  Copyright (c) 2014年 感性情報学研究室. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define HEIGHT 256
#define WIDTH 256
#define TWICE_HEIGHT 512
#define TWICE_WIDTH 512

int main(int argc, const char * argv[]) {
    FILE *input_fp, *output_fp;
    
    int n = WIDTH*HEIGHT;//Y file size
    int n_2 = TWICE_HEIGHT*TWICE_WIDTH;//output Y file size
    
    int n_half = HEIGHT*(WIDTH/2); //U,V file size
    int n_half_2 = TWICE_HEIGHT*(TWICE_WIDTH/2);//output U,Vfile size
    int width_half = WIDTH/2;//U,V width
    
    unsigned char yin[HEIGHT][WIDTH];
    unsigned char uin[HEIGHT][WIDTH/2];
    unsigned char vin[HEIGHT][WIDTH/2];
    unsigned char yout[HEIGHT][WIDTH];
    unsigned char uout[HEIGHT][(WIDTH/2)];
    unsigned char vout[HEIGHT][(WIDTH/2)];
    
    char *fnameIn   = "/Users/KanseiInfo/Desktop/noise_copy/Lenna256_256_422.yuv";
    char *fnameOut1 = "/Users/KanseiInfo/Desktop/noise_copy/noise_output.yuv";
    
    if((input_fp = fopen(fnameIn, "rb")) == NULL){
        printf("%s open error!\n", fnameIn);
        exit(EXIT_FAILURE);
    }else{
        printf("%s open.\n", fnameIn);
    }
    
    fread(yin, sizeof(unsigned char),n,input_fp);
    fread(uin, sizeof(unsigned char),n_half,input_fp);
    fread(vin, sizeof(unsigned char),n_half,input_fp);
    
    fclose(input_fp);
    
    for (int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            yout[i][j] = yin[i][j] + rand()%(10-(-10)+1)-10;
            uout[i][j] = uin[i][j];
            vout[i][j] = vin[i][j];
        }
    }

    if((output_fp = fopen(fnameOut1, "wb")) == NULL){ //ÉGÉâÅ[èàóù
        printf("%s open error!\n", fnameOut1);
        exit(EXIT_FAILURE);
    }else{
        printf("%s open.\n", fnameOut1);
    }
    
    fwrite(yout,sizeof(unsigned char),n_2,output_fp);
    fwrite(uout,sizeof(unsigned char),n_half_2,output_fp);
    fwrite(vout,sizeof(unsigned char),n_half_2,output_fp);
    
    fclose(output_fp);
    
    return 0;
}

