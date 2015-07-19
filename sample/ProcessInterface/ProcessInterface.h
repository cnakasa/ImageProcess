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
		PE_PROCESS_IMG_FAILED,		// 图像处理异常
		PE_OPEN_PRINTFILE_FAILED,	// 打开文件失败
		PE_CREATE_DATABUFFER_FAILED,// 创建数据缓冲区失败
		PE_OUT_OF_PRINT_RANGE,		// 当前任务超出打印范围
		PE_WAIT_EVENT_OVERTIME,		// 线程等待超时	
		PE_WRITE_MEMORY_FAILED,		// 写内存失败
		PE_DOWNLOADTHREAD_TERMINATE_FAILED,// 写内存线程中断
		PE_COLOR_OFFSET_OUTOF_RANGE,	// 偏移值越界
		PE_LOADIMGDATATHREAD_TERMINATE_FAILED,// 读取图像数据线程中断
		PE_UNKOWN_RIP_FILE_TYPE,	// 不明的RIP文件类型
		PE_HASP_EXPIRED				// 加密狗过期
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

		// 指针
		System::IntPtr^ _handle = System::IntPtr::Zero;
	};

}
