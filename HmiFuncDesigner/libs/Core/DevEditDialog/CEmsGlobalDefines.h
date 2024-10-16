#ifndef CEMSGLOBALDEFINES_H
#define CEMSGLOBALDEFINES_H

#include <QObject>
#include <QSharedPointer>
#include <QMetaEnum>
#include <QtCore/qmetatype.h>
#define EMSKEY2VALUE "KEY2VALUE" // 从ESB总线更新键值对标识
/*保留系统内部设备命令字传递的键值*/
#define INTKEY_HEALTH "HealthStatus"
#define INTKEY_COMMAND "Command"
#define INTKEY_COMMAND_LST "CommandList" // 融合指令处理时的隐项
#define INTKEY_WKMODE "WorkMode"
#define INTKEY_WKPARAM "WorkParam"
#define INTKEY_WKPARAM_2 "WorkParam_2"
#define INTKEY_RESPONSE "Response"
#define INTKEY_CTRLTIMESTAMP "CtrlTmStm"
#define INTKEY_BARNNO "BarnNo" // 多支路PCS控制标记

/*虚拟设备架构类型*/
constexpr int EMSPHYSIC = 0; // 物理设备 访问实体设备的模型，包括访问实体设备所需的总线设备。此架构设备在策略端不创建
constexpr int EMSMAPPER = 1; // 映射设备（系统内部ESB上信息交互设备，该设备映射实体设备读取的真值，并将其解析为管道定义的交互数据结构（键值对)
constexpr int EMSESBCOM = 2; // 通讯总线设备 系统内部进程间通信管道

typedef quint8 EMS_DEV_ARCH;
#define EMS_ARCH_TO_STRING(input, output) \
    {                                     \
        switch (input) {                  \
        case EMSPHYSIC:                   \
            output = "Physic";            \
            break;                        \
        case EMSMAPPER:                   \
            output = "Mapper";            \
            break;                        \
        case EMSESBCOM:                   \
            output = "BusComm";           \
            break;                        \
        default:                          \
            output = "Undef";             \
            break;                        \
        }                                 \
    }

/*设备类别定义*/
constexpr int UNKOWNDEV = -1;              // 未知设备
constexpr int EMSBAMS = 1;                  // 电池管理
constexpr int EMSBMS = 2;                   // 电池管理
constexpr int EMSPCS = 3;                   // PCS设备管理
constexpr int EMSBUS = 4;                   // 总线设备
constexpr int EMSBATSTACK = 5;              // 电池堆
constexpr int EMSBATBANK = 6;               // 电池组
constexpr int EMSCOMREG = 7;                // 通用寄存器
constexpr int EMSMETER = 8;                 // 电表
constexpr int EMSFIREFIGHT = 9;             // 消防
constexpr int EMSARICOND = 10;              // 空调
constexpr int EMSTRANSF = 11;               // 变压器
constexpr int EMSIOMODULE = 12;             // 三方IO模块
constexpr int EMSLIQCOOL = 13;              // 液冷机
constexpr int EMSLIQBAT = 14;               // 液流电池循环控制器
constexpr int EMSPANEL = 15;                // 人机交互面板
constexpr int EMSPV = 16;                   // 新能源机组 光伏 或 风机
constexpr int EMSDCDC = 17;                 // DCDC直流模块 光伏耦合模块
constexpr int EMSSMOKE = 18;                // 烟感报警器
constexpr int EMSVALVEGROUP = 19;           // 阀门组

class CEmsGlobalDefines : public QObject
{
    Q_OBJECT
public:
    enum EmsDevType {
        EMSBAMS = EMSBAMS,
        EMSBMS = EMSBMS,
        EMSPCS = EMSPCS,
        EMSBUS = EMSBUS,
        EMSBATSTACK = EMSBATSTACK,
        EMSBATBANK = EMSBATBANK,
        EMSCOMREG = EMSCOMREG,
        EMSMETER = EMSMETER,
        EMSFIREFIGHT = EMSFIREFIGHT,
        EMSARICOND = EMSARICOND,
        EMSTRANSF = EMSTRANSF,
        EMSIOMODULE = EMSIOMODULE,
        EMSLIQCOOL = EMSLIQCOOL,
        EMSLIQBAT = EMSLIQBAT,
        EMSPANEL = EMSPANEL,
        EMSPV = EMSPV,
        EMSDCDC = EMSDCDC,
        EMSSMOKE = EMSSMOKE,
        EMSVALVEGROUP = EMSVALVEGROUP,
        UNKOWNDEV = UNKOWNDEV
    };
    Q_ENUM(EmsDevType)

