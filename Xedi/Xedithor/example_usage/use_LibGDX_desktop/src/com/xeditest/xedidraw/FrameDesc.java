package com.xeditest.xedidraw;

public class FrameDesc {
	public int m_moduleCount;
	public int m_frameID;
    public int[][] m_modules;
    
    FrameDesc(int nmodules,int frameid){
    	m_frameID = frameid;
    	m_moduleCount = nmodules;
    	m_modules     = new int[nmodules][];
    	for(int i=0;i<nmodules;i++){
    		m_modules[i] = new int[5];
    	}
    	
    }
}
