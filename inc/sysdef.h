#ifndef SYSDEF_H
#define SYSDEF_H

//////////////////////////////////////////////////////////////////////////
#define SYSDEF_VER				(0x000001)

//////////////////////////////////////////////////////////////////////////
#define MAX_COLORS				12
#define MAX_GROUPS              4
#define MAX_CHANELS             384
#define MAX_EXTEND_FILE			99
#define MAX_HEADS_PER_COLOR		8

//每个喷头最大的堵点数，超过次数请清洗喷头或更换喷头
#define MAX_JAMMED_DOT_COUNT	100
#define NORMAL_DOT				1000
#define JAMMED_DOT				1020
//////////////////////////////////////////////////////////////////////////

//Macro define
#define ALIGNUP(X, Y) (((X) + (Y) - 1)/(Y)*(Y))
#define	ALIGN(X, Y)	((X)/(Y)*(Y))	//X按Y对齐
#define MM_TO_DOT(X,DPI)  (int)((double)(X*DPI)/25.4)   
#define DOT_TO_MM(X,DPI)  (int)(((double)X*25.4)/DPI)
#define LIMIT(NUM, MINLIMIT, MAXLIMIT) (((NUM)<(MAXLIMIT))?(((NUM)>(MINLIMIT))?(NUM):(MINLIMIT)):(MAXLIMIT))
//////////////////////////////////////////////////////////////////////////

//系统异常定义
typedef enum _IMAGEPROCESS_EXCEPTION
{
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
}IMAGEPROCESS_EXCEPTION, LIMAGEPROCESS_EXCEPTION;

// 机器颜色
enum MACH_COLORTYPE{
	MC_4C = 0,
	MC_4C_W,
	MC_4C_W_V,
	MC_4C_2W,
	MC_6C,
	MC_6C_W,
	MC_6C_W_V,
	MC_6C_2W,
	MC_6C_V,
	MC_6C_2V,
	MC_8C,
	MC_12C
};

enum MACH_HEADERTYPE{
	HT_SP512 = 0, 
	HT_SG1024,
	HT_XAAR_1001,
	HT_KM512,
	HT_KM1024
};

// 同色喷头组排列方式
enum MACH_GROUPTYPE{
	MG_VERTICAL = 0,   // 纵向排列
	MG_HORIZONTAL	   // 横向排列
};

enum BANK_TYPE{
	A_BANK,
	B_BANK,
	BANK_ALL
};

enum WHITE_PRINT_POS{
	WP_TOP = 0,
	WP_BOTTOM,
	WP_MIDDLE
};//白色打印位置

enum PRINT_DIR{
	DIR_LEFT = 0,
	DIR_RIGHT,
	DIR_MAX
};//X向打印方向

enum PRT_IMG_TYPE{
	NORMAL_IMG,						// 正常图
	HEAD_STATE_IMAGE,				// 状态图
	HEAD_MODIFY_IMAGE,				// 调整图
	HEAD_INSIDECOLUMN_IMAGE,		// 内部列套色图
	HEAD_GROUPOFFSET_IMAGE,			// 组套色图
	HEAD_BIDIRECTIONAL_IMAGE,		// 往返打印套色图
	HEAD_CROSSCOLOR_BASECOLOR_IMAGE,// 喷头套色图
	HEAD_SETP_IMAGE					// 步进调整图
};//打印图像类型

enum DIR{
	DIR_X = 0,
	DIR_Y,
	MAX_DIRS
};//打印方向

enum SUPERBLOCK_TYPE{
	SUPERBLOCK_FILEDPI = 0,
	SUPERBLOCK_PRINTDPI
}; // 超级抽快类型

enum COLOR{
	COLOR_K = 0,
	COLOR_C,
	COLOR_M,
	COLOR_Y,
	COLOR_LC,
	COLOR_LM,
	COLOR_W,
	COLOR_V,
	COLOR_ALL
};

enum PASS_MODE{
	TEST = 0,  // 1
	DRAFT,					// 2
	NORMAL,					// 4
	NORMAL_PLUS,			// 6
	ENHANCE,				// 8
	ULTRA,					// 16
	ULTRA_DRAFT,			// 32
	ULTRA_NORMAL,			// 64
	THREEPASS,				// 3
	FIVEPASS,				// 5
	SEVENPASS,              // 7
	NINEPASS,				// 9
	TENPASS,				// 10
	ULTRA_12,               // 12
	ULTRA_13,               // 13
	ULTRA_14,				// 14
	EIGHTTEENPASS,			// 18
	ULTRA_17,				// 17
	ULTRA_34,				// 34
	ULTRA_33,				// 33
	ULTRA_15,
	ULTRA_20,				// 20
	ULTRA_21,
	ULTRA_24,				// 24
	ULTRA_26,               // 26
	ULTRA_27,
	ULTRA_28,				// 28
	ULTRA_30,
	ULTRA_36,				// 36
	ULTRA_39,
	ULTRA_42,
	ULTRA_51,
	ULTRA_54,
	ULTRA_66,				// 66
	ULTRA_68,				// 68
	ULTRA_99,
	ULTRA_102,
	MAX_PASS_MODES
};//打印Pass模式

