/*
 * Copyright 2012 Edi Ermawan  < edi.ermawan@gmail.com >
 * 
 */

package com.xdr.lib;

import java.io.IOException;

import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

public class XDRSprite {

	private int[][] m_modules;
	private XDRFrameDescription[] m_frames;
	private XDRAnimDescription[] m_anims;
	private Texture m_texture;
	private SpriteBatch m_batcher;
	private TextureRegion[] m_imgModules;
	private int m_currentFrame=0;
	private int m_limiter=0;
	private int m_animPlayed=1;
	private boolean isAnimating = false;
	
	private int m_animPosX =0;
	private int m_animPosY =0;
	
	private int m_adjust_cx= 0;
	private int m_adjust_cy= XDRSetting.H_SCREEN;
	
	private void loadSpriteDescriptor(int[] a32Sprite)
	{		
		int i=0;
		while(i<a32Sprite.length){
			if(a32Sprite[i] == XDRConstant.BYTES_START_MODULE)  // MODULE
			{   
				int nModule = a32Sprite[++i];
				m_modules = new int [nModule][XDRConstant.N_MODULE_DEF];	
				for(int j=0;j<nModule;j++)
				{
					for(int k=0;k<XDRConstant.N_MODULE_DEF;k++)
					{   
						m_modules[j][k] = a32Sprite[++i];
					}
				}
				i++;
			}
			if(a32Sprite[i] == XDRConstant.BYTES_START_FRAME)  // FRAME
			{ 
				int nFrame = a32Sprite[++i];
				m_frames= new XDRFrameDescription[nFrame];
				
				for(int j=0;j<nFrame;j++)
				{
					int nFrameID = a32Sprite[++i];
					int nModInFrame = a32Sprite[++i];				
					m_frames[j] = new XDRFrameDescription(nModInFrame,nFrameID);

					for(int k=0;k<nModInFrame;k++)
					{
						for(int l=0;l<XDRConstant.N_FRAME_DEF;l++)
						{   
							m_frames[j].m_modules[k][l] = a32Sprite[++i];
						}
					}
				}
				i++;
			}
			if(a32Sprite[i] == XDRConstant.BYTES_START_ANIM){  // ANIMATION
				int nAnim = a32Sprite[++i];		
				m_anims = new XDRAnimDescription[nAnim];
				for(int j=0;j<nAnim;j++)
				{
					     // anim id is not used yet, only skip this 
					++i; // future: int animID = a32Sprite[++i];
					int nFrameAnim  = a32Sprite[++i];					
					m_anims[j] = new XDRAnimDescription(nFrameAnim);
					for(int k=0;k<nFrameAnim;k++)
					{
						for(int l=0;l<XDRConstant.N_ANIM_DEF;l++)
						{  
							m_anims[j].m_frames[k][l] = a32Sprite[++i];
						}
					}
				}
				i++;				
			}
			i++;
		}
		
		// create texture region for each available module
		m_imgModules = new TextureRegion[m_modules.length];
		for(int j=0;j<m_modules.length;j++)
		{
			m_imgModules[j] = new TextureRegion(m_texture, m_modules[j][1], m_modules[j][2], m_modules[j][3], m_modules[j][4]);
		}		
	}
	
	private int[] getModule(int id)
	{
		for(int j=0;j<m_modules.length;j++)
		{
			if(id==m_modules[j][0]){
				return m_modules[j];
			}
		}
		return null; 
	}
	
	private TextureRegion getTextureModule(int id)
	{
		for(int j=0;j<m_modules.length;j++)
		{
			if(id==m_modules[j][0]){
				return m_imgModules[j];
			}
		}
		return null; 
	}
	
	private void paintModule_I(int index,int offx,int offy)
	{
		int[] module = getModule(index);
		TextureRegion tr = getTextureModule(index);
		// xedithor: 0,0 is top left
		// here    : 0,0 is bottom left
		m_batcher.draw(tr,(m_animPosX+offx),(m_animPosY-offy) - module[4], module[3], module[4]);
	}
	
	private void paintModule(int index,int offx,int offy)
	{
		int[] module = getModule(index);
		TextureRegion tr = getTextureModule(index);//- m_adjust_cy;
		m_batcher.draw(tr,(offx+m_animPosX), offy , module[3], module[4]);
	}
	
