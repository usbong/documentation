#!/bin/bash

# Copyright 2020~2022 SYSON, MICHAEL B.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You ' may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, ' WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing ' permissions and limitations under the License.
#
# Verify and Scan Document using Linux PC
# @company: USBONG
# @author: SYSON, MICHAEL B.
# @date created: 2020
# @last modified: 20220307; from 20210711
# @websie address: http://www.usbong.ph
#
# Reference:
# 1) https://github.com/usbong/documentation/blob/master/Usbong/hardware%20software%20integration/Machine%20Drivers/Printers%20and%20Scanners.md;
# last accessed: 20220307

sudo scanimage -L
sudo scanimage --format=jpeg > outputImage.jpeg
