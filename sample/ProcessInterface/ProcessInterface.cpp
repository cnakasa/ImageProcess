// ������ DLL �ļ���

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
	// ��stringת����C++��ʶ���ָ��
	pin_ptr<const wchar_t> pPrtPath = PtrToStringChars(sPrtPath);
	return CreatePreview((char*)pPrtPath, (ProcessPosCallback)((void *)Marshal::GetFunctionPointerForDelegate(pPos))); // ί��תΪ����ָ��
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

