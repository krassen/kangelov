using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GameLiveManager : SingletonManager<GameLiveManager> {

	public int lives = 2;
	public Text displayScore;

	int oldLives;

	void Update() {
		if (oldLives != lives) {
			displayScore.text = "Lives : " + lives;
			oldLives = lives;
		}
	}

	public void TakeLive() {
		lives -= 1;
	}

	public bool PlayerDead() {
		return lives == 0;
	}
}
