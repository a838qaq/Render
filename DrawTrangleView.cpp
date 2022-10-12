
// DrawTrangleView.cpp: CDrawTrangleView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawTrangle.h"
#endif

#include "DrawTrangleDoc.h"
#include "DrawTrangleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Line.h"
#include "Mesh.h"
#include <iostream>

// CDrawTrangleView

IMPLEMENT_DYNCREATE(CDrawTrangleView, CView)

BEGIN_MESSAGE_MAP(CDrawTrangleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CDrawTrangleView 构造/析构

CDrawTrangleView::CDrawTrangleView() noexcept
{
	// TODO: 在此处添加构造代码
	nWidth = nHeight = 0;
	
	//初始化参数
	cubeT.Init();
	ifDeletFace = TRUE;


		
	//设置相机参数
	camera.SetPosition(1420, 450, 410);
	camera.SetDirector(0.95467009225299149, 0.19934771704798687, 0.22105542894355878);
	camera.SetHead(0.086944225713829468, 0.057748823413309877, -0.99453797062223881);
	camera.SetN(-1800);
	camera.SetF(-1800);
	//初始为模型模式
	UI.SetModeModel();

	//初始化光源和材质
	InitLightingAndMaterial();
	
//	DrawObject();
}

CDrawTrangleView::~CDrawTrangleView()
{
	//ReleaseDC(pDC);
}

BOOL CDrawTrangleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawTrangleView 绘图

void CDrawTrangleView::OnDraw(CDC* pDC)
{
	CDrawTrangleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//pDC = GetDC();
	
	CRect rect;
	GetClientRect(&rect);//获得客户区大小
	pDC->SetMapMode(MM_ANISOTROPIC);//设置映射模式
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//设置视区范围，y向上为正方向
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//设置坐标系原点
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);//校正客户区矩形


	//DrawObject(pDC, rect.Height(), rect.Width());

	

	//DoubleBuffer(pDC, 0);
	Transformation();
	cubeT.DeletFace(camera.Position, ifDeletFace);
	DrawObject(pDC, rect.Height(), rect.Width());
	//	OnPrint(pDC);
	// TODO: 在此处为本机数据添加绘制代码
}


// CDrawTrangleView 打印

BOOL CDrawTrangleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawTrangleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
//	pDC = GetDC();
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawTrangleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDrawTrangleView::DoubleBuffer(CDC* pDC, BOOL msaa)
{
	CRect rect;
	GetClientRect(&rect);
	nWidth = rect.Width();
	nHeight = rect.Height();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap NewBitmap, * pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&NewBitmap);
	memDC.FillSolidRect(rect, pDC->GetBkColor());
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);//校正客户区矩形
	memDC.SetMapMode(MM_ANISOTROPIC);//设置映射模式
	memDC.SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	memDC.SetViewportExt(rect.Width(), -rect.Height());//设置视区范围，y向上为正方向
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//设置坐标系原点
	
	DrawObject(&memDC, rect.Height(), rect.Width());

	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width()/2, -rect.Height() / 2, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
}

void CDrawTrangleView::DrawObject()
{
	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);//获得客户区大小
	pDC->SetMapMode(MM_ANISOTROPIC);//设置映射模式
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//设置视区范围，y向上为正方向
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//设置坐标系原点
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);//校正客户区矩形

	UI.Draw(pDC, nHeight, nWidth);
	coordinate.Draw(pDC, camera.GetZbuffer(), camera.Position, lighting, nHeight, nWidth, cubeT);
	cubeT.Draw(pDC, camera.GetZbuffer(), camera.Position, lighting);

	ReleaseDC(pDC);
}

void CDrawTrangleView::DrawObject(CDC *pDC, int nHeight, int nWidth)
{

	coordinate.Draw(pDC, camera.GetZbuffer(),camera.Position,lighting, nHeight, nWidth, cubeT);
	cubeT.Draw(pDC, camera.GetZbuffer(), camera.Position, lighting);
	UI.Draw(pDC, nHeight, nWidth);
}

void CDrawTrangleView::Transformation()
{
	//将变换读入缓存
	cubeT.LoadBuffer();
	coordinate.LoadBufferPoint();

	//选中缓存
	trans.SetMatrix(cubeT.GetBufferPoint(), cubeT.PNumber);
	Trans.SetMatrix(coordinate.GetBufferPoint(), coordinate.PNumber);
	trans.SetFnNumber(cubeT.FNumber);
	Trans.SetFnNumber(0);

	//开始Camera变换
	trans.Translate(-camera.Position.x, -camera.Position.y, -camera.Position.z);
	Trans.Translate(-camera.Position.x, -camera.Position.y, -camera.Position.z);
	trans.RotateByCamera(camera.Position, camera.Director, camera.Head);
	Trans.RotateByCamera(camera.Position, camera.Director, camera.Head);

	//开始透视/正交变换
	switch (UI.GetRasterMode())
	{
	case 1:
		trans.Perspective(camera.n, camera.f);
		Trans.Perspective(camera.n, camera.f);
		break;
	}
	trans.Orthographic();
	Trans.Orthographic();
}

