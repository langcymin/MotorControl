
// MotorControl_v1.3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MotorControl_v1.3.h"
#include "MotorControl_v1.3Dlg.h"
#include "afxdialogex.h"
#include "math.h"
#define PI 3.141592


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExec();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EXEC, &CAboutDlg::OnBnClickedButtonExec)
END_MESSAGE_MAP()


void CAboutDlg::OnBnClickedButtonExec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



// CMotorControlv13Dlg 대화 상자



CMotorControlv13Dlg::CMotorControlv13Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOTORCONTROL_V13_DIALOG, pParent)
	, m_a1(0)
	, m_a2(0)
	, m_b1(0)
	, m_b2(0)

	, m_input_no(0)
	, m_input_size(0)
	, m_cheta(0)
	, m_omega_n(0)
	, m_mp(0)
	, m_ts(0)
	, m_Ke(0)
	, m_Kt(0)
	, m_J(0)
	, m_R(0)
	, m_Kd(0)

	, m_Kff0(0)
	, m_Kff1(0)
	, m_Kff2(0)
	, m_Kff3(0)
	, m_Ka(0)
	, m_Kc(0)
	, m_Ffdegree(0)
	, m_Mx(0)
	, m_My(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	samp_num = m_input_no;
	for (int i = 0; i < samp_num; i++)
	{
		real_data[i] = (long)(127.5 * sin((2 * PI / samp_num) * i));
	}

}

void CMotorControlv13Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_GRAPH, m_rect);
	DDX_Text(pDX, IDC_EDIT_A1, m_a1);
	DDX_Text(pDX, IDC_EDIT_A2, m_a2);
	DDX_Text(pDX, IDC_EDIT_B1, m_b1);
	DDX_Text(pDX, IDC_EDIT_B2, m_b2);
	DDX_Text(pDX, IDC_EDIT_INPUT_NO, m_input_no);
	DDX_Text(pDX, IDC_EDIT_INPUT_SIZE, m_input_size);
	DDX_Text(pDX, IDC_EDIT_CHDTA, m_cheta);
	DDX_Text(pDX, IDC_EDIT_FREQ, m_omega_n);
	DDX_Text(pDX, IDC_EDIT_OVER, m_mp);
	DDX_Text(pDX, IDC_EDIT_TS, m_ts);
	DDX_Text(pDX, IDC_EDIT_KE, m_Ke);
	DDX_Text(pDX, IDC_EDIT_KT, m_Kt);
	DDX_Text(pDX, IDC_EDIT_J, m_J);
	DDX_Text(pDX, IDC_EDIT_R, m_R);
	DDX_Text(pDX, IDC_EDIT_KD, m_Kd);
	DDX_Text(pDX, IDC_EDIT_KI, m_Ki);
	DDX_Text(pDX, IDC_EDIT_KP, m_Kp);
	DDX_Control(pDX, IDC_CHECK_SAT, m_sat);
	DDX_Control(pDX, IDC_CHECK_QUANT, m_quant);
	DDX_Control(pDX, IDC_LIST_OUTPUT, m_listOut);
	DDX_Text(pDX, IDC_EDIT_KFF0, m_Kff0);
	DDX_Text(pDX, IDC_EDIT_KFF1, m_Kff1);
	DDX_Text(pDX, IDC_EDIT_KFF2, m_Kff2);
	DDX_Text(pDX, IDC_EDIT_KFF3, m_Kff3);
	DDX_Text(pDX, IDC_EDIT_KA, m_Ka);
	DDX_Text(pDX, IDC_EDIT_KC, m_Kc);
	DDX_CBIndex(pDX, IDC_COMBO_FF_DEGREE, m_Ffdegree);
	DDX_Text(pDX, IDC_EDIT_MOUSE_X, m_Mx);
	DDX_Text(pDX, IDC_EDIT_MOUSE_Y, m_My);
}