    enum ArchType {
        EMSPHYSIC = 0,
        EMSMAPPER ,
        EMSESBCOM ,
    };
    Q_ENUM(ArchType)

};

typedef quint8 EMS_DEV;
#define EMSDEVICETYPENUMS 18

#define EMS_DEV_TO_STRING(input, output) \
    {                                    \
        switch (input) {                 \
        case EMSPANEL:                   \
            output = "Control-panel";    \
            break;                       \
        case EMSBAMS:                    \
            output = "Bams";             \
            break;                       \
        case EMSBMS:                     \
            output = "Bms";              \
            break;                       \
        case EMSPCS:                     \
            output = "Pcs";              \
            break;                       \
        case EMSBUS:                     \
            output = "Bus";              \
            break;                       \
        case EMSBATSTACK:                \
            output = "Battery-Stack";    \
            break;                       \
        case EMSBATBANK:                 \
            output = "Battery-Bank";     \
            break;                       \
        case EMSCOMREG:                  \
            output = "Common-Registor";  \
            break;                       \
        case EMSMETER:                   \
            output = "Electric-Meter";   \
            break;                       \
        case EMSFIREFIGHT:               \
            output = "FireFighting";     \
            break;                       \
        case EMSARICOND:                 \
            output = "AirCondition";     \
            break;                       \
        case EMSTRANSF:                  \
            output = "Transformer";      \
            break;                       \
        case EMSIOMODULE:                \
            output = "IoModule";         \
            break;                       \
        case EMSLIQCOOL:                 \
            output = "LiquitCooler";     \
            break;                       \
        case EMSLIQBAT:                  \
            output = "LiquitBat";        \
            break;                       \
        case EMSPV:                      \
            output = "NewPower";         \
            break;                       \
        case EMSDCDC:                    \
            output = "DCDC";             \
            break;                       \
        case EMSVALVEGROUP:              \
            output = "valveGroup";       \
            break;                       \
        default:                         \
            output = "Undefined";        \
            break;                       \
        }                                \
    }

/*
 * 设备状态定义
 */
#define STANDBY 0
#define CHARGING 1
#define DISCHARGING 2
#define DROP 3
#define FAULT 4
#define POWEROFF 5
typedef quint8 EMS_DEV_STATE;

class CEmsDevice;
class QtRedis;

struct EmsGroupDevice {
    QString devInst;
    QSharedPointer<CEmsDevice> pDev;
};

typedef QSharedPointer<CEmsDevice> CEmsSharedDevice;       // 设备共享指针
typedef QMap<QString, QList<EmsGroupDevice>> CEmsDevGroup; // 设备组 仅策略进程使用
// 设备对，首指针为实体设备，次指针为映射设备
typedef QPair<CEmsSharedDevice, CEmsSharedDevice> CEmsDevicePair;

#define DEVICBASEVESRION "1.2.6.0"

/**
 * @brief 定义设备状态类型
 */
