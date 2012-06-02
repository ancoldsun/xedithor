/*
 * Copyright 2012 Edi Ermawan  < edi.ermawan@gmail.com >
 * 
 */

package com.xdr.lib;

public class XDRAnimationObject {
	private XDRSprite m_sprite;
	private int m_animIndex;
	private int m_currentFrame=0;
	private int m_frameWhenAnimFinish=0;
	private int m_posX=0;
	private int m_posY=0;
	private int m_animLoop=1;
	private boolean m_isAnimFinish;
	private int m_limiter=0;
	private boolean m_paintFrameWhenAnimFinish=false;
	
	public XDRAnimationObject(XDRSprite v_Sprite,int px,int py)
	{
		this.m_sprite = v_Sprite;
		m_posX = px;
		m_posY = py;
	}

	public void setSprite(XDRSprite v_Sprite) {
		this.m_sprite = v_Sprite;
	}
	
	public void setAnimIndex(int m_animIndex) {
		this.m_animIndex = m_animIndex;
	}

	public int getAnimIndex() {
		return m_animIndex;
	}

	public void setPosX(int m_posX) {
		this.m_posX = m_posX;
	}

	public int getPosX() {
		return m_posX;
	}

	public void setPosY(int m_posY) {
		this.m_posY = m_posY;
	}

	public int getPosY() {
		return m_posY;
	}

	public void setAnimLoop(int m_animLoop) {
		this.m_animLoop = m_animLoop;
	}

	public int getAnimLoop() {
		return m_animLoop;
	}

	public boolean isAnimFinish() {
		return m_isAnimFinish;
	}
	
	public void update() {
		if(m_animLoop>0 || m_animLoop == -1)
		{
		   if(m_limiter%10 == 0){
		        if(m_currentFrame<m_sprite.getNumberFrameInAnim(m_animIndex)-1)
		        {
		        	m_currentFrame=m_currentFrame+1;
		        }
		        else
		        {
		        	m_currentFrame=0;
		        	if(m_animLoop>0)
		        		m_animLoop--;
		        }
		    }
		    m_limiter++;
		}
	}
	
	public void render() {
			
		if(m_animLoop>0 || m_animLoop == -1)
			m_sprite.paintFrame(m_animIndex, m_currentFrame, m_posX, m_posY);
		else if(m_paintFrameWhenAnimFinish)// m_animLoop==0
			m_sprite.paintFrame(m_animIndex, m_frameWhenAnimFinish, m_posX, m_posY);
	}

	public void setPaintFrameWhenAnimFinish(boolean m_paintFrameWhenAnimFinish) {
		this.m_paintFrameWhenAnimFinish = m_paintFrameWhenAnimFinish;
	}

	public boolean isPaintFrameWhenAnimFinish() {
		return m_paintFrameWhenAnimFinish;
	}

	public void setFrameWhenAnimFinish(int m_frameWhenAnimFinish) {
		this.m_frameWhenAnimFinish = m_frameWhenAnimFinish;
	}

	public int getFrameWhenAnimFinish() {
		return m_frameWhenAnimFinish;
	}
	

}
