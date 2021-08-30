using UnityEngine;
using System.Collections;

public class PlayerSpawnManager : MonoBehaviour {

	public GameObject SecondPlayer;

	void Awake () {
		switch (CurrentSettings.players) {
		case 2:
			Instantiate(SecondPlayer);
			break;
		}
	}
}