void CDrawTrangleView::InitLightingAndMaterial()
{
	//设置光源
	lighting.SetLighting(1);
	for (int i = 0; i < lighting.LightNumber; i++)
	{
		lighting.LightSRC[i].SetPosition(CP3(1000, 1000, 1000));
		lighting.LightSRC[i].SetDiffuse(CRGB(1, 1, 1));
		lighting.LightSRC[i].SetSpecular(CRGB(1, 1, 1));
		lighting.LightSRC[i].SetFade(1, 0.000001, 0.0000001);
		lighting.LightSRC[i].SetLightON(TRUE);
	}	

	//设置材质
	cubeT.material.SetAmbient(CRGB(0.847, 0.1, 0.075));
	cubeT.material.SetDiffuse(CRGB(0.852, 0.006, 0.026));
	cubeT.material.SetSpecular(CRGB(1, 1, 1));
	cubeT.material.SetEmission(CRGB(0, 0, 0));
	cubeT.material.SetHightLight(7);

	coordinate.material.SetAmbient(CRGB(0.847, 0.1, 0.075));
	coordinate.material.SetDiffuse(CRGB(0.52, 0.206, 0.226));
	coordinate.material.SetSpecular(CRGB(1, 1, 1));
	coordinate.material.SetEmission(CRGB(0, 0, 0));
	coordinate.material.SetHightLight(5000000);
}


// CDrawTrangleView 诊断

#ifdef _DEBUG
void CDrawTrangleView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawTrangleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawTrangleDoc* CDrawTrangleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawTrangleDoc)));
	return (CDrawTrangleDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawTrangleView 消息处理程序


void CDrawTrangleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);//设置映射模式
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//设置视区范围，y向上为正方向
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//设置坐标系原点
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);//校正客户区矩形	
	nWidth = rect.Width();
	nHeight = rect.Height();
	if (point.x > 0.9 * nWidth && point.y < 0.1 * nHeight)
	{
		if (UI.GetMode() == 0)
		{
			UI.SetModeCamera();
			MessageBox(L"已切换到摄像机模式");
		}
		else if (UI.GetMode()== 1)
		{
			UI.SetModeModel();
			MessageBox(L"已切换到模型模式");
		}
	}
	else if (point.x > 0.8 * nWidth && point.x < 0.9 * nWidth && point.y < 0.1 * nHeight)
	{
		if (UI.GetRasterMode() == 0)
		{
			UI.SetRasterPers();
			MessageBox(L"已切换为透视投影");
		}
		else if (UI.GetRasterMode() == 1)
		{
			UI.SetRasterOrth();
			MessageBox(L"已切换为正交投影");
		}
	}
	//实时变换
	Invalidate(TRUE);
	camera.InitZbuffer();
	cubeT.DeletFace(camera.Position, ifDeletFace);
	Transformation();
	//DoubleBuffer(pDC, 1);
	DrawObject(pDC, rect.Height(), rect.Width());

	ReleaseDC(pDC);
	CView::OnLButtonDown(nFlags, point);
}

void CDrawTrangleView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
}


//void CDrawTrangleView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CView::OnKeyDown(nChar, nRepCnt, nFlags);
//}


