@echo off
REM Copyright 2021 USBONG SOCIAL SYSTEMS, INC. (USBONG)
REM
REM Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You ' may obtain a copy of the License at
REM
REM http://www.apache.org/licenses/LICENSE-2.0
REM
REM Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, ' WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing ' permissions and limitations under the License.
REM
REM @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
REM @author: SYSON, MICHAEL B.
REM @date created: 20210327
REM @last modified: 20210327
REM @website: http://www.usbong.ph

java -cp .\software; generateOpenGLInstructionsFromBlenderOBJFile input/*.obj

PAUSE