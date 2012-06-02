/*
 * Copyright 2012 Edi Ermawan  < edi.ermawan@gmail.com >
 * 
 */

package com.xdr.lib;
/*
 *  class for hold a frame
 *  a frame is consist of modules
 *  this class is supposed to act like "struct" in C
 */
public class XDRFrameDescription {
	
	public int m_moduleCount;
	public int m_frameID;
    public int[][] m_modules;
    
    XDRFrameDescription(int nmodules,int frameid)
    {
    	m_frameID = frameid;
    	m_moduleCount = nmodules;
    	m_modules     = new int[nmodules][];
    	
    	for(int i=0;i<nmodules;i++)
    	{
    		m_modules[i] = new int[XDRConstant.N_FRAME_DEF];
    	}
    	
    }
}