	private void paintFrame_I(int index,int offAx,int offAy)
	{
		m_batcher.begin();
		XDRFrameDescription frame= m_frames[index];
		for(int i=0;i<frame.m_moduleCount;i++){
			int idMod= frame.m_modules[i][0];
			int offx = frame.m_modules[i][1];
			int offy = frame.m_modules[i][2];
			paintModule_I(idMod,offAx+offx,(offAy+offy));
		}
		 m_batcher.end();
	}
	public void paintFrame(int index,int offAx,int offAy)
	{
		m_batcher.begin();
		XDRFrameDescription frame= m_frames[index];
		for(int i=0;i<frame.m_moduleCount;i++){
			int idMod= frame.m_modules[i][0];
			int offx = frame.m_modules[i][1];
			int offy = frame.m_modules[i][2];
			paintModule(idMod,offAx+offx,offAy-offy);
		}
		 m_batcher.end();
	}
	// for anim object
	public void paintFrame(int animPlayed,int currentFrame,int posx,int posy)
	{
		setPos(posx,posy);
		XDRAnimDescription anim= m_anims[animPlayed];
		int offx = (anim.m_frames[currentFrame][1]);
		int offy = (anim.m_frames[currentFrame][2]) ;
		paintFrameID(anim.m_frames[currentFrame][0],offx,offy);		
	}
	private void paintFrameID(int frmID,int offx,int offy)
	{
		int index=0;
		for(int j=0;j<m_frames.length;j++)
		{
			if(frmID==m_frames[j].m_frameID){
				index=j;
				break;
			}
		}
		paintFrame_I(index,offx,offy);
	}
	
	public void setAnim(int index)
	{
		m_animPlayed = index;
	}
	
	public void setPos(int posx,int posy){
		m_animPosX = posx;
		m_animPosY = posy;
	}
	/*
	public void render()
	{		
		if(isAnimating)
		{
			deAnimDescription anim= m_anims[m_animPlayed];
			int offx = (anim.m_frames[m_currentFrame][1]);
			int offy = (anim.m_frames[m_currentFrame][2]) ;
			paintFrameID(anim.m_frames[m_currentFrame][0],offx,-offy);
			
		   if(m_limiter%10 == 0){
		        if(m_currentFrame<anim.m_frameCount-1)
		        {
		        	m_currentFrame=m_currentFrame+1;
		        }
		        else
		        {
		        	isAnimating =false;
		        	m_currentFrame=0;
		        }
		    }
		    m_limiter++;
		} 
		else
		{
			deAnimDescription anim= m_anims[m_animPlayed];
			int offx = (anim.m_frames[m_currentFrame][1]);
			int offy = (anim.m_frames[m_currentFrame][2]) ;
			paintFrameID(0,offx,-offy);
		}
       
	}
	*/
	public XDRAnimDescription[] getAnims()
	{
		return m_anims;
	}
	
	public XDRFrameDescription[] getFrames()
	{
		return m_frames;
	}
	
	public int getNumberFrameInAnim(int animIdx)
	{
		XDRAnimDescription anim= m_anims[animIdx];
		return anim.m_frameCount;
	}
	public void loadData(int sprID)
	{
		XDRPackReader dataPack = new XDRPackReader(sprID);
		try {
			dataPack.ReadSprite();
		} catch (IOException e) {
			System.out.println("error read sprite");
			e.printStackTrace();
		}
		
		byte[] bytesPNG = dataPack.getPNGByteArray();
		int[] sprDesc   = dataPack.getSprIntDesc();

		Pixmap pxmap  = new Pixmap(bytesPNG,0,bytesPNG.length);	
		m_texture     = new Texture(pxmap);
		
		loadSpriteDescriptor(sprDesc);
	}
	
	public void setSptiteBatch(SpriteBatch batcher)
	{
		m_batcher = batcher;
	}

	public void coordinateAdjustment(int adjustcx,int adjustcy)
	{
		m_adjust_cx =adjustcx;
		m_adjust_cy =adjustcy;
	}
	public void dispose() {
		// TODO Auto-generated method stub
		m_texture.dispose();
		m_modules =null;
		m_frames  =null;
		m_anims   =null;
			
	}

	public void setIsAnimating(boolean isAnimating) {
		this.isAnimating = isAnimating;
	}

	public boolean getIsAnimating() {
		return isAnimating;
	}
}
