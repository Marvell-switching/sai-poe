/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
********************************************************************************
 * @file pdlLibMd5.c
 * @copyright
 *    (c), Copyright (C) 2023, Marvell International Ltd.
 *    THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.
 *    NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT
 *    OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE
 *    DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.
 *    THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,
 *    IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.
********************************************************************************
 *
 * @brief Platform driver layer - Lib related API
 *
 * @version   1
********************************************************************************
*/

/* *************************************************************************
 *$              EXTERNAL DECLARATIONS (IMPORT)
 *!**************************************************************************
 *!*/
#include <stdarg.h>
#include <pdlib/init/pdlInit.h>
#include <pdlib/lib/pdlLib.h>
#include <pdlib/lib/private/prvPdlLib.h>

#define PRV_PDL_MD5_WORDS_IN_DIGEST_CNS     PDL_LIB_MD5_DIGEST_LENGTH_CNS
#define PRV_PDL_MD5_MSG_BLOCK_LEN_CNS       64

PDL_PRAGMA_NOALIGN
    typedef PDL_PACKED_STRUCT_START union {
        UINT_32                     words[PRV_PDL_MD5_WORDS_IN_DIGEST_CNS];
        PDL_LIB_MD5_DIGEST_STC      bytes;
} PDL_PACKED_STRUCT_END PRV_PDL_LIB_MD5_DIGEST_UNT;
PDL_PRAGMA_ALIGN

/* the value of the message digest before the first step of the algorithm */
static const PRV_PDL_LIB_MD5_DIGEST_UNT  prvPdlLibMd5InitialDigestValue =
                                                                  { {0x67452301,
                                                                     0xefcdab89,
                                                                     0x98badcfe,
                                                                     0x10325476} };

/* the unique term in each iteration based on floor( pow(2, 32) * |sin(i)| ) */
static const UINT_32 prvPdlLibMd5Unique[64] = 
                                       { 0xd76aa478,   /*  1 */
                                         0xe8c7b756,   /*  2 */
                                         0x242070db,   /*  3 */
                                         0xc1bdceee,   /*  4 */
                                         0xf57c0faf,   /*  5 */
                                         0x4787c62a,   /*  6 */
                                         0xa8304613,   /*  7 */
                                         0xfd469501,   /*  8 */
                                         0x698098d8,   /*  9 */
                                         0x8b44f7af,   /* 10 */
                                         0xffff5bb1,   /* 11 */
                                         0x895cd7be,   /* 12 */
                                         0x6b901122,   /* 13 */
                                         0xfd987193,   /* 14 */
                                         0xa679438e,   /* 15 */
                                         0x49b40821,   /* 16 */

                                         0xf61e2562,   /* 17 */
                                         0xc040b340,   /* 18 */
                                         0x265e5a51,   /* 19 */
                                         0xe9b6c7aa,   /* 20 */
                                         0xd62f105d,   /* 21 */
                                          0x2441453,   /* 22 */
                                         0xd8a1e681,   /* 23 */
                                         0xe7d3fbc8,   /* 24 */
                                         0x21e1cde6,   /* 25 */
                                         0xc33707d6,   /* 26 */
                                         0xf4d50d87,   /* 27 */
                                         0x455a14ed,   /* 28 */
                                         0xa9e3e905,   /* 29 */
                                         0xfcefa3f8,   /* 30 */
                                         0x676f02d9,   /* 31 */
                                         0x8d2a4c8a,   /* 32 */

                                         0xfffa3942,   /* 33 */
                                         0x8771f681,   /* 34 */
                                         0x6d9d6122,   /* 35 */
                                         0xfde5380c,   /* 36 */
                                         0xa4beea44,   /* 37 */
                                         0x4bdecfa9,   /* 38 */
                                         0xf6bb4b60,   /* 39 */
                                         0xbebfbc70,   /* 40 */
                                         0x289b7ec6,   /* 41 */
                                         0xeaa127fa,   /* 42 */
                                         0xd4ef3085,   /* 43 */
                                          0x4881d05,   /* 44 */
                                         0xd9d4d039,   /* 45 */
                                         0xe6db99e5,   /* 46 */
                                         0x1fa27cf8,   /* 47 */
                                         0xc4ac5665,   /* 48 */

                                         0xf4292244,   /* 49 */
                                         0x432aff97,   /* 50 */
                                         0xab9423a7,   /* 51 */
                                         0xfc93a039,   /* 52 */
                                         0x655b59c3,   /* 53 */
                                         0x8f0ccc92,   /* 54 */
                                         0xffeff47d,   /* 55 */
                                         0x85845dd1,   /* 56 */
                                         0x6fa87e4f,   /* 57 */
                                         0xfe2ce6e0,   /* 58 */
                                         0xa3014314,   /* 59 */
                                         0x4e0811a1,   /* 60 */
                                         0xf7537e82,   /* 61 */
                                         0xbd3af235,   /* 62 */
                                         0x2ad7d2bb,   /* 63 */
                                         0xeb86d391    /* 64 */ };


