
// DrawTrangleView.h: CDrawTrangleView 类的接口
//

#pragma once
#include "line.h"
#include "Mesh.h"
#include "Face.h"
#include "Transform3.h"
#include "Cube.h"
#include "Camera.h"
#include "Coordinate.h"
#include "UI.h"
#include "CubeT.h"
#include "Lighting.h"

class CDrawTrangleView : public CView
{
protected: // 仅从序列化创建
	CDrawTrangleView() noexcept;
	DECLARE_DYNCREATE(CDrawTrangleView)

// 特性
public:
	CDrawTrangleDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void DoubleBuffer(CDC* pDC, BOOL msaa);
	virtual void DrawObject();
	virtual void DrawObject(CDC *pDC, int nHeight, int nWidth);
	virtual void Transformation();
	virtual void InitLightingAndMaterial();

// 实现
public:
	virtual ~CDrawTrangleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
	int nWidth, nHeight;

	CTransform3 trans;

	CCoordinate coordinate;
	CTransform3 Trans;
	BOOL ifDeletFace;
	
	CUI UI;
	CCamera camera;

	CCubeT cubeT;
	CLighting lighting;

	//CDC* pDC;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
};

#ifndef _DEBUG  // DrawTrangleView.cpp 中的调试版本
inline CDrawTrangleDoc* CDrawTrangleView::GetDocument() const
   { return reinterpret_cast<CDrawTrangleDoc*>(m_pDocument); }
#endif

