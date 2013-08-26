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

/*! \addtogroup WormHoleGroup
 *  @{
 */

/** @defgroup WormHoleGroup Wormhole Library
 *  @{
 */

/**
 * @file FileUtil.h
 * @author Mikael Kindborg
 *
 * #brief High-level utility functions for working with files.
 */

#ifndef WORMHOLE_FILE_UTIL_H_
#define WORMHOLE_FILE_UTIL_H_

#include <ma.h>
#include <MAUtil/String.h>

namespace Wormhole
{
/**
 * @brief Class that contains utility methods.
 *
 * TODO: Add copy constructor and assignment operator.
 */
class FileUtil
{
	public:
		/**
		 * Constructor.
		 */
		FileUtil();

		/**
		 * Destructor.
		 */
		virtual ~FileUtil();

		/**
		 * Get the path to the local file system.
		 * @return Path that ends with a slash.
		 */
		virtual MAUtil::String getLocalPath();

		/**
		 * Get the path to the directory to be used as the
		 * root path by File APIs.
		 * @return Full path to the current root directory.
		 */
		virtual MAUtil::String getAppPath();

		/**
		 * Set the path to the directory to be used as the
		 * root path by File APIs.
		 * @param fullPath Full path to the root directory.
		 */
		virtual void setAppPath(const MAUtil::String& fullPath);

		/**
		 * Extract a file system bundle to a directory in the
		 * local file system on the device/emulator.
		 * @param handle The resource handle of the bundled
		 * file system. Bundles are created with the Bundle tool
		 * that comes with MoSync.
		 * @param destinationPath The path of the directory where
		 * the file system will be extracted.
		 */
		virtual bool extractFileSystem(
			MAHandle handle,
			const MAUtil::String& destinationPath);

		/**
		 * Extract the files in the file system bundle defined
		 * as the first resource in the resource file. Files are
		 * extracted to the root of the local file system on the
		 * device/emulator.
		 *
		 * This function is intended as a high-level way to
		 * extract files packaged in the standard way used in
		 * the HTML5 Project Template.
		 */
		virtual bool extractLocalFiles();

		/**
		 * Get the checksum of a file bundle.
		 * @param handle The resource handle of the bundled
		 * file system. Bundles are created with the Bundle tool
		 * that comes with MoSync.
		 * @return A 32-bit checksum.
		 */
		virtual int getFileSystemChecksum(MAHandle handle);

		/**
		 * Open a file for writing.
		 * Create the file if it does not exist.
		 * Note: Will truncate the file if it exists.
		 * @return Handle to the open file, <0 on error.
		 */
		virtual MAHandle openFileForWriting(const MAUtil::String& filePath);

		/**
		 * Open a file for reading.
		 * @return Handle to the open file, <0 on error.
		 */
		virtual MAHandle openFileForReading(const MAUtil::String& filePath);

		/**
		 * Write a data object to a file.
		 * @return true on success, false on error.
		 */
		virtual bool writeDataToFile(
			const MAUtil::String& filePath,
			MAHandle outData);

		/**
		 * Write a text string to a file.
		 * @return true on success, false on error.
		 */
		virtual bool writeTextToFile(
			const MAUtil::String& filePath,
			const MAUtil::String& outText);

		/**
		 * Read a data object from a file.
		 * @param filePath Full path of file to read.
		 * @param inPlaceholder Placeholder handle for data object.
		 * @return true on success, false on error.
		 */
		virtual bool readDataFromFile(
			const MAUtil::String& filePath,
			MAHandle inPlaceholder);

		/**
		 * Read a text string from a file.
		 * @return true on success, false on error.
		 */
		virtual bool readTextFromFile(
			const MAUtil::String& filePath,
			MAUtil::String& inText);

		/**
		 * Create a text string from data handle.
		 */
		virtual MAUtil::String createTextFromHandle(MAHandle data);

	protected:
		/**
		 * Full path to the current root directory to be used
		 * by File APIs.
		 */
		MAUtil::String mAppPath;
	};

} // namespace

#endif

/*! @} */
