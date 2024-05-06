/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
********************************************************************************
*/
/**
********************************************************************************
* @file cpssDriverPpHw.h
*
* @brief CPSS PP Driver Hardware Access API
*
* @version   8
********************************************************************************
*/
#ifndef __cpssDriverPpHwh
#define __cpssDriverPpHwh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <h/ipc/cpssTypes.h>
#include <h/ipc/cpssHwInfo.h>


/*******************************************************************************
*   Note: about the 'portGroupId' parameter , in the next APIs.
*   portGroupId - The port group Id. relevant only to 'multi-port-groups' devices.
*       when value is CPSS_PORT_GROUP_UNAWARE_MODE_CNS :
*       1. For write APIs CPSS_PORT_GROUP_UNAWARE_MODE_CNS, meaning function should write
*          all active port groups , to the specified table entry
*          (same as there was no portGroupId parameter)
*       2. For read APIs CPSS_PORT_GROUP_UNAWARE_MODE_CNS, meaning function should read
*          register only from 1st active port group , from the specified table entry
*          (same as there was no portGroupId parameter).
*******************************************************************************/


/**
* @enum CPSS_DRV_HW_TRACE_TYPE_ENT
 *
 * @brief HW Trace type
*/
typedef enum{

    /** HW access is read. */
    CPSS_DRV_HW_TRACE_TYPE_READ_E,

    /** HW access is write. */
    CPSS_DRV_HW_TRACE_TYPE_WRITE_E,

    /** Both HW access read and write. */
    CPSS_DRV_HW_TRACE_TYPE_BOTH_E,

    /** HW access is write and delay. */
    CPSS_DRV_HW_TRACE_TYPE_WRITE_DELAY_E,

    /** HW access is write, read and delay. */
    CPSS_DRV_HW_TRACE_TYPE_ALL_E

} CPSS_DRV_HW_TRACE_TYPE_ENT;

// /**
// * @enum CPSS_HW_DRIVER_AS_ENT
//  *
//  * @brief Defines driver type
// */
// typedef enum
// {

//     CPSS_HW_DRIVER_TYPE_NONE_E                      = 0x0,
//     CPSS_HW_DRIVER_TYPE_ARMADA_SMI_E                = 0x1,
//     CPSS_HW_DRIVER_TYPE_I2C_E                       = 0x2,
//     CPSS_HW_DRIVER_TYPE_GEN_MMAP_E                  = 0x3,
//     CPSS_HW_DRIVER_TYPE_EAGLE_E                     = 0x4,
//     CPSS_HW_DRIVER_TYPE_GEN_MMAP_AC4_E              = 0x5,
//     CPSS_HW_DRIVER_TYPE_GEN_MMAP_AC8_E              = 0x6,
//     CPSS_HW_DRIVER_TYPE_GEN_MMAP_RELOF_E            = 0x7,
//     CPSS_HW_DRIVER_TYPE_GEN_SLAVE_SMI_E             = 0x8,
//     CPSS_HW_DRIVER_TYPE_PCI_KERN_E                  = 0x9,
//     CPSS_HW_DRIVER_TYPE_FALCON_Z_E                  = 0xA,
//     CPSS_HW_DRIVER_TYPE_PEX_E                       = 0xB,
//     CPSS_HW_DRIVER_TYPE_MBUS_E                      = 0xC,
//     CPSS_HW_DRIVER_TYPE_SRV_CPU_RAM_INDIRECT_E      = 0xD,
//     CPSS_HW_DRIVER_TYPE_SIMULATION_EAGLE_E          = 0xE,
//     CPSS_HW_DRIVER_TYPE_SIMULATION                  = 0xF,
//     CPSS_HW_DRIVER_TYPE_SRV_CPU_RAM_DIRECT_E        = 0x10,
//     CPSS_HW_DRIVER_TYPE_SMI_E                       = 0x11,
//     CPSS_HW_DRIVER_TYPE_LAST_E                      = 0xFFFF

// } CPSS_HW_DRIVER_TYPE_ENT;

