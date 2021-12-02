// Alpha.O.02Dlg.cpp: ���� ����
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



// CAlphaO02Dlg ��ȭ ����


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


// CAlphaO02Dlg �޽��� ó����

BOOL CAlphaO02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���ø����̼��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CAlphaO02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAlphaO02Dlg::OnPaint()
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

	if (IsIconic()) {} // �� ���ø����̼��� �ּ�ȭ �Ǿ��� �� �̷��� ó���ϰڴٴ� ���ǹ�. ������ ��� X. ����! 	} 
	else
	{

		CBrush MyBrush(RGB(248, 207, 143));	 //�ٵ��� ��ä���
		dc.SelectObject(&MyBrush);


		for (int x = 0; x < 18; x++) //19x19 �ٵ��� �׸���
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

		dc.SelectStockObject(DC_BRUSH);		//�ٵ��Ǿȿ� �ٵϵ� �׸���
		for (int x = 0; x < 19; x++)
		{
			for (int y = 0; y < 19; y++)
			{
				if (dol[y][x]) // 0�̸� �׸��� �ʴ´�.
				{
					dc.SetDCBrushColor(0x00FFFFFF * (dol[y][x] - 1)); // +1�� ���� ���������� �ٽ� -1�� �Ͽ� step���� �����Ѵ�.
					dc.Ellipse(x * WIDTH + OFFSET - (WIDTH / 2),
						y * WIDTH + OFFSET - (WIDTH / 2),
						x * WIDTH + WIDTH + OFFSET - (WIDTH / 2),
						y * WIDTH + WIDTH + OFFSET - (WIDTH / 2));
				}
			}
		}

	}
}



//��Ŭ���� ������ �δ� �̺�Ʈ
void CAlphaO02Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int index_x;
	int index_y;

	index_x = (point.x - OFFSET + (WIDTH / 2)) / WIDTH;
	index_y = (point.y - OFFSET + (WIDTH / 2)) / WIDTH;

	if (pause_count == 0) {
		if (index_x < 19 && index_y < 19 && index_x >= 0 && index_y >= 0 && dol[index_y][index_x] == 0)
		{
			// Ÿ�̸� �ʱ�ȭ, Ÿ�̸Ӹ���Ʈ �ʱ�ȭ, ���� �ð� �Է�
			KillTimer(1);
			m_timer.ResetContent();
			turn = TURNTIME;


			if (index_x < 19 && index_y < 19 && index_x >= 0 && index_y >= 0)
			{
				dol[index_y][index_x] = step + 1; // �������̸� 0 + 1 , ���̸� 1+1 �� ���Ե�.
				InvalidateRect(CRect(index_x * WIDTH - (WIDTH / 2) + OFFSET,
					index_y * WIDTH - (WIDTH / 2) + OFFSET,
					index_x * WIDTH - (WIDTH / 2) + OFFSET + WIDTH,
					index_y * WIDTH - (WIDTH / 2) + OFFSET + WIDTH)); //////////////////////////// OnPaint()

				step = !step;
				PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_RESOURCE | SND_SYNC);
			}
		}
	}
	else AfxMessageBox(_T("������ư�� �������ּ���"));


	if (dol[index_y][index_x] != 0) // ���� �¸� �Ǻ�
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


//��Ŭ���� ������ Ÿ�̸� �۵�
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


//���� ��ư Ŭ����
void CAlphaO02Dlg::OnBnClickedPause()
{
	KillTimer(1);
	if (pause_count == 0) pause_count = 1;
	else {
		pause_count = 0;  SetTimer(1, 1000, NULL);
	}
}


//���� ��ư Ŭ���� �̺�Ʈ
void CAlphaO02Dlg::OnBnClickedSave()
{
	OnSave();
	//m_winner.ResetContent();
	//m_dol_log.ResetContent();
}

//�α� �о���� ��ư Ŭ���� �̺�Ʈ
void CAlphaO02Dlg::OnBnClickedLoad()
{
	m_dol_log.ResetContent();
	OnLoad();
}



//�¸� �޼��� ����
void CAlphaO02Dlg::WhoIsWinner(int sum)
{
	CString strMessage;
	CString strBoxMessage;



	KillTimer(1);	//�̰����� Ÿ�̸� ����

	if (sum == 10) {
		//strMessage = L"�����մϴ� �鵹���� �¸� �ϼ̽��ϴ�\r\n";
		white_win_count++;
		m_dol_log.InsertString(-1, wWin);
	}

	else if (sum == 5) {
		//strMessage = L"�����մϴ� �浹���� �¸� �ϼ̽��ϴ�\r\n";
		black_win_count++;
		m_dol_log.InsertString(-1, bWin);
	}
	else
		return;

	//�������� ȣ��
	WhoIsLastWinner();

	CClientDC dc(this);

	int left = 20 * WIDTH - (WIDTH / 2) + OFFSET;
	dc.DrawText(strMessage, CRect(left, 100, left + 300, 200), DT_SINGLELINE | DT_LEFT);

	strBoxMessage = strMessage + L"�� ���� �� �Ͻðڽ��ϱ�?";

	if (IDOK == AfxMessageBox(strBoxMessage, MB_OKCANCEL))
	{
		// �¸� ������ ������ ȭ���� ��� ��������, ���� ���� ����ִ� �迭�� �ʱ�ȭ�Ͽ� ���� ������ ������ �� �ֵ��� �ߴ�. 
		memset(dol, 0, sizeof(int) * 19 * 19);
		Invalidate();
		step = false;
	}
	else
	{
		OnOK();
	}
}

