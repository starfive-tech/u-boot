// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2t025 StarFive Technology Co., Ltd.
 * Author:	Wei Sheng Ch'ng <weisheng.chng@starfivetech.com>
 */

#include <asm/arch/starfive_reset.h>
#include <command.h>
#include <env.h>
#include <env_internal.h>
#include <stdlib.h>
#include <spl.h>

#define KEY_BUF_SIZE		64
#define VAL_BUF_SIZE		512

void starfive_append_bootargs_generic(char *parsed_str, char *val_str)
{
	strcpy(parsed_str, val_str);
}

void env_filter_add_bootarg(void (*str_fn)(char *ostr, char *istr),
			    char *key_str, char *val_str)
{
	/* Initialise variable */
	char new_bootarg[1024];
	char parsed_bootargs[1024];
	char new_entry[1024];
	char *existing_bootargs = env_get("bootargs");
	char *key_str_start = strstr(existing_bootargs, key_str);

	/* Get returned string */
	str_fn(new_bootarg, val_str);

	/* Try to filter reset_event keyword */
	if (key_str_start) {
		/* Found keyword if here */
		char *key_str_end = strchr(key_str_start, ' ');

		if (!key_str_end) {
			/* Actually at end of string */
			key_str_end = key_str_start +
				      strlen(key_str_start);
		}

		/* Remove the keyword and 'space' from previous appendation */
		size_t str_size_before;

		if (key_str_start == existing_bootargs) {
			str_size_before = 0;
			parsed_bootargs[0] = '\0';
		} else {
			str_size_before = key_str_start - existing_bootargs - 1;
			strncpy(parsed_bootargs, existing_bootargs, str_size_before);
			parsed_bootargs[str_size_before] = '\0';
		}

		if (key_str_start == existing_bootargs && *key_str_end == ' ')
			key_str_end++;

		strcat(parsed_bootargs, key_str_end);
		env_set("bootargs", parsed_bootargs);
	}

	/* Append the keyword */
	existing_bootargs = env_get("bootargs");
	snprintf(new_entry, sizeof(new_entry), "%s%s", key_str, new_bootarg);

	if (existing_bootargs && strlen(existing_bootargs) > 0) {
		snprintf(parsed_bootargs, sizeof(parsed_bootargs), "%s %s",
			 existing_bootargs ? existing_bootargs : "", new_entry);
	} else {
		snprintf(parsed_bootargs, sizeof(parsed_bootargs), "%s", new_entry);
	}

	env_set("bootargs", parsed_bootargs);
}

static int do_starfive_affix_bootargs(struct cmd_tbl *cmdtp, int flag, int argc,
				      char *const argv[])
{
	while (--argc > 0) {
		char *c_arg = *++argv;

		if (*c_arg == '-') {
			switch (*++c_arg) {
			case 'h':
				return CMD_RET_USAGE;
			default:
				goto err;
			}
		} else if (strchr(c_arg, '=')) {
			char key_buf[KEY_BUF_SIZE];
			char val_buf[VAL_BUF_SIZE];
			char *key_val = strdup(c_arg);

			if (!key_val)
				return CMD_RET_USAGE;

			char *f_occur = strchr(key_val, '=');
			*f_occur = '\0';

			char *key = key_val;
			char *val = f_occur + 1;

			snprintf(key_buf, KEY_BUF_SIZE, "%s=", key);
			snprintf(val_buf, VAL_BUF_SIZE, "%s", val);

			printf("Key: %s\n", key_buf);
			printf("Value: %s\n", val_buf);

			env_filter_add_bootarg(starfive_append_bootargs_generic,
					       key_buf, val_buf);

			free(key_val);
		}
	}
	env_filter_add_bootarg(starfive_get_reset_event, "reset_event=", NULL);
	return CMD_RET_SUCCESS;
err:
	printf("Unknown argument, refer to help command...\n");
	return CMD_RET_USAGE;
}

U_BOOT_LONGHELP(affixbootargs,
		"-\n    - Affix additional runtime generated boot arguments, if available\n"
		"\tpass: String <key=value> - Boot argument string, e.g argument=val\n"
		"\t      -h                 - help\n"
		"\tIf no parameter passed, only affix default generated boot arguments\n"
);

U_BOOT_CMD(affixbootargs, CONFIG_SYS_MAXARGS, 1, do_starfive_affix_bootargs,
	   "Affix additional boot arguments if available",
	   affixbootargs_help_text
);
