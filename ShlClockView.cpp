// ShlClockView.cpp : implementation of the CShlClockView class
//

#include "stdafx.h"
#include "ShlClock.h"

#include "ShlClockDoc.h"
#include "ShlClockView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  pi  3.1415926

/////////////////////////////////////////////////////////////////////////////
// CShlClockView

IMPLEMENT_DYNCREATE(CShlClockView, CFormView)

BEGIN_MESSAGE_MAP(CShlClockView, CFormView)
	//{{AFX_MSG_MAP(CShlClockView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShlClockView construction/destruction

CShlClockView::CShlClockView()
	: CFormView(CShlClockView::IDD)
{
	
	//{{AFX_DATA_INIT(CShlClockView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CShlClockView::~CShlClockView()
{
}

void CShlClockView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShlClockView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CShlClockView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CShlClockView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
//	GetParentFrame()->RecalcLayout();
//	ResizeParentToFit();
//	ShowWindow(SW_MAXIMIZE);
	GetNum();
	SetTimer(1,1500,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CShlClockView diagnostics

#ifdef _DEBUG
void CShlClockView::AssertValid() const
{
	CFormView::AssertValid();
}

void CShlClockView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CShlClockDoc* CShlClockView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShlClockDoc)));
	return (CShlClockDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShlClockView message handlers

/*
void CShlClockView::DrawCursor(CDC *pDC)
{
//	CDC *pDC=GetDC();
	CPoint Center=CPoint(252,152);
	int Radius=50;
//	int angle=0;
	CPen apen(PS_SOLID,1,RGB(80,80,80));
	CPen *oldpen=pDC->SelectObject(&apen);
	pDC->Ellipse(CRect(int(Center.x-7),int(Center.y-7),int(Center.x+7),int(Center.y+7)));
	pDC->MoveTo(int(Center.x+7*sin(angle-1)),int(Center.y-7*cos(angle-1)));
	pDC->LineTo(int(Center.x+50*sin(angle)),int(Center.y-50*cos(angle)));
	pDC->MoveTo(int(Center.x+7*sin(angle+1)),int(Center.y-7*cos(angle+1)));
	pDC->LineTo(int(Center.x+50*sin(angle)),int(Center.y-50*cos(angle)));
	pDC->MoveTo(int(Center.x+7*sin(angle)),int(Center.y-7*cos(angle)));
	pDC->LineTo(int(Center.x+50*sin(angle)),int(Center.y-50*cos(angle)));

	
	pDC->SelectObject(oldpen);

}*/
void CShlClockView::GetNum()
{
	/*
	SYSTEMTIME m_Time;
		CString str;
		//获取当前系统时间
		GetLocalTime(&m_Time);
		//设置当前系统时间格式
		str.Format("%d-%d-%d %d:%d:%d",
			m_Time.wYear,m_Time.wMonth,m_Time.wDay,m_Time.wHour,
			m_Time.wMinute,m_Time.wSecond);
		//显示当前系统时间
		SetDlgItemText(IDC_TIME,str);*/
	
	time_t ltime;
	tm* ptime;
	ltime=time(NULL);			//取得长整数系统时间
	ptime=localtime(&ltime);		//转成tm时间结构
	nHour=ptime->tm_hour;
	nMin=ptime->tm_min;
	nSec=ptime->tm_sec;
	nYear=ptime->tm_year+1900;
	nMon=ptime->tm_mon+1;
	nDay=ptime->tm_mday;
	if(ptime->tm_wday)
		nWeek=ptime->tm_wday;
	else
		nWeek=7;
	
}

void CShlClockView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	OnPrepareDC(&dc);


//背景和表盘
	CBitmap m_bitmap_panel,MemBitmap,*pOldBit;//定义位图资源
	CDC m_dcMemory_panel,MemDC;//双缓存
	CRect rect;
	GetClientRect(&rect);f
	MemDC.Create0CompatibleDC(&dc);
	MemBitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(149,163,163));
//表盘
	m_bitmap_panel.LoadBitmap(IDB_PANEL);	
	if(m_dcMemory_panel.GetSafeHdc()==NULL)
		m_dcMemory_panel.CreateCompatibleDC(&MemDC);
	m_dcMemory_panel.SelectObject(&m_bitmap_panel);	
	MemDC.BitBlt(150,50,593,563,&m_dcMemory_panel,0,0,SRCCOPY);

	CPoint Center=CPoint(252,152)//中心
	int Radius=5000;
