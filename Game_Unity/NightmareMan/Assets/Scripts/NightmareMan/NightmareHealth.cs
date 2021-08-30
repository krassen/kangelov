using UnityEngine;
using System.Collections;

public class NightmareHealth : MonoBehaviour {
	NightmareManMovement nightmareManMovement;
	Animator nightmareManAnim;
	CapsuleCollider nightmareManCapsule;

	void Awake() {
		nightmareManMovement = GetComponent<NightmareManMovement> ();
		nightmareManAnim 	 = GetComponent<Animator> ();
		nightmareManCapsule  = GetComponent<CapsuleCollider> ();
	}

	public void TakeDamage() {
		GameLiveManager.Instance.TakeLive();

		if (GameLiveManager.Instance.PlayerDead()) { 
			nightmareManAnim.SetTrigger ("Die");
			GameStateManager.Instance.gameState = GameStateManager.States.Lose;

			nightmareManMovement.enabled = false;
			nightmareManCapsule.enabled = false;

			gameObject.tag = "PlayerDead";
		} else {
			SpawnPlayerManager.Instance.Respawn(gameObject);
		}
	}
}