BEGIN_MESSAGE_MAP(CMotorControlv13Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_MAIN_GRAPH, &CMotorControlv13Dlg::OnStnClickedMainGraph)
	ON_BN_CLICKED(IDC_BUTTON_EXEC, &CMotorControlv13Dlg::OnBnClickedButtonExec)

	ON_BN_CLICKED(IDC_RADIO_STEP, &CMotorControlv13Dlg::OnBnClickedRadioStep)
	ON_BN_CLICKED(IDC_RADIO_RAMP, &CMotorControlv13Dlg::OnBnClickedRadioRamp)
	ON_BN_CLICKED(IDC_BUTTON_MAKE_REF, &CMotorControlv13Dlg::OnBnClickedButtonMakeRef)
	ON_BN_CLICKED(IDC_BUTTON_MODEL, &CMotorControlv13Dlg::OnBnClickedButtonModel)
	ON_BN_CLICKED(IDC_RADIO_OPEN, &CMotorControlv13Dlg::OnBnClickedRadioOpen)
	ON_BN_CLICKED(IDC_RADIO_CLOSED, &CMotorControlv13Dlg::OnBnClickedRadioClosed)
	ON_BN_CLICKED(IDC_CHECK_SAT, &CMotorControlv13Dlg::OnBnClickedCheckSat)
	ON_BN_CLICKED(IDC_CHECK_QUANT, &CMotorControlv13Dlg::OnBnClickedCheckQuant)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMotorControlv13Dlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_RADIO_PARA, &CMotorControlv13Dlg::OnBnClickedRadioPara)
	ON_BN_CLICKED(IDC_RADIO_SINE, &CMotorControlv13Dlg::OnBnClickedRadioSine)
	ON_BN_CLICKED(IDC_RADIO_FEEDFORWARD, &CMotorControlv13Dlg::OnBnClickedRadioFeedforward)
	ON_BN_CLICKED(IDC_BUTTON_MODELWHOLE, &CMotorControlv13Dlg::OnBnClickedButtonModelwhole)
	ON_BN_CLICKED(IDC_BUTTON_OVERSHOOT, &CMotorControlv13Dlg::OnBnClickedButtonOvershoot)
	ON_CBN_SELCHANGE(IDC_COMBO_FF_DEGREE, &CMotorControlv13Dlg::OnCbnSelchangeComboFfDegree)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMotorControlv13Dlg 메시지 처리기

BOOL CMotorControlv13Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//화면에 그리기 위한 매핑//
	m_rect.GetClientRect(&rect_user);
	rect_user.NormalizeRect();
	m_rect.ClientToScreen(&rect_user);
	ScreenToClient(&rect_user);
	init_graph();
	InitParameter();



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMotorControlv13Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMotorControlv13Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255)); //배경
	dc.FillRect(rect_user, &brush);

	CPen pen2, * pOldpen;
	pen2.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pOldpen = dc.SelectObject(&pen2);
	for (int i = 0; i < samp_num - 1; i++)
	{
		dc.MoveTo(graph_data[i]);
		dc.LineTo(graph_data[i + 1]);
	}
	CPen pen5;
	pen5.CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	pOldpen = dc.SelectObject(&pen5);
	for (int i = 0; i < samp_num - 1; i++)
	{
		dc.MoveTo(graph_data2[i]);
		dc.LineTo(graph_data2[i + 1]);
	}

	CPen pen3;
	int k;
	pen3.CreatePen(PS_DOT, 1, RGB(100, 100, 100));
	pOldpen = dc.SelectObject(&pen3);

	CString y_val;
	CRect y_pos;
	
	k = rect_user.bottom - (rect_user.Height() * (zero_off)) / data_puls;
	y_pos.top = k;
	y_pos.bottom = k + 20;
	y_pos.left = rect_user.left - 40;
	y_pos.right = rect_user.left;

	//중심선
	dc.MoveTo(rect_user.left, k);
	dc.LineTo(rect_user.right, k);
	y_val.Format(_T("%d"), 0);
	dc.DrawText(y_val, y_pos, DT_RIGHT);

	//x축 격자
	CString x_val;
	CRect x_pos;
	x_pos.top = rect_user.bottom;
	x_pos.bottom = x_pos.top + 20;

	for (int j = samp_num / 10; j < samp_num; j = j + (samp_num / 10))
	{
		k = rect_user.left + (rect_user.Width() * j) / samp_num;
		x_pos.left = k - 20;
		x_pos.right = x_pos.left + 40;
		x_val.Format(_T("%d"), j);
		dc.MoveTo(k, rect_user.top);
		dc.LineTo(k, rect_user.bottom);
		dc.DrawText(x_val, x_pos, DT_CENTER);
	}

	//y축 최대/ 최소값 표기
	int i;
	CPen pen4;
	pen4.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pOldpen = dc.SelectObject(&pen4);
	for (i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			k = rect_user.bottom - (rect_user.Height() * (max_data + zero_off)) / data_puls;
			y_val.Format(_T("%d"), max_data);
		}
		else
		{
			k = rect_user.bottom - (rect_user.Height() * (min_data + zero_off)) / data_puls;
			y_val.Format(_T("%d"), min_data);
		}
		y_pos.top = k;
		y_pos.bottom = k + 20;
		dc.MoveTo(rect_user.left, k);
		dc.LineTo(rect_user.right, k);
		dc.SetTextColor(RGB(0, 0, 255));
		dc.DrawText(y_val, y_pos, DT_RIGHT);

	}
	

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMotorControlv13Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMotorControlv13Dlg::OnStnClickedMainGraph()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMotorControlv13Dlg::init_graph()
{
	// TODO: 여기에 구현 코드 추가.
	int margin = 20; //그래프의 margin
	max_data = min_data = real_data[0];
	for (int i = 1; i < samp_num; i++)
	{
		if (real_data[i] > max_data)
			max_data = real_data[i];
		if (real_data[i] < min_data)
			min_data = real_data[i];
	}
	data_puls = max_data - min_data + 2 * margin; //data_puls는 데이터의 진폭
	zero_off = -(min_data - margin);
	for (int i = 0; i < samp_num; i++)
	{
		graph_data[i].x = rect_user.left + rect_user.Width() * i / samp_num;
		graph_data[i].y = rect_user.bottom - rect_user.Height() * (real_data[i] + zero_off) / data_puls;
		graph_data2[i].x = rect_user.left + rect_user.Width() * i / samp_num;
		graph_data2[i].y = rect_user.bottom - rect_user.Height() * (real_data2[i] + zero_off) / data_puls;
	}
}



