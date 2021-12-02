
// Alpha.O.02Dlg.h: 헤더 파일
//

#pragma once
#pragma comment(lib, "winmm")
#include <mmsystem.h>

// CAlphaO02Dlg 대화 상자
class CAlphaO02Dlg : public CDialogEx
{
// 생성입니다.
public:

	CAlphaO02Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALPHAO02_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	enum { WIDTH = 30, OFFSET = 20, TURNTIME = 30 };//WIDTH (한칸의 간격), OFFSET(바둑판과 메인윈도우사이 간격), TURNTIME(제한시간)
	int step = 0;	//0, 1, 2 (돌이없다, 흑돌, 백돌)
	int dol[19][19] = { 0, }; //바둑판 2차원 배열
	int black_win_count = 0; //흑승리 카운트 ++
	int white_win_count = 0; //백승리 카운트 ++
	int turn; //현재 타이머시간
	int pause_count = 0;	// 0, 1 (타이머동작, 타이머정지)
	CString bWin = L"BLACK WIN";	//흑 승리
	CString wWin = L"WHITE WIN";	//백 승리
	CString Tie = L"TIE";			//무승부
	int GetFindCharCount(CString parm_string, char parm_find_char); //CString -> 배열
	CString GetTextListBox();	//리스트박스에 있는 문자열을 CString으로 읽어오기

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog(); //Dialog 초기화
	void WhoIsWinner(int sum); //승리검정
	void WhoIsLastWinner(void); //최종승자 검정
	void OnSave(void);	//로그 출력
	void OnLoad(void);	//로그 불러오기
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSave();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedReset();
	CListBox m_dol_log;
	CListBox m_timer;
	CListBox m_winner;
	virtual BOOL PreTranslateMessage(MSG* pMsg);	//PreTranslateMessage() 메소드 재정의
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedCancel();
};
