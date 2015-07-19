
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

//#region 
//#define ss 100
//#endregion


namespace forPG
{
    
    public static class Information_System
    {
        /// <summary>
        /// /////////////////////////////////////////////////////////////////////////////////////////////////////
        /// 以下是枚举
        /// /////////////////////////////////////////////////////////////////////////////////////////////////////
        /// </summary>
        //系统异常定义
        public enum _IMAGEPROCESS_EXCEPTION
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
        }//IMAGEPROCESS_EXCEPTION, LIMAGEPROCESS_EXCEPTION;

        // 机器颜色
        public enum MACH_COLORTYPE
        {
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

        public enum MACH_HEADERTYPE
        {
            HT_SP512 = 0,
            HT_SG1024,
            HT_XAAR_1001,
            HT_KM512,
            HT_KM1024
        };

        // 同色喷头组排列方式
        public enum MACH_GROUPTYPE
        {
            MG_VERTICAL = 0,   // 纵向排列
            MG_HORIZONTAL	   // 横向排列
        };

        public enum BANK_TYPE
        {
            A_BANK,
            B_BANK,
            BANK_ALL
        };

        public enum WHITE_PRINT_POS
        {
            WP_TOP = 0,
            WP_BOTTOM,
            WP_MIDDLE
        };//白色打印位置

        public enum PRINT_DIR
        {
            DIR_LEFT = 0,
            DIR_RIGHT,
            DIR_MAX
        };//X向打印方向

        public enum PRT_IMG_TYPE
        {
            NORMAL_IMG,						// 正常图
            HEAD_STATE_IMAGE,				// 状态图
            HEAD_MODIFY_IMAGE,				// 调整图
            HEAD_INSIDECOLUMN_IMAGE,		// 内部列套色图
            HEAD_GROUPOFFSET_IMAGE,			// 组套色图
            HEAD_BIDIRECTIONAL_IMAGE,		// 往返打印套色图
            HEAD_CROSSCOLOR_BASECOLOR_IMAGE,// 喷头套色图
            HEAD_SETP_IMAGE					// 步进调整图
        };//打印图像类型

        public enum DIR
        {
            DIR_X = 0,
            DIR_Y,
            MAX_DIRS
        };//打印方向

        public enum SUPERBLOCK_TYPE
        {
            SUPERBLOCK_FILEDPI = 0,
            SUPERBLOCK_PRINTDPI
        }; // 超级抽快类型

        public enum COLOR
        {
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

        public enum PASS_MODE
        {
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

        public enum PRINT_MODE
        {
            MODE_NORMAL = 0,
            MODE_MULTI,
            MODE_REGION
            //MODE_SINGLECOLOR,        // 分色打印
            //SEQUENCE_PRINT,          // 连续打印
            //STEP_PRINT               // 步进打印
        };

        public enum NOIZE_UNIT_TYPE
        {
            ONE_TO_ZERO_TWO = 0,
            TWO_TO_ONE_THREE,
            THREE_TO_TWO_FOUR,
            FOUR_TO_THREE,
            MAX_NOIZE_UNIT
        };

        public enum NOIZE_UNIT_RANDOM_TYPE
        {
            MINUS_RANDOM = 0,
            ADD_RANDOM,
            NOIZE_UNIT_MAX_RANDOM
        };

        /// <summary>
        /// /////////////////////////////////////////////////////////////////////////////////////////////////////
        /// 以下是结构体
        /// /////////////////////////////////////////////////////////////////////////////////////////////////////
        /// </summary>

