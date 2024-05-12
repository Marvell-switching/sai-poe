/*
 *  Copyright (C) 2024, MARVELL. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

#ifndef __POE_V3_H__
#define __POE_V3_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <h/sai/saitypes.h>

typedef struct poe_object_id_t {
    uint32_t id;
    uint32_t object_type;
} poe_object_id_t;

typedef struct poeObjectId {
    uint32_t id;
    uint32_t objecte;
} poeObjectId;

/* status */
typedef enum {
    poeOpOk = 0,
    poeOpFailed,
    poeOpNotSupported,
} poeOpResult;

typedef enum {
    poePortHwTypeAf = 0,
    poePortHwTypeAt,
    poePortHwType60W,
    poePortHwTypeBt3,
    poePortHwTypeBt4,
    /* must be last */
    poePortHwTypeInvalid
} poePortHwType;

typedef struct poePowerManagementUnitDb {
    /* set */
    uint32_t mainPsePowerMw;
    uint32_t mainPseConsumptionPowerMw;
    uint32_t calculatedPowerMw;
    uint32_t availablePowerMw;
} poePowerManagementUnitDb;

typedef uint32_t Unite;
#define UniteNone 0
#define UnitePse 1
#define UnitePd 2
#define UnitePsePd 3

typedef uint8_t PowerLimitMode;
#define PowerLimitModePort 0
#define PowerLimitModeClass 1

typedef struct poeDeviceDb {
    uint32_t deviceId;
    uint32_t totalPower;
    uint32_t powerConsumption;
    char *version;
    PowerLimitMode powerLimitMode;
    uint32_t allocatedPower;
    poePowerManagementUnitDb powerManagement;                                                     
    Unite unite;
} poeDeviceDb;

typedef uint8_t poeV3PseStatus;
#define poeV3PseStatusNr 0
#define poeV3PseStatusActive 1
#define poeV3PseStatusI2cFailure 2
#define poeV3PseStatusNotPresent 0xFF

#define poeMaxNumOfPseDevsInUnit 16

typedef struct poeDeviceSysStatus {
    union{
        poeV3PseStatus pseStatus[poeMaxNumOfPseDevsInUnit];
        uint8_t hwPseSt[poeMaxNumOfPseDevsInUnit];
    }param;
} poeDeviceSysStatus;

typedef struct poePseDb {
    uint32_t pseId;
    char *softwareVersion ;
    char *hardwareVersion;
    int16_t temperature;                                                     
    poeDeviceSysStatus status;
} poePseDb;

typedef uint16_t poeV3BtClass;
#define poeV3BtClassNoClass 0
#define poeV3BtClassClass1 1
#define poeV3BtClassClass2 2
#define poeV3BtClassClass3 3
#define poeV3BtClassClass4 4
#define poeV3BtClassClass5 5
#define poeV3BtClassClass6 6
#define poeV3BtClassClass7 7
#define poeV3BtClassClass8 8
#define poeV3BtClassNa 0xFFFF

typedef uint16_t poeV3BtClassMethod;
#define poeV3BtClassMethodRegular 1
#define poeV3BtClassMethodAutoClass 2

typedef struct poeBtPowerClassifications {
    poeV3BtClass btPortAltASsMeasuredClass;  /* Ss or Ds-Alt-A measured class */
    poeV3BtClass btPortAltASsAssignedClass;  /* Ss or Ds-Alt-A assigned class */
    poeV3BtClass btPortAltBMeasuredClass;    /* Ds-Alt-B measured class */
    poeV3BtClass btPortAltBAssignedClass;    /* Ds-Alt-B assigned class */
    poeV3BtClassMethod btPortClassMethod;
} poeBtPowerClassifications;

typedef struct poeAtPowerClassifications {
    poeV3BtClass pethPsePortPowerClassifications;
} poeAtPowerClassifications;

typedef uint16_t poeV3BtSignaturee;
#define poeV3BtSignatureeSingle 1
#define poeV3BtSignatureeDual 2

typedef struct poePowerClassifications {
    poeV3BtSignaturee signaturee;
    poeAtPowerClassifications poeAtClass;
    poeBtPowerClassifications poeBtClass;
}poePowerClassifications;

typedef uint8_t poeV3PortActiveChannel;
#define poeV3PortActiveChannelA 1
#define poeV3PortActiveChannelB 2
#define poeV3PortActiveChannelAB 3

