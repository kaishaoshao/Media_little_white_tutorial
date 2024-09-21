#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//  分离YUV420P像素数据中的Y、U、V分量
//////////////////////////////////////////
// split Y,U,V planes in YUV420P file
/// @param url       Location of Input YUV file
/// @param width     Width of Input YUV file
/// @param height    Height of Input YUV file
/// @param num       Number of frames to process
//////////////////////////////////////////
int Split_yuv420(const char *url,int width,int height,int num)
{
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
    // If the video frame width and height are width and height, respectively,
    // then a frame of YUV420P pixels takes up width*height*3/2 Byte of data.
    // The first width*height Byte stores Y, the next width*height*1/4 Byte stores U,
    // and the last width*height*1/4 Byte stores V.
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
/// @param url       Location of Input YUV file
/// @param width     Width of Input YUV file
/// @param height    Height of Input YUV file
/// @param num       Number of frames to process
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
    // If the video frame width and height are width and height, respectively,
    // then a frame of YUV444P pixels takes up width*height Byte of data.
    // The first width*height Byte stores Y, the next width*height Byte stores U,
    // and the last width*height*1/4 Byte stores V.
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
/// @param url       Location of Input YUV file
/// @param width     Width of Input YUV file
/// @param height    Height of Input YUV file
/// @param num       Number of frames to process
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
/// @param url       Location of Input YUV file
/// @param width     Width of Input YUV file
/// @param height    Height of Input YUV file
/// @param num       Number of frames to process
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
/// @param url       Location of Input YUV file
/// @param width     Width of Input YUV file
/// @param height    Height of Input YUV file
/// @param num       Number of frames to process
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
/// @param width    Width of Output YUV file.
/// @param height   Height of Output YUV file.
/// @param ymin     Max value of Y
/// @param ymax     Min value of Y
/// @param barnum   Number of bars
/// @param url_out  Location of Output YUV file.
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
/// @param url1     Location of first Input YUV file.
/// @param url2     Location of another Input YUV file.
/// @param width    Width of Input YUV file.
/// @param height   Height of Input YUV file.
/// @param num      Number of frames to process.
///////////////////////////////////////////////////////
int Psnr_yuv420(const char *url1,const char *url2,int width,int height,int num){
	FILE *fp1=fopen(url1,"rb+");
	FILE *fp2=fopen(url2,"rb+");
	unsigned char *pic1=(unsigned char *)malloc(width*height);
	unsigned char *pic2=(unsigned char *)malloc(width*height);
 
	for(int i=0;i<num;i++){
		fread(pic1,1,width*height,fp1);
		fread(pic2,1,width*height,fp2);
 
		double mse_sum=0,mse=0,psnr=0;
		for(int j=0;j<width*height;j++){
			mse_sum+=pow((double)(pic1[j]-pic2[j]),2);
		}
		mse=mse_sum/(width*height);
		psnr=10*log10(255.0*255.0/mse);
		printf("%5.3f\n",psnr);
 
		fseek(fp1,width*height/2,SEEK_CUR);
		fseek(fp2,width*height/2,SEEK_CUR);
 
	}
 
	free(pic1);
	free(pic2);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

///////////////////////////////////////////////////////
// Split R,G,B planes in RGB24 file
/// @param url      Location of first Input RGB file.
/// @param width    Width of Input RGB file.
/// @param height   Height of Input RGB file.
/// @param num      Number of frames to process.
///////////////////////////////////////////////////////
int Split_rgb24(const char *url,int width,int height,int num)
{
    FILE *fp = fopen(url,"rb+");
    if(fp == NULL)
    {
       perror("Error opening file");
       return -1;  
    }
    FILE *fp_r = fopen("../../output/basic/pic/output_r.y","wb+");
    FILE *fp_g = fopen("../../output/basic/pic/output_g.y","wb+");
    FILE *fp_b = fopen("../../output/basic/pic/output_b.y","wb+");
    
    int frames = width * height * 3;

    unsigned char *pic = (unsigned char*)malloc(frames);
    if (pic == NULL) {
        perror("Memory allocation failed");  
        fclose(fp);
        fclose(fp_r);
        fclose(fp_g);
        fclose(fp_b);
        return -1;
    }

    for (int i = 0; i < num; i++)
    {
        fread(pic,1,frames,fp);
        for (int j = 0; j < frames; j+=3)
        {
            // R
            fwrite(pic+j,1,1,fp_r);
            // G
            fwrite(pic+j+1,1,1,fp_g);
            // B
            fwrite(pic+j+2,1,1,fp_b);
        } 
    }
    
    free(pic);
    fclose(fp_r);
    fclose(fp_g);
    fclose(fp_b);
    return 0;
}


//  将RGB24格式像素数据封装为BMP图像
///////////////////////////////////////////////////////
// Split R,G,B planes in RGB24 file
/// @param url      Location of first Input RGB file.
/// @param width    Width of Input RGB file.
/// @param height   Height of Input RGB file.
/// @param num      Number of frames to process.
   



///////////////////////////////////////////////////////
// Convert RGB24 file to YUV420P file
/// @param url_in   Location of first Input RGB file.
/// @param width    Width of Input RGB file.
/// @param height   Height of Input RGB file.
/// @param num      Number of frames to process.
/// @param url_out  Location of first Output YUV file.
///////////////////////////////////////////////////////
// 
unsigned char clip_value(unsigned char x,unsigned char min_val,unsigned char max_val)
{
    if(x > max_val)
        return max_val;
    else if(x < min_val)
        return min_val;
    else
        return x;
}

bool rgb24_to_yuv420(unsigned char *RgbBuf,int width,int height,unsigned char *yuvBuf)
{
    unsigned char *prtY, *prtU, *prtV, *prtRGB;
    unsigned char y, u, v, r, g, b;
    memset(yuvBuf,0,width * height * 3 / 2);
    prtY = yuvBuf;
    prtU = prtY + width * height;
    prtV = prtU + width * height / 4;
    for (int i = 0; i < height; i++)
    {
        prtRGB = RgbBuf + width * i * 3;
        for (int j = 0; j < width; j++)
        {
            r = *(prtRGB++); // r = *prtRGB ; *prtRGB = *prtRGB->next
            g = *(prtRGB++);
            b = *(prtRGB++);
            y = (unsigned char)((66 * r + 129 * g +  25 * b + 128) >> 8) +  16;
            u = (unsigned char)((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128;
            v = (unsigned char)((112 * r - 94 * g -  18 * b + 128) >> 8) + 128;

            *(prtY++) = clip_value(y,0,255);
            // Y = 2U / y = 2V
            if(i % 2 == 0 && j % 2 == 0)
                *(prtU++) = clip_value(u,0,255);
            else{
                if(j % 2 == 0)
                    *(prtV++) = clip_value(v,0,255);
            }

        }
        
    }
    return true;
}


int Convert_rgb24_to_yuv420(const char *url_in,int width,int height,int num,const char *url_out)
{
    FILE *fp = fopen(url_in,"rb+");
    FILE *fp_out = fopen(url_out,"wb+");

    unsigned char *pic_rgb24 = (unsigned char*)malloc(width * height * 3);
    unsigned char *pic_yuv420 = (unsigned char*)malloc(width * height * 3 / 2);

    int frames = width * height * 3;

    for (int i = 0; i < num; i++)
    {
        fread(pic_rgb24,1,frames, fp);
        rgb24_to_yuv420(pic_rgb24,width,height,pic_yuv420);
        fwrite(pic_yuv420,1,frames / 2,fp_out);
    }

    free(pic_rgb24);
    free(pic_yuv420);
    fclose(fp);
    fclose(fp_out);
    
    return 0;
} 


///////////////////////////////////////////////////////
// Generate RGB24 colorbar
/// @param width    Width of Output RGB file.
/// @param height   Height of Output RGB file.
/// @param url_out      Location of Output RGB file.
///////////////////////////////////////////////////////
int Colorbar_rgb24(int height,int width,const char *url)
{
    unsigned char *data = NULL;
    int barwidth;
    char filename[100] = {0};
    FILE *fp = NULL;

    int frames = width * height * 3;
    data = (unsigned char*)malloc(frames);
    barwidth = height / 8; 

    if((fp=fopen(url,"wb+")) == NULL){
        printf("Error:Cannot create file!");
        return -1;
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int barnum = j / barwidth;
            switch (barnum)
            {
            case 0:{
                data[(i*height+j)*3+0] = 255;
                data[(i*height+j)*3+1] = 255;
                data[(i*height+j)*3+2] = 255;
                break;
            }
            case 1:{
                data[(i*height+j)*3+0] = 255;
                data[(i*height+j)*3+1] = 255;
                data[(i*height+j)*3+2] = 0;
                break;
            }
            case 2:{
                data[(i*height+j)*3+0] = 255;
                data[(i*height+j)*3+1] = 0;
                data[(i*height+j)*3+2] = 255;
                break;
            }
            case 3:{
                data[(i*height+j)*3+0] = 255;
                data[(i*height+j)*3+1] = 0;
                data[(i*height+j)*3+2] = 0;
                break;
            }
            case 4:{
                data[(i*height+j)*3+0] = 0;
                data[(i*height+j)*3+1] = 255;
                data[(i*height+j)*3+2] = 255;
                break;
            }
            case 5:{
                data[(i*height+j)*3+0] = 0;
                data[(i*height+j)*3+1] = 255;
                data[(i*height+j)*3+2] = 0;
                break;
            }
            case 7:{
                data[(i*height+j)*3+0] = 0;
                data[(i*height+j)*3+1] = 0;
                data[(i*height+j)*3+2] = 255;
                break;
            }
            case 8:{
                data[(i*height+j)*3+0] = 0;
                data[(i*height+j)*3+1] = 0;
                data[(i*height+j)*3+2] = 0;
                break;
            }        
                
            default:
                break;
            }
        }
        
    }
    
    fwrite(data,frames,1,fp);
    fclose(fp);
    free(data);
    
    return 0;
}

int main(int argc,char* argv[])
{
    const char *url1 = "../../res/basic/pic/lena_256x256_yuv420p.yuv";
    const char *url2 = "../../res/basic/pic/lena_256x256_yuv444p.yuv";
    const char *url3 = "../../res/basic/pic/graybar_640x360.yuv";
    const char *url4 = "../../res/basic/pic/lena_distort_256x256_yuv420p.yuv";
    const char *url5 = "../../res/basic/pic/cie1931_500x500.rgb";
    const char *url6 = "../../res/basic/pic/lena_256x256_rgb24.rgb";

    const char *url_out1 = "../../output/basic/pic/output_lena.yuv";
    const char *url_out2 = "../../output/basic/pic/colorbar_640x360.rgb";
    // Split_yuv420(url1,256,256,1);
    // Split_yuv444(url2,256,256,1);
    // Convert_yuv420_gray(url1,256,256,1);
    // Halfy_yuv420(url1,256,256,1);
    // Border_yuv420(url1,256,256,20,1);
    // Graybar_yuv420(640, 360,0,255,10,url3);  
    // Psnr_yuv420(url1,url4,256,256,1);
    // Split_rgb24(url5,500,500,1);
    Convert_rgb24_to_yuv420(url6,256,256,1,url_out1);
    //Colorbar_rgb24(640,360,url_out2);
    return 0;
}  