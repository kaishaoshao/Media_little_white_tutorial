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
    FILE *fp_y = fopen("../../output/basic/data/output_420_y.yuv","wb+");
    FILE *fp_u = fopen("../../output/basic/data/output_420_u.yuv","wb+");
    FILE *fp_v = fopen("../../output/basic/data/output_420_v.yuv","wb+");

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



//  分离YUV444P像素数据中的Y、U、V分量
//////////////////////////////////////////
// split Y,U,V planes in YUV420P file
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
    FILE *fp_y = fopen("output_444_y.yuv","wb+");
    FILE *fp_u = fopen("output_444_u.yuv","wb+");
    FILE *fp_v = fopen("output_444_v.yuv","wb+");

     int frames_y = width * height;
    // size for yuv424
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



//  将YUV420P像素数据去掉颜色（变成灰度图）
//  将YUV420P像素数据的亮度减半
//  将YUV420P像素数据的周围加上边框
//  生成YUV420P格式的灰阶测试图
//  计算两个YUV420P像素数据的PSNR
//  分离RGB24像素数据中的R、G、B分量
//  将RGB24格式像素数据封装为BMP图像
//  将RGB24格式像素数据转换为YUV420P格式像素数据
//  生成RGB24格式的彩条测试图




int main()
{
    Split_yuv420("./home/shaokai/Desktop/work/vscode/Media_little_white_tutorial/res/basic/lena_256x256_yuv420p.yuv",256,256,1);
    // Split_yuv444("./lena_256x256_yuv420p.yuv",256,256,1);
    return 0;
}