typedef struct poeOutputData {
    poeV3PortActiveChannel activeChannel;
    uint32_t outputVoltage;
    uint32_t outputCurrent;
    uint32_t outputPower;
} poeOutputData;

typedef uint8_t poePortDetectionStatus;
#define poePortDetectionStatusOff 1
#define poePortDetectionStatusSearching 2
#define poePortDetectionStatusDeliveringPower 3
#define poePortDetectionStatusFault 4

typedef uint8_t poeV3PortStatus;
#define poeV3PortStatusOnResDetect 1
#define poeV3PortStatusOnCapDetect 2
#define poeV3PortStatusOn4Pair 3
#define poeV3PortStatusOnForce4Pair 4
#define poeV3PortStatusOffVoltHigh 5 /* Deprecated */
#define poeV3PortStatusOffVoltLow 6
#define poeV3PortStatusOffHwPinDisPort 7
#define poeV3PortStatusOffUserDisable 8
#define poeV3PortStatusOffInDetection 9
#define poeV3PortStatusOffPdNoStandard 10
#define poeV3PortStatusOffOverUnderLoad 11
#define poeV3PortStatusOffUnderload 12
#define poeV3PortStatusOffOverload 13
#define poeV3PortStatusOffPwrBudgExc 14
#define poeV3PortStatusOffVoltInj 15
#define poeV3PortStatusOffCapDetInvSig 16
#define poeV3PortStatusOffDischarged 17
#define poeV3PortStatusOnForceOn 18
#define poeV3PortStatusOffPwErr 19
#define poeV3PortStatusOffPwBudget 20
#define poeV3PortStatusOffShortCond 21
#define poeV3PortStatusOffOverTemp 22
#define poeV3PortStatusOffDeviceHot 23
#define poeV3PortStatusOffClassError 24
#define poeV3PortStatusOffRLowDetect 25
#define poeV3PortStatusOffPowerOnVerificationFault 26
#define poeV3PortStatusOnNonStdBtdevice 27
#define poeV3PortStatusOffUnreachable 28
#define poeV3PortStatusAltBSingleSignature 255

typedef struct poeDetectionStatus {
    /* input */
    /* output */
    bool capacitorSignatureDetected;
    poeV3PortStatus poePseHwPortStatus;      /* PSE side - real port status from HW */
    uint32_t unknownErrorInternalStatus;
    poeV3PortStatus poePseHwPortStatusAltB;
    uint32_t unknownErrorInternalStatusAltB;
} poeDetectionStatus;


typedef enum {
    poePsePortPowerPriorityCritical =  1,
    poePsePortPowerPriorityHigh =      2,
    poePsePortPowerPriorityLow =       3
} poePsePortPowerPriority;

typedef uint8_t poeV3PowerMngMode;
#define poeV3PowerMngModeDynamic 0
#define poeV3PowerMngModeStatic 1

typedef struct poePortConfigurableData {
    bool pethPsePortAdminEnable;         
    poePsePortPowerPriority pethPsePortPowerPriority;       
    uint32_t pethPsePortPowerLimit;          
    bool legacySupportStatus;          
    poeV3PowerMngMode powerMngStatus;               
    poeV3BtClass poePortClassLimit;
    bool numOfEvents;        
} poePortConfigurableData;


typedef struct poePortPowerConsumptionDataDb {
    poePowerClassifications poePortPowerClassifications;
    poeOutputData poePortOutputData;
    poeDetectionStatus poePortDetectionStatus;
    uint32_t portStaticModeAllocPower;
    uint32_t portBtPrimaryAltAllocPower;
    uint32_t portBtSecondaryAltAllocPower;
} poePortPowerConsumptionDataDb;

/* Port POE DB, per physical port */
typedef struct poePortDb {
    /* key */
    uint32_t frontPanelIndex;
    /* hw related params */
    poePortHwType portStandard;
    uint32_t physicalIndexA;
    uint32_t physicalIndexB;
    /* power related param s*/
    poePortPowerConsumptionDataDb powerConsumptionData; 
    /* set params - user configurable data*/
    poePortConfigurableData configurableData;
    /* read only params */
    poeDetectionStatus status;
    uint32_t maxPowerLimit;
    bool operStatus;                                                                               
} poePortDb;

