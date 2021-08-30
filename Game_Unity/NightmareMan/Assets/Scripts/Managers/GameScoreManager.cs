using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GameScoreManager : SingletonManager<GameScoreManager> {

	public int score = 0;
	public Text displayScoreText;
	public int dotReward = 10;
	public int pelletReward = 50;
	public int cherryReward = 100;
	public int strawberryReward = 300;
	public int ghostReward = 200;

	int oldScore = 0;

	void Update ()
	{
		if (score != oldScore) {
			displayScoreText.text = "Score : " + score;
			oldScore = score;
		}
	}

	public void EatFoodDot() {
		score += dotReward;
	}

	public void EatFoodPellet() {
		score += pelletReward;
	}

	public void EatFoodCherry() {
		score += cherryReward;
	}

	public void EatFoodStrawberry() {
		score += strawberryReward;
	}

	public void EatGhost() {
		int zombiesDead = GameObject.FindGameObjectsWithTag("EnemyDead").Length - 1;
		score += ghostReward * (1 << zombiesDead);
	}

}