class CEmsPropertySheet : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 设备通讯总线协议
     */
    enum EmsBus {
        ESHAREDMEM = 0,
        EREDIS,
        EDATABASE,
        ESERIALRTU,
        ESERIALASCII,
        ETCPRTU,
        ETCPASCII,
        EUDPRTU,
        EUDPASCII,
        EBUSDEVICE,
        UNKONWNBUS
    };
    Q_ENUM(EmsBus)

    /**
     * @brief 设备应用层协议标准代号
     */
    enum EmsProto {
        /**科工EMS页面交互协议标准*/
        KGHMI = 0,
        /**科工BAMS交互协议标准*/
        KGBAMS,
        /**科工云平台交互协议标准*/
        KGCLOUD,
        /*第三方协议*/
        MODBUS,
        DLT6452007,
        DLT6451997,
        CAN,
        /*科工数据流*/
        KGSTREAM,
        UNKONWNPROTO
    };
    Q_ENUM(EmsProto)

    /**
     * @brief PCS调度模式
     */
    enum POWERDISPATCH {
        /**整机调度*/
        whole = 0,
        /**分支调度*/
        barns
    };

    /**
     * @brief PCS设备支持功率配置工作模式
     */
    enum POWERWORKMODE {
        /**并网：直流恒压*/
        constDirVol = 0,
        /**并网：直流恒流*/
        constDirCur,
        /**并网：直流功率*/
        constDirPow,
        /**并网：交流功率*/
        constPow,
        /**并网：直流下垂*/
        constDirDroop,
        /**并网：直流恒压恒流*/
        constDirVolCur,
        /**离网：离网电压*/
        constVolOff,
        /**离网：交流下垂*/
        constDroopOff,
        /**无功:恒定因数*/
        constWgFactor,
        /**无功:恒定功率*/
        constWgPow,
        /**无效项*/
        unkownMode
    };

    Q_ENUM(POWERWORKMODE);

    /**
     * @brief 光伏或类似新能源设备工作配置模式
     */
    enum PVWORKMODE {
        /**配置功率百分比，支持有功和无功*/
        POWERPERC = POWERWORKMODE::constDirVol, // 同PCS工作模式对齐
        /**功率因素配置，支持无功调节*/
        POWERFACTOR
    };

    Q_ENUM(PVWORKMODE);

    /**
     * @brief 空调配置字
     */
    enum AIRCONCONFIG {
        /**配置制冷参数*/
        //        cfgCool = POWERWORKMODE::constDirVol, // 同PCS工作模式对齐,
        SetCoolTarget = 0,
        /**配置制热参数*/
        //        cfgHeat,
        SetHeatTarget,
        /**配置除湿参数(温度型)*/
        //        cfgWetT,
        SetHumidityTarget,
        /**配置除湿参数(湿度型)*/
        cfgWetW,
        /**配置温度报警*/
        //        cfgTmpAlm,
        SetTmpAlm,
        /**配置湿度报警*/
        cfgWetAlm,
        /**强制制冷开关*/
        //        setCool,
        SetForcedCool,
        /**强制加热开关*/
        //        setHeat,
        SetForcedHeat,
        /**强制通风开关*/
        //        setAir
        SetForcedVentilation,
    };

    Q_ENUM(AIRCONCONFIG);

    /**
     * @brief 储罐工作模式
     * @date 2024-06-04
     */
    enum TANKRUNMODE {
        /**人工配速 下设手动基准速度*/
        MANUV = POWERWORKMODE::constDirVol, // 同PCS工作模式对齐,
        /**自动配速 参数可忽略*/
        AUTOV
    };
    Q_ENUM(TANKRUNMODE)

    /**
     * @brief 充放电方向枚举量(有功：正为放电，负为充电,无功：感性为负 容性为正)
     */
    enum POWERDIRECTFACTOR {
        /**电流禁止*/
        zero = 0,
        /**放电因子*/
        out = 1,
        /**充电因子*/
        in = -1,
        /**感性*/
        inductive = -1,
        /**容性*/
        capacitive = 1,
    };


    /**
     * @brief 阀门工作模式
     * @date 2024-09-25
     */

    enum VALVEGROUPCONCONFIG {
        SetWork = 0, //
    };

    Q_ENUM(VALVEGROUPCONCONFIG);


    /**
     * @brief 设备支持的指令列表
     */
    enum COMMANDLIST {
        /**
         *@brief 关机指令(ESB总线内传递此整型值)
         *@note
         * <pre>
         * 2、指令调用前调用方需保证设备状态允许设备开机动作
         * </pre>*/
        Close = 0,
        /**
         *@brief 开机指令(ESB总线内传递此整型值)
         *@note
         * <pre>
         * 2、指令调用前调用方需保证设备状态允许设备开机动作
         * </pre>*/
        Open,
        /**
         *@brief 待机指令(ESB总线内传递此整型值)
         *@note
         * <pre>
         * 2、指令调用前调用方需保证设备状态允许设备开机动作
         * </pre>*/
        Standy,
        /**从设备读取数据表信息*/
        ReadInfo,
        /**从本设备读取控制表信息*/
        ReadCtrl,
        /**从本设备读取全部表信息*/
        ReadAll,
        /**
         *@brief 设置有功功率参数(ESB总线内传递此整型值)
         *@note
         * <pre>
         * 1、仅供策略服务调用
         * 2、需要两参数（参数1 功率模式[POWERWORKMODE]；参数2 功率数值[float]）
         * 3、EMS内定义功率数值为正数(充电)，负数(放电）
         * </pre>*/
        SetYgPow,
        /**
         *@brief 设置无功功率参数(ESB总线内传递此整型值)
         *@note
         * <pre>
         * 1、仅供策略服务调用
         * 2、需要两参数（参数1 功率模式[POWERWORKMODE]；参数2 功率数值[float]）
         * 3、EMS内定义功率数值为正数(充电)，负数(放电）
         * </pre>*/
        SetWgPow,
        /**
         * @brief 设置指令响应的回应
         * @note
         * <pre>
         * 1、仅设置RESPONSE内Ready和unkownState状态以外的状态
         * 2、仅更新控制信息。
         * 3、仅设备服务调用
         * </pre>
         */
        Response,
        /**
         * @brief 使用物理设备数据表更新映射设备信息。
         * @note
         * <pre>
         * 1、设备服务端调用。
         * 2、仅更新设备数据相关内容，不影响控制信息。
         * </pre>
         */
        UpdateFromDevice,
        /**
         * @brief ESB缓存内设备数据表更新到映射设备信息。
         * @note
         * <pre>
         * 1、策略服务端调用。
         * 2、无条件更新物理设备数据
         * 3、输入控制信息较映射设备内新时更新映射设备数据。
         * </pre>
         */
        UpdateFromEsb,
        /**
         * @brief 更新设备健康状态。
         * @note
         * <pre>
         * 1、设备服务端调用。
         * 2、修改HealthStatus键值
         * 3、只能在设备健康状态范围内选择使用
         * </pre>
         */
        SetHealth,
        /**
         *@brief 读取设备健康状态
         */
        ReadHealth,
        /**
         *@brief 插入空指令
         *<pre>
         * 1、参数表：无
         * 2、约束：前一指令响应或超时时执行。
         *</pre>
         */
        Clear,
        /**获取设备支持的寄存器列表*/
        GetRegistors,
        /**并网指令*/
        OnGrid,
        /**离网指令*/
        OffGrid,
        /**就地指令*/
        Local,
        /**远程指令*/
        Remote,
        /**错误复位指令*/
        ResetError,
        /**获取面向具体设备的控制参数·服务配置工具*/
        GetDeviceControl,
        /**综合指令合成工具*/
        AddCommand,
        /**综合指令执行*/
        CompCmdExe,
        /**空调写命令*/
        AirConWrite,
        /**储罐写命令*/
        LqTankWrite,
        AnyCommand,
        /**储罐写命令*/
        ValveGroupWrite,
    };
    Q_ENUM(COMMANDLIST)

    /**
     * @brief PCS统一状态字
     * <pre>
     * 统一状态字配置严格按照(停机、故障、热备、自检、独立逆变、其它并网运行状态)顺序进行
     * </pre>
     */
    enum PCSSTATUS {
        UNKOWNSTATUS = 0,
        /**初始停机*/
        init = 1,
        /**紧急停机*/
        emergy = 2,
        /**待机*/
        standy = 4,
        /**直流恒流充电*/
        consDCurIn = 8,
        /**直流恒压充电*/
        consDVolIn = 16,
        /**直流恒功率充电*/
        consDpwIn = 32,
        /**交流恒功率充电*/
        consPwIn = 64,
        /**热备态（多机热备)*/
        sparing = 98,
        /**自检*/
        check = 99,
        /**运行*/
        run = 100,
        /**直流恒流放电*/
        consDCurOut = 256,
        /**直流恒压放电*/
        consDVolOut = 512,
        /**直流恒功率放电*/
        consDpwOut = 1024,
        /**交流恒功率放电*/
        consPwOut = 2048,
        /**独立逆变(离网模式 仅支持电压配置)*/
        ISOLATE = 8192,
        /**设备故障*/
        error = 65536,
        /**设备停机*/
        stopped = 131072
    };
    Q_ENUM(PCSSTATUS)

    /**
     * @brief PCS并离网状态
     */
    enum PCSGRIDSTATE {
        On = 0, // 并网
        Off     // 离网
    };

    enum BmsState {
        BMS_HEALTH           = 0xBBBB, // 正常
        BMS_FAULT            = 0xAAAA, // 故障
        BMS_ALARM            = 0x5555, // 告警
        BMS_STOP_CHARGING    = 0x1111, // 禁充
        BMS_STOP_DISCHARGING = 0x2222, // 禁放
        BMS_PRE_ALARM        = 0xCCCC  // 预警
    };

    /**
     * @brief 系统等级报警状态
     */
    enum EMSALARMLEVEL {
        /**正常态*/
        common = 0,
        /**预警*/
        alarm,
        /**故障*/
        fault,
        /**保护*/
        critical,
        /**制动*/
        emergystop
    };
    Q_ENUM(EMSALARMLEVEL)

    /**
     * @brief 储罐控制指令字
     * @date 2024-06-04
     */
    enum TANKINSTRMENT {
        NOP = 0,
        STOP,
        RUN
    };

    /**
     * @brief 储罐运行状态
     * @date 2024-06-04
     */
    enum TANKRUNSTATE {
        STOPPED = 0,
        STARTING,
        AUTO,
        MANUAL
    };

    /**
     * @brief 阈值报警测点参数表
     */
    enum MeasurePoint {
        LQFlow_Thred = 0,
        LQStress_Thred,
        LQLevel_Thred,
        LQTemp_Thred,
        StnVol_Thred,
        SglVol_Thred,
        StnCur_Thred,
        BankCur_Thred
    };
    Q_ENUM(MeasurePoint)

    /**
     * @brief 收益计算参数模型
     */
    enum ProfitModel {
        /**计算开关*/
        IsCalcProfit = 0,
        /**峰价*/
        peakPrice,
        /**谷价*/
        valleryPrice,
        /**平价*/
        balancePrice
    };
    Q_ENUM(ProfitModel)

    /*控制面板设备模型键定义*/
    /**
     * @brief 控制面板设备类型
     */
    enum KgUiPanelType {
        /**功率控制面板*/
        PowerCtrl = 0,
        /**监控交互面板*/
        MonitorCtrl,
        /**液流电池泵控制面板*/
        PumpCtrl,
        /**合成数据展示面板**/
        CombineScreen
    };

    Q_ENUM(KgUiPanelType);

    /**
     * @brief 控制面板设备 总合成屏幕键值
     */
    enum CombineScreenKeys {
        TotalShiZai = 0, // 总视在功率
        TotalYouGong,    // 总有功
        TotalWuGong,     // 总无功
        TotalACur,       // 总A相电流
        TotalBCur,       // 总B相电流
        TotalCCur,       // 总C相电流
        TotalFactor,     // 总功率因数
        TotalDayChgEQ,   // 日充电量
        TotalDayDChgEQ,  // 日放电量
        TotalChgEQ,      // 累计充电量
        TotalDChgEQ,     // 累计放电量
        TotalDayProf,    // 日收益数据
        TotalProf        // 累计收益值
    };
    Q_ENUM(CombineScreenKeys)

    /**
     *@brief 控制面板设备 监控设备操作键 页面修改 本地读取
     */
    enum MonitorCtrlWord {
        EmergySwitch, // 设置为1为紧急停机 0为允许开机 (只能页面手动设置)
    };
    Q_ENUM(MonitorCtrlWord)

    /**
     * @brief 控制面板设备 监控设备数据键 本地刷新 页面读取
     * */
    enum MonitorInfoWord {

        // 策略写入值 不读取
        AlarmLevel, // 阈值报警键 EMSALARMLEVEL (只能策略写入)
        // 报警阈值项 上限up(1~3) (0) 下限down(1~3)
        ThresFlowAlm,      // 1、管道流量
        ThresStressAlm,    // 2、管道压力：上限、下限
        ThresLevelAlm,     // 3、储罐液位：上限、下限
        ThresLqTmpAlm,     // 4、储罐温度：上限、下限
        ThresStackVolAlm,  // 5、簇电压：上限、下限
        ThresSingleVolAlm, // 6、堆(单体)电压：：上限、下限
        ThresStackCurAlm,  // 7、簇电流：：上限、下限
        ThresBankCurAlm,   // 8、单组电流：上限、下限
        // TODO:针对锂电池的报警项目
    };
    Q_ENUM(MonitorInfoWord)

    /**
     * @brief 控制面板设备 功率控制设备操作键 页面刷新 本地读取
     */
    enum PowerCtrlWord {
        // 页面写入
        SetManuMode = 0,
        ManuMode,
        CtrlOneStartStop,
        CtrlOneRemote, // 远程就地开关 0 远程 1就地 (只能页面手动设置)
        AGCDestYgMode, // 离网状态只能选择 离网电压模式
        AGCDestYgPower,
        AVCDestWgMode,
        AVCDestWgPower,
        Barns,      // 支路数量（策略单方面写)
        enableBars, // 0 总体 # 支路#
        BarnNumber, // 支路调度编号
        // 忽略配置开关，存在即动作
        EmergenceStop,  // 紧急关停
        CtrlOneParallel // 并离网开关
    };
    Q_ENUM(PowerCtrlWord)

    /**
     * @brief 控制面板设备 通用反馈信息（反馈手自动状态)
     */
    /*   enum CommanInfoWord
       {
           // 策略写入
           ManuMode = 0
       };*/
    //    Q_ENUM(CommanInfoWord)

    /**
     * @brief 控制面板设备 储罐控制操作键 页面写入 本地读取
     */
    enum PumpCtrlWord {
        // 页面写入
        SetManuModeS = 0,
        TANKDestPumpSpd, // 基准泵速 2为小数 单位 HZ
    };
    Q_ENUM(PumpCtrlWord)

    /**
     * @brief 电堆向下映射设备种类
     */
    enum KGSUBPACKTYPE {
        Kgunknown = -1,
        Kgstack   = 0,
        Kgbank,
        Kgsingle
    };
    Q_ENUM(KGSUBPACKTYPE)

    enum TransType {
        Bus2Str,
        Proto2Str,
        PowerMd2Str,
        Command2Str,
        MeasurePoint2Str,
        ProfitModel2Str,
        AlarmLevel2Str,
        PowerCtrl2Str,
        PumpMd2Str,
        AIRMd2Str,
        ValveGroupMd2Str,
    };

    /**
     * @brief 给定类型转为字符串
     * @param trans 指定要求转换的类型
     * @param type  指定待转换类型值
     * @return 类型字符串表达
     */
    static QString transType2String(const TransType &trans, int type)
    {
        QMetaEnum types;
        switch (trans) {
        case CEmsPropertySheet::Bus2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::EmsBus>();
            break;
        case CEmsPropertySheet::Proto2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::EmsProto>();
            break;
        case CEmsPropertySheet::PowerMd2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::POWERWORKMODE>();
            break;
        case CEmsPropertySheet::Command2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::COMMANDLIST>();
            break;
        case CEmsPropertySheet::MeasurePoint2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::MeasurePoint>();
            break;
        case CEmsPropertySheet::ProfitModel2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::ProfitModel>();
            break;
        case CEmsPropertySheet::AlarmLevel2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::EMSALARMLEVEL>();
            break;
        case CEmsPropertySheet::PowerCtrl2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::PowerCtrlWord>();
            break;
        case CEmsPropertySheet::PumpMd2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::TANKRUNMODE>();
            break;
        case CEmsPropertySheet::AIRMd2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::AIRCONCONFIG>();
            break;
        case CEmsPropertySheet::ValveGroupMd2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::VALVEGROUPCONCONFIG>();
            break;
        default:
            break;
        }
        QString &&typeName = types.key(type);
        return std::move(typeName);
    };

    static int transType2EnumValue(const TransType &trans, int type)
    {
        QMetaEnum types;
        switch (trans) {
        case CEmsPropertySheet::Bus2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::EmsBus>();
            break;
        case CEmsPropertySheet::Proto2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::EmsProto>();
            break;
        case CEmsPropertySheet::PowerMd2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::POWERWORKMODE>();
            break;
        case CEmsPropertySheet::Command2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::COMMANDLIST>();
            break;
        case CEmsPropertySheet::MeasurePoint2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::MeasurePoint>();
            break;
        case CEmsPropertySheet::ProfitModel2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::ProfitModel>();
            break;
        case CEmsPropertySheet::AlarmLevel2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::EMSALARMLEVEL>();
            break;
        case CEmsPropertySheet::PowerCtrl2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::PowerCtrlWord>();
            break;
        case CEmsPropertySheet::PumpMd2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::TANKRUNMODE>();
            break;
        case CEmsPropertySheet::AIRMd2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::AIRCONCONFIG>();
            break;
        case CEmsPropertySheet::ValveGroupMd2Str:
            types = QMetaEnum::fromType<CEmsPropertySheet::VALVEGROUPCONCONFIG>();
            break;


        default:
            break;
        }
        //        QString&& typeName = types.key(type);
        return types.value(type);
    };

    /**
     * @brief 功率设备指令合成辅助工具
     * @param appendOut
     * @param newCmd
     * @return 0 成功 1 插入指令重复 2 插入指令冲突 3 输入指令缺失必要数据 4 指令长度超标
     */
    static int AddCommandForPvPcs(QMap<QString, QVariant> &appendOut, const QMap<QString, QVariant> &newCmd, const bool &forceNew = false)
    {
        QMap<int, QList<int>> ConflictCmds;
        ConflictCmds[COMMANDLIST::Open]   = (QList<int>() << COMMANDLIST::Close << COMMANDLIST::Standy);
        ConflictCmds[COMMANDLIST::Standy] = (QList<int>() << COMMANDLIST::Open << COMMANDLIST::Close << COMMANDLIST::SetYgPow);
        ConflictCmds[COMMANDLIST::Close]  = (QList<int>() << COMMANDLIST::Open << COMMANDLIST::Standy);
        ConflictCmds[COMMANDLIST::OnGrid] = (QList<int>() << COMMANDLIST::OffGrid);
        ConflictCmds[COMMANDLIST::Remote] = (QList<int>() << COMMANDLIST::Local);
        ConflictCmds[COMMANDLIST::Clear]  = (QList<int>() << -1);
        int check                         = 3;
        /*冲突判断 0 无冲突 1 重复项 2 矛盾指令*/
        auto checkConflict = [&](const int &newCmd, const QString &oldCmd) -> int {
            if (COMMANDLIST::CompCmdExe == newCmd) {
                return 2;
            }
            QStringList &&oldCmds = oldCmd.split(",", Qt::SplitBehaviorFlags::SkipEmptyParts);
            QList<int> oldCmdlst;
            for (auto &str : oldCmds) {
                QStringList &&llst = str.split(":");
                oldCmdlst << llst.at(1).toInt();
            }
            if (oldCmdlst.contains(newCmd)) {
                return 1;
            }
            if (!oldCmdlst.isEmpty()) {
                oldCmdlst << newCmd; // 将新指令暂时插入队列
                for (auto &cmd : oldCmdlst) {
                    // 输入项判断
                    if (ConflictCmds.contains(cmd)) {
                        // 检索给定指令 cmd 的冲突指令表
                        const QList<int> &conflictEles = ConflictCmds.find(cmd).value();
                        for (auto &conflict : conflictEles) {
                            if (conflict < 0) {
                                // 独占性 指令 与所有指令冲突
                                return 2;
                            }
                            if (oldCmdlst.contains(conflict)) {
                                // 当前指令序列已存在同CMD冲突的指令
                                return 2;
                            }
                        }
                    }
                }
            }
            return 0;
        };
        QString prefix = "a";
        if (forceNew) {
            appendOut.clear();
        }
        if (newCmd.contains(INTKEY_COMMAND) && newCmd.contains(INTKEY_WKMODE) && newCmd.contains(INTKEY_WKPARAM)) {
            if (appendOut.isEmpty()) {
                // 新指令
                appendOut[INTKEY_COMMAND]   = "";
                appendOut[INTKEY_WKMODE]    = "";
                appendOut[INTKEY_WKPARAM]   = "";
                appendOut[INTKEY_WKPARAM_2] = "";
            }
            check = checkConflict(newCmd.find(INTKEY_COMMAND)->toInt(), appendOut.find(INTKEY_COMMAND)->toString());
            // 核算标记字符
            QString str = appendOut[INTKEY_COMMAND].toString();
            int lastPos = str.lastIndexOf(":");
            if (lastPos > 0) {
                prefix = str.mid(lastPos - 1, 1);
                if (prefix == 'z') {
                    check = 4;
                } else {
                    prefix = prefix.at(0).toLatin1() + 1;
                }
            }
            if (0 == check) {
                if (prefix != 'a') {
                    prefix = QString(",%1").arg(prefix);
                }
                // 附加指令
                str.append(QString("%1:%2").arg(prefix).arg(newCmd.find(INTKEY_COMMAND)->toString()));
                appendOut[INTKEY_COMMAND] = str;
                // 附加工作模式
                str = appendOut[INTKEY_WKMODE].toString();
                str.append(QString("%1:%2").arg(prefix).arg(newCmd.find(INTKEY_WKMODE)->toString()));
                appendOut[INTKEY_WKMODE] = str;
                // 附加参数
                str            = appendOut[INTKEY_WKPARAM].toString();
                QString &&str2 = appendOut[INTKEY_WKPARAM_2].toString();
                auto &&value   = newCmd.find(INTKEY_WKPARAM).value();
                if (value.type() != QVariant::List) {
                    str.append(QString("%1:%2").arg(prefix).arg(value.toDouble(), 0, 'f', 2));
                    str2.append(QString("%1:%2").arg(prefix).arg(0.0));
                } else {
                    auto &&val = value.toList();
                    str.append(QString("%1:%2").arg(prefix).arg(val.at(0).toDouble(), 0, 'f', 2));
                    str2.append(QString("%1:%2").arg(prefix).arg((val.size() > 1 ? val.at(1).toDouble() : 0.0), 0, 'f', 2));
                }
                appendOut[INTKEY_WKPARAM]   = str;
                appendOut[INTKEY_WKPARAM_2] = str2;
            }
        }
        return check;
    };
};

