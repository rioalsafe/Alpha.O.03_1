// Alpha.O.02Dlg.cpp: 구현 파일
//
#include <stdio.h>
#include "pch.h"
#include "framework.h"
#include "Alpha.O.02.h"
#include "Alpha.O.02Dlg.h"
#include "afxdialogex.h"
#include "locale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CAlphaO02Dlg 대화 상자


CAlphaO02Dlg::CAlphaO02Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ALPHAO02_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlphaO02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG, m_dol_log);
	DDX_Control(pDX, IDC_WINNER, m_winner);
	DDX_Control(pDX, IDC_TIMER, m_timer);
}

BEGIN_MESSAGE_MAP(CAlphaO02Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SAVE, &CAlphaO02Dlg::OnBnClickedSave)
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_PAUSE, &CAlphaO02Dlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_LOAD, &CAlphaO02Dlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_RESET, &CAlphaO02Dlg::OnBnClickedReset)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDCANCEL, &CAlphaO02Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAlphaO02Dlg 메시지 처리기

BOOL CAlphaO02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAlphaO02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAlphaO02Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic()) {} // 내 어플리케이션이 최소화 되었을 때 이렇게 처리하겠다는 조건문. 지금은 사용 X. 생략! 	} 
	else
	{

		CBrush MyBrush(RGB(248, 207, 143));	 //바둑판 색채우기
		dc.SelectObject(&MyBrush);


		for (int x = 0; x < 18; x++) //19x19 바둑판 그리기
		{
			for (int y = 0; y < 18; y++)
			{
				dc.Rectangle(
					OFFSET + x * WIDTH,
					OFFSET + y * WIDTH,
					OFFSET + WIDTH + 1 + x * WIDTH,
					OFFSET + WIDTH + 1 + y * WIDTH
				);
			}
		}

		dc.SelectStockObject(DC_BRUSH);		//바둑판안에 바둑돌 그리기
		for (int x = 0; x < 19; x++)
		{
			for (int y = 0; y < 19; y++)
			{
				if (dol[y][x]) // 0이면 그리지 않는다.
				{
					dc.SetDCBrushColor(0x00FFFFFF * (dol[y][x] - 1)); // +1한 값을 저장했으니 다시 -1을 하여 step값을 복구한다.
					dc.Ellipse(x * WIDTH + OFFSET - (WIDTH / 2),
						y * WIDTH + OFFSET - (WIDTH / 2),
						x * WIDTH + WIDTH + OFFSET - (WIDTH / 2),
						y * WIDTH + WIDTH + OFFSET - (WIDTH / 2));
				}
			}
		}

	}
}