enum PRINT_MODE{
	MODE_NORMAL = 0,
	MODE_MULTI,
	MODE_REGION
	//MODE_SINGLECOLOR,        // 分色打印
	//SEQUENCE_PRINT,          // 连续打印
	//STEP_PRINT               // 步进打印
};

enum NOIZE_UNIT_TYPE{
	ONE_TO_ZERO_TWO = 0,
	TWO_TO_ONE_THREE,
	THREE_TO_TWO_FOUR,
	FOUR_TO_THREE,
	MAX_NOIZE_UNIT
};

enum NOIZE_UNIT_RANDOM_TYPE{
	MINUS_RANDOM = 0,
	ADD_RANDOM,
	NOIZE_UNIT_MAX_RANDOM
};
//////////////////////////////////////////////////////////////////////////

//RIP file Informations
typedef struct __RIPFILEHEADINFO
{
	long Signature;
	long XDPI;
	long YDPI;
	long BytesPerLine;	//每行的字节数
	long Height;		//行数
	long Width;			//每行的像素数
	long PaperWidth;
	long Colors;		//颜色数。rip文件实际高度=Height×colors
	long Reserved[4];
}RIPFILEHEADINFO, *LPRIPFILEHEADINFO;

//REGIN_INFO （单位是mm）
typedef struct __REGIN_INFO
{
	float	Left;
	float	Top;
	float	Width;
	float	Length;
}REGIN_INFO, *LPREGIN_INFO;

//RANDOM_INFO（单位是mm）
typedef struct __RANDOM_INFO
{
	bool    UseRandomRegion; // 是否使用随机局域打印
	double	LeftRange;
	double	TopRange;
	double	ImageWidth;
	double	ImageHight;
}RANDOM_INFO, *LPRANDOM_INFO;

//MUTI_INFO	
typedef struct __MUTI_INFO
{
	unsigned int	CopyCount[MAX_DIRS];		// 拷贝数(两个方向，小于1的时候当1使用)
	float	Spacing[MAX_DIRS];		// 间距（单位是mm）
}MUTI_INFO, *LPMUTI_INFO;

//COLORBAR_INFO
typedef struct __COLORBAR_INFO
{
	unsigned int 	Width;				// 色条宽（单位:mm）
	unsigned int	DistanceFromImg;	// 离图像的距离（单位:mm）
	bool			Fixed;				// 是否固定位置
	unsigned int	FixedPosition;		// 固定的位置（相对复位位置）（单位:mm）
	bool			bAllColor;			// 是否所有颜色
}COLORBAR_INFO, *LPCOLORBAR_INFO;

//WHITE CONTROL白色控制参数
typedef struct _WHITE_CONTROL
{
	bool			UseWhite;		//是否使用白色	
	bool			SyncPrint;		//同步打印标志1: 同步0:异步
	unsigned int	WhitePosition;	//白色打印位置0: bottom 1: Top  2:Middle
	bool			bCWCMirror;     // 是否彩白彩
	bool			bUseTwoFile;	// 是否使用两个文件(白色来自于独立文件,[A.prt(彩色) + A.prt1(白色)]的形式) 
}WHITE_CONTROL, *LPWHITE_CONTROL;

//VARNISH CONTROL 清漆控制参数
typedef struct _VARNISH_CONTROL
{
	bool UseVarnish;    // 是否使用清漆	
	bool SyncUV;		// 同步UV照射
	bool SyncPrint;	    // 同步清漆打印
}VARNISH_CONTROL, *LPVARNISH_CONTROL;

// 堵点补偿
typedef struct _tagJammedDotPara
{
	short*	pHeadNozzleStatusBuf[MAX_COLORS];	//单个喷头的喷点状态信息buf，，表示没堵塞，表示堵塞
	short	iHeadPerSingleColor;				//此颜色实际装了几个喷头
}SJammedDotPara;

///////////////////////////////////////////////////////////////////////////////////////
typedef struct __SMART_PRINT_INFO
{
	long	StartOffset;     // 开始位置
	long	EndOffset;		 // 结束位置
	bool	NeedJumpPrintY;  // 是否需要跳Pass
}SMART_PRINT_INFO, *LPSMART_PRINT_INFO;

