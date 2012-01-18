package com.xeditest.xedidraw;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import javax.imageio.ImageIO;
import javax.imageio.stream.ImageOutputStream;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Pixmap.Blending;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;


public class GameScreen extends BaseScreen {
	private SpriteBatch m_spriteBatch;
	private Texture m_texture; //texture as image container
    private Sprite m_sprite; 
    private XorSprite m_testXorSprite;
	public GameScreen(XediDraw xedidraw) {
		super(xedidraw);

		// TODO Auto-generated constructor stub

		//test read sprite pack
		PackReader dataPack = new PackReader("assets/soldier.bin");
		BufferedImage img;
		byte[] bytesSprite=null;
		try {
			dataPack.ReadSprite();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		//byte[] bytesPNG=null;
		byte[] bytesPNG = dataPack.getSpriteBytes();
		int[] sprDesc = dataPack.getSprIntDesc();

		m_spriteBatch = new SpriteBatch();

		//System.out.println("length: "+bytesPNG.length);
		Pixmap pxmap= new Pixmap(bytesPNG,0,bytesPNG.length);
		
		m_texture = new Texture(pxmap);//Gdx.files.internal("assets/xedithor.png"));//take image from asset folder
		
		
		m_testXorSprite = new XorSprite();
		m_testXorSprite.setData(m_spriteBatch,m_texture,sprDesc);
		
		//m_texture = new Texture(Gdx.files.internal("assets/spriteA.bin"));//take image from asset folder
		System.out.println("h: "+ m_texture.getHeight());
		System.out.println("w: "+ m_texture.getWidth());

		m_sprite = new Sprite(m_texture, 0, 0, m_texture.getWidth(), m_texture.getHeight());
		m_sprite.setPosition(100, 100);
	}
    public void render(float delta) {
        //super.render(delta);
        Gdx.gl.glClear(GL10.GL_COLOR_BUFFER_BIT);   //clear screen
        Gdx.gl.glClearColor(255, 255, 255, 255);    //fill screen with white color
 
        //batch drawing must began with batch.begin() and ended with batch.end()
        //m_spriteBatch.disableBlending();
       // m_spriteBatch.begin();
       // m_sprite.draw(m_spriteBatch);        //sprite has draw function inside
        //m_spriteBatch.end();
        m_testXorSprite.setPos(100, 100);
        m_testXorSprite.setAnim(1);
        m_testXorSprite.render();
    }
	
	
}