#define poeGetSystemStatusStubCreateMac(__funcName)  \
    BOOLEAN __funcName (                                               \
        BOOLEAN hwMode,                                                \
        /*!     OUTPUTS:        */                                      \
        poeDeviceSysStatus *oSysStatusPtr)

typedef enum {
    poeVendorNone = 0,
    poeVendorMicrochip,
    poeVendorTi, 
    poeVendorAdi,
    poeVendorLast
} poeVendor;

typedef enum {
    poeCommunicationModeBlocking = 0,
    poeCommunicationModeNonBlocking,
    poeCommunicationModeLast
} poeCommunicationMode;

typedef enum {
    poeGuardBandModeNotSupported = 0,
    poeGuardBandModeDynamic,
    poeGuardBandModeStatic
} poeGuardBandMode;

typedef uint8_t HappoePortBtSige;
#define HappoePortBtSigeSingle 0
#define HappoePortBtSigeDual 1


typedef enum {
    HappoePortBtChannelAltA,
    HappoePortBtChannelAltB,
    HappoePortBtChannelAltBoth
} HappoePortBtChannelAlt;

/* Current Version Constants */
#define poeV3DragoniteVersionNum 0xe000100 /* November 26th, 2017: Dragonite FW 0xE.0x0.0x1.0x0 */

/**** General parameters ****/
#define poeV3MaxNumOfPse 16
#define poeV3InvalidTemperature 0x7FFF

#define poeV3MsgPortLayer2CdpPseDataPortIsOnCdp 0x2000
#define poeV3MsgPortLayer2CdpPseDataPortIsOnLldp 0x3000

typedef uint8_t poeV3DevHwVersion;
#define poeV3DevHwVersionLtc4291 0x38 /* 802.3 BT: LTC4291 */

/**** Message parameters ****/
#define ExtDrvIpcMaxMsgSize 256 
#define poeV3MsgMaxSize ExtDrvIpcMaxMsgSize

#define poeV3MsgHeaderSize 8  /* Bytes */
#define poeV3MsgMaxDataSize (poeV3MsgMaxSize - poeV3MsgHeaderSize)

typedef uint8_t poeV3MsgLevel;
#define poeV3MsgLevelSystem 0
#define poeV3MsgLevelPort 1
#define poeV3MsgLevelCause 2
#define poeV3MsgLevelDebug 3
 
typedef uint8_t poeV3MsgDirection;
#define poeV3MsgDirGet 0
#define poeV3MsgDirSet 1

typedef struct poeV3MsgOpCodeInfo {
    poeV3MsgLevel level;
    poeV3MsgDirection direction;
    uint16_t msgIdSwap;
} poeV3MsgOpCodeInfo;

typedef union poeV3MsgOpCode {
    poeV3MsgOpCodeInfo params;
    uint32_t opCodeNum32;
} poeV3MsgOpCode;

/*** system messages id's ***/
#define poeV3SysMsgPortMatrix 0x1
#define poeV3SysMsgPortSupportStandard 0x2
#define poeV3SysMsgPowerBankConfig 0x4
#define poeV3SysMsgActiveRpsPowerBank 0x10
#define poeV3SysMsgPowerLimitMode 0x20
#define poeV3SysMsgL2AllocSetting 0x40
#define poeV3SysMsgPowerConsumption 0x80
#define poeV3SysMsgSystemVersion 0x100
#define poeV3SysMsgPseTemperature 0x101
#define poeV3SysMsgUpgReadyStatus 0x102
#define poeV3SysMsgUpgDataTrans 0x103
#define poeV3SysMsgUpgStatus 0x104
#define poeV3SysMsgServiceNotification 0x105
#define poeV3SysMsgPseStatus 0x106
#define poeV3SysMsgFirmwareReadiness 0x107

/*** system messages types ***/
typedef uint8_t poeV3PortSupStandard;
#define poeV3PortSupStandardAf 1
#define poeV3PortSupStandardAt 2
#define poeV3PortSupStandard60 3
#define poeV3PortSupStandardBte2 4
#define poeV3PortSupStandardBte3 5
#define poeV3PortSupStandardBte4 6

typedef uint8_t poeV3PowerLimitMode;
#define poeV3PowerLimitModePort 0
#define poeV3PowerLimitModeClass 1

typedef uint8_t poeV3OperationMode;
#define poeV3OperationModeIndependent 1
#define poeV3OperationModeNormal 2

