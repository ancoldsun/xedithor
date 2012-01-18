package com.xeditest.xedidraw;

import com.badlogic.gdx.Game;

public class XediDraw extends Game {
	@Override
	public void create() {
		setScreen(new GameScreen(this));
	}
}
