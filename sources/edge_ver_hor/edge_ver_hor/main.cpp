//
//  main.cpp
//  edge_ver_hor
//
//  Created by 隆之 on 2014/11/24.
//  Copyright (c) 2014年 隆之. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define HEIGHT 256
#define WIDTH 256

int main(int argc, const char * argv[]) {
    FILE *input_fp, *output_fp;
    
    int n = WIDTH*HEIGHT;//File size of 'Y'
    int n_half = HEIGHT*(WIDTH/2); //File size of 'U,V'
    int width_half = WIDTH/2;//Width of 'U,V'. y's width is twice of u,v's width.
    double k = 0.7;//edge volume??
    
    unsigned char yin[HEIGHT][WIDTH];
    unsigned char uin[HEIGHT][WIDTH/2];
    unsigned char vin[HEIGHT][WIDTH/2];
    
    unsigned char yout[HEIGHT][WIDTH];
    unsigned char uout[HEIGHT][WIDTH/2];
    unsigned char vout[HEIGHT][WIDTH/2];
    
    unsigned char yEdge[HEIGHT][WIDTH];
    unsigned char uEdge[HEIGHT][WIDTH/2];
    unsigned char vEdge[HEIGHT][WIDTH/2];
    
    double temp;
    
    char *fnameIn   = "/Users/KanseiInfo/Desktop/edge_ver_hor/Lenna256_256_422.yuv";
    char *fnameOut = "/Users/KanseiInfo/Desktop/edge_ver_hor/edge_output_horizon.yuv";
    
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
    
    //Y
    for (int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            //0.5 will be normalization constant
            yEdge[i][j] = (0.5 * yin[i-1][j]) - yin[i][j] + (0.5 * yin[i+1][j]);
            temp = double(yin[i][j]) + double(k * yEdge[i][j]);
            if(temp > 255) temp = 255;
            if(temp < 0) temp = 0;
            yout[i][j] = (unsigned char)(temp);
        }
    }
    
    //U
    for (int i=0; i<HEIGHT; i++){
        for(int j=0; j<width_half; j++){
            uEdge[i][j] = (0.5 * uin[i-1][j]) - uin[i][j] + (0.5 * uin[i+1][j]);
            temp = double(uin[i][j]) + double(k * uEdge[i][j]);
            if(temp > 255) temp = 255;
            if(temp < 0) temp = 0;
            uout[i][j] = (unsigned char)(temp);
        }
    }
    
    //V
    for (int i=0; i<HEIGHT; i++){
        for(int j=0; j<width_half; j++){
            vEdge[i][j] = (0.5 * vin[i-1][j]) - vin[i][j] + (0.5 * vin[i+1][j]);
            temp = double(vin[i][j]) + double(k * vEdge[i][j]);
            if(temp > 255) temp = 255;
            if(temp < 0) temp = 0;
            vout[i][j] = (unsigned char)(temp);
        }
    }
    
    if((output_fp = fopen(fnameOut, "wb")) == NULL){
        printf("%s open error!\n", fnameOut);
        exit(EXIT_FAILURE);
    }else{
        printf("%s open.\n", fnameOut);
    }
    fwrite(yout,sizeof(unsigned char),n,output_fp);
    fwrite(uout,sizeof(unsigned char),n_half,output_fp);
    fwrite(vout,sizeof(unsigned char),n_half,output_fp);
    fclose(output_fp);
    
    return 0;
}