typedef uint8_t poeV3L2AllocPriorty;
#define poeV3L2AllocPriortyNoraml 0
#define poeV3L2AllocPriortyHigh 1

typedef uint8_t poeV3L2AllocMngMode;
#define poeV3L2AllocMngModeAsPort 0
#define poeV3L2AllocMngModeStatic 1

typedef uint8_t poeV3UpgReadinesss;
#define poeV3UpgReadinesssRefuse 0
#define poeV3UpgReadinesssReady 1

typedef uint16_t poeV3UpgBlocke;
#define poeV3UpgBlockeStandard 0
#define poeV3UpgBlockeFinal 1
#define poeV3UpgBlockeUnPlTerm 2   /* unplanned termination */

typedef uint8_t poeV3UpgStatusCode;
#define poeV3UpgStatusCodeSuccess 0
#define poeV3UpgBlockeRetryBlock 1
#define poeV3UpgBlockeRestart 2
#define poeV3UpgBlockeAbort 3
#define poeV3UpgBlockeProcessing 4

typedef uint8_t poeV3FirmwareReadiness;
#define poeV3FirmwareReadinessInit 0
#define poeV3FirmwareReadinessReady 1

#define poeMaxNumOfPhysPorts 48
#define poeMaxNumOfPowerBanks 16

/*** system messages messages structs ***/
typedef struct poeV3MsgSysPortMatrix {
    struct {
        uint8_t  logicalPort;
        uint8_t  physPort;
    }physicLogicalPair[poeMaxNumOfPhysPorts];
} poeV3MsgSysPortMatrix;

typedef struct poeV3MsgSysPortSupportedStd {
    struct{
        uint8_t                                 logicPort;
        poeV3PortSupStandard portSupportedStd;
    }supportedStdData[poeMaxNumOfPhysPorts];
} poeV3MsgSysPortSupportedStd;

typedef struct poeV3MsgSysPowerBank {
    uint16_t powerBankWSwap[poeMaxNumOfPowerBanks];
} poeV3MsgSysPowerBank;

typedef struct poeV3MsgSysActiveRpsPowerBank {
    uint8_t activeRpsPowerBankIndex;
} poeV3MsgSysActiveRpsPowerBank;

typedef struct poeV3MsgSysPowerLimitMode {
    poeV3PowerLimitMode   limitMode;
} poeV3MsgSysPowerLimitMode;

typedef struct poeV3MsgSysL2AllocSetting {
    poeV3L2AllocPriorty   priority;
    poeV3L2AllocMngMode   mngMode;
} poeV3MsgSysL2AllocSetting;

typedef struct poeV3MsgSysPowerConsumption {
    uint32_t                                  powerConsumptionSwap;
    uint32_t                                  powerAllocationSwap;
} poeV3MsgSysPowerConsumption;

typedef struct poeV3MsgSysServiceNotification {
    poeV3OperationMode                          operationMode;
    uint8_t                                     reserved[3];
} poeV3MsgSysServiceNotification;

typedef struct poeV3MsgSysFirmwareReadiness {
    poeV3FirmwareReadiness                      firmwareReadiness;
    uint8_t                                     reserved[3];
} poeV3MsgSysFirmwareReadiness;

#define poeFwVersionNumOfBytes 4

typedef union poeV3MsgSwVersion {
    uint8_t  verBytes[poeFwVersionNumOfBytes];
    uint32_t verNum;
} poeV3MsgSwVersion;

typedef struct poeV3MsgSysSystemVersion {
    /* outputs */
    poeV3MsgSwVersion   poeFwVersion;
    poeV3MsgSwVersion   converterSwVersion;
    struct {
        uint8_t                              pseSwVersion;
        uint8_t                              pseHwVersion;
    }pseVersionData[poeV3MaxNumOfPse];
} poeV3MsgSysSystemVersion;

typedef struct poeV3MsgSysPseTemperature {
    /* outputs */
    int16_t              pseTempSwap[poeV3MaxNumOfPse];
} poeV3MsgSysPseTemperature;

typedef struct poeV3MsgSysPseStatus {
    /* outputs */
    poeV3PseStatus    pseStatus[poeV3MaxNumOfPse];
} poeV3MsgSysPseStatus;

typedef struct poeV3MsgSysUpgReadyStatus {
    /* outputs */
    poeV3UpgReadinesss    readiness;
    uint8_t                                  reserved;
    uint16_t                                 blockSizeSwp;
} poeV3MsgSysUpgReadyStatus;

