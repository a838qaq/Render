#pragma once
#include "P3.h"
 class CTransform3 
 {
 public:
	 void Init();//�����Խǵ�λ����
	 void MultiplyMatrix();//������˷�Ӧ�õ�����
	 void MultiplyMatrixForTranslate();//ר��Ϊƽ��д�ģ�����
	 void SetMatrix(CP3* P, int PNumber);//������
	 void SetFnNumber(int FnNumber);//������������

	 void Translate(double tx, double ty, double tz);//ƽ��
	 void Scale(double sx, double sy, double sz);//����
	 void RotateX(double angle);//��x����ת
	 void RotateY(double angle);//��y����ת
	 void RotateZ(double angle);//��z����ת
	 void RotateThisX(double angle, CP3 CenterPoint);//��������x����ת
	 void RotateThisY(double angle, CP3 CenterPoint);//��������y����ת
	 void RotateThisZ(double angle, CP3 CenterPoint);//��������z����ת
	 void RotateByCamera(CP3 Posision, CP3 Director, CP3 Head);//camera�任
	 void Perspective(double n, double f);//͸��ͶӰ������ȫ
	 void Orthographic();//����ͶӰ��ֻ��һ�������������ϸ�

 public:
	 double Matrix[4][4];
	 CP3 *P;
	 int PNumber;//ȫ������
	 int FnNumber;//��������
 };

