package com.xeditest.xedidraw;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

public class XorSprite {

	private static int[][] m_modules;
	private static FrameDesc[] m_frames;
	private static AnimDesc[] m_anims;
	private Texture m_texture;
	private SpriteBatch m_batcher;
	private TextureRegion[] m_imgModules;
	private int m_currentFrame=0;
	private int m_limiter=0;
	private int m_animPlayed=1;
	
	private int m_animPosX =0;
	private int m_animPosY =0;

	public void setData(SpriteBatch batcher,Texture texture, int[] a32Sprite)
	{	
		m_texture = texture;
		m_batcher = batcher;
		int i=0;
		while(i<a32Sprite.length){
			if(a32Sprite[i] == 0xEFFE0EEF){  // MODULE
				int nModule = a32Sprite[++i];
				m_modules = new int [nModule][5];	
				for(int j=0;j<nModule;j++){
					for(int k=0;k<5;k++){   // 5 = n column table modules in xedithor
						m_modules[j][k] = a32Sprite[++i];
					}
				}
				i++;
			}
			if(a32Sprite[i] == 0xFFFA0EFF){ // FRAME
				int nFrame = a32Sprite[++i];
				m_frames= new FrameDesc[nFrame];
				
				for(int j=0;j<nFrame;j++){
					int nFrameID = a32Sprite[++i];
					int nModInFrame = a32Sprite[++i];				
					m_frames[j] = new FrameDesc(nModInFrame,nFrameID);

					for(int k=0;k<nModInFrame;k++)
					{
						for(int l=0;l<5;l++)
						{   // 5 = n column table frame desc in xedithor
							m_frames[j].m_modules[k][l] = a32Sprite[++i];
						}
					}
				}
				i++;
			}
			if(a32Sprite[i] == 0xEEEA0EFF){  // ANIMATION
				int nAnim = a32Sprite[++i];		
				m_anims = new AnimDesc[nAnim];
				for(int j=0;j<nAnim;j++)
				{
					System.out.print("--  AnimID       :"+a32Sprite[++i]);
					int nFrameAnim  = a32Sprite[++i];					
					m_anims[j] = new AnimDesc(nFrameAnim);
					for(int k=0;k<nFrameAnim;k++)
					{
						for(int l=0;l<5;l++)
						{   // 5 = n column table anim desc in xedithor
							m_anims[j].m_frames[k][l] = a32Sprite[++i];
						}
					}
				}
				i++;				
			}
			i++;
		}
		
		// create img modules
		System.out.print("-----------------------------------------");
		m_imgModules = new TextureRegion[m_modules.length];
		for(int j=0;j<m_modules.length;j++)
		{
			m_imgModules[j] = new TextureRegion(m_texture, m_modules[j][1], m_modules[j][2], m_modules[j][3], m_modules[j][4]);
		}		
	}
	
	private int[] getModule(int id){

		for(int j=0;j<m_modules.length;j++)
		{
			if(id==m_modules[j][0]){
				return m_modules[j];
			}
		}
		return null; 
	}
	
	private TextureRegion getTextureModule(int id){

		for(int j=0;j<m_modules.length;j++)
		{
			if(id==m_modules[j][0]){
				return m_imgModules[j];
			}
		}
		return null; 
	}
	
	private void paintModule(int index){
		int[] module = getModule(index);
		TextureRegion tr = getTextureModule(index);
		m_batcher.draw(tr, m_animPosX,m_animPosY, module[3], module[4]);//module[1], module[2]
	}
	
	public void paintFrame(int index)
	{
		FrameDesc frame= m_frames[index];
		for(int i=0;i<frame.m_moduleCount;i++){
			int idMod= frame.m_modules[i][0];
			paintModule(idMod);
		}
	}
	
	private void paintFrameID(int frmID){
		int index=0;
		for(int j=0;j<m_frames.length;j++)
		{
			if(frmID==m_frames[j].m_frameID){
				index=j;
				break;
			}
		}
		paintFrame(index);
	}
	
	public void setAnim(int index)
	{
		m_animPlayed = index;
	}
	
	public void setPos(int posx,int posy){
		m_animPosX = posx;
		m_animPosY = posy;
	}
	
	public void render()
	{		
		m_batcher.begin();
		AnimDesc anim= m_anims[m_animPlayed];
		paintFrameID(anim.m_frames[m_currentFrame][0]);
		
       if(m_limiter%10 == 0){
	        if(m_currentFrame<anim.m_frameCount-1)
	        	m_currentFrame=m_currentFrame+1;
	        else
	        	m_currentFrame=0;
        }
        m_limiter++;

		//m_texture
        m_batcher.end();
		
	}
}
