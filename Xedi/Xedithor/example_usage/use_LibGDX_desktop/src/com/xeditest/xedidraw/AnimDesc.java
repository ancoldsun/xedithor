
package com.xeditest.xedidraw;

public class AnimDesc {
	public int m_frameCount;
    public int[][] m_frames;
    
    AnimDesc(int nframes){
    	m_frameCount = nframes;
    	m_frames     = new int[nframes][];
    	for(int i=0;i<nframes;i++){
    		m_frames[i] = new int[5];
    	}
    	
    }
}

