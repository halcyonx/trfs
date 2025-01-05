package com.timewalk.breakout;

import org.libsdl.app.SDLActivity;

/**
 * A sample wrapper class that just calls SDLActivity
 */

public class GameActivity extends SDLActivity {
	@Override
	protected String[] getLibraries() {
		return new String[] {
				"SDL2",
				"sandbox"
		};
	}
}
