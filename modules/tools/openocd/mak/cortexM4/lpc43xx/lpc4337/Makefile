###############################################################################
#
# Copyright 2014, Mariano Cerdeiro
# Copyright 2014, 2015, Juan Cecconi
# Copyright 2015, Esteban Volentini (LabMicro, UNT)
# All rights reserved
#
# This file is part of CIAA Firmware.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################
# openocd config
OPENOCD_CFG				= $(OPENOCD_PATH)$(DS)cfg$(DS)$(ARCH)$(DS)$(CPUTYPE)$(DS)$(CPU)$(DS)ciaa-nxp.cfg
# A relocation offset used when write the image file to the current target’s flash bank
TARGET_DOWNLOAD_FLASH_BASE_ADDR = 0x1A000000
TARGET_DOWNLOAD_FLASH_BANK = 0
# A relocation offset used when write the image file to the current target’s qspi bank
TARGET_DOWNLOAD_QSPI_BASE_ADDR = 0x14000000
TARGET_DOWNLOAD_QSPI_BANK = 1
# The file type to be flashed, must be specified explicitly. ex.: bin
TARGET_DOWNLOAD_EXTENSION = bin
# Flash write command
FLASH_WRITE_COMMAND = flash write_image erase unlock
# Flash erase comand
FLASH_ERASE_COMMAND = flash erase_sector
# Flash mass erase comand
MASS_ERASE_COMMAND = flash erase_sector 0 0 last
