//Download by www.cctry.com
#if !defined(AFX_BITBUTTONNL_H__413ED251_E607_4CAB_8868_B58825104543__INCLUDED_)
#define AFX_BITBUTTONNL_H__413ED251_E607_4CAB_8868_B58825104543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//add new
#define	BTNNL_USE_SOUND				//��������

#define BTNNL_COLOR_FG_NORMAL	0
#define BTNNL_COLOR_FG_CLICK	1
#define BTNNL_COLOR_FG_HIGH		2

#define NL_ALIGN_LEFT			0
#define NL_ALIGN_RIGHT			1
#define NL_ALIGN_CENTER			2

// BitButtonNL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitButtonNL window

class CBitButtonNL : public CButton
{
// Construction
public:
	CBitButtonNL();

private:
	typedef struct _STRUCT_BITMAPS		//λͼ��Ϣ�ṹ��
	{
		HBITMAP		hBitmap;
		DWORD		dwWidth;
		DWORD		dwHeight;
	} STRUCT_BITMAPS;

#ifdef	BTNNL_USE_SOUND
#pragma pack(1)
	typedef struct _STRUCT_SOUND
	{
		TCHAR		szSound[_MAX_PATH];
		LPCTSTR		lpszSound;
		HMODULE		hMod;
		DWORD		dwFlags;
	} STRUCT_SOUND;
#pragma pack()

	STRUCT_SOUND	m_csSounds[2];	// Index 0 = Over	1 = Clicked

#endif

	STRUCT_BITMAPS	m_csBitmaps[4];	// Button bitmap
	COLORREF	m_crForceColors[3];	// Colors to be used

	BOOL		m_bMouseOnButton;	// Is mouse over the button?
	POINT		m_ptPressedOffset;	// ƫ����
	BOOL		m_bIsPressed;		// Is button pressed?
	BOOL		m_bIsFocused;		// Is button focused?
	BOOL		m_bIsDisabled;		// Is button disabled?
	BOOL		m_bDrawText;		// Draw Text for button?
	BOOL		m_bDrawFlatFocus;	// Draw focus rectangle for flat button?
	int			m_iDeflateRect_x;	// DrawFlateFouse deflate rect _ x
	int			m_iDeflateRect_y;	// DrawFlateFouse deflate rect _ y
	HCURSOR		m_hCursor;			// Handle to cursor
	UINT		m_nTypeStyle;		// Button style
	BOOL		m_bIsDefault;		// Is default button?

	//�������йصı���
	CFont		m_font;
	LOGFONT		m_lf;
	BYTE		m_byTextAlign;		// Align text
	BOOL		m_bDrawDisableText;	// is Draw text as disable?
	BOOL		m_bFont3d;
	COLORREF	m_cr3DBKColor;
	int			m_iText3d_x, m_iText3d_y;

private:
	void FreeResources(BOOL bCheckForNULL = TRUE);
	//���Ʊ���ͼ��
	virtual void DrawTheBitmap(CDC* pDC,  RECT* rpItem, 
					 BOOL bIsPressed, BOOL bIsDisabled);
	//�����ı�
	virtual void DrawTheText(CDC* pDC, LPCTSTR lpszText, RECT* rpItem,
					CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled);
	//����뿪�¼�
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	//�ָ���ť��������µ�����
	void CancelHover(void);
	//�ع�����
	void ReconstructFont(void);

// Attributes
public:

// Operations
public:
	//���ð�ťλͼͼ��
	BOOL SetBitmaps(UINT nBitmapNormal, UINT nBitmapMouseDown = NULL, 
					UINT nBitmapHigh = NULL, UINT nBitmapDisable = NULL);
	BOOL SetBitmaps(HBITMAP hBitmapNormal, HBITMAP hBitmapMouseDown = NULL,
					HBITMAP hBitmapHigh = NULL, HBITMAP hBitmapDisable = NULL);
	//����������ɫ
	BOOL SetForceColor(COLORREF crColorNormal, COLORREF crColorMouseDown, 
					   COLORREF crColorHigh, BOOL bRepaint = TRUE);
	//���ð�ť����Ӧ��һ��λͼ��С
	void SizeToContent(void);
	//�����������ָ��
	BOOL SetBtnCursor(int nCursorId = NULL, BOOL bRepaint = TRUE);
	//�����Ƿ���ʾ��ť����
	virtual CBitButtonNL& SetDrawText(BOOL bDraw = TRUE, BOOL bRepaint = TRUE);
	//���� 3d ����
	virtual CBitButtonNL& SetFont3D(BOOL bSet, int i3dx = 3, int i3dy = 2, BOOL bRepaint = TRUE);
	//���� 3d ���� ��Ӱɫ��
	virtual CBitButtonNL& SetText3DBKColor(COLORREF cr3DBKColor, BOOL bRepaint = TRUE);
	//���������Ƿ�Ϊ����
	virtual CBitButtonNL& SetFontBold(BOOL bBold, BOOL bRepaint = TRUE);
	//���������ֺ�
	virtual CBitButtonNL& SetFontSize(int nSize, BOOL bRepaint = TRUE);
	//������������
	virtual CBitButtonNL& SetFontName(const CString& strFont, BYTE byCharSet = DEFAULT_CHARSET,
									  BOOL bRepaint = TRUE);
	//���ð�ť�������з�ʽ
	BOOL SetTextAlign(BYTE byAlign, BOOL bRepaint = TRUE);

#ifdef	BTNNL_USE_SOUND

	BOOL SetSound(LPCTSTR lpszSound, HMODULE hMod = NULL, BOOL bPlayOnClick = FALSE,
				  BOOL bPlayAsync = TRUE);
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitButtonNL)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBitButtonNL();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBitButtonNL)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITBUTTONNL_H__413ED251_E607_4CAB_8868_B58825104543__INCLUDED_)
