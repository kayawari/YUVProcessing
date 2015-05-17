//
//  main.cpp
//  edge_video
//
//  Created by 感性情報学研究室 on 2014/12/03.
//  Copyright (c) 2014年 感性情報学研究室. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define HEIGHT 480
#define WIDTH 720

int main(int argc, const char * argv[]) {
    FILE *input_fp, *output_fp;
    
    int n = WIDTH*HEIGHT;//File size of 'Y'
    int n_half = HEIGHT*(WIDTH/2); //File size of 'U,V'
    int width_half = WIDTH/2;//Width of 'U,V'. y's width is twice of u,v's width.
    
    unsigned char yin[HEIGHT][WIDTH];
    unsigned char uin[HEIGHT][WIDTH/2];
    unsigned char vin[HEIGHT][WIDTH/2];
    
    unsigned char yout[HEIGHT][WIDTH];
    unsigned char uout[HEIGHT][WIDTH/2];
    unsigned char vout[HEIGHT][WIDTH/2];
    
    int max_frame = 1200;
    int frame = 300;
    
    char *fnameIn   = "/Users/KanseiInfo/Desktop/edge_video/02SDH720V480.yuv";
    char *fnameOut1 = "/Users/KanseiInfo/Desktop/edge_video/output_02SDH720V480.yuv";
    
    if((input_fp = fopen(fnameIn, "rb")) == NULL){
        printf("%s open error!\n", fnameIn);
        exit(EXIT_FAILURE);
    }else{
        printf("%s open.\n", fnameIn);
    }
    
    if((output_fp = fopen(fnameOut1, "wb")) == NULL){
        printf("%s open error!\n", fnameOut1);
        exit(EXIT_FAILURE);
    }else{
        printf("%s open.\n", fnameOut1);
    }
    
    //freadするときは、yuvの1フレーム分しか入っていない。
    for(int i=0; i<max_frame; i++){
        fread(yin, sizeof(unsigned char),n,input_fp);
        fread(uin, sizeof(unsigned char),n_half,input_fp);
        fread(vin, sizeof(unsigned char),n_half,input_fp);
        if(i >= frame){
            for (int i=0; i<HEIGHT; i++){
                for(int j=0; j<WIDTH; j++){
                    yout[i][j] = yin[i][j];
                    uout[i][j] = uin[i][j];
                    vout[i][j] = vin[i][j];
                }
            }
        fwrite(yout,sizeof(unsigned char),n,output_fp);
        fwrite(uout,sizeof(unsigned char),n_half,output_fp);
        fwrite(vout,sizeof(unsigned char),n_half,output_fp);
        }
    }
    
    fclose(input_fp);
    fclose(output_fp);
    
    return 0;
}


