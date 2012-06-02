package com.game.test;

import com.badlogic.gdx.Application;
import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Gdx;

public class Example01App implements ApplicationListener {
	/** flag indicating whether we were initialized already **/
	private boolean isInitialized =false;

	/** the current screen **/
	private ScreenBase m_screenState;
	long lastRender = System.nanoTime();

	//@Override
	public void dispose () {

	}

	//@Override
	public void render () {
		Application app = Gdx.app;
		// update the screen
		m_screenState.update(app);
		// render the screen
		m_screenState.render(app);
		
		// fps limiter		
		long now = System.nanoTime();		
		if (now - lastRender < 20000000) { // 30 ms, ~33FPS
			try {
				Thread.sleep(30 - (now - lastRender) / 1000000);
			} catch (InterruptedException e) {
			}
		}
		lastRender = now;
	}

	//@Override
	public void resize (int width, int height) {

	}

	//@Override
	public void create () {		
		if (!isInitialized) {
			m_screenState = new ScreenGame(Gdx.app);
			isInitialized = true;
		}
	}

	//@Override
	public void pause () {
		System.out.println("pause");
	}

	//@Override
	public void resume () {
		System.out.println("resume");
	}
}
