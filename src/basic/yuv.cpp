#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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

//////////////////////////////////////////
// Halve Y value of YUV420P file
// @param url Location of Input YUV file
// @param width Width of Input YUV file
// @param height Height of Input YUV file
// @param num Number of frames to process
//////////////////////////////////////////
int Halfy_yuv420(const char *url, int width, int height,int num){
	FILE *fp=fopen(url,"rb+");
	FILE *fp_h=fopen("../../output/basic/pic/output_half.yuv","wb+");
    if(fp == NULL || fp_h == NULL)
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
        fclose(fp_h);
        return -1;
    }
    // If you want to halve the brightness of the image, 
    // just take out the Y value of each pixel of the image 
    // and divide it by 2. Each Y value of the image occupies 
    // 1 Byte and ranges from 0 to 255, corresponding to the 
    // unsigned char data type in the C language
	for(int i=0;i < num;i++){
		fread(pic,1,size,fp);
		for(int j=0;j < frames_y;j++){
			unsigned char temp=pic[j]/2;
			pic[j]=temp;
		}
		fwrite(pic,1,size,fp_h);
	}

	free(pic);
	fclose(fp);
	fclose(fp_h);
 
	return 0;
}


//////////////////////////////////////////
// Add border for YUV420P file
// @param url Location of Input YUV file
// @param width Width of Input YUV file
// @param height Height of Input YUV file
// @param num Number of frames to process
//////////////////////////////////////////
int Border_yuv420(const char *url, int width, int height,int border,int num){
	FILE *fp=fopen(url,"rb+");
	FILE *fp_b=fopen("../../output/basic/pic/output_border.yuv","wb+");
 
	int frames_y = width * height;
    // size for yuv420
    int size = frames_y * 3 / 2;
    unsigned char *pic = (unsigned char*)malloc(size);
    
    // The value of Y is set to the maximum value 
    // of 255 for pixels within the border of the image
	for(int i = 0;i < num;i++){
		fread(pic,1,size,fp);
		//Y
		for(int j = 0;j < height;j++){
			for(int k = 0;k < width;k++){
				if(k < border || k > (width-border)|| j < border|| j > (height-border))
                {
					pic[j*width+k]=255;
				}
			}
		}
		fwrite(pic,1,size,fp_b);
	}
 
	free(pic);
	fclose(fp);
	fclose(fp_b);
 
	return 0;
}


///////////////////////////////////////////////
// Generate YUV420P gray scale bar.
// @param width    Width of Output YUV file.
// @param height   Height of Output YUV file.
// @param ymin     Max value of Y
// @param ymax     Min value of Y
// @param barnum   Number of bars
// @param url_out  Location of Output YUV file.
///////////////////////////////////////////////
int Graybar_yuv420(int width, int height,int ymin,int ymax,int barnum,const char *url_out){
	int barwidth;               // 每条灰度条宽度
	float lum_inc;              // 亮度
	unsigned char lum_temp;
	int uv_width,uv_height;     // uv的宽高
	FILE *fp=NULL;
	unsigned char *data_y=NULL;
	unsigned char *data_u=NULL;
	unsigned char *data_v=NULL;

 
	barwidth = width / barnum;      
	lum_inc=((float)(ymax-ymin))/((float)(barnum-1));
	uv_width=width/2;
	uv_height=height/2;
 
	data_y=(unsigned char *)malloc(width*height);
	data_u=(unsigned char *)malloc(uv_width*uv_height);
	data_v=(unsigned char *)malloc(uv_width*uv_height);
 
	if((fp=fopen(url_out,"wb +"))==NULL){
 		return -1;
	}
 
	//Output Info
	printf("Y, U, V value from picture's left to right:\n");
	for(int t=0;t<(width/barwidth);t++){
		lum_temp=ymin+(char)(t*lum_inc);
		printf("%3d, 128, 128\n",lum_temp);
	}

	//Gen Data
    // Y
	for(int j=0;j<height;j++){
		for(int i=0;i<width;i++){
			int t=i/barwidth;
			lum_temp=ymin+(char)(t*lum_inc);
			data_y[j*width+i]=lum_temp;
		}
	}
    // U
	for(int j=0;j<uv_height;j++){
		for(int i=0;i<uv_width;i++){
			data_u[j*uv_width+i]=128;
		}
	}
    // V
	for(int j=0;j<uv_height;j++){
		for(int i=0;i<uv_width;i++){
			data_v[j*uv_width+i]=128;
		}
	}
	fwrite(data_y,width*height,1,fp);
	fwrite(data_u,uv_width*uv_height,1,fp);
	fwrite(data_v,uv_width*uv_height,1,fp);
	fclose(fp);
	free(data_y);
	free(data_u);
	free(data_v);
	return 0;
}

///////////////////////////////////////////////////////
// Calculate PSNR between 2 YUV420P file
// @param url1     Location of first Input YUV file.
// @param url2     Location of another Input YUV file.
// @param w        Width of Input YUV file.
// @param h        Height of Input YUV file.
// @param num      Number of frames to process.
///////////////////////////////////////////////////////
int Psnr_yuv420(char *url1,char *url2,int w,int h,int num){
	FILE *fp1=fopen(url1,"rb+");
	FILE *fp2=fopen(url2,"rb+");
	unsigned char *pic1=(unsigned char *)malloc(w*h);
	unsigned char *pic2=(unsigned char *)malloc(w*h);
 
	for(int i=0;i<num;i++){
		fread(pic1,1,w*h,fp1);
		fread(pic2,1,w*h,fp2);
 
		double mse_sum=0,mse=0,psnr=0;
		for(int j=0;j<w*h;j++){
			mse_sum+=pow((double)(pic1[j]-pic2[j]),2);
		}
		mse=mse_sum/(w*h);
		psnr=10*log10(255.0*255.0/mse);
		printf("%5.3f\n",psnr);
 
		fseek(fp1,w*h/2,SEEK_CUR);
		fseek(fp2,w*h/2,SEEK_CUR);
 
	}
 
	free(pic1);
	free(pic2);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
//  分离RGB24像素数据中的R、G、B分量
//  将RGB24格式像素数据封装为BMP图像
//  将RGB24格式像素数据转换为YUV420P格式像素数据
//  生成RGB24格式的彩条测试图


int main(int argc,char* argv[])
{
    // Split_yuv420("../../res/basic/pic/lena_256x256_yuv420p.yuv",256,256,1);
    // Split_yuv444("../../res/basic/pic/lena_256x256_yuv444p.yuv",256,256,1);
    // Convert_yuv420_gray("../../res/basic/pic/lena_256x256_yuv420p.yuv",256,256,1);
    // Halfy_yuv420("../../res/basic/pic/lena_256x256_yuv420p.yuv",256,256,1);
    // Border_yuv420("../../res/basic/pic/lena_256x256_yuv420p.yuv",256,256,20,1);
    // Graybar_yuv420(640, 360,0,255,10,"../../res/basic/pic/graybar_640x360.yuv");  x
    
    return 0;
}  