//실행 버튼
void CMotorControlv13Dlg::OnBnClickedButtonExec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double x[1500], r[1500];
	double Ka = m_Ka;
	double Kc = m_Kc;

	samp_num = m_input_no;
	reference_input_set(input_type, samp_num, r);

	UpdateData(TRUE); //Edit box값 읽어오기

	a1 = m_a1; a2 = m_a2; b1 = m_b1; b2 = m_b2;
	//a1 = -1.8349, a2 = 0.8597, b1 = 0.01272, b2 = 0.01203;
	x[0] = 0.0;
	PlantOut(0.0, 1);

	for (int k = 0; k < samp_num; k++)
	{
		if (control_mode == 0)// 제어모드 open loop인 경우
			x[k + 1] = PlantOut(r[k], 0);

		else // 시뮬레이션 체크박스에 따라 분기됨.
		{
			double ufb;
			ufb = PIDControl(r[k] - x[k]);

			if (control_mode == 2)
				ufb += FeedforwardComp(r[k], kff, k, m_Ffdegree);

			if (saturation == 1)//PWM 최대값
				ufb = sat(ufb, 1500);

			if (quantization == 0)
				x[k + 1] = PlantOut(ufb * Ka, 0) * Kc;

			else
				x[k + 1] =(int)( PlantOut((int)ufb*Ka,0) * Kc);
		}
	}
	for (int i = 0; i < samp_num; i++)
	{
		real_data2[i] = (long)r[i];
		real_data[i] = (long)x[i];
	}
	init_graph();
	Invalidate();
	ChetaOmega();
	ShowListBox(samp_num, r, x);
}

//차분 방정식 계산
double CMotorControlv13Dlg::PlantOut(double r, int reset)
{
	// TODO: 여기에 구현 코드 추가.
	static double x, x1, x2, r1;
	if (reset == 1)
		x1 = x2 = r1 = 0.0;
	x = -a1 * x1 - a2 * x2 + b1 * r + b2 * r1;
	r1 = r;
	x2 = x1;
	x1 = x;
	return x;
}

//기준입력 함수
void CMotorControlv13Dlg::reference_input_set(int itype, int no_of_samples, double* r)
{
	// TODO: 여기에 구현 코드 추가.
	int k;
	if (itype == 0)
		for (k = 0; k < no_of_samples; k++)
			r[k] = (double)m_input_size;
	else if (itype == 1)
		for (k = 0; k < no_of_samples; k++)
			r[k] = (double)k * m_input_size;

	else if (input_type == 2)
	{
		for (k = 0; k < samp_num; k++)
		{
			r[k] = (double)k * k * m_input_size;
		}
	}
	else
	{
		for (k = 0; k < samp_num; k++)
		{
			r[k] = (double)((1 - cos(k * 2.0 * PI / samp_num)) * m_input_size);
		}
	}

	if (quantization == 1)
	{
		for (k = 0; k < samp_num; k++)
		{
			r[k] = (int)r[k];
		}
	}

}