BOOL CDrawTrangleView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	GetClientRect(&rect);
	CDC* pDC = GetDC();

	pDC->SetMapMode(MM_ANISOTROPIC);//设置映射模式
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//设置视区范围，y向上为正方向
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//设置坐标系原点
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);//校正客户区矩形

	trans.SetMatrix(cubeT.GetPoints(), cubeT.PNumber);
	Trans.SetMatrix(coordinate.GetPoint(), coordinate.PNumber);

	if (pMsg->message == WM_KEYDOWN)
	{
		CP3 CenterPoint = cubeT.GetCenterPoint();
		//RedrawWindow();
		Invalidate(TRUE);

		//全局控制
		switch (pMsg->wParam)
		{
		case 'C':
			if (ifDeletFace)
			{
				ifDeletFace = !ifDeletFace;
				for (int i = 0; i < cubeT.FNumber; i++)
				{
					cubeT.VisionableFace[i] = 1;
				}
			}
			else 
			{
				ifDeletFace = !ifDeletFace;
			}
			break;

		case 'V':
			switch (cubeT.GetMode())
			{
			case 0:
				cubeT.SetModeFace();
				break;
				
			case 1:
				cubeT.SetModeTriangle();
				break;

			case 2:
				cubeT.SetModeRGBBB();
				break;

			case 3:
				cubeT.SetDepth();
				break;

			case 4:
				cubeT.SetModePhong();
				break;

			case 5:
				cubeT.SetModeLineFrame();
				break;
			}
			break;

		case 'B':
			switch (coordinate.GetDrawMode())
			{
			case 0:
				coordinate.SetDrawModeColor();
				break;

			case 1:
				coordinate.SetDrawModeDepth();
				break;

			case 2:
				coordinate.SetDrawModeLine();
				break;
			}
			break;

		case 'P':
			std::cout << 1;
			break;
		}

		//模型控制
		if (UI.GetMode() == 0)
		{
			trans.SetMatrix(cubeT.GetPoints(), cubeT.PNumber);
			switch (pMsg->wParam)
			{
			case 'W':
				trans.Translate(-10, 0, 0);
				break;

			case 'S':
				trans.Translate(10, 0, 0);
				break;

			case 'D':
				trans.Translate(0, 10, 0);
				break;

			case 'A':
				trans.Translate(0, -10, 0);
				break;

			case 'Q':
				trans.Translate(0, 0, 10);
				break;

			case 'E':
				trans.Translate(0, 0, -10);
				break;

			case 'Z':
				trans.Translate(-CenterPoint.x, -CenterPoint.y, -CenterPoint.z);
				trans.Scale(1.1, 1.1, 1.1);
				trans.Translate(CenterPoint.x, CenterPoint.y, CenterPoint.z);
				break;

			case 'X':
				trans.Translate(-CenterPoint.x, -CenterPoint.y, -CenterPoint.z);
				trans.Scale(0.9, 0.9, 0.9);
				trans.Translate(CenterPoint.x, CenterPoint.y, CenterPoint.z);
				break;

			case 'F':
				trans.RotateX(10);
				break;

			case 'H':
				trans.RotateX(-10);
				break;

			case 'T':
				trans.RotateY(10);
				break;

			case 'G':
				trans.RotateY(-10);
				break;

			case 'R':
				trans.RotateZ(10);
				break;

			case 'Y':
				trans.RotateZ(-10);
				break;

			case 'I':
				trans.RotateThisX(10, CenterPoint);
				break;

			case 'K':
				trans.RotateThisX(-10, CenterPoint);

			case 'J':
				trans.RotateThisY(10, CenterPoint);
				break;

			case 'L':
				trans.RotateThisY(-10, CenterPoint);
				break;

			case 'U':
				trans.RotateThisZ(10, CenterPoint);
				break;

			case 'O':
				trans.RotateThisZ(-10, CenterPoint);
				break;
			}
		}
		else if (UI.GetMode() == 1)//相机控制
		{
			//选中相机
			trans.SetMatrix(camera.GetPositonPoint(), 1);
			switch (pMsg->wParam)
			{
			case 'W':
				trans.Translate(-10, 0, 0);
				break;

			case 'S':
				trans.Translate(10, 0, 0);
				break;

			case 'D':
				trans.Translate(0, 10, 0);
				break;

			case 'A':
				trans.Translate(0, -10, 0);
				break;

			case 'Q':
				trans.Translate(0, 0, 10);
				break;

			case 'E':
				trans.Translate(0, 0, -10);
				break;

			case 'J':
				trans.SetMatrix(camera.GetDirectorPoint(), 1);
				trans.RotateX(10);
				trans.SetMatrix(camera.GetHeadPoint(), 1);
				trans.RotateX(10);
				break;

			case 'L':
				trans.SetMatrix(camera.GetDirectorPoint(), 1);
				trans.RotateX(-10);
				trans.SetMatrix(camera.GetHeadPoint(), 1);
				trans.RotateX(-10);
				break;

			case 'I':
				trans.SetMatrix(camera.GetDirectorPoint(), 1);
				trans.RotateY(10);
				trans.SetMatrix(camera.GetHeadPoint(), 1);
				trans.RotateY(10);
				break;

			case 'K':
				trans.SetMatrix(camera.GetDirectorPoint(), 1);
				trans.RotateY(-10);
				trans.SetMatrix(camera.GetHeadPoint(), 1);
				trans.RotateY(-10);
				break;

			case 'U':
				trans.SetMatrix(camera.GetDirectorPoint(), 1);
				trans.RotateZ(10);
				trans.SetMatrix(camera.GetHeadPoint(), 1);
				trans.RotateZ(10);
				break;

			case 'O':
				trans.SetMatrix(camera.GetDirectorPoint(), 1);
				trans.RotateZ(-10);
				trans.SetMatrix(camera.GetHeadPoint(), 1);
				trans.RotateZ(-10);
				break;
			case 'R':
				camera.MoreWide();
				break;

			case 'Y':
				camera.MoreNarrow();
				break;

			case 'F':
				coordinate.Axis[0] = !coordinate.Axis[0];
				break;
				
			case 'G':
				coordinate.Axis[1] = !coordinate.Axis[1];
				break;

			case 'H':
				coordinate.Axis[2] = !coordinate.Axis[2];
				break;
			}
		}
		//Model变换完成
		
		// 开始背面剔除
		cubeT.DeletFace(camera.Position, ifDeletFace);
		camera.InitZbuffer();

		// 开始进行下一步变换
		Transformation();
	}
	ReleaseDC(pDC);
	return CView::PreTranslateMessage(pMsg);
}


void CDrawTrangleView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 在此添加专用代码和/或调用基类

	CView::OnPrint(pDC, pInfo);
}
