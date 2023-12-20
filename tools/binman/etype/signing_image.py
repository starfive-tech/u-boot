# SPDX-License-Identifier: GPL-2.0+
# Copyright (c) 2023 StarFive Technology Co., Ltd.
#
# Entry-type module for signing an image using StarFive signing tool
#

#from collections import OrderedDict

from binman.entry import Entry
from dtoc import fdt_util
from u_boot_pylib import tools
import os

class Entry_signing_image(Entry):
    """Executing command specified in args

    Properties / Entry arguments:
        - args: arguments to pass

    e.g.::

        arg {
            args = "mkimage -k ../starfive_key/linux_key -K u-boot.dtb -r -F kernel_sign.itb";
        };

    """
    def __init__(self, section, etype, node):
        super().__init__(section, etype, node)
        self.cmd1 = fdt_util.GetString(self._node, 'cmd1').split('  ')

    def ObtainContents(self):
        uniq = self.GetUniqueName()
        output_fname = tools.get_output_filename('arg-out.%s' % uniq)
        tools.run('touch', 'arg-out.%s' % uniq);
        os.system(*self.cmd1)
        self.SetContents(tools.read_file(output_fname))
        return True