/*
 * Typedef enum CPSS_DRV_HW_RESOURCE_TYPE_ENT
 *
 * Description:
 *      define the resource type.
 *
 *      CPSS_DRV_HW_RESOURCE_SWITCHING_AND_MG0_CORE_E:
 *         The Switching Core of the Packet Processor
 *         that also includes management unit #0
 *
 *      CPSS_DRV_HW_RESOURCE_MG1_CORE_E:
 *          Management Unit #1
 *
 *      CPSS_DRV_HW_RESOURCE_MG2_CORE_E:
 *          Management Unit #2
 *
 *      CPSS_DRV_HW_RESOURCE_MG3_CORE_E:
 *          Management Unit #3
 *
 *      CPSS_DRV_HW_RESOURCE_DFX_CORE_E:
 *          The reset and Init Controler
 *
 *      CPSS_DRV_HW_RESOURCE_INTERNAL_PCI_E
 *          The internal PCI registers
 **/
typedef enum {
    CPSS_DRV_HW_RESOURCE_SWITCHING_AND_MG0_CORE_E = CPSS_HW_DRIVER_AS_SWITCHING_E,
    CPSS_DRV_HW_RESOURCE_MG1_CORE_E = CPSS_HW_DRIVER_AS_MG1_E,
    CPSS_DRV_HW_RESOURCE_MG2_CORE_E = CPSS_HW_DRIVER_AS_MG2_E,
    CPSS_DRV_HW_RESOURCE_MG3_CORE_E = CPSS_HW_DRIVER_AS_MG3_E,
    CPSS_DRV_HW_RESOURCE_INTERNAL_PCI_E = CPSS_HW_DRIVER_AS_CNM_E,
    CPSS_DRV_HW_RESOURCE_DFX_CORE_E = CPSS_HW_DRIVER_AS_DFX_E

} CPSS_DRV_HW_RESOURCE_TYPE_ENT;

/**
* @internal cpssDrvPpHwRegisterRead function
* @endinternal
*
* @brief   Read a register value from the given PP.
*
* @param[in] devNum                   - The PP to read from.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] regAddr                  - The register's address to read from.
*
* @param[out] data                     - Includes the register value.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwRegisterRead
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   regAddr,
    OUT GT_U32  *data
);

/**
* @internal cpssDrvPpHwRegisterWrite function
* @endinternal
*
* @brief   Write to a PP's given register.
*
* @param[in] devNum                   - The PP to write to.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] regAddr                  - The register's address to write to.
*                                      data    - The value to be written.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwRegisterWrite
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   regAddr,
    IN GT_U32   value
);

/**
* @internal cpssDrvPpHwRegFieldGet function
* @endinternal
*
* @brief   Read a selected register field.
*
* @param[in] devNum                   - The PP device number to read from.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] regAddr                  - The register's address to read from.
* @param[in] fieldOffset              - The start bit number in the register.
* @param[in] fieldLength              - The number of bits to be read.
*
* @param[out] fieldData                - Data to read from the register.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwRegFieldGet
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   regAddr,
    IN GT_U32   fieldOffset,
    IN GT_U32   fieldLength,
    OUT GT_U32  *fieldData
);

/**
* @internal cpssDrvPpHwRegFieldSet function
* @endinternal
*
* @brief   Write value to selected register field.
*
* @param[in] devNum                   - The PP device number to write to.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] regAddr                  - The register's address to write to.
* @param[in] fieldOffset              - The start bit number in the register.
* @param[in] fieldLength              - The number of bits to be written to register.
* @param[in] fieldData                - Data to be written into the register.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*
* @note this function actually read the register modifies the requested field
*       and writes the new value back to the HW.
*
*/
GT_STATUS cpssDrvPpHwRegFieldSet
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   regAddr,
    IN GT_U32   fieldOffset,
    IN GT_U32   fieldLength,
    IN GT_U32   fieldData

);

/**
* @internal cpssDrvPpHwRegBitMaskRead function
* @endinternal
*
* @brief   Reads the unmasked bits of a register.
*
* @param[in] devNum                   - PP device number to read from.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] regAddr                  - Register address to read from.
* @param[in] mask                     - Mask for selecting the read bits.
*
* @param[out] dataPtr                  - Data read from register.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*
* @note The bits in value to be read are the masked bit of 'mask'.
*
*/
GT_STATUS cpssDrvPpHwRegBitMaskRead
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   regAddr,
    IN GT_U32   mask,
    OUT GT_U32  *dataPtr
);