/* the shift value for rotate functions for different rounds */

static const UINT_32        prvPdlLibMd5S1[] = {7, 12, 17, 22};
static const UINT_32        prvPdlLibMd5S2[] = {5,  9, 14, 20};
static const UINT_32        prvPdlLibMd5S3[] = {4, 11, 16, 23};
static const UINT_32        prvPdlLibMd5S4[] = {6, 10, 15, 21};

/*!**************************************************************************
 *$              LOCAL FUNCTION DEFINITIONS
 *!**************************************************************************
 *!*/


/*!**************************************************RND Template version 4.1
 *!     F U N C T I O N   D E S I G N   &   I M P L E M E N T A T I O N
 *!==========================================================================
 *$ TITLE: Processing (64-octet) Block of Data
 *!--------------------------------------------------------------------------
 *$ FILENAME: 
 *!--------------------------------------------------------------------------
 *$ SYSTEM, SUBSYSTEM: LIB, MD5
 *!--------------------------------------------------------------------------
 *$ AUTHORS: Igor M.
 *!--------------------------------------------------------------------------
 *$ LATEST UPDATE: 18-Jan-2001, 11:49 AM CREATION DATE: 1-Jan-2001
 *!**************************************************************************
 *!
 *!**************************************************************************
 *!
 *$ FUNCTION: prvPdlLibMd5ProcessOneBlock
 *!
 *$ GENERAL DESCRIPTION: Performs the current digest modification induced by
 *!                      the considered 512-bit message block
 *!
 *$ RETURNS: void
 *!
 *$ ALGORITHM: Passes the block 4 times, each time cycling over the 32-bit words
 *!            of the message digest in the specified order and modifying the
 *!            selected word in the following way:
 *!             - incrementing it by
 *!                - the value of the related function on the rest of the words
 *!                  (one of the following four auxiliary functions
 *!                   each receiving three 32-bit words as input
 *!                   and returning one-word output:
 *!                    F(X, Y, Z) = X & Y |~X & Z
 *!                    G(X, Y, Z) = X & Z | Y &~Z
 *!                    H(X, Y, Z) = X ^ Y ^ Z
 *!                    I(X, Y, Z) = Y ^ (X |~Z)                     )
 *!                - the value of the specified message word
 *!                - the predefined constant which is unique for each step:
 *!                  T(step) = floor( pow(2, 32) * fabs( sin(step) ) )
 *!             - rotating it left by the value of the related shift function:
 *!               S1(i) = 7 + 5i
 *!               S2(i) =  i(i + 7)/2 + 5
 *!               S3(0) = 4,  S3(1) = 11,  S3(2) = 16,  S3(3) = 23
 *!               S4(i) =  (i + 3)(i + 4)/2
 *!             - incrementing it by the value of the next word in the cycle
 *!            Finally, the obtained message digest is added to the initial one
 *!
 *$ ASSUMPTIONS:
 *!
 *$ REMARKS: Derived from
 *!          the RSA Data Security, Inc. MD5 Message-Digest Algorithm
 *!
 *!**************************************************************************
 *!*/
