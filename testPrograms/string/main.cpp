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

#include <MAUtil/String.h>
#include <conprint.h>
#include <maheap.h>

using namespace MAUtil;

struct A {
int a;
String b;
};

struct S {
	int a;
	String n;
	Vector<A> b;
};

Vector<S> s;
//String s;

extern "C" int MAMain() {
	InitConsole();
	printf("reading stroe...");
	//printf("%s", s[0].b[0].b.c_str());
	s.resize(7);
	maExit(999);
	return 0;
}
