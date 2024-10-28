#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//===----------------------------------------------------------------------===//
/// @brief Separate the left and right channels of the PCM16LE two-channel sampled data
//
/// @param url The path to the input PCM audio file. 
/// @return 0/-1
//===----------------------------------------------------------------------===//
int Split_pcm16le(const char *url){
    FILE *fp = fopen(url,"rb+");
    FILE *fp_left = fopen("../../output/basic/audio/output_left.pcm","wb+");
    FILE *fp_right = fopen("../../output/basic/audio/output_right.pcm","wb+");
     
    unsigned char *sample = (unsigned char *)malloc(4);
    if(sample == NULL){
        fclose(fp);
        fclose(fp_left);
        fclose(fp_right);
        return -1;
    }
    
    while(!feof(fp)){
        fread(sample,1,4,fp);
        // left
        fwrite(sample,1,2,fp_left);
        // right
        fwrite(sample+2,1,2,fp_right);
    } 
    
    free(sample);
    fclose(fp);
    fclose(fp_left);
    fclose(fp_right);
    
    return 0;    
}


int main(int argc,char **argv)
{
    // 分离PCM16LE双声道采样数据的左声道和右声道
    Split_pcm16le("../../res/basic/audio/NocturneNo2inEflat_44.1k_s16le.pcm");
    // 将PCM16LE双声道音频采样数据中左声道的音量降一半

    // 将PCM16LE双声道音频采样数据的声音速度提高一倍

    // 将PCM16LE单声道音频采样数据转换为PCM8音频采样数据

    // 从PCM16LE单声道音频采样数据中截取一部分数据

    // 将PCM16LE双声道音频采样数据转换为WAVE格式音频数据


    return 0;
}