static void prvPdlLibMd5ProcessOneBlock(
    IN    UINT_32                  *blockPtr,  /*! the beginning of the block   */
    IN    BOOLEAN                         isBigEndian,
    INOUT PRV_PDL_LIB_MD5_DIGEST_UNT     *currentPtr /*! the digest computed thus far */
)
{
/*!*************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!*************************************************************************/
    INT_32   i;             /* the ordinal of an iteration in a round     */
    INT_32   word_index;    /* the ordinal of a word in the message block */
    UINT_32  A, B, C, D;    /* the initial message digest words values    */
    UINT_32  a, b, c, d;    /* the current message digest words values    */
    UINT_32  F, G, H, I;    /* the current value of the relevant function */
    UINT_32  rotated;       /* the expression subjected to left rotation  */
    UINT_32  shift;         /* the "angle" of the rotation in bits        */

    UINT_32 blockArr4Swap[PRV_PDL_MD5_WORDS_IN_DIGEST_CNS]; /* block for swapping */

    UINT_32 *block_arr = blockPtr;


/*!*************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!*************************************************************************/

    if (isBigEndian)
    {
        for (i = 0; i < PRV_PDL_MD5_WORDS_IN_DIGEST_CNS; i++) {

            blockArr4Swap[i] = pdlLibSwapWord(blockPtr[i]);
            block_arr = blockArr4Swap;
        }
    }

    A = currentPtr->words[0];               /* saves the initial digest */
    B = currentPtr->words[1];
    C = currentPtr->words[2];
    D = currentPtr->words[3];

                            /* round 1 */
    for (i = 0, shift = prvPdlLibMd5S1[0];
         i < PRV_PDL_MD5_WORDS_IN_DIGEST_CNS;
         ++i, shift = prvPdlLibMd5S1[i & 3]) {

        a = currentPtr->words[(  - i) & 3];
        b = currentPtr->words[(1 - i) & 3];
        c = currentPtr->words[(2 - i) & 3];
        d = currentPtr->words[(3 - i) & 3];

        F = (b & c) | (~b & d );

        rotated = a + F + block_arr[i] + prvPdlLibMd5Unique[i];

        rotated = (rotated << shift) | ( rotated >> (32 - shift) );

        currentPtr->words[(  - i) & 3] = b + rotated;
    }

                            /* round 2 */
    for (i = 0, word_index = 1, shift = prvPdlLibMd5S2[0];
         i < PRV_PDL_MD5_WORDS_IN_DIGEST_CNS;
         ++i, word_index = (word_index + 5) & 15, shift = prvPdlLibMd5S2[i & 3]) {

        a = currentPtr->words[(  - i) & 3];
        b = currentPtr->words[(1 - i) & 3];
        c = currentPtr->words[(2 - i) & 3];
        d = currentPtr->words[(3 - i) & 3];

        G = (b & d) | (c & ~d);

        rotated = a + G + block_arr[word_index] + prvPdlLibMd5Unique[i + 16];

        rotated = (rotated << shift) | ( rotated >> (32 - shift) );

        currentPtr->words[(  - i) & 3] = b + rotated;
    }

                            /* round 3 */
    for (i = 0, word_index = 5, shift = prvPdlLibMd5S3[0];
         i < PRV_PDL_MD5_WORDS_IN_DIGEST_CNS;
         ++i, word_index = (word_index + 3) & 15, shift = prvPdlLibMd5S3[i & 3]) {

        a = currentPtr->words[(  - i) & 3];
        b = currentPtr->words[(1 - i) & 3];
        c = currentPtr->words[(2 - i) & 3];
        d = currentPtr->words[(3 - i) & 3];

        H = b ^ c ^ d;

        rotated = a + H + block_arr[word_index] + prvPdlLibMd5Unique[i + 32];

        rotated = (rotated << shift) | ( rotated >> (32 - shift) );

        currentPtr->words[(  - i) & 3] = b + rotated;
    }

                            /* round 4 */
    for (i = 0, word_index = 0, shift = prvPdlLibMd5S4[0];
         i < PRV_PDL_MD5_WORDS_IN_DIGEST_CNS;
         ++i, word_index = (word_index + 7) & 15, shift = prvPdlLibMd5S4[i & 3]) {

        a = currentPtr->words[(  - i) & 3];
        b = currentPtr->words[(1 - i) & 3];
        c = currentPtr->words[(2 - i) & 3];
        d = currentPtr->words[(3 - i) & 3];

        I = c ^ (b | ~d);

        rotated = a + I + block_arr[word_index] + prvPdlLibMd5Unique[i + 48];

        rotated = (rotated << shift) | ( rotated >> (32 - shift) );

        currentPtr->words[(  - i) & 3] = b + rotated;
    }

    currentPtr->words[0] += A;              /* updates the message digest */
    currentPtr->words[1] += B;
    currentPtr->words[2] += C;
    currentPtr->words[3] += D;
}
/*$ END OF prvPdlLibMd5ProcessOneBlock */


