// ProcessInterface.h

#pragma once

//#pragma comment( lib, "../../bin/x64/debug/ImageProcess.lib")
#include "sysdef.h"
#include "imageProcessBase.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

namespace ProcessInterface {

	public enum IMAGEPROCESS_EXCEPTION{
		PE_SUCCESS = 0,
		PE_PROCESS_IMG_FAILED,		// ͼ�����쳣
		PE_OPEN_PRINTFILE_FAILED,	// ���ļ�ʧ��
		PE_CREATE_DATABUFFER_FAILED,// �������ݻ�����ʧ��
		PE_OUT_OF_PRINT_RANGE,		// ��ǰ���񳬳���ӡ��Χ
		PE_WAIT_EVENT_OVERTIME,		// �̵߳ȴ���ʱ	
		PE_WRITE_MEMORY_FAILED,		// д�ڴ�ʧ��
		PE_DOWNLOADTHREAD_TERMINATE_FAILED,// д�ڴ��߳��ж�
		PE_COLOR_OFFSET_OUTOF_RANGE,	// ƫ��ֵԽ��
		PE_LOADIMGDATATHREAD_TERMINATE_FAILED,// ��ȡͼ�������߳��ж�
		PE_UNKOWN_RIP_FILE_TYPE,	// ������RIP�ļ�����
		PE_HASP_EXPIRED				// ���ܹ�����
	};

	public delegate void cProcessPosCallback(int nPos);
	public delegate void cDownloadImageDataToHardware(System::Byte lpWriteData, System::UInt32 uiBufferID, System::UInt32 uiBytes);

	public ref class ImageProcess
	{
	public:
		ImageProcess();
		~ImageProcess();

	public:

		//////////////////////////////////////////////////////////////////////////
		static int CreatePrtPreview(System::String^ sPrtPath, cProcessPosCallback^ pPos);


		////////////////////////////////////////////////////////////////////////////
		////
		//IMAGEPROCESS_EXCEPTION ProcessInit([ref] IntPtr^ lpParam);

		//void UpdateSysInfo([ref] PRINTER sSysInfo, bool bCurTask, bool bInitSys);

		//IMAGEPROCESS_EXCEPTION CleanUp();

		//IMAGEPROCESS_EXCEPTION ProcessImg(int nCount, bool bDir, LPCUR_PASS_INFO pCurPassInfo
		//	, bool bWaitingProcessEnd, ProcessPosCallback callbackPos, DownloadImageDataToHardware downloadData);

		//IMAGEPROCESS_EXCEPTION WaitingForProcessOK(unsigned int dwMilliseconds, LPSMART_PRINT_INFO pSmartPrintInfo);

		//int ProcessInit(PROCESS_PARAM* lpParam);


		//static void CreareProcessObj();
		//static void CDestoryProcessObj();


		//void SetCallback(ProcessPosCallback^ call)
		//{
		//	//SetCallback(_handle, call);
		//}



	private:
		CImgProcessBase* pBase = 0;

		// ָ��
		System::IntPtr^ _handle = System::IntPtr::Zero;
	};

}