/**
 * @brief 功率命令结构
 */
struct EmsPowerPortCommand {
    /**接受命令的设备分类*/
    EMS_DEV category;
    /**命令字 关联设备的枚举代码*/
    int Command;
    /**模式 关联相关设备的模式代码*/
    int Mode;
    /**命令参数 可能多个参数，参数顺序有其固定意义*/
    QVariant value;
};

/**
 * @brief 功率命令字，多参数对位含义定义
 */
enum EmsPowerPortCommandParam {
    /**功率类参数 电压、电流、功率*/
    Power = 0,
    /**频率参数*/
    Freq
};

/**
 * @brief 电站并离网状态
 */
enum OFFGRIDSTATE {
    /**电网并网*/
    Parallel = 0,
    /**电网离网*/
    OffGrid,
    /**离并网无意义*/
    Inconsistent
};

/**
 * @brief 策略输入参数表
 */
enum INPUTSPARAM {
    /**判定类型*/
    type = 0,
    /**期望有功功率*/
    expect,
    /**负载有功功率*/
    load,
    /**关口有功功率*/
    gateway,
    /**储能发电功率*/
    generator,
    /**新能源发电功率*/
    pvgenerator,
    /**储能可用充电功率*/
    maxAllowChargePower,
    /**当前新能源限功率百分数*/
    currentLimitPerc,
    /**并网点并离网状态侦测*/
    onOffGridState
};

/**
 * @brief 策略输出参数表
 */
enum OUTPUTPARAM {
    /**PCS直接功率下设*/
    power = 0,
    /**新能源机组限功率百分比*/
    powPercent,
    /**下设电压值*/
    voltage,
    /**下设频率值*/
    freq
};

/**机组支路ID字符*/
typedef QString CEmsBarnID;
/**机组ID字符*/
typedef QString CEmsPortID;
/**机组内多设备单指令模式*/
typedef QMap<EMS_DEV, EmsPowerPortCommand> EmsPowerPortCommandList;

/**机组内多分支多指令模式*/
typedef QMap<int, QList<EmsPowerPortCommand>> EmsPowerPortCommandSet;

#endif // CEMSGLOBALDEFINES_H