/**
* @internal cpssDrvPpHwRegBitMaskWrite function
* @endinternal
*
* @brief   Writes the unmasked bits of a register.
*
* @param[in] devNum                   - PP device number to write to.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] regAddr                  - Register address to write to.
* @param[in] mask                     - Mask for selecting the written bits.
* @param[in] value                    - Data to be written to register.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*
* @note The bits in value to be written are the masked bit of 'mask'.
*
*/
GT_STATUS cpssDrvPpHwRegBitMaskWrite
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   regAddr,
    IN GT_U32   mask,
    IN GT_U32   value
);

/**
* @internal cpssDrvPpHwRamRead function
* @endinternal
*
* @brief   Read from PP's RAM.
*
* @param[in] devNum                   - The PP device number to read from.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] addr                     - Address offset to read from.
* @param[in] length                   - Number of Words (4 byte) to read.
*
* @param[out] data                     - An array containing the read data.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwRamRead
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   addr,
    IN GT_U32   length,
    OUT GT_U32  data[]       /*arrSizeVarName=length*/
);

/**
* @internal cpssDrvPpHwRamWrite function
* @endinternal
*
* @brief   Writes to PP's RAM.
*
* @param[in] devNum                   - The PP device number to write to.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] addr                     - Address offset to write to.
* @param[in] length                   - Number of Words (4 byte) to write.
* @param[in] data                     - An array containing the  to be written.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwRamWrite
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   addr,
    IN GT_U32   length,
    IN GT_U32   data[]       /*arrSizeVarName=length*/
);

/**
* @internal cpssDrvPpHwVectorRead function
* @endinternal
*
* @brief   Read from PP's RAM a vector of addresses.
*
* @param[in] devNum                   - The PP device number to read from.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] addrArr[]                - Address array to read from.
* @param[in] arrLen                   - The size of addrArr/dataArr.
*
* @param[out] dataArr[]                - An array containing the read data.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwVectorRead
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   addrArr[], /*arrSizeVarName=arrLen*/
    OUT GT_U32  dataArr[], /*arrSizeVarName=arrLen*/
    IN GT_U32   arrLen
);

/**
* @internal cpssDrvPpHwVectorWrite function
* @endinternal
*
* @brief   Writes to PP's RAM a vector of addresses.
*
* @param[in] devNum                   - The PP device number to write to.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] addrArr[]                - Address offset to write to.
* @param[in] dataArr[]                - An array containing the data to be written.
* @param[in] arrLen                   - The size of addrArr/dataArr.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwVectorWrite
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   addrArr[], /*arrSizeVarName=arrLen*/
    IN GT_U32   dataArr[], /*arrSizeVarName=arrLen*/
    IN GT_U32   arrLen
);

/**
* @internal cpssDrvPpHwRamInReverseWrite function
* @endinternal
*
* @brief   Writes to PP's RAM in reverse.
*
* @param[in] devNum                   - The PP device number to write to.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] addr                     - Address offset to write to.
* @param[in] length                   - Number of Words (4 byte) to write.
* @param[in] data                     - An array containing the  to be written.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwRamInReverseWrite
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   addr,
    IN GT_U32   length,
    IN GT_U32   *data
);

/*******************************************************************************
* cpssDrvPpHwIsrRead
*
* DESCRIPTION:
*       Read a register value using special interrupt address completion region.
*
* INPUTS:
*       devNum  - The PP to read from.
*       portGroupId  - The port group Id. relevant only to 'multi-port-groups' devices.
*                          (APPLICABLE DEVICES: Lion2)
*                 supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*       regAddr - The register's address to read from.
*                 Note: regAddr should be < 0x1000000
*
* OUTPUTS:
*       dataPtr - Includes the register value.
*
* RETURNS:
*       GT_OK   - on success
*       GT_FAIL - on hardware error
*       GT_NOT_INITIALIZED - if the driver was not initialized
*       GT_HW_ERROR - on hardware error
*
* COMMENTS:
*       None.
*
*******************************************************************************/
GT_STATUS cpssDrvPpHwIsrRead
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   regAddr,
    IN GT_U32   *dataPtr
);

