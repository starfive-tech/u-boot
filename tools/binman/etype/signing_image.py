# SPDX-License-Identifier: GPL-2.0+
# Copyright (c) 2023 StarFive Technology Co., Ltd.
#
# Entry-type module for signing an image using StarFive signing tool
#

#from collections import OrderedDict

from binman.entry import Entry
from dtoc import fdt_util
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
        parts = fdt_util.GetStringList(self._node, 'cmd1')
        self.cmd1 = ''.join(parts) if parts else ''

    def ObtainContents(self):
        os.system(self.cmd1)
        self.SetContents(b'')
        return True
