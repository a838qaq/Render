#pragma once
class CUI
{
public:
	CUI();
	virtual ~CUI();

	int GetMode();//返回当前控制模式
	void SetModeModel();//设置为控制模型
	void SetModeCamera();//设置为控制相机
	
	int GetRasterMode();//返回当前渲染模式
	void SetRasterOrth();//设置为正交投影
	void SetRasterPers();//设置为透视投影

	void Draw(CDC* pDC, int nHeight, int nWidth);//绘制UI

public:
	int Mode;//当前控制模式
	int RasterMode;//当前透视模式
};

