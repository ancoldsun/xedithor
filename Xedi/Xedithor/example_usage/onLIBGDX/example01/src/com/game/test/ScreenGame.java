 // Edi Ermawan  < edi.ermawan@gmail.com >

package com.game.test;

import com.badlogic.gdx.Application;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.xdr.lib.*;

public class ScreenGame implements ScreenBase {

	private SpriteBatch m_spriteBatch;
	
    private XDRSprite m_soldierSprite;
    private XDRSprite m_bgSprite;
    
    private XDRAnimationObject m_anim01;
    private XDRAnimationObject m_anim02;
    
    private boolean m_isStateDone=false;

	public ScreenGame(Application app) {

		m_spriteBatch    = new SpriteBatch();
		// create n load soldier sprite
		m_soldierSprite = new XDRSprite();
		m_soldierSprite.setSptiteBatch(m_spriteBatch);
		m_soldierSprite.loadData(DATA_SPRITE.SPR_SOLDIER);
		// create n load bg sprite	
		m_bgSprite = new XDRSprite();
		m_bgSprite.setSptiteBatch(m_spriteBatch);
		m_bgSprite.loadData(DATA_SPRITE.SPR_BGMAIN);
		
		// animation 01 from soldier sprite
		m_anim01 = new XDRAnimationObject(m_soldierSprite,0,0);
		// note : 0,0 is on left-below screen here
		m_anim01.setPosX(450);
		m_anim01.setPosY(120);
		m_anim01.setPaintFrameWhenAnimFinish(false);
		// loop forever
		m_anim01.setAnimLoop(-1);
		m_anim01.setAnimIndex(SPRITE_SOLDIER.TROWGRANAT_1);
		
		// animation 02 from soldier sprite
		m_anim02 = new XDRAnimationObject(m_soldierSprite,0,0);
		// note : 0,0 is on left-below screen here
		m_anim02.setPosX(250);  
		m_anim02.setPosY(120);
		m_anim02.setPaintFrameWhenAnimFinish(false);
		// loop forever
		m_anim02.setAnimLoop(-1);
		m_anim02.setAnimIndex(SPRITE_SOLDIER.BOMBER_0);
	}

	//@Override
	public void update(Application app) {
		// animation update
		m_anim01.update();
		m_anim02.update();
	}

	//@Override
	public void render(Application app) {
		// clear screen
        Gdx.gl.glClear(GL10.GL_COLOR_BUFFER_BIT);
        // fill screen with white color
        Gdx.gl.glClearColor(255, 255, 255, 255);    
		// paint frame via sprite
		m_bgSprite.paintFrame(SPRITE_BGMAIN.FRM_BG_0, 0, 0);
		// render animation 1
		m_anim01.render();
		// render animation 2
		m_anim02.render();
						
	}

	//@Override
	public boolean isDone() {
		return m_isStateDone;
	}

	//@Override
	public void dispose() {
		m_spriteBatch.dispose();
		m_soldierSprite.dispose();
		m_bgSprite.dispose();
	}
	
	public int getNextState() {
		return 1;
	}

}
