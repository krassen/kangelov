using UnityEngine;
using System.Collections;

public class PlayerMovementManager : SingletonManager<PlayerMovementManager> {

	public bool enableWalking = true;

	public bool CanPlayerMove() {
		return !(
			GameStateManager.Instance.IsGameOver () ||
			GameStateManager.Instance.IsGamePaused () ||
			GameStateManager.Instance.IsGameAtResume () || 
			!enableWalking
		);
	}

}
