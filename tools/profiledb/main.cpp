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

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "profiledb/profiledb.h"

using namespace std;

void printUsage();
string handleStandaloneWildcard(string& qouted);

void printUsage() {
	printf("Usage: profiledb [OPTIONS] COMMAND [PARAMETERS]\n"
		"\n"
		"Commands:\n"
		"-l, --list  [PATTERN]            List all available profiles that\n"
		"                                 matches PATTERN. A PATTERN is a\n"
		"                                 comma-separated list of sub-PATTERNs,\n"
		"                                 that may be either the name of a\n"
		"                                 profile, or a name followed by a\n"
		"                                 wildcard character (*) to match\n"
		"                                 all profiles that starts with a\n"
		"                                 specific string.\n"
		"-f, --list-families              List all available profile families.\n"
		"-g, --get   [PATTERN]            Return a description of all\n"
		"                                 profiles that matches PATTERN.\n"
		"-m, --match PROFILE CAPABILITIES Return a profile matching PROFILE.\n"
		"                                 and CAPABILITIES\n"
		"-c, --list-capabilities [STATE]  List all available capabilities.\n"
		"                                 that matches TYPE, which is a comma-\n"
		"                                 separated list of states (may be\n"
		"                                 SUPPORTED, UNSUPPORTED, NOT_IMPLEMENTED\n"
		"                                 REQUIRES_PERMISSION or\n"
		"                                 REQUIRES_PRIVILEGED_PERMISSION\n"
		"-r, --list-runtime [PROFILE]     List the runtime for a profile\n\n"
		"Options:\n"
		"-x, --exclude PATTERN            Filter out all profiles matching\n"
		"                                 PATTERN.\n"
		"-b, --brief                      List all profiles in a short list\n"
		"                                 instead of using XML.\n"
		"    --no-caps                    Do not include capabilities in\n"
		"                                 XML output"
		"\n"
		"Environment variables used:\n"
		" MOSYNCDIR               Path to the MoSync installation directory.\n");
}

string handleStandaloneWildcard(string& quoted) {
	if (quoted == "+") { // We can also use a + character.
		return "*";
	}
	string unquoted = string(quoted);
	string::iterator unquotedBegin = unquoted.begin();
	string::iterator unquotedEnd = unquoted.end() - 1;
	if ((*unquotedBegin == '\'') && (*unquotedEnd == '\'')) {
		unquoted.erase(unquotedBegin);
		unquoted.erase(unquotedEnd);
	}
	return unquoted;
}

int main(int argc, char *argv[]) {
	// Parse option(s):
	ProfileDB db = ProfileDB();
	db.setIncludeCapabilities(true);
	db.setBrief(false);
	db.setOutputMappings(false);
	int curArg = 0;
	while (curArg < argc) {
		curArg++;
		string cmd = argc > curArg ? string(argv[curArg]) : string("");
		string param = argc > curArg + 1 ? string(argv[curArg + 1])
		        : string("");
		if (cmd == "--exclude" || cmd == "-x") {
			db.setExcluded(param);
			curArg++;
		} else if (cmd == "--no-caps") {
			db.setIncludeCapabilities(false);
		} else if ((cmd == "--brief" || cmd == "-b")) {
			db.setBrief(true);
		} else if (cmd == "--list-mappings") {
			db.setOutputMappings(true);
		} else if ("--get" == cmd || "-g" == cmd) {
			param = handleStandaloneWildcard(param);
			db.getProfiles(param);
			return 0;
		} else if ("--list" == cmd || "-l" == cmd) {
			string profilePattern = param.length() > 0 ? param : string("*");
			profilePattern = handleStandaloneWildcard(profilePattern);
			db.listProfiles(profilePattern, false);
			return 0;
		} else if ("--list-families" == cmd || "-f" == cmd) {
			db.listProfiles("*", true);
			return 0;
		} else if ("--match" == cmd || "-m" == cmd) {
			string profilePattern = param;
			vector<Capability> requiredCapabilities;
			vector<Capability> optionalCapabilities;
			vector<Capability>* currentCapabilities = &requiredCapabilities;
			for (int i = curArg + 2; i < argc; i++) {
				string cap = string(argv[i]);
				if ("-o" == cap || "--optional" == cap) {
					currentCapabilities = &optionalCapabilities;
				} else {
					currentCapabilities->push_back(
					        Capability(cap, string(), string(), SUPPORTED,
					                RUNTIME));
				}
			}

			profilePattern = handleStandaloneWildcard(profilePattern);
			db.matchProfiles(profilePattern, requiredCapabilities,
			        optionalCapabilities);
			return 0;
		} else if ("--list-capabilities" == cmd || "-c" == cmd) {
			string statePattern = param.length() > 0 ? param : string("*");
			statePattern = handleStandaloneWildcard(statePattern);
			db.listCapabilities(statePattern);
			return 0;
		} else if ("--list-runtime" == cmd || "-r" == cmd) {
			db.listRuntime(param);
			return 0;
		}
	}

	printUsage();
	return 1;
}