#define poeV3MsgUpgDataMaxSize (poeV3MsgMaxDataSize-12)

typedef struct poeV3MsgSysUpgDataTrans {
    uint32_t             pseVersionIdSwp;
    uint16_t             blockNumSwp;
    uint16_t             blockeSwp;
    uint16_t             checksumSwp;
    uint16_t             reserved;
    uint8_t              data[poeV3MsgUpgDataMaxSize];
} poeV3MsgSysUpgDataTrans;

typedef struct {
    uint16_t                                 block_num_swp;
    poeV3UpgStatusCode                       statusCode;
    bool                                     err_exists;
    char                                     err_msg[32];
} poeV3MsgSysUpgStatus;


/*** End of system level ***/

/***************************/

/*** port messages id's ***/
#define poeV3PortMsgPortEnableCns          0x10
#define poeV3PortMsgPhysClassMethodCns     0x11
#define poeV3PortMsgLegacyDetectedCns      0x12
#define poeV3PortMsgAltBEnableCns          0x14
#define poeV3PortMsgPortPowerLimitCns      0x20
#define poeV3PortMsgPortPriorityCns        0x21
#define poeV3PortMsgPowerMngCns            0x22
#define poeV3PortMsgBtAutoClassCns         0x23
#define poeV3PortMsgPortClassLimitCns      0x24
#define poeV3PortMsgL2ReqPowerLldpCns      0x40
#define poeV3PortMsgL2ReqPowerLins      0x41
#define poeV3PortMsgAllocPowerCns          0x42
#define poeV3PortMsgBtManualAutoClassCns   0x43
#define poeV3PortMsgPowerConsumInfoCns     0x80
#define poeV3PortMsgPortStatusCns          0x81
#define poeV3PortMsgPortCountersCns        0x82
#define poeV3PortMsgPortConfigCns          0x83

/*** port messages types ***/

typedef uint8_t poeV3PortAdmin;
#define poeV3PortAdminDisableCns   0
#define poeV3PortAdminEnableCns    1
#define poeV3PortAdminInvalidCns   0xff

typedef uint8_t poeV3PhysLayerClass;
#define poeV3PhysLayerClass1EventCns   1
#define poeV3PhysLayerClass2EventCns   2

typedef uint8_t poeV3LegacyMode;
#define poeV3LegacyModeDisableCns       0
#define poeV3LegacyModeEnableCns        1
#define poeV3LegacyModeAutoCns          2

typedef uint8_t poeV3AltBMode;
#define poeV3AltBModeDisableCns       0
#define poeV3AltBModeEnableCns        1
#define poeV3AltBModeForceEnableCns   2

typedef uint8_t poeV3PortPriority;
#define poeV3PortPriorityLowCns        0
#define poeV3PortPriorityHighCns       1
#define poeV3PortPriorityCriticalCns   2

typedef uint8_t poeV3ClassLimit;
#define poeV3ClassLimitUnlimitedCns     0
#define poeV3ClassLimitClass3Cns        3
#define poeV3ClassLimitClass4Cns        4
#define poeV3ClassLimitClass5Cns        5
#define poeV3ClassLimitClass6Cns        6
#define poeV3ClassLimitClass7Cns        7

typedef uint8_t poeV3PortPowerAllocBy;
#define poeV3PortPowerAllocByHwCns     0
#define poeV3PortPowerAllocByLldpCns   1
#define poeV3PortPowerAllocByCdpCns    2

#define poeV3PortStatusMaxStatusCns poeV3PortStatusOffUnreachableCns /* must be updated whenever a new status added above */

typedef uint8_t poeV3BtAutoClass;
#define poeV3BtAutoClassDisabledCns     0
#define poeV3BtAutoClassAutoCns         1
#define poeV3BtAutoClassForceCns        2

typedef uint8_t poeV3BtAutoClassAction;
#define poeV3BtAutoClassActionDoNothingCns  0
#define poeV3BtAutoClassActionInitCalcCns   1

#define poeV3PowerRequestNrCns          MaxUint32T

/*** port level messages structs ***/
typedef struct {    
    uint8_t                              logicPortNum;
    poeV3PortAdmin                       portAdminEnableDisable;
    uint8_t                              reserved[2];
} poeV3MsgPortEnable;

