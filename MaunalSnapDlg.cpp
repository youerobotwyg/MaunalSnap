
// MaunalSnapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MaunalSnap.h"
#include "MaunalSnapDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMaunalSnapDlg �Ի���



CMaunalSnapDlg::CMaunalSnapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMaunalSnapDlg::IDD, pParent)
	, m_iVehicleIndex(0)
	, m_csTrafficLight(_T(""))
{

	m_nDevPort = 8000;
	m_csUser = _T("admin");
	m_csPWD = _T("sfijdl0727");

	//login parameters
	m_bIsLogin = FALSE;
	m_bIsPlaying = FALSE;
	m_bIsRecording = FALSE;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMaunalSnapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REALTIME_LIST, m_RealtimeList);
	DDX_Control(pDX, IDC_COMBO_VEHICLE_COLOR, m_comVehicleColor);
	DDX_Check(pDX, IDC_CHECK_CLOSE_OSD, m_bOSDClose);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_INDEX, m_iVehicleIndex);
	DDX_Text(pDX, IDC_EDIT_TRAFFIC_LIGHT, m_csTrafficLight);

	DDX_Control(pDX, IDC_IPADDRESS_DEV, m_ctrlDevIp);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nDevPort);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUser);
	DDX_Text(pDX, IDC_EDIT_PWD, m_csPWD);
	DDX_Control(pDX, IDC_TREE_CHAN, m_ctrlTreeChan);
}

BEGIN_MESSAGE_MAP(CMaunalSnapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MANUAL_SNAP, &CMaunalSnapDlg::OnBnClickedBtnManualSnap)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMaunalSnapDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CMaunalSnapDlg::OnBnClickedButtonPlay)
END_MESSAGE_MAP()


// CMaunalSnapDlg ��Ϣ�������

BOOL CMaunalSnapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_ctrlDevIp.SetAddress(192, 168, 1, 64);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMaunalSnapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMaunalSnapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMaunalSnapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMaunalSnapDlg::OnBnClickedBtnManualSnap()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMaunalSnapDlg::OnBnClickedButtonLogin()
{
	if (!m_bIsLogin)    //login
	{
		if (!DoLogin())
			return;
		DoGetDeviceResoureCfg();  //��ȡ�豸��Դ��Ϣ	
		CreateDeviceTree();        //����ͨ����
		GetDecoderCfg();                           //��ȡ��̨��������Ϣ
		InitDecoderReferCtrl();         //��ʼ����������ؿؼ�      
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("Logout");
		m_bIsLogin = TRUE;

	}
	else      //logout
	{


		if (m_bIsPlaying || m_bIsRecording)
		{
			MessageBox("Stop Play or record first!");
			return;
		}
		NET_DVR_Logout_V30(m_struDeviceInfo.lLoginID);
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("Login");
		m_ctrlTreeChan.DeleteAllItems();
		m_struDeviceInfo.lLoginID = -1;
		m_bIsLogin = FALSE;
	}


}

/*************************************************
������:    	DoLogin
��������:	���豸ע��
�������:
�������:
����ֵ:
**************************************************/
BOOL CMaunalSnapDlg::DoLogin()
{
// 	//-------------V30---------------------------------
// 	UpdateData(TRUE);
// 	CString DeviceIp;
// 	BYTE nField0, nField1, nField2, nField3;
// 	m_ctrlDevIp.GetAddress(nField0, nField1, nField2, nField3);
// 	DeviceIp.Format("%d.%d.%d.%d", nField0, nField1, nField2, nField3);
// 
// 	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
// 	memset(&DeviceInfoTmp, 0, sizeof(NET_DVR_DEVICEINFO_V30));
// 
// 	LONG lLoginID = NET_DVR_Login_V30(DeviceIp.GetBuffer(DeviceIp.GetLength()), m_nDevPort, \
// 		m_csUser.GetBuffer(m_csUser.GetLength()), m_csPWD.GetBuffer(m_csPWD.GetLength()), &DeviceInfoTmp);
// 	if (lLoginID == -1)
// 	{
// 		MessageBox("Login to Device failed!\n");
// 		return FALSE;
// 	}
// 	m_struDeviceInfo.lLoginID = lLoginID;
// 	m_struDeviceInfo.iDeviceChanNum = DeviceInfoTmp.byChanNum;
// 	m_struDeviceInfo.iIPChanNum = DeviceInfoTmp.byIPChanNum;
// 	m_struDeviceInfo.iStartChan = DeviceInfoTmp.byStartChan;
// 	m_struDeviceInfo.iIPStartChan = DeviceInfoTmp.byStartDChan;
// 	return TRUE;

	//--------------V40----------------------------------
	UpdateData(TRUE);
	NET_DVR_USER_LOGIN_INFO struLoginInfo = { 0 };
	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = { 0 };
	CString DeviceIp;
	BYTE nField0, nField1, nField2, nField3;
	m_ctrlDevIp.GetAddress(nField0, nField1, nField2, nField3);
	DeviceIp.Format("%d.%d.%d.%d", nField0, nField1, nField2, nField3);

	struLoginInfo.wPort = m_nDevPort;
	memcpy(struLoginInfo.sDeviceAddress, DeviceIp, NET_DVR_DEV_ADDRESS_MAX_LEN);
	memcpy(struLoginInfo.sUserName, m_csUser, NAME_LEN);
	memcpy(struLoginInfo.sPassword, m_csPWD, NAME_LEN);
	//struLoginInfo.byUseTransport = 1;
	//struLoginInfo.byRes3[119] = 2;

	//DEBUG
	//struLoginInfo.byHttps = 2;
	//struLoginInfo.byLoginMode = 2;

	//        struLoginInfo.byVerifyMode = 2;
	LONG lLoginID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

	return TRUE;
}

