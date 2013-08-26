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

/*
 * base.h
 *
 *  Created on: Mar 14, 2011
 *      Author: fmattias
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <mavsprintf.h>

/**
 * Returns a handle to an icon.
 *
 * @return A handle to an icon. You should not free the memory.
 */
const char *getIconHandleAsString();

#endif /* RESOURCES_H_ */