void CMotorControlv13Dlg::InitParameter() //초기값
{
	// TODO: 여기에 구현 코드 추가.
	// 모터 플랜트 파라미터
	m_a1 = -1.8349;
	m_a2 = 0.8597;
	m_b1 = 0.01272;
	m_b2 = 0.01203;

	//모터 물리량
	m_R = 16.4;
	m_J = 3.8e-7;
	m_Ke = 0.032086;
	m_Kt = 0.0321;
	m_Ka = 24.0 / 1500.0;
	m_Kc = 2048 / 2 / 3.141592;

	//라디오버튼 선택하기
	((CButton*)GetDlgItem(IDC_RADIO_STEP))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO_RAMP))->SetCheck(false);

	((CButton*)GetDlgItem(IDC_RADIO_OPEN))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO_CLOSED))->SetCheck(false);
	m_input_no = 100;
	m_input_size = 512;
	input_type = 0;
	control_mode = 0;

	UpdateData(FALSE);
}


void CMotorControlv13Dlg::OnBnClickedRadioStep()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	input_type = 0;
}


void CMotorControlv13Dlg::OnBnClickedRadioRamp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	input_type = 1;
}


void CMotorControlv13Dlg::OnBnClickedButtonMakeRef()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double r[1500 + 1];

	UpdateData(TRUE); //Edit box값 읽어오기
	samp_num = m_input_no;

	reference_input_set(input_type,samp_num,r);

	for (int i = 0; i < samp_num; i++)
	{
		real_data[i] = (long)r[i];
		real_data2[i] = (long)r[i];
	}
	init_graph();
	Invalidate();
}


void CMotorControlv13Dlg::ChetaOmega()
{
	// TODO: 여기에 구현 코드 추가.
	
}

//모델링 버튼
void CMotorControlv13Dlg::OnBnClickedButtonModel() 
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double Tconst, K, m_b = 0.0, T = 0.001;
	double a1, a2, b1, b2;

	UpdateData(TRUE);

	//calculation of continuous model parameters
	Tconst = m_R * m_J / (m_R * m_b + m_Kt * m_Ke);
	K = m_Kt / (m_R * m_b + m_Kt * m_Ke);

	//calculation of plant
	a1 = -(1. + exp(-T / Tconst));
	a2 = exp(-T / Tconst);
	b1 = K * (T - Tconst + Tconst * exp(-T / Tconst));
	b2 = K * (Tconst - (T + Tconst) * exp(-T / Tconst));
	
	m_a1 = a1;
	m_a2 = a2;
	m_b1 = b1;
	m_b2 = b2;

	//FF제어 계산하기
	double theta[4];
	double Ka = m_Ka; 
	double Kc = m_Kc;

	theta[0] = -m_a1; 
	theta[1] = -m_a2; 
	theta[2] = m_b1 * Ka * Kc; 
	theta[3] = m_b2 * Ka * Kc;

	FeedforwardGain(theta, kff);

	m_Kff0 = kff[0];
	m_Kff1 = kff[1];
	m_Kff2 = kff[2];
	m_Kff3 = kff[3];

	UpdateData(FALSE);
}


void CMotorControlv13Dlg::OnBnClickedRadioOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	control_mode = 0;
}


void CMotorControlv13Dlg::OnBnClickedRadioClosed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	control_mode = 1;
}


double CMotorControlv13Dlg::PIDControl(double e)
{
	// TODO: 여기에 구현 코드 추가.
	double up, ui, ud, kp = m_Kp, u, ki = m_Ki, kd = m_Kd;
	static double ui1, e1;

	up = kp * e;
	ui = ui1 + ki * e;
	ud = kd * (e - e1);
	ui1 = ui;
	e1 = e;
	u = up + ui + ud;

	return u;
}


void CMotorControlv13Dlg::OnBnClickedCheckSat()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_sat.GetCheck() == BST_CHECKED)//saturation 체크박스가 체크된 경우
	{
		saturation = 1;
	}

	else
	{
		saturation = 0;
	}

}


