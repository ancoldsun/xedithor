
/*
 * Copyright 2012 Edi Ermawan  < edi.ermawan@gmail.com >
 * 
 */

package com.xdr.lib;
/*
 *  class for hold an animation
 *  animation is consist of frames
 *  this class is supposed to act like "struct" in C
 */
public class XDRAnimDescription {
	
	public int m_frameCount;
    public int[][] m_frames;
    
    XDRAnimDescription(int nframes)
    {
    	m_frameCount = nframes;
    	m_frames     = new int[nframes][];
    	
    	for(int i=0;i<nframes;i++)
    	{
    		m_frames[i] = new int[XDRConstant.N_ANIM_DEF];
    	}
    	
    }
}