/**
* @internal cpssDrvPpHwIsrWrite function
* @endinternal
*
* @brief   Write a register value using special interrupt address completion region
*
* @param[in] devNum                   - The PP to write to.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] regAddr                  - The register's address to write to.
*                                      data    - The value to be written.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwIsrWrite
(
    IN GT_U8    devNum,
    IN GT_U32   portGroupId,
    IN GT_U32   regAddr,
    IN GT_U32   value
);

/**
* @internal cpssDrvPpHwInternalPciRegRead function
* @endinternal
*
* @brief   This function reads from an internal pci register, it's used by the
*         initialization process and the interrupt service routine.
* @param[in] devNum                   - The Pp's device numbers.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] regAddr                  - The register's address to read from.
*
* @param[out] data                     - The read data.
*
* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - otherwise.
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwInternalPciRegRead
(
    IN  GT_U8   devNum,
    IN GT_U32   portGroupId,
    IN  GT_U32  regAddr,
    OUT GT_U32  *data
);

/**
* @internal cpssDrvPpHwInternalPciRegWrite function
* @endinternal
*
* @brief   This function reads from an internal pci register, it's used by the
*         initialization process and the interrupt service routine.
* @param[in] devNum                   - The Pp's device numbers.
* @param[in] portGroupId              - The port group Id. relevant only to 'multi-port-groups' devices.
*                                      (APPLICABLE DEVICES Lion2)
*                                      supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
* @param[in] regAddr                  - The register's address to read from.
* @param[in] data                     - Data to be written.
*
* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - otherwise.
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwInternalPciRegWrite
(
    IN  GT_U8   devNum,
    IN GT_U32   portGroupId,
    IN  GT_U32  regAddr,
    IN  GT_U32  data
);

/**
* @internal cpssDrvHwPpResetAndInitControllerReadReg function
* @endinternal
*
* @brief   Read a register value from the Reset and Init Controller.
*
* @param[in] devNum                   - The PP to read from.
* @param[in] regAddr                  - The register's address to read from.
*
* @param[out] data                     - Includes the register value.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvHwPpResetAndInitControllerReadReg
(
    IN  GT_U8   devNum,
    IN  GT_U32  regAddr,
    OUT GT_U32  *data
);

/**
* @internal cpssDrvHwPpResetAndInitControllerWriteReg function
* @endinternal
*
* @brief   Write to the Reset and Init Controller given register.
*
* @param[in] devNum                   - The PP to write to.
* @param[in] regAddr                  - The register's address to write to.
* @param[in] data                     - The value to be written.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvHwPpResetAndInitControllerWriteReg
(
    IN  GT_U8   devNum,
    IN  GT_U32  regAddr,
    IN  GT_U32  data
);

/**
* @internal cpssDrvHwPpResetAndInitControllerGetRegField function
* @endinternal
*
* @brief   Read a selected register field from the Reset and Init Controller.
*
* @param[in] devNum                   - The PP device number to read from.
* @param[in] regAddr                  - The register's address to read from.
* @param[in] fieldOffset              - The start bit number in the register.
* @param[in] fieldLength              - The number of bits to be read.
*
* @param[out] fieldData                - Data to read from the register.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvHwPpResetAndInitControllerGetRegField
 (
    IN  GT_U8   devNum,
    IN GT_U32   regAddr,
    IN GT_U32   fieldOffset,
    IN GT_U32   fieldLength,
    OUT GT_U32  *fieldData
);

/**
* @internal cpssDrvHwPpResetAndInitControllerSetRegField function
* @endinternal
*
* @brief   Write value to selected register field of the Reset and Init Controller.
*
* @param[in] devNum                   - The PP device number to write to.
* @param[in] regAddr                  - The register's address to write to.
* @param[in] fieldOffset              - The start bit number in the register.
* @param[in] fieldLength              - The number of bits to be written to register.
* @param[in] fieldData                - Data to be written into the register.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*
* @note this function actually read the register modifies the requested field
*       and writes the new value back to the HW.
*
*/
GT_STATUS cpssDrvHwPpResetAndInitControllerSetRegField
 (
    IN  GT_U8   devNum,
    IN GT_U32   regAddr,
    IN GT_U32   fieldOffset,
    IN GT_U32   fieldLength,
    IN GT_U32   fieldData
);

