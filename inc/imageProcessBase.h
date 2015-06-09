#ifndef IMAGEPROCESSBASE_H
#define IMAGEPROCESSBASE_H

#include "sysdef.h"
#include "imageprocess_global.h"

/*! \typedef typedef ReturnCurPos
*  \brief Pass处理进度反馈
*
* 当前Pass处理进度反馈
*/
typedef void(__cdecl *ProcessPosCallback)(int nPos);


/*! \typedef typedef ReturnCurPos
*  \brief Pass处理上传数据回调
*
* 当前Pass上传数据回调
*/
typedef void(__cdecl *DownloadImageDataToHardware)(unsigned char* lpWriteData, unsigned int uiBufferID, unsigned int uiBytes);


/*! \typedef typedef ReturnCurPos
*  \brief 打印处理接口类
*
* 打印数据处理
*/
class IMAGEPROCESS_EXPORT CImgProcessBase
{
public:
	//virtual ~CImgProcessBase() = 0;

public:
	// 打印前初始化
	virtual IMAGEPROCESS_EXCEPTION ProcessInit(PROCESS_PARAM* lpParam) = 0;
	// 更新打印机设置(喷头/套色等打印机配置参数)
	virtual void UpdateSysInfo(PRINTER& sSysInfo, bool bCurTask, bool bInitSys) = 0;
	// 打印任务结束后的释放工作
	virtual IMAGEPROCESS_EXCEPTION CleanUp() = 0;
	// 数据处理并上传
	virtual IMAGEPROCESS_EXCEPTION ProcessImg(int nCount, bool bDir, LPCUR_PASS_INFO pCurPassInfo
		, bool bWaitingProcessEnd = true, ProcessPosCallback callbackPos = NULL, DownloadImageDataToHardware downloadData = NULL) = 0;
	// 打印等待当前Pass处理并上传完毕（pSmartPrintInfo 返回的跳白信息，用于运动部分实现跳白动作）
	virtual IMAGEPROCESS_EXCEPTION WaitingForProcessOK(long dwMilliseconds = 10000, LPSMART_PRINT_INFO pSmartPrintInfo = NULL) = 0;
};

CImgProcessBase* CreareImageProcessObj();
void CDestoryImageProcessObj(CImgProcessBase* p);

#endif // IMAGEPROCESSBASE_H