        [StructLayout(LayoutKind.Sequential)]
        public struct __RIPFILEHEADINFO
        {
            public long Signature;
            public long XDPI;
            public long YDPI;
            public long BytesPerLine;	//每行的字节数
            public long Height;		//行数
            public long Width;			//每行的像素数
            public long PaperWidth;
            public long Colors;		//颜色数。rip文件实际高度=Height×colors
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            public long[] Reserved;    //long Reserved[4];
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __REGIN_INFO
        {
            public float Left;
            public float Top;
            public float Width;
            public float Length;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __RANDOM_INFO
        {
            public bool UseRandomRegion; // 是否使用随机局域打印
            public double LeftRange;
            public double TopRange;
            public double ImageWidth;
            public double ImageHight;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __MUTI_INFO
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_DIRS)]
            public uint[] CopyCount;//CopyCount[MAX_DIRS];		// 拷贝数(两个方向，小于1的时候当1使用)
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_DIRS)]
            public float[] Spacing;//Spacing[MAX_DIRS];		// 间距（单位是mm）
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __COLORBAR_INFO
        {
            public uint Width;				// 色条宽（单位:mm）
            public uint DistanceFromImg;	// 离图像的距离（单位:mm）
            public bool Fixed;				// 是否固定位置
            public uint FixedPosition;		// 固定的位置（相对复位位置）（单位:mm）
            public bool bAllColor;			// 是否所有颜色
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct _WHITE_CONTROL
        {
            public bool UseWhite;		//是否使用白色	
            public bool SyncPrint;		//同步打印标志1: 同步0:异步
            public uint WhitePosition;	//白色打印位置0: bottom 1: Top  2:Middle
            public bool bCWCMirror;     // 是否彩白彩
            public bool bUseTwoFile;	// 是否使用两个文件(白色来自于独立文件,[A.prt(彩色) + A.prt1(白色)]的形式) 
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct _VARNISH_CONTROL
        {
            public bool UseVarnish;    // 是否使用清漆	
            public bool SyncUV;		// 同步UV照射
            public bool SyncPrint;	    // 同步清漆打印
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct _tagJammedDotPara
        {
            [MarshalAs(UnmanagedType.ByValArray,SizeConst=MAX_DIRS)]
            public System.Int16[] pHeadNozzleStatusBuf;//short* pHeadNozzleStatusBuf[MAX_COLORS];	//单个喷头的喷点状态信息buf，，表示没堵塞，表示堵塞
            public short pHeadNozzleStatusBuf1;
            public short iHeadPerSingleColor;				//此颜色实际装了几个喷头
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __SMART_PRINT_INFO
        {
            public long StartOffset;     // 开始位置
            public long EndOffset;		 // 结束位置
            public bool NeedJumpPrintY;  // 是否需要跳Pass
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __CUR_PASS_INFO
        {
            public int StepDistance;	//当前Pass步进量,单位Dot
            public int Modify;			//当前Pass整体Modify。用于X向插点
            public __SMART_PRINT_INFO SmartPrintInfo;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct DOUBLE_FACE_PRINT_INFO_TAG
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = DIR_MAX)]
            public float[] OffsetVertical;//float OffsetVertical[DIR_MAX];
            public float OffsetHorizontal;
            public bool UseDoubleFacePrint;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct REVIEW_COLOR_STRUCT_INFO_TAG
        {
            public byte C;
            public byte M;
            public byte Y;
            public byte K;
            public byte color;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __tagSIZE
        {
            public long cx;
            public long cy;
        }

        [StructLayout(LayoutKind.Sequential)]
        struct __HEAD_INFO
        {
            public uint uiNozzle;					// 每列喷头的喷嘴数
            public uint uiUseNozzle;				// 实际每列使用的喷点数
            public uint uiHeadType;					// 喷头类型

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_DIRS)]
            public uint[] uiHeadDPI;//uint		uiHeadDPI[MAX_DIRS];		// 喷头物理分辨率
            public uint uiHeadsPerColor;			// 每个喷头的喷头列数
            public uint uiPixelPerByte;				// 每字节表示像素数（1bit:8, 2bit:4）

            public float fGroupOverlap;				// Y向喷头重合点（垂直排列有效。 负值为重合，正值为分开）
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __MACH_INFO
        {
            public int nMachineColorCount;		// 机器颜色数
            public MACH_COLORTYPE eMachineColorType;      // 机器颜色类型
            public int nMachineGroupCount;		// 喷头组数量
            public MACH_GROUPTYPE eMachineGroupType;		// 喷头组排列方式
            public int nMachineChannelCount;	// 合计通道数（Heads * HeadsPerColor * Group)
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_DIRS)]
            public int[] nEncodeDPI;//int					nEncodeDPI[MAX_DIRS];	// X/Y 光栅和编码盘的DPI
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __CHANNEL_INFO
        {
            public int iGroup;                         // 组No.
            public int iColor;							// 通道对应的颜色No.
            public int iIndex;							// 通道对应的喷头列序号
            public bool bUse;							// 是否使用

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = DIR_MAX)]
            public int[] XStandOffset;//int		XStandOffset[DIR_MAX];			// X向基准偏移
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = DIR_MAX)]
            public int[] XOffset;//int		XOffset[DIR_MAX];				// X向偏移
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = DIR_MAX)]
            public int[] XInchingOffset;//int		XInchingOffset[DIR_MAX];		// X向偏移微调

            public int YStandOffset;					// 基准偏移（默认0）
            public int YOffset;						// 喷头Y向偏移

