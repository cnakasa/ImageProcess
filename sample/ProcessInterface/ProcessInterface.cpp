// 这是主 DLL 文件。

#include "stdafx.h"
#include "windows.h"
#include <vcclr.h>
#include "ProcessInterface.h"

ProcessInterface::ImageProcess::ImageProcess()
{
	pBase = CreareImageProcessObj();
}

ProcessInterface::ImageProcess::~ImageProcess()
{
	CDestoryImageProcessObj(pBase);
}

int ProcessInterface::ImageProcess::CreatePrtPreview(System::String^ sPrtPath, cProcessPosCallback^ pPos)
{
	// 将string转换成C++能识别的指针
	pin_ptr<const wchar_t> pPrtPath = PtrToStringChars(sPrtPath);
	return CreatePreview((char*)pPrtPath, (ProcessPosCallback)((void *)Marshal::GetFunctionPointerForDelegate(pPos))); // 委托转为函数指针
}

//IMAGEPROCESS_EXCEPTION ProcessInterface::ImageProcess::ProcessInit([ref] IntPtr^ lpParam)
//{
//	return IMAGEPROCESS_EXCEPTION::PE_SUCCESS;
//}
//
//void ProcessInterface::ImageProcess::UpdateSysInfo([ref] PRINTER sSysInfo, bool bCurTask, bool bInitSys)
//{
//
//
//	return IMAGEPROCESS_EXCEPTION::PE_SUCCESS;
//}

