/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#import <Foundation/Foundation.h>
#include <helpers/cpp_defs.h>
#include "Syscall.h"

SYSCALL(int, maCameraStart());
SYSCALL(int, maCameraStop());
SYSCALL(int, maCameraSetPreview(MAHandle widgetHandle));
SYSCALL(int, maCameraSelect(MAHandle cameraNumber));
SYSCALL(int, maCameraNumber());
SYSCALL(int, maCameraSnapshot(int formatIndex, MAHandle placeholder));
SYSCALL(int, maCameraSnapshotAsync(MAHandle placeholder, int formatIndex));
SYSCALL(int, maCameraRecord(int stopStartFlag));
SYSCALL(int, maCameraSetProperty(const char *property, const char* value));
SYSCALL(int, maCameraGetProperty(const char *property, char *value, int maxSize));
SYSCALL(int, maCameraPreviewSize());
SYSCALL(int, maCameraPreviewEventEnable(int previewEventType, void* previewBuffer, const MARect* previewArea));
SYSCALL(int, maCameraPreviewEventDisable());
SYSCALL(int, maCameraPreviewEventConsumed());
