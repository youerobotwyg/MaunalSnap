
// MaunalSnapDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "HCNetSDK.h"
#include "GeneralDef.h"


// CMaunalSnapDlg �Ի���
class CMaunalSnapDlg : public CDialogEx
{
// ����
public:
	CMaunalSnapDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAUNALSNAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_RealtimeList;
	CComboBox	m_comVehicleColor;
	BOOL	m_bOSDClose;
	int		m_iVehicleIndex;
	CString	m_csTrafficLight;
	afx_msg void OnBnClickedBtnManualSnap();

	CIPAddressCtrl	m_ctrlDevIp; //login parameters
	UINT	m_nDevPort;
	CString	m_csUser;
	CString	m_csPWD;
	CTreeCtrl	m_ctrlTreeChan;

	afx_msg void OnBnClickedButtonLogin();

	//logic parameter
	BOOL m_bIsLogin;
	BOOL m_bIsPlaying;
	BOOL m_bIsRecording;
	LOCAL_DEVICE_INFO m_struDeviceInfo;
	HTREEITEM m_hDevItem;

	BOOL DoLogin();
	void DoGetDeviceResoureCfg();
	void CreateDeviceTree();
	void GetDecoderCfg();
	void InitDecoderReferCtrl();

	
	afx_msg void OnBnClickedButtonPlay();
};