//分针
	CPen apen(PS_SOLID,1,RGB(0,0,0));
	CPen *oldpen=MemDC.SelectObject(&apen);
	nMinAngle=float(nMin)*6*float(pi)/180;
	MemDC.Ellipse(CRect(int(Center.x-7),int(Center.y-7),int(Center.x+7),int(Center.y+7)));
	MemDC.MoveTo(int(Center.x+7*sin(nMinAngle-1)),int(Center.y-7*cos(nMinAngle-1)));
	MemDC.LineTo(int(Center.x+55*sin(nMinAngle)),int(Center.y-55*cos(nMinAngle)));
	MemDC.MoveTo(int(Center.x+7*sin(nMinAngle+1)),int(Center.y-7*cos(nMinAngle+1)));
	MemDC.LineTo(int(Center.x+55*sin(nMinAngle)),int(Center.y-55*cos(nMinAngle)));
	MemDC.MoveTo(int(Center.x+7*sin(nMinAngle)),int(Center.y-7*cos(nMinAngle)));
	MemDC.LineTo(int(Center.x+55*sin(nMinAngle)),int(Center.y-55*cos(nMinAngle)));
	MemDC.SelectObject(oldpen);
//时针
	CPen newpen(PS_SOLID,1,RGB(0,0,0));
	oldpen=MemDC.SelectObject(&newpen);
	nHourAngle=float(nHour+float(nMin)/60)*30*float(pi)/180;
	MemDC.Ellipse(CRect(int(Center.x-4),int(Center.y-4),int(Center.x+4),int(Center.y+4)));
	MemDC.MoveTo(int(Center.x+7*sin(nHourAngle-1)),int(Center.y-7*cos(nHourAngle-1)));
	MemDC.LineTo(int(Center.x+40*sin(nHourAngle)),int(Center.y-40*cos(nHourAngle)));
	MemDC.MoveTo(int(Center.x+7*sin(nHourAngle+1)),int(Center.y-7*cos(nHourAngle+1)));
	MemDC.LineTo(int(Center.x+40*sin(nHourAngle)),int(Center.y-40*cos(nHourAngle)));
	MemDC.MoveTo(int(Center.x+7*sin(nHourAngle)),int(Center.y-7*cos(nHourAngle)));
	MemDC.LineTo(int(Center.x+40*sin(nHourAngle)),int(Center.y-40*cos(nHourAngle)));
	MemDC.SelectObject(oldpen);
//秒针
	CPen pen(PS_SOLID,3,RGB(255,0,0));
	oldpen=MemDC.SelectObject(&pen);
	nSecAngle=float(nSec)*6*(float)pi/180;
	MemDC.Ellipse(CRect(int(Center.x-2),int(Center.y-2),int(Center.x+2),int(Center.y+2)));
	MemDC.MoveTo(int(Center.x+2*sin(nSecAngle)),int(Center.y-2*cos(nSecAngle)));
	MemDC.LineTo(int(Center.x+35*sin(nSecAngle)),int(Center.y-35*cos(nSecAngle)));
	CPen pen1(PS_SOLID,2,RGB(255,0,0));
	oldpen=MemDC.SelectObject(&pen1);
	MemDC.Ellipse(CRect(int(Center.x-1),int(Center.y-1),int(Center.x+1),int(Center.y+1)));
	MemDC.MoveTo(int(Center.x+35*sin(nSecAngle)),int(Center.y-35*cos(nSecAngle)));
	MemDC.LineTo(int(Center.x+50*sin(nSecAngle)),int(Center.y-50*cos(nSecAngle)));
	CPen pen2(PS_SOLID,1,RGB(255,0,0));
	oldpen=MemDC.SelectObject(&pen2);
	MemDC.Ellipse(CRect(int(Center.x-1),int(Center.y-1),int(Center.x+1),int(Center.y+1)));
	MemDC.MoveTo(int(Center.x+50*sin(nSecAngle)),int(Center.y-50*cos(nSecAngle)));
	MemDC.LineTo(int(Center.x+60*sin(nSecAngle)),int(Center.y-60*cos(nSecAngle)));
//画出位图		
	dc.BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	CString str,strWeek;
	str.Format("%4d-%2d-%2d %2d:%2d:%2d",
		nYear,nMon,nDay,nHour,nMin,nSec);
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(10,20,str);
		switch(nWeek) {
	case 1:
		dc.TextOut(50,50,"星期一");
		break;
	case 2:
		dc.TextOut(50,50,"星期二");
		break;
	case 3:
		dc.TextOut(50,50,"星期三");
		break;
	case 4:
		dc.TextOut(50,50,"星期四");
		break;
	case 5:
		dc.TextOut(50,50,"星期五");
		break;
	case 6:
		dc.TextOut(50,50,"星期六");
		break;
	default:
		dc.TextOut(50,50,"星期日");
		break;
	}

		// TODO: Add your message handler code here
	
	// Do not call CFormView::OnPaint() for painting messages
}

void CShlClockView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CFormView::OnLButtonDown(nFlags, point);
}

void CShlClockView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	angle=angle+1;
//	CRect rect=CRect(150,50,300,250);
//	GetClientRect(&rect);
//	InvalidateRect(&rect,FALSE);
	nSec+=1;
	if(nSec==60)
	{
		nSec=0;
		nMin++;}
	if(nMin==60)
	{
		nHour++;
		nMin=0;}
	Invalidate(FALSE);
	//OnPaint();
	CFormView::OnTimer(nIDEvent);
}

void CShlClockView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
}

void CShlClockView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
