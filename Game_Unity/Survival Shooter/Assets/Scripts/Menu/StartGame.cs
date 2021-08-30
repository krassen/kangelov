using UnityEngine;
using System.Collections;

public class StartGame : MonoBehaviour {

	public void StartGameWithPlayers(int players) {
		CurrentSettings.players = players;
		Application.LoadLevel ("main_scene");
	}
}
