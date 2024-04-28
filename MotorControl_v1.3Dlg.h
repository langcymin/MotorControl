
// MotorControl_v1.3Dlg.h: 헤더 파일
//

#pragma once


// CMotorControlv13Dlg 대화 상자
class CMotorControlv13Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMotorControlv13Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOTORCONTROL_V13_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//기본 그래프 그리기
	afx_msg void OnStnClickedMainGraph();
	CStatic m_rect;
	CRect rect_user;
	long real_data[1500];
	CPoint graph_data[1500];
	int samp_num;
	int data_puls;
	int zero_off;
	void init_graph();
	int max_data;
	int min_data;

	//실행버튼
	afx_msg void OnBnClickedButtonExec();
	double a1,a2,b1,b2;

	double PlantOut(double r,int reset);
	void reference_input_set(int itype, int no_of_samples, double* r);

	//기준입력(초록점선)
	long real_data2[1500];
	CPoint graph_data2[1500];

	//플랜트 파라미터 관련
	double m_a1;
	double m_a2;
	double m_b1;
	double m_b2;

	//초기입력값
	void InitParameter();

	//기준입력 관련
	int m_input_no;
	int m_input_size;
	int input_type;
	afx_msg void OnBnClickedRadioStep();
	afx_msg void OnBnClickedRadioRamp();
	afx_msg void OnBnClickedButtonMakeRef();

	//과도응답 관련
	double m_cheta;
	double m_omega_n;
	double m_mp;
	double m_ts;
	void ChetaOmega();

	//모터물리량 관련
	double m_Ke;
	double m_Kt;
	double m_J;
	double m_R;
	afx_msg void OnBnClickedButtonModel();

	//제어모드, 제어게인 및 PID 제어 관련
	int control_mode;
	afx_msg void OnBnClickedRadioOpen();
	afx_msg void OnBnClickedRadioClosed();
	double m_Kd;
	double m_Ki;
	double m_Kp;
	double PIDControl(double e);

	//시뮬레이션 관련
	CButton m_sat;
	CButton m_quant;
	afx_msg void OnBnClickedCheckSat();
	afx_msg void OnBnClickedCheckQuant();
	int saturation;
	int quantization;
	double sat(double u, double umax);
	int sgn(double x);
	double abs(double x);

	//저장 관련
	CListBox m_listOut;
	void ShowListBox(int n, double* r, double* x);
	afx_msg void OnBnClickedButtonSave();

	//피드포워드 제어 관련
	afx_msg void OnBnClickedRadioPara();
	afx_msg void OnBnClickedRadioSine();
	double kff[5];
	void FeedforwardGain(double *theta,double *kff);
	double m_Kff0;
	double m_Kff1;
	double m_Kff2;
	double m_Kff3;
	afx_msg void OnBnClickedRadioFeedforward();
	double FeedforwardComp(double r, double* kff, int k, int m_Ffdegree);
	double m_Ka;
	double m_Kc;
	afx_msg void OnBnClickedButtonModelwhole();
	afx_msg void OnBnClickedButtonOvershoot();
	int m_Ffdegree;
	afx_msg void OnCbnSelchangeComboFfDegree();

	CPoint m_Pos;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	double m_Mx;
	double m_My;
};