/**
* @internal cpssDrvPpHwTraceEnable function
* @endinternal
*
* @brief   This function enables/disables to trace hw access.
*
* @param[in] devNum                   - The Pp's device number.
* @param[in] traceType                - trace access type.
* @param[in] enable                   - GT_TRUE:  hw access info tracing
*                                      GT_FALSE: disable hw access info tracing
*                                       None.
*/
GT_STATUS cpssDrvPpHwTraceEnable
(
    IN GT_U8                        devNum,
    IN CPSS_DRV_HW_TRACE_TYPE_ENT   traceType,
    IN GT_BOOL                      enable
);

/*******************************************************************************
* cpssDrvHwPpHwInfoStcPtrGet
*
* DESCRIPTION:
*       Read pointer to CPSS_HW_INFO_STC for a given devNum/portGroupId
*
* INPUTS:
*       devNum  - The PP device number to read from.
*       portGroupId  - The port group Id. relevant only to 'multi-port-groups' devices.
*                          (APPLICABLE DEVICES: Lion2)
*                 supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*
* OUTPUTS:
*       None
*
* RETURNS:
*       Pointer to CPSS_HW_INFO_STC
*       NULL - if not set/invalid parameter
*
* COMMENTS:
*       None.
*
*******************************************************************************/
CPSS_HW_INFO_STC* cpssDrvHwPpHwInfoStcPtrGet
(
    IN  GT_U8   devNum,
    IN GT_U32   portGroupId
);


/**
* @enum CPSS_DRV_HW_ACCESS_STAGE_ENT
 *
 * @brief Enumeration of HW access callback function stages
*/
typedef enum{

    /** first position, actual logic takes place. */
    CPSS_DRV_HW_ACCESS_STAGE_PRE_E,

    /** second position - after logic takes place */
    CPSS_DRV_HW_ACCESS_STAGE_POST_E

} CPSS_DRV_HW_ACCESS_STAGE_ENT;


/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_READ_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines register read callback function for Hw access.
 *
 * INPUTS:
 *       devNum       -  The PP to read from.
 *       portGroupId  - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       regAddr      - The register's address to read from.
 *       stage        - stage for callback run.
 *
 * OUTPUTS:
 *       data - Includes the register value.
 *
 * RETURNS:
 *       GT_OK       - callback success to get the data.
 *       GT_FAIL     - callback failed.
 *       GT_ABORTED  - operation aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *      2. If callback returns GT_ABORTED, this indicates to the parent CPSS function to stop
 *          and return GT_OK to its caller.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_READ_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN  GT_U32   regAddr,
    OUT GT_U32  *data,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);

/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_WRITE_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines register write callback function for Hw access.
 *
 * INPUTS:
 *       devNum       -  The PP to read from.
 *       portGroupId  - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       regAddr      - The register's address to read from.
 *       data         - The value to be written.
 *       stage        - stage for callback run.
 *
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       GT_OK       - callback success to get the data.
 *       GT_FAIL     - callback failed.
 *       GT_ABORTED  - operation done and aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *      2. If callback returns GT_ABORTED, this indicates to the parent CPSS function to stop
 *          and return GT_OK to its caller.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_WRITE_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN  GT_U32   regAddr,
    IN  GT_U32   data,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);