//�������� ����
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



//�¸� �α� ����
void CAlphaO02Dlg::OnSave(void)
{

	setlocale(LC_ALL, "");

	CString m_strPath, str;
	FILE* m_pFile;
	TCHAR BASED_CODE szFilter[] = _T("�ؽ�Ʈ ����(*.TXT) | *.TXT;*.txt; | �������(*.*) |*.*|");
	CFileDialog dlg(FALSE, _T("*.txt"), 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if (dlg.DoModal() == IDOK) {
		m_strPath = dlg.GetPathName();

		errno_t err = _tfopen_s(&m_pFile, m_strPath, _T("wt,ccs=UNICODE"));
		if (err != 0) { return; }
		CStdioFile m_File(m_pFile);

		//����Ʈ�ڽ��� �ؽ�Ʈ�� ���پ� txt���Ϸ� �ۼ�
		for (int i = 0; i < m_dol_log.GetCount(); ++i) {
			m_dol_log.GetText(i, m_strPath);
			m_strPath += L"\n";
			m_File.Write((LPCTSTR)m_strPath, m_strPath.GetLength() * sizeof(TCHAR));
		}
		m_File.Close();
	}



}

//�¸� �α� �ҷ�����
void CAlphaO02Dlg::OnLoad(void)
{
	setlocale(LC_ALL, "");

	m_timer.ResetContent();
	m_winner.ResetContent();
	KillTimer(1);
	//�� �¸�ī��Ʈ, �� �¸�ī��Ʈ �ʱ�ȭ
	black_win_count = 0;
	white_win_count = 0;

	CString display_str, strPath, win_log;
	FILE* m_pFile;
	TCHAR BASED_CODE szFilter[] = _T("�ؽ�Ʈ ����(*.TXT) | *.TXT;*.txt; | �������(*.*) |*.*|");
	CFileDialog dlg(FALSE, _T("*.txt"), 0, OFN_HIDEREADONLY, szFilter);

	//txt���Ͽ��� �α� �о����
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

	

	//��¸��� ��¸��� ã��

	CString string_dol_log = GetTextListBox();

	white_win_count = GetFindCharCount(string_dol_log, 'H');
	black_win_count = GetFindCharCount(string_dol_log, 'B');

	WhoIsLastWinner();

}

//����Ʈ�ڽ��� �ִ� ���ڿ��� CString���� �о����
CString CAlphaO02Dlg::GetTextListBox() {

	CString load_dol_log, dol_log_copy;
	int count = m_dol_log.GetCount();

	for (int i = count - 1; i >= 0; i--) {
		m_dol_log.GetText(i, load_dol_log);
		dol_log_copy += load_dol_log;
	}

	return dol_log_copy;
}




//���ڿ����� char ã��
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


// Ÿ�̸� �̺�Ʈ
void CAlphaO02Dlg::OnTimer(UINT_PTR nIDEvent)
{
	m_timer.ResetContent();	//Ÿ�̸Ӹ���Ʈ�ڽ� �ʱ�ȭ
	CString timenumber;
	CString wWin;

	switch (nIDEvent)
	{
	case 1: // Ÿ�̸�(1)
		timenumber.Format(_T(" %d"), turn);
		m_timer.InsertString(0, timenumber);
		turn--;
		break;
	}


	if (turn == -1) {	//Ÿ�̸ӽð��� 0�� �ɽ� ���� �� ����
		KillTimer(1);
		//CString wWin = _T("���� �Ѿ�ϴ�");
		//AfxMessageBox(wWin);
		wWin = L"���� �Ѿ�ϴ�";
		if (IDOK == AfxMessageBox(wWin)) SetTimer(1, 1000, NULL);

		m_timer.ResetContent();
		step = !step;
		turn = TURNTIME;
	}

	CDialogEx::OnTimer(nIDEvent);
}



//���� ��ư
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
		//�����ư ���� ��
	}
	else if (nID == SC_MAXIMIZE)
	{
		//�ִ�ȭ ��ư ���� ��
	}
	else if (nID == SC_MINIMIZE)
	{
		//�ּ�ȭ ��ư ���� ��
	}
	else if (nID == SC_RESTORE)
	{
		//���� ��Ȳ����
	}
	CDialogEx::OnSysCommand(nID, lParam);
}


void CAlphaO02Dlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}