typedef struct {    
    uint8_t                                  logicPortNum;
    poeV3PhysLayerClass   numOfEvents;
    uint8_t                                  reserved[2];
} poeV3MsgPortPhysLayerClassMethod;

typedef struct {
    uint8_t                              logicPortNum;
    poeV3LegacyMode   legacyMode;
} poeV3MsgPortLegacy;

typedef struct {
    uint8_t                              logicPortNum;
    poeV3AltBMode                        altbMode;
    uint8_t                              reserved[2];
} poeV3MsgPortAltB;

typedef struct {
    uint8_t                              logicPortNum;
    uint8_t                              reserved[3];
    uint32_t                             powerLimitMwSwap;
} poeV3MsgPortPowerLimit;

typedef struct {
    uint8_t                                  logicPortNum;
    poeV3PortPriority                        portPriority;
    uint8_t                                  reserved[2];
} poeV3MsgPortPriority;

typedef struct {
    uint8_t                              logicPortNum;
    poeV3PowerMngMode mngMode;
    uint8_t                              reserved[2];
} poeV3MsgPortPowerMngMode;

typedef struct {
    uint8_t                              logicPortNum;
    poeV3ClassLimit   classLimitVal;
    uint8_t                              reserved[2];
} poeV3MsgPortClassLimit;

typedef struct {
    uint8_t                              logicPortNum;
    uint8_t                              reserved[3];
    uint32_t                             powerRequestMwSwap;
    uint32_t                             powerRequestBMwSwap;
} poeV3MsgPortSetL2PowerReqLldp;

typedef struct {
    uint8_t              logicPortNum;
    uint8_t              reserved[3];
    uint32_t             powerRequestMwSwap[4];
} poeV3MsgPortSetL2PowerReqList;

typedef struct {
    uint8_t                                      logicPortNum;
    poeV3PortPowerAllocBy     allocBy;
    uint8_t                                      reserved[2];
    uint32_t                                     powerAllocMwSwap;
    uint32_t                                     powerSuppliedMwSwap;
    uint32_t                                     powerAllocBMwSwap;
    uint32_t                                     powerSuppliedBMwSwap;
} poeV3MsgPortGetAllocPower;

typedef struct {
    uint8_t                                      logicPortNum;
    uint8_t                                      reserved[3];
    uint8_t                                      state; /* admin enable/disable */
    poeV3PhysLayerClass                          numOfEvents;
    poeV3LegacyMode                              legacySupport;
    poeV3AltBMode                                altBMode;
    poeV3PortPriority                            priority;
    poeV3PortPriority                            mngMode;
    poeV3BtAutoClass                             autoClass;
    poeV3ClassLimit                              classLimit;
    uint32_t                                     powerLimitSwap;
} poeV3MsgPortGetConfig;

typedef struct {
    uint8_t                                      logicPortNum;
    poeV3PortActiveChannel                       activeChannel;
    uint8_t                                      reserved[2];
    uint32_t                                     voltageInVoltsSwap;
    uint32_t                                     currentInMaSwap;
    uint32_t                                     powerInMwSwap;
    uint32_t                                     classificationSwap;
} poeV3MsgPortPowerConsumInfo;

typedef struct {
    uint8_t                                      logicPortNum;
    poeV3PortStatus                              portStatusA;
    poeV3PortStatus                              portStatusB;
    uint8_t                                      reserved;
} poeV3MsgPortStatus;

typedef struct {
    uint8_t                          logicPortNum;
    uint8_t                          reserved[3];
    uint32_t                         invalidSinatureSwap;
    uint32_t                         invalidSinatureASwap;
    uint32_t                         invalidSinatureBSwap;
    uint32_t                         powerDeniedSwap;
    uint32_t                         powerDeniedASwap;
    uint32_t                         powerDeniedBSwap;
    uint32_t                         overloadSwap;
    uint32_t                         overloadASwap;
    uint32_t                         overloadBSwap;
    uint32_t                         shortSwap;
    uint32_t                         absentSwap;
    uint32_t                         absentASwap;
    uint32_t                         absentBSwap;
} poeV3MsgPortCounters;

/** BT **/
typedef struct {
    uint8_t                              logicPortNum;
    poeV3BtAutoClass  autoClassStatus;
    uint16_t                             reserved;
} poeV3MsgPortBtAutoClass;

