// xve7Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "xve7.h"
#include "xve7Dlg.h"

char fb[0x800010];
const int per=0x800000;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXve7Dlg dialog

CXve7Dlg::CXve7Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXve7Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXve7Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXve7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXve7Dlg)
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXve7Dlg, CDialog)
	//{{AFX_MSG_MAP(CXve7Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXve7Dlg message handlers

BOOL CXve7Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXve7Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXve7Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXve7Dlg::OnOK()
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

     inline void DoEvents(){
        MSG msg; //定义一个MSG类型的变量，不多解释
        while(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) //获取消息并把该消息从消息队列中移除（防止重复响应）。
        {
        DispatchMessage(&msg); //将消息移交给过程函数
        TranslateMessage(&msg);//翻译消息 在合适的机会产生char消息
        }
     }
void CXve7Dlg::disp(char* s){
	CString str;
	m_edit.GetWindowText(str);
	str=CString(s)+str;
	m_edit.SetWindowText(str);
	DoEvents();
}
int CXve7Dlg::conv(const char* fn, BOOL fast){
	int i,l,r,peek[0x400],mn,type=0,pass,mb=0,res;
    char buf[200]={0},bc[200];
    FILE *fin,*fout,*flog=0;
    struct tm *t;
    time_t long_time;
    time( &long_time );
    t = localtime( &long_time );
    sprintf(bc,"开始时间：%4d-%.2d-%.2d %.2d:%.2d:%.2d\r\n", t->tm_year+1900, t->tm_mon, t->tm_mday,t->tm_hour, t->tm_min, t->tm_sec);
	disp(bc);
	if(fast){
		    fin=fopen(fn,"rb+");
    fseek(fin,0x200000,SEEK_SET);
    for(i=0;i<0x400;i++)peek[i]=fgetc(fin);
    mn=('L'-peek[1]+0x100)&0xff;
    if(((peek[1]+mn)&0xff)=='L'&&((peek[2]+mn)&0xff)=='V'){
    sprintf(bc,"打开文件%s\r\n",fn);
	disp(bc);
      disp("格式：flv\r\n");
      disp("--启用1秒转换!--\r\n");
      fseek(fin,0x200000,SEEK_SET);
      fputc('F',fin);
      for(i=1;i<4;i++)fputc((peek[i]+mn)&0xff,fin);
      for(i=0;i<0x3fc;i++){
        r=peek[i+4];
        r=(r+mn)&0xff;
        fputc(r,fin);
      }
      fseek(fin,0x20000A,SEEK_SET);
      fputc(0x20,fin);
      fseek(fin,0,SEEK_SET);
      fputc(0x46,fin);//0
      fputc(0x4C,fin);
      fputc(0x56,fin);
      fputc(0x1,fin);
      fputc(0x5,fin);//4
      fputc(0x0,fin);
      fputc(0x0,fin);
      fputc(0x0,fin);
      fputc(0x9,fin);//8
      fputc(0x0,fin);
      fputc(0x0,fin);
      fputc(0x0,fin);
      fputc(0x0,fin);//C
      fputc(0xFF,fin);
      fputc(0x1F,fin);
      fputc(0xFF,fin);
      fputc(0xF1,fin);//10
      fclose(fin);
      sprintf(buf,"%s.flv",fn);
      if(rename(fn,buf)!=0)disp("文件重命名失败，请手动改为.flv扩展名，或检查系统权限\r\n");
      disp("转换完成\r\n");
	  goto fastexit;
    }else disp("非flv格式，不能转换，切换到普通模式\r\n");
	}
    l=strlen(fn);
    strcpy(buf,fn);
    fin=fopen(fn,"rb");
    sprintf(bc,"打开文件%s\r\n",fn);
	disp(bc);
    for(i=0;i<=0x200000;i++)fb[i]=(char)fgetc(fin);
    for(i=0;i<0x4;i++){
      peek[i]=r;
      r=fgetc(fin);
    }
    mn=('R'-peek[1]+0x100)&0xff;
    if(((peek[1]+mn)&0xff)=='R'&&((peek[2]+mn)&0xff)=='M'&&((peek[3]+mn)&0xff)=='F'){
      sprintf(bc,"格式：rm/rmvb  Magic Number = %d\r\n",mn);
//      if(flog)fprintf(flog,"格式：rm/rmvb  Magic Number = %d\r\n",mn);
      type=1;
    }else{
      mn=(0x26-peek[1]+0x100)&0xff;
      if(((peek[2]+mn)&0xff)==0xb2&&((peek[3]+mn)&0xff)==0x75){
        sprintf(bc,"格式：wmv  Magic Number = %d\r\n",mn);
//        if(flog)fprintf(flog,"格式：wmv  Magic Number = %d\r\n",mn);
        type=2;
      }else{
        mn=('L'-peek[1]+0x100)&0xff;
        if(((peek[1]+mn)&0xff)=='L'&&((peek[2]+mn)&0xff)=='V'){
          sprintf(bc,"格式：flv  Magic Number = %d\r\n",mn);
//          if(flog)fprintf(flog,"格式：flv  Magic Number = %d\r\n",mn);
          type=3;
        }else{
          mn=('I'-peek[1]+0x100)&0xff;
          if(((peek[1]+mn)&0xff)=='I'&&((peek[2]+mn)&0xff)=='F'&&((peek[3]+mn)&0xff)=='F'){
            sprintf(bc,"格式：avi  Magic Number = %d\r\n",mn);
//            if(flog)fprintf(flog,"格式：avi  Magic Number = %d\r\n",mn);
            type=4;
          }else{
            mn=(-peek[1]+0x100)&0xff;
            if(((peek[1]+mn)&0xff)==0&&((peek[2]+mn)&0xff)==0){
              sprintf(bc,"格式：mp4?  Magic Number = %d\r\n",mn);
//              if(flog)fprintf(flog,"格式：mp4?  Magic Number = %d\r\n",mn);
              type=5;
            }else{
              mn=(-peek[1]+0x100)&0xff;
              if(((peek[1]+mn)&0xff)==0&&((peek[2]+mn)&0xff)==1&&((peek[3]+mn)&0xff)==0xBA){
                sprintf(bc,"格式：mpeg  Magic Number = %d\r\n",mn);
//                if(flog)fprintf(flog,"格式：mpeg  Magic Number = %d\r\n",mn);
                type=6;
              }else{
                mn=(0x45-peek[1]+0x100)&0xff;
                if(((peek[1]+mn)&0xff)==0x45&&((peek[2]+mn)&0xff)==0xDF&&((peek[3]+mn)&0xff)==0xA3){
                  sprintf(bc,"格式：mkv  Magic Number = %d\r\n",mn);
//                  if(flog)fprintf(flog,"格式：mkv  Magic Number = %d\r\n",mn);
                  type=7;
                }else{
                  sprintf(buf,"%s1",fn);
                  fout=fopen(buf,"wb");
                  for(i=0;i<0x200000;i++)fputc(fb[i],fout);
                  for(i=0;i<4;i++)fputc(peek[i],fout);
                  fputc(r,fout);
                  for(i=0;i<0x100000;i++)fputc(fgetc(fin),fout);
                  fclose(fin);
                  fclose(fout);
                  sprintf(bc,"格式无法识别，请将目标文件下生成的错误信息文件%s发给作者，以便及时解决问题。\r\n注：该文件为xv文件的前3MB内容，不含有任何涉及您的隐私的信息。\r\n作者的电子邮件：692827763@qq.com\r\n请注明迅雷看看版本号。\r\n",buf);
				  disp(bc);
                  return 0;
                }
              }
            }
          }
        }
      }
    }
	disp(bc);
    if(type==1)strcat(buf,".rmvb");
    else if(type==2)strcat(buf,".wmv");
    else if(type==3)strcat(buf,".flv");
    else if(type==4)strcat(buf,".avi");
    else if(type==5)strcat(buf,".mp4");
    else if(type==6)strcat(buf,".mpg");
    else if(type==7)strcat(buf,".mkv");
    fout=fopen(buf,"wb");
    sprintf(bc,"打开了输出文件：%s\r\n",buf);
	disp(bc);
//    if(flog)fprintf(flog,"打开了输出文件：%s\r\n",buf);
    if(type==1)fputc('.',fout);
    else if(type==1)fputc('.',fout);
    else if(type==2)fputc(0x30,fout);
    else if(type==3)fputc('F',fout);
    else if(type==4)fputc('R',fout);
    else if(type==5)fputc(0,fout);
    else if(type==6)fputc(0,fout);
    else if(type==7)fputc(0x1A,fout);
    for(i=1;i<4;i++)fputc((peek[i]+mn)&0xff,fout);
    for(i=0;i<0x3fc;i++){
      r=(r+mn)&0xff;
      fputc(r,fout);
      r=fgetc(fin);
    }
    pass=0x400;
    fputc(r,fout);
    while(1){
      res=fread(fb,1,per,fin);
      if(res==0)break;
      fwrite(fb,1,res,fout);
      pass+=res;
      mb+=pass/0x100000;
      pass%=0x100000;
      sprintf(bc,"已完成 %d 兆\r\n",mb);
	  disp(bc);
    }
	if(type==3){
	      fseek(fout,0xA,SEEK_SET);
      fputc(0x0,fout);
	}
    fclose(fin);
    fclose(fout);
fastexit:
    time( &long_time );
    t = localtime( &long_time );
    sprintf(bc,"结束时间：%4d-%.2d-%.2d %.2d:%.2d:%.2d\r\n", t->tm_year+1900, t->tm_mon, t->tm_mday,t->tm_hour, t->tm_min, t->tm_sec);
	disp(bc);
	return 0;
}
void CXve7Dlg::OnCancel()
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

