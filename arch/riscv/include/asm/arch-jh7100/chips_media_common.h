/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */
//
// chips && media.h
//
// JH chips and media Defines
//
// Description:
//
// Revision History:
//        DATE        VERSION  AUTHOR        NOTE
//        ----------  -------  -----------   ------------------------------
//        2019/04/29  0.1      jing.rao       Initial
//

#ifndef _CM_COMMON_H
#define _CM_COMMON_H


#define JH_WAVE_VDEC
//#define JH_WAVE_VENC   1

extern int vdec_bs_mode;

#define JH_DDR0    1

#ifdef JH_DDR0
#define JH_CODE_START_BASE             0x80000000  ///0x1000000000///
#else
#define JH_CODE_START_BASE             0x1000000000
#endif
#define JH_VODE_START_SIZE             0x4000000///0x3200000   /* 64MB */

#define SYSTEMPORT_START    0x1000000000
#define MEMPORT_START       0x80000000
#define JPEG_DEC_MEMPORT_TO_SYSTEMPORT  (SYSTEMPORT_START-MEMPORT_START)

#define WAVE5_SEC_ADDR      0x18080000


/* firware                  1MB          [ 0x8400_0000 ] */
#define WAVE5_FIWMWARE_BUFFER_BASE      (/*JPEG_DEC_MEMPORT_TO_SYSTEMPORT + */JH_CODE_START_BASE + JH_VODE_START_SIZE)
#define WAVE5_FIWMWARE_BUFFER_SIZE      (0x100000)    /* 1024*1024*1 -- 1MB */

/* H265 bitstream           10MB         [ 0x8410_0000 ] */
#define WAVE5_FILE_BUFFER_BASE          (/*JPEG_DEC_MEMPORT_TO_SYSTEMPORT + */WAVE5_FIWMWARE_BUFFER_BASE + WAVE5_FIWMWARE_BUFFER_SIZE)
#define WAVE5_FILE_BUFFER_SIZE          (0xA00000)    /* 1024*1024*10 -- 10MB */

/* vdb_video_memory         128MB       [ 0x84B0_0000 ] */
#define WAVE5_VPU_DRAM_PHYSICAL_BASE    (WAVE5_FILE_BUFFER_BASE + WAVE5_FILE_BUFFER_SIZE)
#define WAVE5_VPU_DRAM_SIZE             (128*1024*1024)         /* 128MB */

/* WAVE5 yuv data buffer    4MB     	[ 0x8CB0_0000 ] */
#define WAVE5_YUV_BUFFER_BASE     		(WAVE5_VPU_DRAM_PHYSICAL_BASE + WAVE5_VPU_DRAM_SIZE)
#define WAVE5_YUV_BUFFER_SIZE     		0xA00000

#define WAVE5_BUFF_FLUSH_BASE           (WAVE5_FIWMWARE_BUFFER_BASE)
#define WAVE5_BUFF_FLUSH_SIZE           (WAVE5_FIWMWARE_BUFFER_SIZE + WAVE5_FILE_BUFFER_SIZE + WAVE5_VPU_DRAM_SIZE)

#if 1
/* enc: bitstream buffer to put jpg data 4MB    [ 0x8400_0000 ] */
#define JPEG_BITSTREAM_BUFFER_BASE      (JH_CODE_START_BASE + JH_VODE_START_SIZE)
#define JPEG_BITSTREAM_BUFFER_SIZE      0x400000        /* 4MB */

/* jpeg yuv data feeder buffer          4MB     [ 0x8440_0000 ] */
#define JPEG_YUV_FEEDER_BUFFER_BASE     (JPEG_BITSTREAM_BUFFER_BASE + JPEG_BITSTREAM_BUFFER_SIZE)
#define JPEG_YUV_FEEDER_BUFFER_SIZE     0x400000

/* s_jdb_video_memory                   128MB   [ 0x8480_0000 ] */
#define JPEG_DRAM_PHYSICAL_BASE         (JPEG_YUV_FEEDER_BUFFER_BASE + JPEG_YUV_FEEDER_BUFFER_SIZE)
#define JPEG_JDI_DRAM_PHYSICAL_SIZE     (128*1024*1024)         /* 8000000 128MB */

/* dec: bitstream buffer to put jpg data 4MB [ 0x8C80_0000 ] */
#define JPEG_BITSTREAM_JPG_FEEDING_BUFFER_BASE  (JPEG_DRAM_PHYSICAL_BASE + JPEG_JDI_DRAM_PHYSICAL_SIZE)
#define JPEG_BITSTREAM_JPG_FEEDING_BUFFER_SIZE  0x400000

