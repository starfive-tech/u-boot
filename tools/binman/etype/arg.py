# SPDX-License-Identifier: GPL-2.0+
# Copyright (c) 2016 Google, Inc
# Written by Simon Glass <sjg@chromium.org>
#
# Entry-type module for producing an image using mkimage
#

from collections import OrderedDict

from binman.entry import Entry
from dtoc import fdt_util
from patman import tools

class Entry_arg(Entry):
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
        self._args = fdt_util.GetString(self._node, 'args').split(' ')
        #self._mkimage_entries = OrderedDict()
        #self.align_default = None

    def ObtainContents(self):
        uniq = self.GetUniqueName()
        output_fname = tools.GetOutputFilename('arg-out.%s' % uniq)
        tools.Run('touch', 'arg-out.%s' % uniq);
        tools.Run(*self._args, output_fname)        
        self.SetContents(tools.ReadFile(output_fname))
        return True
