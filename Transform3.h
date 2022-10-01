#pragma once
#include "P3.h"
 class CTransform3 
 {
 public:
	 void Init();//创建对角单位矩阵
	 void MultiplyMatrix();//将矩阵乘法应用到顶点
	 void MultiplyMatrixForTranslate();//专门为平移写的！！！
	 void SetMatrix(CP3* P, int PNumber);//传入点表
	 void SetFnNumber(int FnNumber);//设置面向量数

	 void Translate(double tx, double ty, double tz);//平移
	 void Scale(double sx, double sy, double sz);//缩放
	 void RotateX(double angle);//绕x轴旋转
	 void RotateY(double angle);//绕y轴旋转
	 void RotateZ(double angle);//绕z轴旋转
	 void RotateThisX(double angle, CP3 CenterPoint);//以任意点的x轴旋转
	 void RotateThisY(double angle, CP3 CenterPoint);//以任意点的y轴旋转
	 void RotateThisZ(double angle, CP3 CenterPoint);//以任意点的z轴旋转
	 void RotateByCamera(CP3 Posision, CP3 Director, CP3 Head);//camera变换
	 void Perspective(double n, double f);//透视投影（不完全
	 void Orthographic();//正交投影（只是一项修正，并不严格

 public:
	 double Matrix[4][4];
	 CP3 *P;
	 int PNumber;//全部点数
	 int FnNumber;//面向量数
 };

