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

/**
 * \file GraphicsSoftware.h
 * \brief Software implementation of the graphics API.
 * \author Niklas Nummelin
 */

#define _NO_OLDNAMES	//avoid conflicts with y1()
#include <ma.h>

#ifndef _SE_MSAB_MAUTIL_GRAPHICS_SOFTWARE_H_
#define _SE_MSAB_MAUTIL_GRAPHICS_SOFTWARE_H_

#include "Graphics.h"

#ifdef __cplusplus
extern "C" {
#endif

	//MAGraphicsDriver* Gfx_getDriverSoftware(void);
	void Gfx_useDriverSoftware(void);

#ifdef __cplusplus
}
#endif

#endif