/**
* @fn  PDL_STATUS pdlibMd5DigestCompute ( IN void * fdPtr, IN void * msgPtr, IN UINT_32 msgLen, OUT PDL_LIB_MD5_DIGEST_STC *digestPtr )
*
* @brief   Compute MD5 digest of the message contained in specified file or message buffer
*
* @param [in]  fdPtr          If non-null, points to file descriptor of type FILE**, containing the message to compute the digest
* @param [in]  msgPtr         If non-null, points to the first octet of the message to compute the digest
* @param [in]  msgLen         size of the message to 
* @param [out] digestPtr      Computed digest of the message
*
* @return  A PDL_STATUS.
*/

/* ALGORITHM: Step 1: padding the message
*            ---------------------------
*            A single "1" bit followed by the necessary amount of "0" bits
*            are appended to the input message to reach the length in bits
*            congruent to 448, modulo 512. If the length is already congruent
*            to 448, modulo 512, then 512 bits are appended.
*
*            Step 2: appending length
*            Two 32-bit words are appended, low-order word first,
*            to represent the length of the message, modulo 264,
*            before the padding bits were added.
*
*            Step 3: initializing MD buffer
*            ------------------------------
*            The message digest is computed
*            in a buffer of four 32-bit words: A, B, C, D.
*            The words are initialized, the low-order bytes first, as follows:
*            A: 01 23 45 67,  B: 89 ab cd ef,  C: fe dc ba 98,  D: 76 54 32 10
*
*            Step 4: processing message blocks
*            ----------------------------------
*            The function prvPdlLibMd5ProcessOneBlock is invoked
*            for each block of the padded message.
*            The algorithm is detailed in its body.
*
*            Step 5: output
*            --------------
*            The words A, B, C, and D, with the low-order bytes first,
*            represent the message digest.
*
*
*/
extern PDL_STATUS pdlibMd5DigestCompute (
    IN  void                    *fdPtr,
    IN  UINT_8                  *msgPtr,
    IN  const UINT_32            msgLen,
    OUT PDL_LIB_MD5_DIGEST_STC  *digestPtr
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/
    UINT_32  message_bits[2];           /* the message length in bits         */


    UINT_32  word_offset;               /* in the digest (expressed in words) */


    UINT_32  residue_octets;            /* the number of octets in a partly
                                           occupated message block            */


    UINT_32  octets_in_unpadded_blocks; /* the number of octets in the original
                                           message, rounded to whole blocks
                                           (without the fractional residue)   */

    UINT_32  mandatory_octets;          /* the octets number in the residue and
                                           the message length                 */


    UINT_32  padding_blocks;            /* the number of the whole blocks
                                           appended to the message            */


    UINT_32  pad_buffer_octets;         /* the number of octets in
                                           the complementary block(s)         */


    UINT_32  *message_blockPtr;        /* points to the message block
                                           being presently processed          */


    UINT_8   *border_PTR = NULL;        /* points to the fractional residue
                                           of the message                     */


    UINT_8   *message_length_PTR;       /* the the message length appendix    */



    UINT_8   pad_buffer[PRV_PDL_MD5_MSG_BLOCK_LEN_CNS * 2] = {0};
                                        /* the complementary blocks           */


    PRV_PDL_LIB_MD5_DIGEST_UNT

             intermediate_digest;       /* holds the intermediate results
                                           of the message digest computation  */

    UINT_32   block[PRV_PDL_MD5_WORDS_IN_DIGEST_CNS] ;

    UINT_32   pad_offset = 0;

    UINT_32   actual_size_read;

    BOOLEAN   isFileDigest;             /* flag is on - digest compute on file
                                           flag is off - digest compute on buffer */

    /* determine endianess */
    unsigned int x = 1;
    char        *c = (char*) &x;
    int         isBigEndian = (!((int)*c));
/*!*************************************************************************/
/*!                      F U N C T I O N   L O G I C                       */
/*!*************************************************************************/
    if ((fdPtr == NULL && msgPtr == NULL) || msgLen == 0)
        return PDL_BAD_PARAM;

    isFileDigest = (fdPtr == NULL)? FALSE:TRUE;

    residue_octets = msgLen % PRV_PDL_MD5_MSG_BLOCK_LEN_CNS;

    octets_in_unpadded_blocks = msgLen - residue_octets;

    mandatory_octets = residue_octets + 2 * sizeof(UINT_32);

    padding_blocks = (mandatory_octets >= PRV_PDL_MD5_MSG_BLOCK_LEN_CNS)? 2 : 1;

    pad_buffer_octets = padding_blocks * PRV_PDL_MD5_MSG_BLOCK_LEN_CNS;

    if (!isFileDigest){
        border_PTR = msgPtr + msgLen - residue_octets;
    }else{
        pad_offset = msgLen - residue_octets;
    }

    message_length_PTR = pad_buffer + pad_buffer_octets - 2 * sizeof(UINT_32);

    intermediate_digest = prvPdlLibMd5InitialDigestValue;

    if (isBigEndian)
    {
        message_bits[0] = pdlLibSwapWord(msgLen << 3);
        message_bits[1] = pdlLibSwapWord(msgLen >> 29);
    }
    else
    {
        message_bits[0] = msgLen << 3;
        message_bits[1] = msgLen >> 29;
    }

    if (!isFileDigest){
        /* copies the fractional residue to the complementary block */
        memcpy(pad_buffer, border_PTR, residue_octets);
    }else{
        /* copies the fractional residue directly from flash
           to the complementary block */
        /* If we fail to read from file we simulate an empty NOR flash.
           This should never be required since it should never fail, so
           a FATAL ERROR might be needed here in this case. */
        if(fseek(*(FILE**)fdPtr, pad_offset, SEEK_SET) ||
           (1 != fread(pad_buffer, residue_octets, 1, *(FILE**)fdPtr))) 
        {
            memset(pad_buffer, 0xFF, residue_octets);
        }
    }

    /* sets the first padding bit to 1 */
    pad_buffer[residue_octets] = (UINT_32)0x80;

    /* appends the message length as the final padding fraction */
    memcpy( message_length_PTR, message_bits, sizeof(UINT_32)*2 );

    if (!isFileDigest){
        /* processes the original (non-padding) blocks of the message */
        for ( message_blockPtr  = (UINT_32 *) msgPtr;
              message_blockPtr  < (UINT_32 *) (msgPtr +
                                                octets_in_unpadded_blocks);
              message_blockPtr += PRV_PDL_MD5_WORDS_IN_DIGEST_CNS) {
            memcpy(block, message_blockPtr,sizeof(block));
            prvPdlLibMd5ProcessOneBlock( block, isBigEndian, &intermediate_digest );
        }
    }else{
        /* processes the original (non-padding) blocks of the file */
        actual_size_read = 0;
        while (actual_size_read<octets_in_unpadded_blocks){
            /* If we fail to read from file we simulate an empty NOR flash.
               This should never be required since it should never fail, so
               a FATAL ERROR might be needed here in this case. */
            if(fseek(*(FILE**)fdPtr, actual_size_read, SEEK_SET) ||
               (1 != fread(block, sizeof(block), 1, *(FILE**)fdPtr))) 
            {
                memset(block, 0xFF, sizeof(block));
            }
            prvPdlLibMd5ProcessOneBlock( block, isBigEndian, &intermediate_digest );
            actual_size_read += PRV_PDL_MD5_WORDS_IN_DIGEST_CNS*sizeof(UINT_32);
        }
    }
    /* processes the padding blocks */
    for ( message_blockPtr  = (UINT_32 *) pad_buffer;
          message_blockPtr  < (UINT_32 *) (pad_buffer + pad_buffer_octets);
          message_blockPtr += PRV_PDL_MD5_WORDS_IN_DIGEST_CNS         ) {

        prvPdlLibMd5ProcessOneBlock( message_blockPtr, isBigEndian, &intermediate_digest );

    }

    if (isBigEndian)
    {
        /* converts the message digest to the "big endian" */
        for (word_offset = 0; word_offset < PRV_PDL_MD5_WORDS_IN_DIGEST_CNS; word_offset++)
        {
            intermediate_digest.words[word_offset] =
                pdlLibSwapWord(intermediate_digest.words[word_offset]);
        }
    }

    /* copies the message digest to the final destination */
    memcpy(digestPtr, &intermediate_digest.bytes, PRV_PDL_MD5_WORDS_IN_DIGEST_CNS);

    return PDL_OK;
}
/*$ END OF  pdlibMd5DigestCompute */