void CXve7Dlg::OnButton1()
{
	// TODO: Add your control notification handler code here

	CFileDialog dlg(TRUE,_T("xv文件"),NULL,OFN_ALLOWMULTISELECT,_T("xv文件|*.xv|转换失败的flv文件|*.flv|所有文件|*.*"));
	        DWORD   MAXFILE   =   100000;
            dlg.m_ofn.nMaxFile   =   MAXFILE;
            char*   pc   =   new   char[MAXFILE];
            dlg.m_ofn.lpstrFile   =   pc;
            dlg.m_ofn.lpstrFile[0]   =   NULL;
	if(dlg.DoModal()==IDOK){
		this->m_list.ResetContent();
		POSITION po=dlg.GetStartPosition();
		while(po)this->m_list.AddString(dlg.GetNextPathName(po));
	}
}

void CXve7Dlg::OnButton2()
{
	// TODO: Add your control notification handler code here

	CString str("");
	m_edit.SetWindowText(str);
	DoEvents();
	for(int i=0;i<m_list.GetCount();i++){
		CString s;
		m_list.GetText(i,s);
		conv((LPCSTR)s,FALSE);
	}
	MessageBox("全部完成！");
}

void CXve7Dlg::OnButton3()
{
	// TODO: Add your control notification handler code here

	CString str("");
	m_edit.SetWindowText(str);
	DoEvents();
	for(int i=0;i<m_list.GetCount();i++){
		CString s;
		m_list.GetText(i,s);
		conv((LPCSTR)s,TRUE);
	}
	MessageBox("全部完成！");
}
