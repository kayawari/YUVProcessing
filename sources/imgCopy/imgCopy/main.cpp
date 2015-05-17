//
//  main.cpp
//  imgCopy
//
//  Created by 隆之 on 2014/11/23.
//  Copyright (c) 2014年 隆之. All rights reserved.
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
    
    int n = WIDTH*HEIGHT;//Yのファイルサイズ
    int n_2 = TWICE_HEIGHT*TWICE_WIDTH;//出力のYのファイルサイズ（fwiret時に使用）
    /*
     int n_half = n/2;
     int n_half_2 = n_2/2;
     */
    int n_half = HEIGHT*(WIDTH/2); //U,Vのファイルサイズ
    int n_half_2 = TWICE_HEIGHT*(TWICE_WIDTH/2);//出力のU,Vのファイルサイズ（fwiret関数に使用）
    int width_half = WIDTH/2;//U,Vの横幅。U,VはYよりも、横幅が半分だから。
    
    unsigned char yin[HEIGHT][WIDTH];
    unsigned char uin[HEIGHT][WIDTH/2];
    unsigned char vin[HEIGHT][WIDTH/2];
    //unsigned char yout[HEIGHT][WIDTH];
    //unsigned char uout[HEIGHT][(WIDTH/2)];
    //unsigned char vout[HEIGHT][(WIDTH/2)];
    unsigned char yout[HEIGHT*2][WIDTH*2];
    unsigned char uout[HEIGHT*2][(WIDTH/2)*2];
    unsigned char vout[HEIGHT*2][(WIDTH/2)*2];
    
    char *fnameIn   = "/Users/KanseiInfo/Desktop/imgCopy/Lenna256_256_422.yuv";//入力ファイル名の宣言
    char *fnameOut1 = "/Users/KanseiInfo/Desktop/imgCopy/twice_output.yuv"; //出力ファイル名の宣言
    //unix(mac)環境のxcodeで行ったため、フルパス記述。

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
    
    /*普通のコピー*/
    /*for (int i=0; i<HEIGHT; i++){
     for(int j=0; j<WIDTH; j++){
     yout[i][j] = yin[i][j];
     uout[i][j] = uin[i][j];
     vout[i][j] = vin[i][j];
     }
     }*/
    
    
    /*縦横２倍*/
    //Y
    for (int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            //Yのみ。下半分が上手く入らない。
            //原因　出力の書き込みのデータサイズが半分になっていた。->define TWICE_HEIGHTなど追加
            yout[i*2][j*2] = yin[i][j];
            yout[i*2][(j*2)+1] = (yin[i][j]+yin[i][j+1])/2;
            yout[(i*2)+1][j*2] = (yin[i][j]+yin[i+1][j])/2;
            yout[(i*2)+1][(j*2)+1] = (yout[i*2][(j*2)+1] + yout[(i*2)+1][j*2])/2;
            
        }
    }
    
    //U
    for (int i=0; i<HEIGHT; i++){
        for(int j=0; j<width_half; j++){
            uout[i*2][j*2] = uin[i][j];
            uout[i*2][(j*2)+1] = (uin[i][j]+uin[i][j+1])/2;
            uout[(i*2)+1][j*2] = (uin[i][j]+uin[i+1][j])/2;
            uout[(i*2)+1][(j*2)+1] = (uout[i*2][(j*2)+1] + uout[(i*2)+1][j*2])/2;
            
        }
    }
    
    //V
    for (int i=0; i<HEIGHT; i++){
        for(int j=0; j<width_half; j++){
            vout[i*2][j*2] = vin[i][j];
            vout[i*2][(j*2)+1] = (vin[i][j]+vin[i][j+1])/2;
            vout[(i*2)+1][j*2] = (vin[i][j]+vin[i+1][j])/2;
            vout[(i*2)+1][(j*2)+1] = (vout[i*2][(j*2)+1] + vout[(i*2)+1][j*2])/2;
            
        }
    }
    
    // 出力ファイルオープンの判定
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
    
    /*授業のスライドにあったプログラム
     fp = fopen("outputfile.yuv","rb");
     for(int i=0; i < HEIGHT; i++){
     for (int j=0; j < WIDTH; j++){
     
     }
     }
     
     fclose(fp);
     
     unsigned char (*Y)[256] = new unsigned char[256][256];
     unsigned char (*U)[128] = new unsigned char[256][128];
     unsigned char (*V)[128] = new unsigned char[256][128];
     
     fp = fopen("Lenna256_256_422.yuv","rb");
     fread(Y,sizeof(unsigned char),256*256,fp);
     fread(U,sizeof(unsigned char),256*128,fp);
     fread(V,sizeof(unsigned char),256*128,fp);
     fclose(fp);
     
     fp = fopen("outputfile.yuv","wb");
     fwrite(Y,sizeof(unsigned char),256*256,fp);
     fwrite(U,sizeof(unsigned char),256*128,fp);
     fwrite(V,sizeof(unsigned char),256*128,fp);
     fclose(fp);
     
     delete[] Y;
     delete[] U;
     delete[] V;
     //普通のコピーを行うプログラム？？
     */
    
    return 0;
}
