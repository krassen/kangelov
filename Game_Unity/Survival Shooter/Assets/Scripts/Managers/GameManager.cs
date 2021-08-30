using UnityEngine;

public class GameManager {
	public static bool IsGameOver() {
		return GameObject.FindGameObjectWithTag ("Player") == null;
	}
}