typedef struct {
    uint8_t                                      logicPortNum;
    poeV3BtAutoClassAction                       action;
    uint16_t                                     reserved;
} poeV3MsgPortBtAutoClassAction;

typedef struct {
    uint8_t                                      logicPortNum;
    poeV3PortActiveChannel                       activeChannel;
    uint8_t                                      reserved[2];
    uint32_t                                     voltVSwap;
    uint32_t                                     currentMaSwap;
    uint32_t                                     consumpMwSwap;
    poeV3BtSignaturee                            signatureTypeSwap;
    poeV3BtClassMethod                           classMethodSwap;
    uint16_t                                     measuredClassASwap;
    uint16_t                                     assignedClassASwap;
    uint16_t                                     measuredClassBSwap;
    uint16_t                                     assignedClassBSwap;
} poeV3MsgPortBtPowerConsumInfo;


/*** End of port level ***/

/***************************/

/*** cause messages id's ***/
#define poeV3CausePortStatusCns             0x80

typedef struct {    
    union{
        uint8_t          portStatusChangeBitmap[8];
        uint64_t         portChangeNum;
    };
} poeV3MsgCausePortStatus;

/* messages union */
typedef union {
    uint8_t                                              data[poeV3MsgMaxDataSize];
    /* system level */
    poeV3MsgSysPortMatrix            sysPortMatrixParams;
    poeV3MsgSysPortSupportedStd      sysPortSupportStdParams;
    poeV3MsgSysPowerBank             sysPowerBankParams;
    poeV3MsgSysActiveRpsPowerBank    sysActiveRpsPowerBankParams;
    poeV3MsgSysPowerLimitMode        sysPowerLimitModeParams;
    poeV3MsgSysL2AllocSetting        sysL2AllocSettingParams;
    poeV3MsgSysPowerConsumption      sysPowerConsumptionParams;
    poeV3MsgSysSystemVersion         sysSystemVerionParams;
    poeV3MsgSysPseTemperature        sysPseTemperatureParams;
    poeV3MsgSysPseStatus             sysPseStatusParams;
    poeV3MsgSysUpgReadyStatus        sysUpgReadyStatusParams;
    poeV3MsgSysUpgDataTrans          sysUpgDataTransParams;
    poeV3MsgSysUpgStatus             sysUpgStatusParams;
    poeV3MsgSysServiceNotification   sysServiceNotificationParams;
    poeV3MsgSysFirmwareReadiness     sysFirmwareReadinessParams;

    /* port level */
    poeV3MsgPortEnable               portEnaleDisableParams;
    poeV3MsgPortPhysLayerClassMethod portPhysClassParams;
    poeV3MsgPortLegacy               portLegacyParams;
    poeV3MsgPortAltB                 portAltbParams;
    poeV3MsgPortPowerLimit           portPowerLimitParams;
    poeV3MsgPortPriority             portPriorityParams;
    poeV3MsgPortPowerMngMode         portPowerMngModeParams;
    poeV3MsgPortClassLimit           portClassLimitParams;
    poeV3MsgPortSetL2PowerReqLldp    portL2PowerReqLldpSetParams;
    poeV3MsgPortSetL2PowerReqList    portL2PowerReqListSetParams;
    poeV3MsgPortGetAllocPower        portAllocPowerGetParams;
    poeV3MsgPortPowerConsumInfo      portPowerConsumInfoParams;
    poeV3MsgPortStatus               portStatusParams;
    poeV3MsgPortCounters             portCountersParams;
    poeV3MsgPortGetConfig            portConfigGetParams;
    /* port level - BT */
    poeV3MsgPortBtAutoClass          portBtAutoClassParams;
    poeV3MsgPortBtAutoClassAction    portBtAutoClassActionParams;
    poeV3MsgPortBtPowerConsumInfo    portBtPowerConsumInfoParams;
    /* cause level */
    poeV3MsgCausePortStatus          causePortStatusParams;
} poeV3MsgUnt;

/* PSE FW update - PSE FW header*/
typedef struct
{
    uint8_t              headerSize;    /* header size, include this byte */
    uint32_t             versionIdSwap;
} poeV3PseUpdateFwHeader;

/**** Messages MACROs ****/
#define poeV3SetMsgOpCodeMac(_opcode, _level, _dir, _id)   \
    memset(&_opcode, 0, sizeof(_opcode));                                   \
    _opcode.params.level = _level;                                          \
    _opcode.params.direction = _dir;                                        \
    _opcode.params.msgIdSwap = swap16(_id);

