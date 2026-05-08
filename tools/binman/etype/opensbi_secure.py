# SPDX-License-Identifier: GPL-2.0+
#
# Entry-type module for a secure RISC-V OpenSBI binary blob
#

from binman.etype.blob_named_by_arg import Entry_blob_named_by_arg


class Entry_opensbi_secure(Entry_blob_named_by_arg):
    """Secure RISC-V OpenSBI fw_dynamic blob

    Properties / Entry arguments:
        - opensbi-secure-path: Filename of the secure OpenSBI firmware blob
    """
    def __init__(self, section, etype, node):
        super().__init__(section, etype, node, 'opensbi-secure')
        self.external = True