/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_FIELD_READ_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines register field read callback function for Hw access.
 *
 * INPUTS:
 *       devNum       -  The PP to read from.
 *       portGroupId  - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       regAddr      - The register's address to read from.
 *       fieldOffset  - The start bit number in the register.
 *       fieldLength  - The number of bits to be read.
 *       stage        - stage for callback run.
 *
 * OUTPUTS:
 *       data - Includes the register value.
 *
 * RETURNS:
 *       GT_OK        - callback success to get the data.
 *       GT_FAIL      - callback failed.
 *       GT_ABORTED   - operation aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_FIELD_READ_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN  GT_U32   regAddr,
    IN GT_U32   fieldOffset,
    IN GT_U32   fieldLength,
    OUT GT_U32  *data,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);

/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_FIELD_WRITE_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines register field write callback function for Hw access.
 *
 * INPUTS:
 *       devNum       -  The PP to read from.
 *       portGroupId  - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       regAddr          - The register's address to read from.
 *       fieldOffset  - The start bit number in the register.
 *       fieldLength  - The number of bits to be read.
 *       data         - The value to be written.
 *       stage        - stage for callback run.
 *
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       GT_OK        - callback success to get the data.
 *       GT_FAIL      - callback failed.
 *       GT_ABORTED   - operation done and aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *      2. If callback returns GT_ABORTED, this indicates to the parent CPSS function to stop
 *          and return GT_OK to its caller.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_FIELD_WRITE_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN  GT_U32   regAddr,
    IN GT_U32    fieldOffset,
    IN GT_U32    fieldLength,
    IN  GT_U32   data,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);


/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_BIT_MASK_READ_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines register bit-mask read callback function for Hw access.
 *
 * INPUTS:
 *       devNum       -  The PP to read from.
 *       portGroupId  - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       regAddr      - The register's address to read from.
 *       mask         - Mask for selecting the read bits.
 *       stage        - stage for callback run.
 *
 * OUTPUTS:
 *       data - Includes the register value.
 *
 * RETURNS:
 *       GT_OK         - callback success to get the data.
 *       GT_FAIL       - callback failed.
 *       GT_ABORTED    - operation aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *      2. If callback returns GT_ABORTED, this indicates to the parent CPSS function to stop
 *          and return GT_OK to its caller.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_BIT_MASK_READ_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN  GT_U32   regAddr,
    IN GT_U32    mask,
    OUT GT_U32  *data,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);

/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_BIT_MASK_WRITE_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines register bit-mask write callback function for Hw access.
 *
 * INPUTS:
 *       devNum       -  The PP to read from.
 *       portGroupId  - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       regAddr      - The register's address to read from.
 *       mask         - Mask for selecting the read bits.
 *       data         - The value to be written.
 *       stage        - stage for callback run.
 *
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       GT_OK         - callback success to get the data.
 *       GT_FAIL       - callback failed.
 *       GT_ABORTED    - operation done and aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *      2. If callback returns GT_ABORTED, this indicates to the parent CPSS function to stop
 *          and return GT_OK to its caller.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_BIT_MASK_WRITE_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN  GT_U32   regAddr,
    IN  GT_U32   mask,
    IN  GT_U32   data,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);

/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_RAM_READ_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines ram read callback function for Hw access.
 *
 * INPUTS:
 *       devNum       -  The PP to read from.
 *       portGroupId  - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       addr         - Address offset to read from.
 *       length       - Number of Words (4 byte) to read.
 *       stage        - stage for callback run.
 *
 * OUTPUTS:
 *       data - Includes the register value.
 *
 * RETURNS:
 *       GT_OK         - callback success.
 *       GT_FAIL       - callback failed.
 *       GT_ABORTED    - operation aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *      2. If callback returns GT_ABORTED, this indicates to the parent CPSS function to stop
 *          and return GT_OK to its caller.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_RAM_READ_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN GT_U32   addr,
    IN GT_U32   length,
    OUT GT_U32  *data,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);

/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_RAM_WRITE_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines ram write/write in reverse, callback function for Hw access.
 *
 * INPUTS:
 *       devNum       -  The PP to read from.
 *       portGroupId  - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       addr         - Address offset to read from.
 *       length       - Number of Words (4 byte) to read.
 *       data         - The value to be written.
 *       stage        - stage for callback run.
 *
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       GT_OK         - callback success.
 *       GT_FAIL       - callback failed.
 *       GT_ABORTED    - operation aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *      2. If callback returns GT_ABORTED, this indicates to the parent CPSS function to stop
 *          and return GT_OK to its caller.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_RAM_WRITE_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN GT_U32   addr,
    IN GT_U32   length,
    IN  GT_U32  *data,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);