typedef struct __CUR_PASS_INFO
{
	int					StepDistance;	//当前Pass步进量,单位Dot
	int					Modify;			//当前Pass整体Modify。用于X向插点
	SMART_PRINT_INFO	SmartPrintInfo;
}CUR_PASS_INFO, *LPCUR_PASS_INFO;

typedef struct  DOUBLE_FACE_PRINT_INFO_TAG
{
	float OffsetVertical[DIR_MAX];
	float OffsetHorizontal;
	bool	UseDoubleFacePrint;
}DOUBLE_FACE_PRINT_INFO;

typedef struct  REVIEW_COLOR_STRUCT_INFO_TAG
{
	unsigned char		C;
	unsigned char		M;
	unsigned char		Y;
	unsigned char		K;
	unsigned int	color;
}REVIEW_COLOR_STRUCT_INFO, *LPREVIEW_COLOR_STRUCT_INFO;

typedef struct __tagSIZE
{
	long        cx;
	long        cy;
} SIZE_Q, *PSIZE_Q, *LPSIZE_Q;

//HEAD_INFO:
typedef struct __HEAD_INFO
{
	unsigned int		uiNozzle;					// 每列喷头的喷嘴数
	unsigned int		uiUseNozzle;				// 实际每列使用的喷点数
	unsigned int		uiHeadType;					// 喷头类型

	unsigned int		uiHeadDPI[MAX_DIRS];		// 喷头物理分辨率
	unsigned int		uiHeadsPerColor;			// 每个喷头的喷头列数
	unsigned int		uiPixelPerByte;				// 每字节表示像素数（1bit:8, 2bit:4）

	float			fGroupOverlap;				// Y向喷头重合点（垂直排列有效。 负值为重合，正值为分开）

	//int         nNozzleStrip;					// 喷头斜置舍点
	//int         nHeadColStrip[4];				// 舍点方向（-1:不舍点，0：下舍点，1：上舍点）
}HEAD_INFO, *LPHEAD_INFO;

//MACH_INFO:
typedef struct __MACH_INFO
{
	int					nMachineColorCount;		// 机器颜色数
	MACH_COLORTYPE		eMachineColorType;      // 机器颜色类型
	int					nMachineGroupCount;		// 喷头组数量
	MACH_GROUPTYPE		eMachineGroupType;		// 喷头组排列方式
	int					nMachineChannelCount;	// 合计通道数（Heads * HeadsPerColor * Group)

	int					nEncodeDPI[MAX_DIRS];	// X/Y 光栅和编码盘的DPI
}MACH_INFO, *LPMACH_INFO;

//CHANNEL_INFO
typedef struct __CHANNEL_INFO
{
	int		iGroup;                         // 组No.
	int 	iColor;							// 通道对应的颜色No.
	int		iIndex;							// 通道对应的喷头列序号
	bool	bUse;							// 是否使用

	int		XStandOffset[DIR_MAX];			// X向基准偏移
	int		XOffset[DIR_MAX];				// X向偏移
	int		XInchingOffset[DIR_MAX];		// X向偏移微调

	int		YStandOffset;					// 基准偏移（默认0）
	int		YOffset;						// 喷头Y向偏移

	//int		iReadJumpRow;					// 
	int		nInkColors;						// 墨量(0~ 100)
	int		bInvert;						// 是否反转数据
}CHANNEL_INFO, *LPCHANNEL_INFO;


//Special image process
typedef struct __SPECIAL_PROCESS
{
	bool	UseFeather;
	bool	UseBlock;
	bool	UseSuperBlock;

	int		BlockSize;
	int     BlockMode;
	int     SuperBlockSize[4];
	int     SuperBlockMode;
	int     SuperBlockType;
	int     SuperBlockLayer;
	int     SuperBlockFeatherLevel;
	double  SuperBlockFeatherGamma;
	int     SuperBlockNoiseRange;

	bool	bSetSuperBlock;
	bool    bSuperBlockAddInk;
	bool    bSuperBlockDouble;

	// 玻璃机，扫描式陶瓷机用（单Pass）
	bool	UseLittleFeather; 	//(是否使用小羽化)
	unsigned int	FeatherSize; 		//(羽化大小)

	// 堵点补偿参数
	bool	UseSameHeadCompansate[MAX_COLORS];
	SJammedDotPara sJammedDotPara[MAX_COLORS];
	int     JammedKCMYValue[4][MAX_COLORS];
	float	OtherHeadCoefficient[MAX_COLORS][MAX_COLORS];

	// 噪点
	//int		NoisePercent[MAX_COLORS][MAX_NOIZE_UNIT];//m_iNoisePercent[][0]代表转化为和的百分比，m_iNoisePercent[][1]代表转化为和的百分比，m_iNoisePercent[][2]代表转化为和的百分比，

}SPECIAL_PROCESS, LPSPECIAL_PROCESS;


