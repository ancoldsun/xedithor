/*
 * Copyright 2012 Edi Ermawan  < edi.ermawan@gmail.com >
 * 
 */
package com.xdr.lib;

/*
 * constant value for sprite library need
 * 
 */
public interface XDRConstant {
	
	public final int N_MODULE_DEF = 5;  // number of field in single module

	public final int N_FRAME_DEF  = 5; 	// number of field in single frame

	public final int N_ANIM_DEF   = 5; 	// number of field in single animation
	
	public final int BYTES_START_MODULE = 0xEFFE0EEF;  // unique bytes ( 4 byte ) signed starting module data
	
	public final int BYTES_START_FRAME  = 0xFFFA0EFF;  // unique bytes ( 4 byte ) signed starting frame data
	
	public final int BYTES_START_ANIM   = 0xEEEA0EFF;  // unique bytes ( 4 byte ) signed starting anim data
}