void CMotorControlv13Dlg::OnBnClickedCheckQuant()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_quant.GetCheck() == BST_CHECKED)//quanzation 체크박스가 체크된 경우
	{
		quantization = 1;
	}

	else
	{
		quantization = 0;
	}

}


double CMotorControlv13Dlg::sat(double u, double umax)
{
	// TODO: 여기에 구현 코드 추가.
	if (abs(u) > umax)
		u = umax * sgn(u);

	return u;
}


int CMotorControlv13Dlg::sgn(double x)
{
	// TODO: 여기에 구현 코드 추가.
	if (x > 0.0)
		return 1;
	else
		return -1;
}


double CMotorControlv13Dlg::abs(double x)
{
	// TODO: 여기에 구현 코드 추가.
	if (x > 0.0)
		return x;
	else
		return -x;
}


void CMotorControlv13Dlg::ShowListBox(int n, double* r, double* x)
{
	// TODO: 여기에 구현 코드 추가.
	CString str;
	for (int i = 0; i < 1500; i++)
		m_listOut.DeleteString(0);
	for (int i = 0; i < n; i++)
	{
		str.Format(_T("%4d %7.8f %7.8f %6.4f"), i, r[i], x[i], r[i] - x[i]);
		m_listOut.AddString(str);
	}
}


void CMotorControlv13Dlg::OnBnClickedButtonSave()
{
	CString filePath; // 파일 전체 경로를 저장할 변수
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("txt파일(*.txt)|*.txt|모든파일(*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		FILE* fp = nullptr; // 파일 포인터 초기화
		filePath = dlg.GetPathName(); // 사용자가 선택한 전체 파일 경로를 가져옵니다.
		errno_t err = _wfopen_s(&fp, filePath, _T("w")); // 전체 경로를 사용하여 파일 열기

		if (err == 0 && fp != nullptr) { // 파일이 성공적으로 열렸는지 확인
			for (int i = 0; i < samp_num; i++) {
				fprintf(fp, "%d\t%d\t%d\n", i, real_data2[i], real_data[i]); //저장되는 내용
			}
			fclose(fp); // 파일 닫기
		}
		else {
			// 파일 열기 실패 처리
			// 예: 에러 메시지 출력
		}
	}
}


void CMotorControlv13Dlg::OnBnClickedRadioPara()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	input_type = 2;
}


void CMotorControlv13Dlg::OnBnClickedRadioSine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	input_type = 3;
}



//피드포워드 제어기
void CMotorControlv13Dlg::FeedforwardGain(double *theta, double *kff)
{
	// TODO: 여기에 구현 코드 추가.
	kff[0] = (1.0 - theta[0] - theta[1])
		/ (theta[2] + theta[3]);

	kff[1] = ((theta[2] + 2. * theta[3]) * kff[0] + theta[0] + 2. * theta[1])
		/ (theta[2] + theta[3]);

	kff[2] = ((theta[2] + 2. * theta[3]) * kff[1] - theta[3] * kff[0] - theta[1])
		/ (theta[2] + theta[3]);

	for (int i = 3; i <= 3; i++)
	{
		kff[i] = ((theta[2] + 2. * theta[3]) * kff[i - 1] - theta[3] * kff[i - 2])
			/ (theta[2] + theta[3]);
	}


}


void CMotorControlv13Dlg::OnBnClickedRadioFeedforward()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	control_mode = 2;
}