typedef struct __PROCESS_PARAM
{
	//////////////////////////////////////////////////////////////////////////
	// OUT
	int	DotPerModify;				// Dot的偏移值
	int	StepOffsetPassMode;     	// 计算处理后的Pass数对应的PassMode
	int	FeatherBlockPassMode;		// 计算处理后的Pass数
	int	nNextGroupOffsetPass;		// Group间偏移Pass数
	int nNextGroupOffsetLine;		// Group间偏移行数
	unsigned int TotalPrintNum;				//打印pass总数
	double	YDPIRatio;				// Y向DPI比例系数
	SIZE_Q	PrintSize;				//打印尺寸，单位：DOT，表示打印画面的总宽度/高度（包括偏移补白）

	//////////////////////////////////////////////////////////////////////////
	// IN
	PRT_IMG_TYPE    ImageType;					// 图像类型
	unsigned int	PassMode;			// 1Pass, 2Pass,  3Pass, 4Pass, 6Pass 8Pass, 12Pass, 16Pass
	unsigned int	PrintMode;			//Normal, Multi, Regin(正常，多幅，局域)
	wchar_t*		FilePath;					//打印文件路径
	REGIN_INFO		ReginInfo;					//区域打印控制参数
	MUTI_INFO		MutiInfo;					//多幅打印控制参数

	COLORBAR_INFO	ColorBarInfo;				//色条打印参数
	WHITE_CONTROL	WhiteCtrl;					// 白色打印控制参数
	VARNISH_CONTROL VarnishCtrl;				// 光油打印控制参数

	SPECIAL_PROCESS	SpecialProcess;	            // 特殊处理

	bool  			AddColorBar;					// 是否添加ColorBar
	bool			MirrorPrint;				// 是否镜像
	bool			YPrintDir;					// 是否反向打印
	bool			DoubleStrike;				// 是否启用双喷
	bool			SingleDirPrint;				// 是否单向打印
	bool			PrintDir[MAX_DIRS];			// 打印方向
	bool			SmartPrint;					// 是否跳白打印
	//BOOL          bUseDoubleGroup;			// 是否使用双组
	//BOOL			bGroupUse[MAX_GROUPS];	// 喷头组工作开关
	DOUBLE_FACE_PRINT_INFO DoubleFacePrintInfo; // 双面喷控制参数	(IN)RANDOM_INFO	RandomRegionInfo;		// 随机区域打印
	bool 		    bUseRegionPrint;		    // 是否同时使用区域打印

	//BOOL			bUseMutiPrt;				// 是否多文件打印
	//LPCTSTR		ExtendFiles;				// 多文件同时打印时的文件名

}PROCESS_PARAM, *LPPROCESS_PARAM;


//PRINTER打印机系统描述结构
typedef  struct  __PRINTER
{
	//Basic:
	//UINT		MachineColor;                               // 颜色类型	
	//UINT		MachineGroup;                               // 喷头组
	//UINT		MachineChanel;                              // 通道数
	//UINT		MachineCombination;                         // 车头底板喷头排数
	//UINT		MachineHeadArrange;                         // 喷头排列(TRUE为纵向排列，FALSE为横向排列)

	//UINT		ColorCount;									// 颜色数
	//UINT		HeadsPerColor;								// 喷头

	MACH_INFO	MachineInfo;								// 机器类型定义
	HEAD_INFO	HeadInfo;									// 喷头信息

	CHANNEL_INFO Chanel[MAX_CHANELS];						//通道：为每一个喷头列建立一个Chanel对象
	//int         YOverlapOffset[MAX_PASS_MODES];             // 双组喷头套色补偿

	//////////////////////////////////////////////////////////////////////////
	// 预览图生成用
	bool nUseCustomReview;						                    // 是否使用自定义预览
	int nReviewColorNumber;						                    // 预览图颜色数
	REVIEW_COLOR_STRUCT_INFO listReviewColorInfo[MAX_COLORS];       // 预览颜色定义
	//////////////////////////////////////////////////////////////////////////

	// 喷头相关参数
	//		颜色通道映射)
	int     nColorIndex[MAX_COLORS];			// 颜色通道映射表
	int     nFileColorIndex[MAX_COLORS];		// 文件颜色通道映射表
	int     nChannelColorIndex[MAX_COLORS];		// 通道颜色通道映射表

	// 调整8列喷点顺序
	bool   bHeadPosLow[8];					// 底板高低次序
	int     bHeadOrder[8];					// 喷头顺序临时调整用
	double  fHeadOrder[8];					// 喷头顺序临时调整用
	/// -- End add

}PRINTER, *LPPRINTER;

#endif // SYSDEF_H