/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_VECTOR_READ_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines vector of registers read callback function for Hw access.
 *
 * INPUTS:
 *       devNum       -  The PP to read from.
 *       portGroupId  - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       addrArr      - Address offset to write to.
 *       arrLen       - The size of addrArr/dataArr.
 *       stage        - stage for callback run.
 *
 * OUTPUTS:
 *       dataArr - An array containing the read data.
 *
 * RETURNS:
 *       GT_OK         - callback success.
 *       GT_FAIL       - callback failed.
 *       GT_ABORTED    - operation aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *      2. If callback returns GT_ABORTED, this indicates to the parent CPSS function to stop
 *          and return GT_OK to its caller.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_VECTOR_READ_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN GT_U32   addrArr[],
    OUT GT_U32  dataArr[],
    IN GT_U32   arrLen,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);

/*******************************************************************************
 * typedef: GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_VECTOR_WRITE_FUNC)
 *
 *
 * DESCRIPTION:
 *    Defines vector of registers write callback function for Hw access.
 *
 * INPUTS:
 *       devNum      -  The PP to read from.
 *       portGroupId - The port group id. relevant only to 'multi-port-groups'
 *                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                          (APPLICABLE DEVICES: Lion2)
 *       addrArr     - Address offset to write to.
 *       dataArr     - An array containing the data to be written.
 *       arrLen      - The size of addrArr/dataArr.
 *       stage       - stage for callback run.
 *
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       GT_OK         - callback success.
 *       GT_FAIL       - callback failed.
 *       GT_ABORTED    - operation aborted by calback.
 *
 * COMMENTS:
 *   When stage equals to CPSS_DRV_HW_ACCESS_STAGE_PRE_E:
 *      1. If callback returns GT_OK the parrent CPSS function continue processing.
 *      2. If callback returns GT_ABORTED, this indicates to the parent CPSS function to stop
 *          and return GT_OK to its caller.
 *
****************************************************************************** */
typedef GT_STATUS (*CPSS_DRV_HW_ACCESS_PORT_GROUP_VECTOR_WRITE_FUNC)
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN GT_U32   addrArr[],
    OUT GT_U32  dataArr[],
    IN GT_U32   arrLen,
    IN  CPSS_DRV_HW_ACCESS_STAGE_ENT  stage
);


/*
 *  typedef: struct CPSS_DRV_HW_ACCESS_OBJ_STC
 *
 * Description: the structure holds the regiters/memory access callback routines.
 *
 *  COMMENTS:
 *  ----------------------------------------------------------------------------------------
 *             CPSS Function                                   Hw access Callback
 *------------------------------------------------------------------------------------------
 *   1    prvCpssDrvHwPpPortGroupReadRegister             hwAccessRegisterReadFunc;
 *   2    prvCpssDrvHwPpPortGroupWriteRegister             hwAccessRegisterWriteFunc;
 *   3    prvCpssDrvHwPpPortGroupGetRegField               hwAccessRegisterFieldReadFunc;
 *   4    prvCpssDrvHwPpPortGroupSetRegField               hwAccessRegisterFieldWriteFunc;
 *   5    prvCpssDrvHwPpPortGroupReadRegBitMask        hwAccessRegisterBitMaskReadFunc;
 *   6    prvCpssDrvHwPpPortGroupWriteRegBitMask        hwAccessRegisterBitMaskWriteFunc
 *   7    prvCpssDrvHwPpPortGroupReadRam                  hwAccessRamReadFunc;
 *   8    prvCpssDrvHwPpPortGroupWriteRam                  hwAccessRamWriteFunc;
 *   9    prvCpssDrvHwPpPortGroupWriteRamInReverse   hwAccessRamWriteInReverseFunc;
 *  10   prvCpssDrvHwPpPortGroupReadVec                   hwAccessVectorReadFunc;
 *  11   prvCpssDrvHwPpPortGroupWriteVec                   hwAccessVectorWriteFunc;
 *  12   prvCpssDrvHwPpPortGroupIsrRead                    hwAccessRegisterIsrReadFunc;
 *  13   prvCpssDrvHwPpPortGroupIsrWrite                    hwAccessRegisterIsrWriteFunc;
 *---------------------------------------------------------------------------------------------
 */