//좌클릭시 오목돌을 두는 이벤트
void CAlphaO02Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int index_x;
	int index_y;

	index_x = (point.x - OFFSET + (WIDTH / 2)) / WIDTH;
	index_y = (point.y - OFFSET + (WIDTH / 2)) / WIDTH;

	if (pause_count == 0) {
		if (index_x < 19 && index_y < 19 && index_x >= 0 && index_y >= 0 && dol[index_y][index_x] == 0)
		{
			// 타이머 초기화, 타이머리스트 초기화, 제한 시간 입력
			KillTimer(1);
			m_timer.ResetContent();
			turn = TURNTIME;


			if (index_x < 19 && index_y < 19 && index_x >= 0 && index_y >= 0)
			{
				dol[index_y][index_x] = step + 1; // 검은돌이면 0 + 1 , 흰돌이면 1+1 이 들어가게됨.
				InvalidateRect(CRect(index_x * WIDTH - (WIDTH / 2) + OFFSET,
					index_y * WIDTH - (WIDTH / 2) + OFFSET,
					index_x * WIDTH - (WIDTH / 2) + OFFSET + WIDTH,
					index_y * WIDTH - (WIDTH / 2) + OFFSET + WIDTH)); //////////////////////////// OnPaint()

				step = !step;
				PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_RESOURCE | SND_SYNC);
			}
		}
	}
	else AfxMessageBox(_T("정지버튼을 해제해주세요"));


	if (dol[index_y][index_x] != 0) // 오목 승리 판별
	{
		for (int i = 0; i < 5; i++)
		{
			int sum = 0, j = 0;
			for (j = 0; j < 5; j++)
			{
				sum += dol[index_y - 4 + i + j][index_x - 4 + i + j];
				if (dol[index_y - 4 + i + j][index_x - 4 + i + j] == 0) break;
			}
			if (j == 5 && sum == 5) {
				WhoIsWinner(sum);
			}
			else if (sum == 10) {
				WhoIsWinner(sum);
			}
		}
		for (int i = 0; i < 5; i++)
		{
			int sum = 0, j = 0;
			for (j = 0; j < 5; j++)
			{
				sum += dol[index_y + 4 - i - j][index_x - 4 + i + j];
				if (dol[index_y + 4 - i - j][index_x - 4 + i + j] == 0) break;
			}
			if (j == 5 && sum == 5) WhoIsWinner(sum);
			else if (sum == 10) WhoIsWinner(sum);
		}
		for (int i = 0; i < 5; i++)
		{
			int sum = 0, j = 0;
			for (j = 0; j < 5; j++)
			{
				sum += dol[index_y][index_x - 4 + i + j];
				if (dol[index_y][index_x - 4 + i + j] == 0) break;
			}
			if (j == 5 && sum == 5) WhoIsWinner(sum);
			else if (sum == 10) WhoIsWinner(sum);
		}
		for (int i = 0; i < 5; i++)
		{
			int sum = 0, j = 0;
			for (j = 0; j < 5; j++)
			{
				sum += dol[index_y + 4 - i - j][index_x];
				if (dol[index_y + 4 - i - j][index_x] == 0) break;
			}
			if (j == 5 && sum == 5) WhoIsWinner(sum);
			else if (sum == 10) WhoIsWinner(sum);
		}

	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


//좌클릭을 땠을때 타이머 작동
void CAlphaO02Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	int index_x;
	int index_y;

	index_x = (point.x - OFFSET + (WIDTH / 2)) / WIDTH;
	index_y = (point.y - OFFSET + (WIDTH / 2)) / WIDTH;

	if (index_x < 19 && index_y < 19 && index_x >= 0 && index_y >= 0)
	{
		SetTimer(1, 1000, NULL);
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


//정지 버튼 클릭시
void CAlphaO02Dlg::OnBnClickedPause()
{
	KillTimer(1);
	if (pause_count == 0) pause_count = 1;
	else {
		pause_count = 0;  SetTimer(1, 1000, NULL);
	}
}


//저장 버튼 클릭시 이벤트
void CAlphaO02Dlg::OnBnClickedSave()
{
	OnSave();
	//m_winner.ResetContent();
	//m_dol_log.ResetContent();
}

//로그 읽어오기 버튼 클릭시 이벤트
void CAlphaO02Dlg::OnBnClickedLoad()
{
	m_dol_log.ResetContent();
	OnLoad();
}



//승리 메세지 전달
void CAlphaO02Dlg::WhoIsWinner(int sum)
{
	CString strMessage;
	CString strBoxMessage;



	KillTimer(1);	//이겼을시 타이머 종료

	if (sum == 10) {
		//strMessage = L"축하합니다 백돌님이 승리 하셨습니다\r\n";
		white_win_count++;
		m_dol_log.InsertString(-1, wWin);
	}

	else if (sum == 5) {
		//strMessage = L"축하합니다 흑돌님이 승리 하셨습니다\r\n";
		black_win_count++;
		m_dol_log.InsertString(-1, bWin);
	}
	else
		return;

	//최종승자 호출
	WhoIsLastWinner();

	CClientDC dc(this);

	int left = 20 * WIDTH - (WIDTH / 2) + OFFSET;
	dc.DrawText(strMessage, CRect(left, 100, left + 300, 200), DT_SINGLELINE | DT_LEFT);

	strBoxMessage = strMessage + L"한 게임 더 하시겠습니까?";

	if (IDOK == AfxMessageBox(strBoxMessage, MB_OKCANCEL))
	{
		// 승리 판정이 끝나면 화면이 모두 지워지고, 돌의 값이 들어있는 배열도 초기화하여 다음 게임을 진행할 수 있도록 했다. 
		memset(dol, 0, sizeof(int) * 19 * 19);
		Invalidate();
		step = false;
	}
	else
	{
		OnOK();
	}
}

//최종승자 검정
void CAlphaO02Dlg::WhoIsLastWinner()
{
	m_winner.ResetContent();

	if (black_win_count > white_win_count) {
		m_winner.InsertString(-1, bWin);
	}
	else if (white_win_count > black_win_count) {
		m_winner.InsertString(-1, wWin);
	}
	else {
		m_winner.InsertString(-1, Tie);
	}
}



//승리 로그 저장
void CAlphaO02Dlg::OnSave(void)
{

	setlocale(LC_ALL, "");

	CString m_strPath, str;
	FILE* m_pFile;
	TCHAR BASED_CODE szFilter[] = _T("텍스트 파일(*.TXT) | *.TXT;*.txt; | 모든파일(*.*) |*.*|");
	CFileDialog dlg(FALSE, _T("*.txt"), 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if (dlg.DoModal() == IDOK) {
		m_strPath = dlg.GetPathName();

		errno_t err = _tfopen_s(&m_pFile, m_strPath, _T("wt,ccs=UNICODE"));
		if (err != 0) { return; }
		CStdioFile m_File(m_pFile);

		//리스트박스의 텍스트를 한줄씩 txt파일로 작성
		for (int i = 0; i < m_dol_log.GetCount(); ++i) {
			m_dol_log.GetText(i, m_strPath);
			m_strPath += L"\n";
			m_File.Write((LPCTSTR)m_strPath, m_strPath.GetLength() * sizeof(TCHAR));
		}
		m_File.Close();
	}



}

//승리 로그 불러오기
void CAlphaO02Dlg::OnLoad(void)
{
	setlocale(LC_ALL, "");

	m_timer.ResetContent();
	m_winner.ResetContent();
	KillTimer(1);
	//흑 승리카운트, 백 승리카운트 초기화
	black_win_count = 0;
	white_win_count = 0;

	CString display_str, strPath, win_log;
	FILE* m_pFile;
	TCHAR BASED_CODE szFilter[] = _T("텍스트 파일(*.TXT) | *.TXT;*.txt; | 모든파일(*.*) |*.*|");
	CFileDialog dlg(FALSE, _T("*.txt"), 0, OFN_HIDEREADONLY, szFilter);

	//txt파일에서 로그 읽어오기
	if (dlg.DoModal() == IDOK) {
		strPath = dlg.GetPathName();

		errno_t err = _tfopen_s(&m_pFile, strPath, _T("rt,ccs=UNICODE"));
		if (err != 0) { return; }
		CStdioFile m_File(m_pFile);



		while (m_File.ReadString(win_log))
		{
			m_dol_log.AddString(win_log);
		}
		m_File.Close();

	}

	

	//백승리수 흑승리수 찾기

	CString string_dol_log = GetTextListBox();

	white_win_count = GetFindCharCount(string_dol_log, 'H');
	black_win_count = GetFindCharCount(string_dol_log, 'B');

	WhoIsLastWinner();

}

//리스트박스에 있는 문자열을 CString으로 읽어오기
CString CAlphaO02Dlg::GetTextListBox() {

	CString load_dol_log, dol_log_copy;
	int count = m_dol_log.GetCount();

	for (int i = count - 1; i >= 0; i--) {
		m_dol_log.GetText(i, load_dol_log);
		dol_log_copy += load_dol_log;
	}

	return dol_log_copy;
}




//문자열에서 char 찾기
int CAlphaO02Dlg::GetFindCharCount(CString parm_string, char parm_find_char) {
	int length = parm_string.GetLength(), find_count = 0;

	for (int i = 0; i < length; i++)
	{
		if (parm_string[i] == parm_find_char)
		{
			find_count++;
		}
	}
	return find_count;
}


// 타이머 이벤트
void CAlphaO02Dlg::OnTimer(UINT_PTR nIDEvent)
{
	m_timer.ResetContent();	//타이머리스트박스 초기화
	CString timenumber;
	CString wWin;

	switch (nIDEvent)
	{
	case 1: // 타이머(1)
		timenumber.Format(_T(" %d"), turn);
		m_timer.InsertString(0, timenumber);
		turn--;
		break;
	}


	if (turn == -1) {	//타이머시간이 0이 될시 현재 턴 종료
		KillTimer(1);
		//CString wWin = _T("턴이 넘어갑니다");
		//AfxMessageBox(wWin);
		wWin = L"턴이 넘어갑니다";
		if (IDOK == AfxMessageBox(wWin)) SetTimer(1, 1000, NULL);

		m_timer.ResetContent();
		step = !step;
		turn = TURNTIME;
	}

	CDialogEx::OnTimer(nIDEvent);
}



//리셋 버튼
void CAlphaO02Dlg::OnBnClickedReset()
{
	KillTimer(1);
	m_dol_log.ResetContent();
	m_timer.ResetContent();
	m_winner.ResetContent();
	black_win_count = 0;
	white_win_count = 0;
	memset(dol, 0, sizeof(int) * 19 * 19);
	Invalidate();
	step = false;
}

BOOL CAlphaO02Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if (WM_KEYDOWN == pMsg->message)
	{
		if (VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CAlphaO02Dlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	// CDialogEx::OnOK();
}


void CAlphaO02Dlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnCancel();
	step = false;
}


void CAlphaO02Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		//종료버튼 눌릴 시
	}
	else if (nID == SC_MAXIMIZE)
	{
		//최대화 버튼 눌릴 시
	}
	else if (nID == SC_MINIMIZE)
	{
		//최소화 버튼 눌릴 시
	}
	else if (nID == SC_RESTORE)
	{
		//복원 상황에서
	}
	CDialogEx::OnSysCommand(nID, lParam);
}


void CAlphaO02Dlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}