/**
* @fn  PDL_STATUS pdlibMd5DigestComputeWithKey ( IN void * fdPtr, IN void * msgPtr, IN UINT_32 msgLen, IN UINT_8* keyPtr, IN UINT_32 keyLen, OUT PDL_LIB_MD5_DIGEST_STC *digestPtr )
*
* @brief   Perform two iterations of MD5 computation:
* 		First  - Compute MD5 digest of the message contained in specified file or message buffer
* 		Second - Append "Key" to digest and compute MD5 digest on <key+digest>
*
* @param [in]  fdPtr          If non-null, points to file descriptor of type FILE**, containing the message to compute the digest
* @param [in]  msgPtr         If non-null, points to the first octet of the message to compute the digest
* @param [in]  msgLen         size of the message to digest
* @param [in]  keyPtr         Key / secret phrase that will be used for  md5 second iteration
* @param [in]  keyLen         length of key
* @param [out] digestPtr      Computed digest of the message
*
* @return  A PDL_STATUS.
*/
extern PDL_STATUS pdlibMd5DigestComputeWithKey(
	IN  void                    *fdPtr,
	IN  UINT_8                  *msgPtr,
	IN  const UINT_32            msgLen,
	IN  UINT_8                  *keyPtr,
	IN  const UINT_32            keyLen,
	OUT PDL_LIB_MD5_DIGEST_STC  *digestPtr
)
{
	UINT_8 						*tmp;
	UINT_32						i,len = 0;
	PDL_STATUS					status;
	PDL_LIB_MD5_DIGEST_STC		digest;
	memset(&digest,0,sizeof(digest));

	if (msgPtr == NULL || keyPtr == NULL || digestPtr == NULL) {
		return PDL_BAD_PTR;
	}

	if (strlen((char*)keyPtr) > keyLen) {
		return PDL_BAD_SIZE;
	}

	status = pdlibMd5DigestCompute(fdPtr,msgPtr,msgLen,&digest);
	if (status != PDL_OK) {
		return status;
	}
	tmp = prvPdlibOsMalloc(2*PDL_LIB_MD5_DIGEST_LENGTH_CNS + keyLen + 1);
	if (tmp == NULL) {
		return PDL_OUT_OF_CPU_MEM;
	}
	for (i = 0; i < PDL_LIB_MD5_DIGEST_LENGTH_CNS; i++) {
    	len+=sprintf((char*)&tmp[len],"%02x",digest.value[i]);
	}
	len+=sprintf((char*)&tmp[len], "%s",keyPtr);
	status = pdlibMd5DigestCompute(NULL, tmp, strlen((char*)tmp), digestPtr);
	prvPdlibOsFree(tmp);
	return status;
}
