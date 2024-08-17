#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//  分离YUV420P像素数据中的Y、U、V分量
//////////////////////////////////////////
// split Y,U,V planes in YUV420P file
// @param url Location of Input YUV file
// @param width Width of Input YUV file
// @param height Height of Input YUV file
// @param num Number of frames to process
//////////////////////////////////////////
int Split_yuv420(const char *url,int width,int height,int num)
{
    printf("%s\n", url); 
    FILE *fp = fopen(url,"rb+");
    if(fp == NULL)
    {
       perror("Error opening file");
       return -1;  
    }
    FILE *fp_y = fopen("../../output/basic/pic/output_420_y.y","wb+");
    FILE *fp_u = fopen("../../output/basic/pic/output_420_u.y","wb+");
    FILE *fp_v = fopen("../../output/basic/pic/output_420_v.y","wb+");
    
     int frames_y = width * height;
    // size for yuv420
    int size = frames_y * 3 / 2;
    
    unsigned char *pic = (unsigned char*)malloc(size);
    if (pic == NULL) {
        perror("Memory allocation failed");  
        fclose(fp);
        fclose(fp_y);
        fclose(fp_u);
        fclose(fp_v);
        return -1;
    }

    // [------Y------|---U---|---V---]
    // If the video frame width and height are w and h, respectively,
    // then a frame of YUV420P pixels takes up w*h*3/2 Byte of data.
    // The first w*h Byte stores Y, the next w*h*1/4 Byte stores U,
    // and the last w*h*1/4 Byte stores V.
    // output_420_y.y：256x256。
    // output_420_u.y：128x128。
    // output_420_v.y：128x128。

    for(int i = 0;i < num;i++)
    {
        fread(pic,1,size,fp);
        // Y
        fwrite(pic,1,frames_y,fp_y);
        // U
        fwrite(pic+frames_y,1,frames_y/4,fp_u);
        // V
        fwrite(pic+frames_y*5/4,1,frames_y/4,fp_v);
    }

    free(pic);
    fclose(fp);
    fclose(fp_y);
    fclose(fp_u);
    fclose(fp_v);

    return 0;
}



//////////////////////////////////////////
// split Y,U,V planes in YUV444P file
// @param url Location of Input YUV file
// @param width Width of Input YUV file
// @param height Height of Input YUV file
// @param num Number of frames to process
//////////////////////////////////////////
int Split_yuv444(const char *url,int width,int height,int num)
{
    
    FILE *fp = fopen(url,"rb+");
    if(fp == NULL)
    {
       perror("Error opening file");
       return -1;  
    }
    FILE *fp_y = fopen("../../output/basic/pic/output_444_y.y","wb+");
    FILE *fp_u = fopen("../../output/basic/pic/output_444_u.y","wb+");
    FILE *fp_v = fopen("../../output/basic/pic/output_444_v.y","wb+");

     int frames_y = width * height;
    // size for yuv444
    int size = frames_y * 3;
    
    unsigned char *pic = (unsigned char*)malloc(size);
    if (pic == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        fclose(fp_y);
        fclose(fp_u);
        fclose(fp_v);
        return -1;
    }

    // [------Y------|------U------|------V------]
    // If the video frame width and height are w and h, respectively,
    // then a frame of YUV444P pixels takes up w*h Byte of data.
    // The first w*h Byte stores Y, the next w*h Byte stores U,
    // and the last w*h*1/4 Byte stores V.
    // output_420_y.y：256x256。
    // output_420_u.y：256x256。
    // output_420_v.y：256x256。

    for(int i = 0;i < num;i++)
    {
        fread(pic,1,size,fp);
        // Y
        fwrite(pic,1,frames_y,fp_y);
        // U
        fwrite(pic+frames_y,1,frames_y,fp_u);
        // V
        fwrite(pic+frames_y*2,1,frames_y,fp_v);
    }

    free(pic);
    fclose(fp);
    fclose(fp_y);
    fclose(fp_u);
    fclose(fp_v);

    return 0;
}


//////////////////////////////////////////
// Convert YUV420P file to gray picture
// @param url Location of Input YUV file
// @param width Width of Input YUV file
// @param height Height of Input YUV file
// @param num Number of frames to process
//////////////////////////////////////////
int Convert_yuv420_gray(const char *url,int width,int height,int num)
{ 
    FILE *fp = fopen(url,"rb+");
    FILE *fp_g = fopen("../../output/basic/pic/output_gray.yuv","wb+");
    if(fp == NULL || fp_g == NULL)
    {
       perror("Error opening file");
       return -1;  
    }
    int frames_y = width * height;
    // size for yuv420
    int size = frames_y * 3 / 2;
    
    unsigned char *pic = (unsigned char*)malloc(size);
    if (pic == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        fclose(fp_g);
        return -1;
    }

    // To turn YUV format pixel data into grayscale images, 
    // you only need to set U and V components to 128.
    // Because U and V are the biased chromaticity components in the image.
    // The chromaticity component ranges from -128 to 127 before bias processing, 
    // when colorless corresponds to a "0" value. After bias, 
    // the color component value becomes 0 to 255, and the colorless corresponding is 128
    for(int i = 0;i < num;i++)
    {
        fread(pic,1,size,fp);
        memset(pic + frames_y,128,frames_y/2);
        fwrite(pic,1,size,fp_g);
    }

    free(pic);
    fclose(fp);
    fclose(fp_g);

    return 0;
}


//  将YUV420P像素数据的亮度减半
//  将YUV420P像素数据的周围加上边框
//  生成YUV420P格式的灰阶测试图
//  计算两个YUV420P像素数据的PSNR
//  分离RGB24像素数据中的R、G、B分量
//  将RGB24格式像素数据封装为BMP图像
//  将RGB24格式像素数据转换为YUV420P格式像素数据
//  生成RGB24格式的彩条测试图


int main(int argc,char* argv[])
{
    // Split_yuv420("../../res/basic/pic/lena_256x256_yuv420p.yuv",256,256,1);
    // Split_yuv444("../../res/basic/pic/lena_256x256_yuv444p.yuv",256,256,1);
    // Convert_yuv420_gray("../../res/basic/pic/lena_256x256_yuv420p.yuv",256,256,1);
    return 0;
}  