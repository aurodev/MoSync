package com.mosync.internal.android.nfc;

import static com.mosync.internal.generated.MAAPI_consts.MA_NFC_TAG_TYPE_NDEF;

import java.io.IOException;

import android.nfc.FormatException;
import android.nfc.NdefMessage;
import android.nfc.tech.Ndef;

public class NdefTag extends NFCTagBase<Ndef> implements INDEFMessageHolder {

	private NDEFMessage cachedNDEFMessage;

	static NdefTag get(ResourcePool pool, GenericTag tag) {
		Ndef ndef = Ndef.get(tag.getTag());
		if (ndef != null) {
			NdefTag result = new NdefTag(pool, ndef);
			result.cacheNDEFMessage(pool, ndef.getCachedNdefMessage());
			return result;
		}

		return null;
	}

	private void cacheNDEFMessage(ResourcePool pool, NdefMessage newMessage) {
		if (cachedNDEFMessage != null) {
			cachedNDEFMessage.destroy(pool);
		}
		cachedNDEFMessage = new NDEFMessage(pool, newMessage);
	}

	private NdefTag(ResourcePool pool, Ndef ndef) {
		super(pool, ndef, MA_NFC_TAG_TYPE_NDEF);
	}

	@Override
	public byte[] transceive(byte[] buffer) throws IOException {
		throw new IOException("Cannot transceive.");
	}

	@Override
	public void requestNDEFMessage(ResourcePool pool) throws IOException {
		try {
			cacheNDEFMessage(pool, nativeTag.getNdefMessage());
		} catch (FormatException e) {
			throw new IOException("Malformed NDEF");
		}
	}

	@Override
	public NDEFMessage getNDEFMessage() {
		return cachedNDEFMessage;
	}

}
