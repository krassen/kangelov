using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PauseMenuManager : MonoBehaviour {

	Canvas canvas;

	void Start () {
		canvas = GetComponent<Canvas> ();
		ResumeGame ();
	}
	
	void Update () {
		if (!Input.GetKeyDown ("escape"))
			return;

		if (canvas.enabled) {
			ResumeGame();
		} else {
			PauseGame();
		}
	}

	public void ResumeGame() {
		canvas.enabled = false;
		Time.timeScale = 1f;
	}

	public void PauseGame() {
		canvas.enabled = true;
		Time.timeScale = 0f;
	}

	public void QuitGame() {
		Application.Quit ();
	}

	public void QuitToMainMenu() {
		Application.LoadLevel ("menu");
	}
}
