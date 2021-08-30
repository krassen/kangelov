using UnityEngine;
using System.Collections;

public class PauseMenu : MonoBehaviour {
	bool pauseMenuEnabled = false;

	void FixedUpdate() {
		if (GameStateManager.Instance.IsGamePaused() && !pauseMenuEnabled) {
			DisplayChildren(true);
		} else if (GameStateManager.Instance.IsGameAtResume () && pauseMenuEnabled) {
			DisplayChildren(false);
		}
	}

	void DisplayChildren(bool display) {
		pauseMenuEnabled = display;
		for(int i = 0; i < transform.childCount; i++)
			transform.GetChild(i).gameObject.SetActive(display);
	}

	public void QuitToMainMenu() {
		Application.LoadLevel ("Main menu");
	}

	public void ResumeGame() {
		GameStateManager.Instance.StartGame ();
	}
}
