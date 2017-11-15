# Image-Convolution
对输入图像进行基本的卷积操作，两个核分别是5×5，sigma=0.6的高斯核，5×5的平均算子核。
# 核
高斯核：

double G[5][5]=

{

{6.58573e-006,0.000424781,0.00170354,0.000424781,6.58573e-006},

{0.000424781,	0.0273984,  0.109878,  0.0273984,  0.000424781},

{0.00170354,	0.109878,   0.440655,  0.109878,   0.00170354},

{0.000424781,	0.0273984,  0.109878,  0.0273984,  0.000424781},

{6.58573e-006,0.000424781,0.00170354,0.000424781,6.58573e-006},

};

平均算子：

double P[5][5]=

{

{0.04,0.04,0.04,0.04,0.04},

{0.04,0.04,0.04,0.04,0.04},

{0.04,0.04,0.04,0.04,0.04},

{0.04,0.04,0.04,0.04,0.04},

{0.04,0.04,0.04,0.04,0.04}

};
# 运行
./image_convolution test.jpg

即可同时输出原图和经过两个核卷积后的图。