#define poeConvertHwToDetectionStatusMac(_portStatus, _detectionStatus)   \
    _detectionStatus = poeDetectionStatusOffCns;                \
    switch (_portStatus) {                                                             \
        case poeV3PortStatusOffInDetectionCns:                  \
        case poeV3PortStatusOffCapDetInvSigCns:               \                   \
            _detectionStatus = poeDetectionStatusSearchingCns;       \
            break;                                                                      \
        case poeV3PortStatusOnCapDetectCns:                         \
        case poeV3PortStatusOnResDetectCns:                         \
        case poeV3PortStatusOn4PairCns:                                \
        case poeV3PortStatusOnNonStdBTdeviceCns:                        \
            _detectionStatus = poeDetectionStatusDeliveringPowerCns; \
            break;                                                                      \
        case poeV3PortStatusOffUserDisableCns:                      \
            _detectionStatus = poeDetectionStatusOffCns;        \
            break;                                                                      \                                                                    \                                                                     \
        default:                                                                        \
            _detectionStatus = poeDetectionStatusFaultCns;      \
            break;                                                                      \
    }

poeOpResult InternalCreateObject(poeObjectId *poeObjectId);
poeOpResult poeInitialize(void);
bool poePortGetFirstIndex(uint32_t *frontPanelIndex);
bool poePortGetNextIndex(uint32_t *frontPanelIndex);
poePortHwType poeGetPortpoeHwe(uint32_t frontPanelIndex);
bool poePortGetPhysicalIndex(uint32_t frontPanelIndex, uint32_t *physicalIndex);
bool poePortGetSecondPhysicalIndex(uint32_t frontPanelIndex, uint32_t *physicalIndex);
bool ExthwgpoeIpcSendRecieveMsg(bool send, uint32_t opCode, uint8_t dataLen, uint8_t *data);
poeOpResult poeV3SendReceiveMsg(poeV3MsgLevel msge, poeV3MsgDirection direction, uint16_t msgId, uint8_t dataLen, void *dataPtr);
poeOpResult poePortMatrixInitialize();
poeOpResult poePortStandardInitialize();
poeOpResult poePowerBankInitialize();
poeOpResult poeDevGetTotalPower(int32_t poeDevNum, int32_t *totalPowerMwPtr);
poeOpResult poeDevGetPowerConsumption(int32_t poeDevNum, int32_t *powerConsumptionMwPtr);
poeOpResult poeDevGetVersion(int32_t poeDevNum, char *versionPtr);
poeOpResult poeDevGetPowerLimitMode(uint32_t poeDevNum, uint32_t *powerLimitPtr);
poeOpResult poeDevSetPowerLimitMode(uint32_t poeDevNum, uint32_t powerLimitPtr);
poeOpResult poePseGetSoftwareVersion(int32_t poePseNum, char *versionPtr);
poeOpResult poePseGetHardwareVersion(int32_t poePseNum, char *versionPtr);
poeOpResult poePseGetTemperature(int32_t poePseNum, int16_t *temperaturePtr);
poeOpResult poePseGetStatus(int32_t poePseNum, int16_t *statusPtr);
poeOpResult poePortGetPortStandard(uint32_t frontPanelIndex, bool *portStandardPtr);
poeOpResult poePortSetAdminEnable(uint32_t frontPanelIndex, const bool enable);
poeOpResult poePortGetAdminEnable(uint32_t frontPanelIndex, bool *enablePtr);
poeOpResult poePortSetPowerLimit(uint32_t frontPanelIndex, const uint32_t powerLimit);
poeOpResult poePortGetPowerLimit(uint32_t frontPanelIndex, uint32_t *powerLimitPtr);
poeOpResult poePortSetPowerPriority(uint32_t frontPanelIndex, const uint32_t powerPriority);
poeOpResult poePortGetPowerConsumption(uint32_t frontPanelIndex, sai_poe_port_power_consumption_t *powerConsumptionPtr);
poeOpResult poePortGetStatus (uint32_t frontPanelIndex, uint32_t *statusPtr);
uint16_t swap16(uint16_t value);
uint32_t swap32(uint32_t value);


typedef struct {
    bool is_poe_device_initialized;
} global_poe;


#endif /** __POE_V3_H_ */