typedef struct{
    CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_READ_FUNC           hwAccessRegisterReadFunc;         /* 1 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_WRITE_FUNC          hwAccessRegisterWriteFunc;        /* 2 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_FIELD_READ_FUNC     hwAccessRegisterFieldReadFunc;    /* 3 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_FIELD_WRITE_FUNC    hwAccessRegisterFieldWriteFunc;   /* 4 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_BIT_MASK_READ_FUNC  hwAccessRegisterBitMaskReadFunc;  /* 5 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_BIT_MASK_WRITE_FUNC hwAccessRegisterBitMaskWriteFunc; /* 6 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_RAM_READ_FUNC                hwAccessRamReadFunc;              /* 7 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_RAM_WRITE_FUNC               hwAccessRamWriteFunc;             /* 8 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_RAM_WRITE_FUNC               hwAccessRamWriteInReverseFunc;    /* 9 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_VECTOR_READ_FUNC             hwAccessVectorReadFunc;           /* 10 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_VECTOR_WRITE_FUNC            hwAccessVectorWriteFunc;          /* 11 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_READ_FUNC           hwAccessRegisterIsrReadFunc;      /* 12 */
    CPSS_DRV_HW_ACCESS_PORT_GROUP_REGISTER_WRITE_FUNC          hwAccessRegisterIsrWriteFunc;     /* 13 */
} CPSS_DRV_HW_ACCESS_OBJ_STC;


/**
* @internal cpssDrvHwAccessObjectBind function
* @endinternal
*
* @brief   The function binds/unbinds a callback routines for HW access.
*
* @param[in] hwAccessObjPtr           - HW access object pointer.
* @param[in] bind                     -  GT_TRUE -  callback routines.
*                                      GT_FALSE - un bind callback routines.
*
* @retval GT_OK                    - on success
*/
GT_STATUS cpssDrvHwAccessObjectBind
(
    IN CPSS_DRV_HW_ACCESS_OBJ_STC *hwAccessObjPtr,
    IN GT_BOOL                     bind
);

/**
* @internal cpssDrvPpHwResourceReadRegister function
* @endinternal
*
* @brief   Read a register value from a resource.
*
* @param[in] devNum                   - The PP to read from.
* @param[in] portGroupId              - The port group id. relevant only to 'multi-port-groups'
*                                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                                      (APPLICABLE DEVICES Lion2)
* @param[in] resourceType             - The resource type.
* @param[in] regAddr                  - The register's address to read from.
*
* @param[out] dataPtr                  - Includes the register value.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwResourceReadRegister
(
    IN  GT_U8                           devNum,
    IN  GT_U32                          portGroupId,
    IN  CPSS_DRV_HW_RESOURCE_TYPE_ENT   resourceType,
    IN  GT_U32                          regAddr,
    OUT GT_U32                          *dataPtr
);

/**
* @internal cpssDrvPpHwResourceWriteRegister function
* @endinternal
*
* @brief   Write to a resource given register.
*
* @param[in] devNum                   - The PP to write to.
* @param[in] portGroupId              - The port group id. relevant only to 'multi-port-groups'
*                                      devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
*                                      (APPLICABLE DEVICES Lion2)
* @param[in] resourceType             - The resource type.
* @param[in] regAddr                  - The register's address to write to.
* @param[in] data                     - The value to be written.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
* @retval GT_HW_ERROR              - on hardware error
*/
GT_STATUS cpssDrvPpHwResourceWriteRegister
(
    IN  GT_U8                           devNum,
    IN  GT_U32                          portGroupId,
    IN  CPSS_DRV_HW_RESOURCE_TYPE_ENT   resourceType,
    IN  GT_U32                          regAddr,
    IN  GT_U32                          data
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __cpssDriverPpHwh */


