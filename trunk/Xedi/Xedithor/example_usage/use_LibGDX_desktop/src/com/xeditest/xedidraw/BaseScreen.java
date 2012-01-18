package com.xeditest.xedidraw;

import com.badlogic.gdx.Screen;



public class BaseScreen implements Screen {
 
	XediDraw m_xedidrawgame;
	
	public BaseScreen(XediDraw xedidraw) {
	    this.m_xedidrawgame = xedidraw;
	}
	@Override
    public void dispose() {
    }
    @Override
    public void hide() {
    }
    @Override
    public void pause() {
    }
    @Override
    public void render(float delta) {
    }
    @Override
    public void resize(int width, int height) {
    }
    @Override
    public void resume() {
    }
    @Override
    public void show() {
    }
}