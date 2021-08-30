using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class WinLoseCanvas : MonoBehaviour {

	public Text scoreText;
	Animator anim;

	void Start() {
		anim = GetComponent<Animator> ();
	}

	void Update(){
		if (GameStateManager.Instance.IsGameOver()) {
			scoreText.text = "Score : " + GameScoreManager.Instance.score;
		}

		if(GameStateManager.Instance.gameState == GameStateManager.States.Lose) {
			anim.SetTrigger("GameOver");
		}

		if(GameStateManager.Instance.gameState == GameStateManager.States.Win) {
			anim.SetTrigger("YouWin");
		}
	}
}