void CMaunalSnapDlg::DoGetDeviceResoureCfg()
{
	NET_DVR_IPPARACFG_V40 IpAccessCfg;
	memset(&IpAccessCfg, 0, sizeof(IpAccessCfg));
	DWORD  dwReturned;

	m_struDeviceInfo.bIPRet = NET_DVR_GetDVRConfig(m_struDeviceInfo.lLoginID, NET_DVR_GET_IPPARACFG_V40, 0, &IpAccessCfg, sizeof(NET_DVR_IPPARACFG_V40), &dwReturned);

	int i;
	if (!m_struDeviceInfo.bIPRet)   //��֧��ip����,9000�����豸��֧�ֽ���ģ��ͨ��
	{
		for (i = 0; i < MAX_ANALOG_CHANNUM; i++)
		{
			if (i < m_struDeviceInfo.iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo.struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo.iStartChan);
				m_struDeviceInfo.struChanInfo[i].iChanIndex = i + m_struDeviceInfo.iStartChan;  //ͨ����
				m_struDeviceInfo.struChanInfo[i].bEnable = TRUE;

			}
			else
			{
				m_struDeviceInfo.struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo.struChanInfo[i].bEnable = FALSE;
				sprintf_s(m_struDeviceInfo.struChanInfo[i].chChanName, "");
			}
		}
	}
	else        //֧��IP���룬9000�豸
	{
		for (i = 0; i < MAX_ANALOG_CHANNUM; i++)  //ģ��ͨ��
		{
			if (i < m_struDeviceInfo.iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo.struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo.iStartChan);
				m_struDeviceInfo.struChanInfo[i].iChanIndex = i + m_struDeviceInfo.iStartChan;
				if (IpAccessCfg.byAnalogChanEnable[i])
				{
					m_struDeviceInfo.struChanInfo[i].bEnable = TRUE;
				}
				else
				{
					m_struDeviceInfo.struChanInfo[i].bEnable = FALSE;
				}

			}
			else//clear the state of other channel
			{
				m_struDeviceInfo.struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo.struChanInfo[i].bEnable = FALSE;
				sprintf_s(m_struDeviceInfo.struChanInfo[i].chChanName, "");
			}
		}

		//����ͨ��
		for (i = 0; i < MAX_IP_CHANNEL; i++)
		{
			if (IpAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byEnable)  //ipͨ������
			{
				m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = TRUE;
				m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = i + IpAccessCfg.dwStartDChan;
				sprintf_s(m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].chChanName, "IP Camera %d", i + 1);

			}
			else
			{
				m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = FALSE;
				m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = -1;
			}
		}


	}

}

/*************************************************
������:    	CreateDeviceTree
��������:	����ͨ����
�������:
�������:
����ֵ:
**************************************************/
void CMaunalSnapDlg::CreateDeviceTree()
{
	m_hDevItem = m_ctrlTreeChan.InsertItem("Dev");
	m_ctrlTreeChan.SetItemData(m_hDevItem, DEVICETYPE * 1000);
	for (int i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (m_struDeviceInfo.struChanInfo[i].bEnable)  //ͨ����Ч������ͨ����
		{
			HTREEITEM ChanItem = m_ctrlTreeChan.InsertItem(m_struDeviceInfo.struChanInfo[i].chChanName, m_hDevItem);
			m_ctrlTreeChan.SetItemData(ChanItem, CHANNELTYPE * 1000 + i);   //Data��Ӧͨ���������е�����
		}
	}
	m_ctrlTreeChan.Expand(m_hDevItem, TVE_EXPAND);
}

/*************************************************
������:    	GetDecoderCfg
��������:	��ȡ��̨��������Ϣ
�������:
�������:
����ֵ:
**************************************************/
void CMaunalSnapDlg::GetDecoderCfg()
{
	NET_DVR_DECODERCFG_V30 DecoderCfg;
	DWORD  dwReturned;
	BOOL bRet;


	//��ȡͨ����������Ϣ
	for (int i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (m_struDeviceInfo.struChanInfo[i].bEnable)
		{
			memset(&DecoderCfg, 0, sizeof(NET_DVR_DECODERCFG_V30));
			bRet = NET_DVR_GetDVRConfig(m_struDeviceInfo.lLoginID, NET_DVR_GET_DECODERCFG_V30, \
				m_struDeviceInfo.struChanInfo[i].iChanIndex, &DecoderCfg, sizeof(NET_DVR_DECODERCFG_V30), &dwReturned);
			if (!bRet)
			{
				TRACE("Get DecderCfg failed,Chan:%d\n", m_struDeviceInfo.struChanInfo[i].iChanIndex);
				continue;
			}

			memcpy(&m_struDeviceInfo.struChanInfo[i].struDecodercfg, &DecoderCfg, sizeof(NET_DVR_DECODERCFG_V30));
		}

	}

}

/*************************************************
������:    	InitDecoderReferCtrl
��������:	��ʼ����̨������ؿؼ�
�������:
�������:
����ֵ:
**************************************************/
void CMaunalSnapDlg::InitDecoderReferCtrl()
{


}


void CMaunalSnapDlg::OnBnClickedButtonPlay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}