/* dec: jpeg yuv data                   4MB    [ 0x8CC0_0000 ] */
#define JPEG_DEC_YUV_BUFFER_BASE        (JPEG_BITSTREAM_JPG_FEEDING_BUFFER_BASE + JPEG_BITSTREAM_JPG_FEEDING_BUFFER_SIZE + JPEG_DEC_MEMPORT_TO_SYSTEMPORT)
#define JPEG_DEC_YUV_BUFFER_SIZE        0x400000


#define JPEG_ENC_BUFF_FLUSH_BASE        JPEG_BITSTREAM_BUFFER_BASE
#define JPEG_ENC_BUFF_FLUSH_SIZE        (JPEG_BITSTREAM_BUFFER_SIZE + JPEG_YUV_FEEDER_BUFFER_SIZE + JPEG_JDI_DRAM_PHYSICAL_SIZE)

#define JPEG_DEC_BUFF_FLUSH_BASE        JPEG_DRAM_PHYSICAL_BASE
#define JPEG_DEC_BUFF_FLUSH_SIZE        (JPEG_JDI_DRAM_PHYSICAL_SIZE + JPEG_BITSTREAM_JPG_FEEDING_BUFFER_SIZE + JPEG_DEC_YUV_BUFFER_SIZE)

#else
#define JPEG_TEST_INTMEM    1
#define JPEG_ENC_Y_BASE                 (0x18080000)
#define JPEG_ENC_Cb_BASE                (0x18080000 + 0xC800)
#define JPEG_ENC_Cr_BASE                (0x18080000 + 0x19000)

/* enc: bitstream buffer to put jpg data  4MB    0x1801_9000 */
#define JPEG_BITSTREAM_reg_BASE         (0x18000000 + 0x19000)
#define JPEG_BITSTREAM_reg_SIZE         (0xC800)

/* enc: bitstream buffer to put jpg data  4MB    0x1800_C800 */
#define JPEG_BITSTREAM_BUFFER_BASE      (0x18000000 + 0xC800)
#define JPEG_BITSTREAM_BUFFER_SIZE      (0xC800)

/* jpeg yuv data feeder buffer       4MB    0x1800_0000 144x176 = 0x6300*/
#define JPEG_YUV_FEEDER_BUFFER_BASE     (0x18000000)
#define JPEG_YUV_FEEDER_BUFFER_SIZE     (0xC800)

/* s_jdb_video_memory               128MB   0x83A0_0000 or 0x10_03A0_0000 */
#define JPEG_DRAM_PHYSICAL_BASE         (JH_CODE_START_BASE + JH_VODE_START_SIZE)
#define JPEG_JDI_DRAM_PHYSICAL_SIZE     (128*1024*1024)

/* dec: bitstream buffer to put jpg data  128KB    0x1800_0000 */
#define JPEG_BITSTREAM_JPG_FEEDING_BUFFER_BASE  (0x18000000)
#define JPEG_BITSTREAM_JPG_FEEDING_BUFFER_SIZE  (0xC800)

/* dec: jpeg yuv data                   4MB    [ 0x1800_C800 ] */
#define JPEG_DEC_YUV_BUFFER_BASE        (JPEG_BITSTREAM_JPG_FEEDING_BUFFER_BASE + JPEG_BITSTREAM_JPG_FEEDING_BUFFER_SIZE)
#define JPEG_DEC_YUV_BUFFER_SIZE        (0x11800) /* 70KB*/

#define JPEG_DEC_Y_BASE                 (0x18080000)
#define JPEG_DEC_Cb_BASE                (0x18080000 + 0xC800)
#define JPEG_DEC_Cr_BASE                (0x18080000 + 0x19000)

#define JPEG_ENC_BUFF_FLUSH_BASE        JPEG_DRAM_PHYSICAL_BASE
#define JPEG_ENC_BUFF_FLUSH_SIZE        (JPEG_JDI_DRAM_PHYSICAL_SIZE)

#define JPEG_DEC_BUFF_FLUSH_BASE        JPEG_DRAM_PHYSICAL_BASE
#define JPEG_DEC_BUFF_FLUSH_SIZE        JPEG_JDI_DRAM_PHYSICAL_SIZE


#endif



#endif // _CM_COMMON_H
