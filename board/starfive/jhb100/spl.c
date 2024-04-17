/**
  ******************************************************************************
  * @file  spl.c
  * @author  StarFive Technology
  * @version  V1.0
  * @date  25/04/2022
  * @brief
  ******************************************************************************
  * @copy
  *
  * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STARFIVE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * COPYRIGHT 2022 Shanghai StarFive Technology Co., Ltd.
  */
#include <common.h>
#include <init.h>
#include <spl.h>
#include <log.h>
#include <linux/delay.h>
#include <image.h>
#include <asm/csr.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/boot_fallback.h>
#include <asm/arch/boot_mapping.h>
#include <asm/arch/spl.h>

#define OUTPUT_ENABLE   0
#define INPUT_ENABLE    1

int spl_board_init_f(void)
{
	int ret;

	ret = spl_soc_init();
	if (ret) {
		debug("JHB100 SPL init failed: %d\n", ret);
		return ret;
	}

	return 0;
}

void spl_perform_fixups(struct spl_image_info *spl_image)
{
	int fb_map_reg = starfive_get_fb_rec_map();

	starfive_fb_rec_map_handler(&fb_map_reg,
		starfive_get_part(PRIMARY),
		starfive_get_part(SECONDARY),
		FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
		CLEAR);
	starfive_set_fb_rec_map(fb_map_reg);
}

u32 spl_boot_device(void)
{
	return jhb100_get_boot_device();
}

void board_boot_order(u32 *spl_boot_list)
{
	starfive_board_boot_order(spl_boot_list);
}

struct legacy_img_hdr *spl_get_load_buffer(ssize_t offset, size_t size)
{
	return (struct legacy_img_hdr *)(STARFIVE_SPL_BOOT_LOAD_ADDR);
}

void board_init_f(ulong dummy)
{
	int ret;

	ret = spl_early_init();
	if (ret)
		panic("spl_early_init() failed: %d\n", ret);

	preloader_console_init();

	riscv_cpu_setup();

	ret = spl_board_init_f();
	if (ret) {
		printf("spl_board_init_f init failed: %d\n", ret);
		return;
	}
}