double CMotorControlv13Dlg::FeedforwardComp(double r, double* kff, int k, int m_Ffdegree)
{
	// TODO: 여기에 구현 코드 추가.
	static double u1, u2, u3, u4, u5, uc;

	if(m_Ffdegree==0)
	{
		uc = kff[0] * r;
	}
	else if(m_Ffdegree==1)
	{
		if (k == 0)
			u1 = 0.0;
		uc = kff[0] * r + kff[1] * (r - u1);
		u1 = r;
	}
	else if (m_Ffdegree == 2)
	{
		if (k == 0)
			u1 = u2 = 0.0;
		uc = kff[0] * r + kff[1] * (r - u1) + kff[2] * (r - 2 * u1 + u2);
		u2 = u1;
		u1 = r;
	}
	else if (m_Ffdegree == 3)	//피드포워드 3차인 경우

	{
		if (k == 0)
			u1 = u2 = u3 = 0.0;
		uc = kff[0] * r + kff[1] * (r - u1) + kff[2] * (r - 2 * u1 + u2) + kff[3] * (r - 3 * u1 + 3 * u2 - u3);
		u3 = u2;
		u2 = u1;
		u1 = r;
	}

	else if (m_Ffdegree == 4)
	{
		if (k == 0)
			u1 = u2 = u3 = u4 = 0.0;
		uc = kff[0] * r + kff[1] * (r - u1) + kff[2] * (r - 2 * u1 + u2) + kff[3] * (r - 3 * u1 + 3 * u2 - u3) + kff[4] * (r - 4 * u1 + 4 * u2 - 4 * u3 + u4);
		u4 = u3;
		u3 = u2;
		u2 = u1;
		u1 = r;
	}
	else
	{
		if (k == 0)
			u1 = u2 = u3 = 0.0;
		uc = kff[0] * r + kff[1] * (r - u1) + kff[2] * (r - 2 * u1 + u2) + kff[3] * (r - 3 * u1 + 3 * u2 - u3) + kff[4] * (r - 4 * u1 + 4 * u2 - 4 * u3 + u4) + kff[5] * (r - 5 * u1 + 5 * u2 - 5 * u3 + 5 * u4 -u5);
		u5 = u4;
		u4 = u3;
		u3 = u2;
		u2 = u1;
		u1 = r;
		}

	return uc;
}


void CMotorControlv13Dlg::OnBnClickedButtonModelwhole()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double Tconst, K, m_b = 0.0, T = 0.001;
	double a1, a2, b1, b2;

	UpdateData(TRUE);

	//calculation of continuous model parameters
	Tconst = m_R * m_J / (m_R * m_b + m_Kt * m_Ke);
	K = m_Kt / (m_R * m_b + m_Kt * m_Ke);

	//calculation of plant
	a1 = -(1. + exp(-T / Tconst));
	a2 = exp(-T / Tconst);
	b1 = K * (T - Tconst + Tconst * exp(-T / Tconst));
	b2 = K * (Tconst - (T + Tconst) * exp(-T / Tconst));

	//제어기 포함하여 플랜트 파라미터 다시 계산하기
	b1 = m_Kp * m_Ka * m_Kc * b1;
	b2 = m_Kp * m_Ka * m_Kc * b2;
	a1 = a1+ b1;
	a2 = a2 + b2;

	m_a1 = a1;
	m_a2 = a2;
	m_b1 = b1;
	m_b2 = b2;

	//FF제어 계산하기
	double theta[4];
	double Ka = m_Ka;
	double Kc = m_Kc;

	theta[0] = -m_a1;
	theta[1] = -m_a2;
	theta[2] = m_b1 * Ka * Kc;
	theta[3] = m_b2 * Ka * Kc;

	FeedforwardGain(theta, kff);

	m_Kff0 = kff[0];
	m_Kff1 = kff[1];
	m_Kff2 = kff[2];
	m_Kff3 = kff[3];

	UpdateData(FALSE);
}


void CMotorControlv13Dlg::OnBnClickedButtonOvershoot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double a1, a2, a, b, sigma, omega;
	double cheta, omegan, ts, Mp, T = 0.001;

	double Ka = m_Ka;
	double Kc = m_Kc;


	if (control_mode == 0)//제어모드 open loop인 경우
	{
		a1 = m_a1;
		a2 = m_a2;
	}
	else
	{
		a1 = m_a1 + m_Kp * Ka * Kc * m_b1;
		a2 = m_a2 + m_Kp * Ka * Kc * m_b2;
	}

	a = -a1 / 2.0;
	double temp = 4.0 * a2 - a1 * a1;

	if (temp < 0)
		temp *= -1;

	b = sqrt(temp) / 2.0;
	sigma = -log(a * a + b * b) / T / 2.0;
	omega = atan(b / a) / T;
	omegan = sqrt(sigma * sigma + omega * omega);

	cheta = sigma / omegan;
	Mp = exp(-sigma / omega * 3.141592);
	ts = 4.0 / cheta / omegan;

	m_cheta = cheta;
	m_omega_n = omegan;
	m_mp = Mp;
	m_ts = ts;
	UpdateData(FALSE);
}


void CMotorControlv13Dlg::OnCbnSelchangeComboFfDegree()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CMotorControlv13Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//m_Pos = point;                            //point 를 객체에 대입

	//m_Mx = m_Pos.x;
	//m_My = m_Pos.y;



	CDialogEx::OnMouseMove(nFlags, point);
}
