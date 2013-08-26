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

#ifndef _SE_MSAB_MAUTIL_JSONPARSER_H_
#define _SE_MSAB_MAUTIL_JSONPARSER_H_

#include <MAUtil/Connection.h>
#include <MAUtil\String.h>
#include <MAUtil/util.h>

namespace MAUtil {
	
	class JSONListener {
	public:
		virtual int null();
		virtual int boolean(bool value);
		virtual int number(const String& number);
		virtual int string(const String& string);
		virtual int startMap();
		virtual int mapKey(const String& key);
		virtual int endMap();
		virtual int startArray();
		virtual int endArray();
	};

	class JSONParser {
	public:
		JSONParser();
	
		void parseFromMemory(const char* jsonText);
		/* Asynchronous - function will return, and callbacks will be invoked later using Environment event handling. */
		void parseFromUrl(const char* url);
	private:
		yajl_handle parser;
		JSONListener* listener;
	};
}

#endif