            public int nInkColors;						// 墨量(0~ 100)
            public int bInvert;						// 是否反转数据
        }


        [StructLayout(LayoutKind.Sequential)]
        public struct __SPECIAL_PROCESS
        {
            public bool UseFeather;
            public bool UseBlock;
            public bool UseSuperBlock;

            public int BlockSize;
            public int BlockMode;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            public int[] SuperBlockSize;
            //int[]     SuperBlockSize;//int     SuperBlockSize[4];
            public int SuperBlockMode;
            public int SuperBlockType;
            public int SuperBlockLayer;
            public int SuperBlockFeatherLevel;
            public double SuperBlockFeatherGamma;
            public int SuperBlockNoiseRange;

            public bool bSetSuperBlock;
            public bool bSuperBlockAddInk;
            public bool bSuperBlockDouble;

            // 玻璃机，扫描式陶瓷机用（单Pass）
            public bool UseLittleFeather; 	//(是否使用小羽化)
            public uint FeatherSize; 		//(羽化大小)

            // 堵点补偿参数
            public bool[] UseSameHeadCompansate;//bool	UseSameHeadCompansate[MAX_COLORS];
            [MarshalAs(UnmanagedType.ByValArray, SizeConst=MAX_DIRS)]
            public _tagJammedDotPara[] sJammedDotPara;//SJammedDotPara sJammedDotPara[MAX_COLORS];

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4 * MAX_DIRS)]
            public int[] JammedKCMYValue;//int     JammedKCMYValue[4][MAX_COLORS];
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_DIRS * MAX_DIRS)]
            public float[] OtherHeadCoefficient;//float	OtherHeadCoefficient[MAX_COLORS][MAX_COLORS];

            // 噪点
            //int		NoisePercent[MAX_COLORS][MAX_NOIZE_UNIT];
            //m_iNoisePercent[][0]代表转化为和的百分比，m_iNoisePercent[][1]代表转化为和的百分比，m_iNoisePercent[][2]代表转化为和的百分比，

        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __PROCESS_PARAM
        {
            //////////////////////////////////////////////////////////////////////////
            // OUT
            public int DotPerModify;				// Dot的偏移值
            public int StepOffsetPassMode;     	// 计算处理后的Pass数对应的PassMode
            public int FeatherBlockPassMode;		// 计算处理后的Pass数
            public int nNextGroupOffsetPass;		// Group间偏移Pass数
            public int nNextGroupOffsetLine;		// Group间偏移行数
            public uint TotalPrintNum;				//打印pass总数
            public double YDPIRatio;				// Y向DPI比例系数
            public __tagSIZE PrintSize;				//打印尺寸，单位：DOT，表示打印画面的总宽度/高度（包括偏移补白）

            //////////////////////////////////////////////////////////////////////////
            // IN
            public PRT_IMG_TYPE ImageType;					// 图像类型
            public uint PassMode;			// 1Pass, 2Pass,  3Pass, 4Pass, 6Pass 8Pass, 12Pass, 16Pass
            public uint PrintMode;			//Normal, Multi, Regin(正常，多幅，局域)

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////
            [MarshalAs(UnmanagedType.LPWStr)]
            public string FilePath;
            //wchar_t*		FilePath;					//打印文件路径
            /// <summary>
            /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// </summary>
            /// 

            public __REGIN_INFO ReginInfo;					//区域打印控制参数
            public __MUTI_INFO MutiInfo;					//多幅打印控制参数

            public __COLORBAR_INFO ColorBarInfo;				//色条打印参数
            public _WHITE_CONTROL WhiteCtrl;					// 白色打印控制参数
            public _VARNISH_CONTROL VarnishCtrl;				// 光油打印控制参数

            public __SPECIAL_PROCESS SpecialProcess;	            // 特殊处理

            public bool AddColorBar;					// 是否添加ColorBar
            public bool MirrorPrint;				// 是否镜像
            public bool YPrintDir;					// 是否反向打印
            public bool DoubleStrike;				// 是否启用双喷
            public bool SingleDirPrint;				// 是否单向打印

            [MarshalAs(UnmanagedType.ByValArray,SizeConst=MAX_DIRS)]
            public bool[] PrintDir;//bool			PrintDir[MAX_DIRS];			// 打印方向
            public bool SmartPrint;					// 是否跳白打印
            //BOOL          bUseDoubleGroup;			// 是否使用双组
            //BOOL			bGroupUse[MAX_GROUPS];	// 喷头组工作开关
            public DOUBLE_FACE_PRINT_INFO_TAG DoubleFacePrintInfo; // 双面喷控制参数	(IN)RANDOM_INFO	RandomRegionInfo;		// 随机区域打印
            public bool bUseRegionPrint;		    // 是否同时使用区域打印

            //BOOL			bUseMutiPrt;				// 是否多文件打印
            //LPCTSTR		ExtendFiles;				// 多文件同时打印时的文件名

        }

        [StructLayout(LayoutKind.Sequential)]
        public struct __PRINTER
        {
            //Basic:
            //UINT		MachineColor;                               // 颜色类型	
            //UINT		MachineGroup;                               // 喷头组
            //UINT		MachineChanel;                              // 通道数
            //UINT		MachineCombination;                         // 车头底板喷头排数
            //UINT		MachineHeadArrange;                         // 喷头排列(TRUE为纵向排列，FALSE为横向排列)

            //UINT		ColorCount;									// 颜色数
            //UINT		HeadsPerColor;								// 喷头

            public __MACH_INFO MachineInfo;								// 机器类型定义
            __HEAD_INFO HeadInfo;									// 喷头信息

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_CHANELS)]
            public __CHANNEL_INFO[] Chanel;//CHANNEL_INFO Chanel[MAX_CHANELS];						//通道：为每一个喷头列建立一个Chanel对象
            //int         YOverlapOffset[MAX_PASS_MODES];             // 双组喷头套色补偿

            //////////////////////////////////////////////////////////////////////////
            // 预览图生成用
            public bool nUseCustomReview;						                    // 是否使用自定义预览
            public int nReviewColorNumber;						                    // 预览图颜色数
            public REVIEW_COLOR_STRUCT_INFO_TAG[] listReviewColorInfo;       // 预览颜色定义
            //REVIEW_COLOR_STRUCT_INFO listReviewColorInfo[MAX_COLORS];       // 预览颜色定义
            //////////////////////////////////////////////////////////////////////////



            // 喷头相关参数
            //		颜色通道映射)
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_CHANELS)]
            public int[] nColorIndex;//int     nColorIndex[MAX_COLORS];			// 颜色通道映射表
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_CHANELS)]
            public int[] nFileColorIndex;//int     nFileColorIndex[MAX_COLORS];		// 文件颜色通道映射表
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_CHANELS)]
            public int[] nChannelColorIndex;//int     nChannelColorIndex[MAX_COLORS];		// 通道颜色通道映射表

            // 调整8列喷点顺序
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public bool[] bHeadPosLow;//bool   bHeadPosLow[8];					// 底板高低次序
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public int[] bHeadOrder;//int     bHeadOrder[8];					// 喷头顺序临时调整用
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public double[] fHeadOrder;//double  fHeadOrder[8];					// 喷头顺序临时调整用
            /// -- End add
            //public int a;
        }


        public static __RIPFILEHEADINFO RIPFILEHEADINFO;

        public static __PRINTER printer;
        /// <summary>
        /// /////////////////////////////////////////////
        /// </summary>
        public const int MAX_DIRS = 2; //有问题；
        public const int DIR_MAX = 2;
        public const int MAX_CHANELS = 384;
        /// <summary>
        /// ////////////////////////////////////////////
        /// </summary>

        //public __PRINTER printer;

        public static double DisBtwNozzle = 25.4;

        public static int NumPrinthead = 4;

        public static int RowsPrinthead = 1;

        public static int Begin_Position_X = 100;

        public static int Begin_Position_Y = 0;

        //Jump_Margin 跳白打印
        //false 否
        //true  是
        public static bool Jump_Margin = false;

        //Precision 打印精度
        //0 标准
        //1 高精度
        //2 草稿
        public static int Precision = 0;

        //Combination_Color 图层模式
        //0 专色打印
        //1 彩白组合
        //2 浓彩打印
        //3 凹凸打印
        //4 双面打印
        public static int Combination_Color = 0;

        //Print_Mode 打印模式
        //0 单向
        //1 双向
        public static int Print_Mode = 0;

        //X_Speed X轴运动速度
        //0 高速
        //1 中速
        //2 低速
        public static int X_Speed = 0;

        //Y_Speed X轴运动速度
        //0 高速
        //1 中速
        //2 低速
        public static int Y_Speed = 0;

        //Printhead_Setting 喷头设置
        //0 单排 C-M-Y-K
        //1 单排 C-M-Y-K-LC-LM
        //2 错排 C-M-Y-K
        //3 错排 C-M-Y-K-LC-LM
        //4 双排 C-M-Y-K
        //5 双排 C-M-Y-K-LC-LM
        //6 双排 C-M-Y-K-LC-LM-WV
        public static int Printhead_Setting = 0;

        //Printhead_Property 喷头类型
        //0 Konica_1024 (14pL)
        //1 Konica_1024 (42pL)
        //2 Konica_1024 (14+42pL)
        //3 Konica_1024 (4pL)
        //4 Konica_1024 (6pL)
        public static int Printhead_Property = 0;

        //White 白色
        //false 否
        //true  是
        public static bool White = false;

        //Oil 光油
        //false 否
        //true  是
        public static bool Oil = false;

        //Paint 光油
        //false 否
        //true  是
        public static bool Paint = false;

        //Dis_Btw_Printhead 喷头间距
        public static int Dis_Btw_Printhead = 36;


    }
}
