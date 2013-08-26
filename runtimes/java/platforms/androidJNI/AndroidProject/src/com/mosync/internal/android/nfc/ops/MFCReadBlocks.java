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

package com.mosync.internal.android.nfc.ops;

import java.io.IOException;
import java.nio.ByteBuffer;

import com.mosync.internal.android.nfc.MifareClassicTag;

import android.nfc.tech.MifareClassic;

public class MFCReadBlocks extends MFRead<MifareClassicTag> {

	private final MifareClassic mifareTag;

	public MFCReadBlocks(MifareClassicTag mifareTag, int firstBlock,
			ByteBuffer dstBuffer) {
		super(mifareTag, firstBlock, dstBuffer);
		this.mifareTag = mifareTag.nativeTag();
	}

	@Override
	protected byte[] readChunk(int blockIndex) throws IOException {
		return mifareTag.readBlock(blockIndex);
	}

}
