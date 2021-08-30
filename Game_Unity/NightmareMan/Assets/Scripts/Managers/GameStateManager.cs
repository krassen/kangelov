using UnityEngine;
using System.Collections;

public class GameStateManager : SingletonManager<GameStateManager> {

	public enum States { Pause, Start, Resume, Win, Lose }
	public States gameState;
	public float resumeTimeSeconds = 1f;

	void Awake() {
		InitGameData ();
	}

	void FixedUpdate() {
		if (AllFoodCollected ())
			gameState = States.Win;
	}

	void Update() {
		if (!Input.GetKeyDown ("escape") || IsGameAtResume())
			return;

		if (IsGamePaused ()) {
			StartGame();
		} else {
			gameState = States.Pause;
		}
	}

	public void StartGame() {
		gameState = States.Resume;
		Invoke ("ResumeGame", resumeTimeSeconds);
	}

	void ResumeGame() {
		gameState = States.Start;
	}

	void InitGameData() {
		gameState = States.Start;
		SpawnPlayerManager.Instance.SpawnPlayer ();
	}

	public bool AllFoodCollected() {
		return GameObject.FindWithTag ("FoodPoint") == null;
	}

	public bool IsGameOver() {
		return gameState == States.Win || gameState == States.Lose;
	}

	public bool IsGamePaused() {
		return gameState == States.Pause;
	}

	public bool IsGameAtResume() {
		return gameState == States.Resume;
	}
}
