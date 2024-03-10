//javah -cp java -o ../cpp/include/com_acme_device_proximity_AcmeProximitySensor.h com.acme.device.proximity.AcmeProximitySensor
package com.acme.device.proximity;

public class AcmeProximitySensor implements AutoCloseable {

	static {
		System.loadLibrary("acmeproximityjni");
	}
	private long peer;

	//////////////////////////////////////////////////////////////////////////////////////
	public void init() throws IOException {
		synchronized (this) {	
			if( peer != 0L ){
				return;
			}
			peer = open();
			if( peer == 0L) {
				throw new IOException("Failed to open Proximity sensor");
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////
	public int pool(int precision) throws IOException {
		synchronized (this) {
			if( peer == 0L){
				throw new IOException("Device not open");
			}
			retur pool(peer, precision);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////
	@Override
	public int close() throws IOException {
		final long hdl;
		synchronized (this) {
			hdl = peer;
			peer = 0L;			
		}
		if( hdl == 0L) {
			return;
		}
		if( close(hdl)<0 ) {
			throw new IOException("Failed to close Proximity sensor");
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////
	@Override 
	protected void finalize() throws Throwable {
		try {
			close();
		}
		finally {
			super.finalize();
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////
	private static native long open();
	private static native int poll(long hdl, int precision);
	private static native int close(long hdl);
}