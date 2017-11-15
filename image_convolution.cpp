#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

//定义一个5*5，sigma=0.6的高斯卷积核
int N=5;
double G[5][5]={
		  {6.58573e-006,0.000424781,0.00170354,0.000424781,6.58573e-006},
		  {0.000424781,	0.0273984,  0.109878,  0.0273984,  0.000424781},
		  {0.00170354,	0.109878,   0.440655,  0.109878,   0.00170354},
		  {0.000424781,	0.0273984,  0.109878,  0.0273984,  0.000424781},
		  {6.58573e-006,0.000424781,0.00170354,0.000424781,6.58573e-006},
		};

//定义一个5*5的平均算子核
double P[5][5]={
		  {0.04,0.04,0.04,0.04,0.04},
		  {0.04,0.04,0.04,0.04,0.04},
		  {0.04,0.04,0.04,0.04,0.04},
		  {0.04,0.04,0.04,0.04,0.04},
		  {0.04,0.04,0.04,0.04,0.04}
		};
		
//主函数
int main(int argc, char **argv) 
{
  if (argc != 2)
  {
    cout<<"请输入图片！"<<endl;
    cout<<"./image_convolution PATH/TEST.jpg"<<endl;
    return 0;
  }
  //定义一个opencv下的图像对象  
  Mat image;
  
  //将输入图像赋给image
  //argv[1]表示程序执行的第二个参数，第一个参数是程序名
  //cv::imread用于读取指定路径下的图像
  image = imread( argv[1] );
  
  //如果没有图像输入，输出提示信息，程序结束
  if ( image.data == NULL)
  {
    cout <<"图像载入失败。"<<endl;
    return 0;
  }
  
  //判断图像是否为彩色图或者深度图
  //如果都不是，输出提示信息，程序结束
  if ( (image.type() != CV_8UC1) && (image.type() != CV_8UC3))
  {
    cout <<"图像不符合要求，请输入一张彩色图或者灰度图。"<<endl;
    return 0;
  }
  
  //复制两张图像分别进行卷积操作
  Mat image_G = image.clone();
  Mat image_P = image.clone();
  
  //高斯卷积核
  //遍历图像
  //y 遍历行，x 遍历列。y在外围的for里，所以遍历为一行一行遍历
  //for ( size_t  y=image.rows ; y>N/2; y--)
  for ( size_t  y=N/2 ; y<image_G.rows-N/2; y++)
  {
    for  (size_t   x=N/2*image_G.channels() ; x<(image_G.cols-N/2)*image_G.channels(); x++)
    {
      unsigned char* row_ptr_now = image_G.ptr<unsigned char>( y );
      unsigned char data=0;
      for ( size_t i=0;i<N;i++)
	 for (size_t j=0;j<N;j++)
	 {
	   unsigned char* row_ptr = image_G.ptr<unsigned char>( y-(N/2-i) ); 
	   data = data + G[i][j]*row_ptr[x-(N/2-j)*image_G.channels()];
	}
      row_ptr_now[x]=data;  
    }
  }
  
  //平均算子核
  //遍历图像
  //y 遍历行，x 遍历列。y在外围的for里，所以遍历为一行一行遍历
  //for ( size_t  y=image.rows ; y>N/2; y--)
  for ( size_t  y=N/2 ; y<image_P.rows-N/2; y++)
  {
    for  (size_t   x=N/2*image_P.channels() ; x<(image_P.cols-N/2)*image_P.channels(); x++)
    {
      unsigned char* row_ptr_now = image_P.ptr<unsigned char>( y );
      unsigned char data=0;
      for ( size_t i=0;i<N;i++)
	 for (size_t j=0;j<N;j++)
	 {
	   unsigned char* row_ptr = image_P.ptr<unsigned char>( y-(N/2-i) ); 
	   data = data + P[i][j]*row_ptr[x-(N/2-j)*image_P.channels()];
	}
      row_ptr_now[x]=data;  
    }
  }

  Mat img_show(image.rows,image.cols*3,CV_8UC3);
  //cv::Rect的前两个参数矩形左上角的为x和y坐标，后两个为矩形的宽和高
  image.copyTo( img_show( cv::Rect(0,0,image.cols,image.rows) ) );
  image_G.copyTo( img_show( cv::Rect(image.rows,0,image.cols,image.rows) ) );
  image_P.copyTo( img_show( cv::Rect(image.rows*2,0,image.cols,image.rows) ) );
  
  imshow("原图---高斯核---平均算子核",img_show);
  
  
  //暂停程序，等待键盘上的一个输入
  cv::waitKey(0);

  //关闭所有打开的图像
  cv::destroyAllWindows();
  return 0;
}
