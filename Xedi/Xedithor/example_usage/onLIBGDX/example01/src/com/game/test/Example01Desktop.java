 // Edi Ermawan  < edi.ermawan@gmail.com >
package com.game.test;

import com.badlogic.gdx.backends.jogl.JoglApplication;

public class Example01Desktop {
	public static void main (String[] argv) {
		new JoglApplication( new Example01App(), "Example01AppDesktop 800x480 ",800,400, false);
	}
}


