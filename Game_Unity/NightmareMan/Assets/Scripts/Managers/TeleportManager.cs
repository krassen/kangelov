using UnityEngine;
using System.Collections;

public class TeleportManager : SingletonManager<TeleportManager> {

	/* Animated teleport vars */
	public GameObject blackHole;
	public float distFromFieldY = 10;
	public const float blackHoleTimeSpan = 2f;


	bool teleportingPlayer = false;
	enum Directions { UP, DOWN}
	Directions directionTeleporting; 
	Vector3 destinationPosition;

	GameObject [] teleportPoints;
	GameObject player;
		
	void Start() {
		teleportPoints = GameObject.FindGameObjectsWithTag ("TeleportPoint");
	}

	public void TeleportObject(GameObject player) 
	{
		player.transform.position = RandomTeleportPoint().position;
	}

	void Update() {
		if (!teleportingPlayer)
			return;

		if (directionTeleporting == Directions.UP) {
			MoveUp();
		} else {
			MoveDown();
		}
	}

	void MoveUp() {
		Vector3 playerPosition = player.transform.position;

		playerPosition.y += distFromFieldY * Time.deltaTime;
		player.transform.position = playerPosition;

		if (player.transform.position.y >= distFromFieldY) {
			directionTeleporting = Directions.DOWN;
			destinationPosition.y = distFromFieldY;
			player.transform.position = destinationPosition;
		}
	}

	void MoveDown() {
		Vector3 playerPosition = player.transform.position;

		playerPosition.y -= distFromFieldY * Time.deltaTime;
		player.transform.position = playerPosition;

		if (player.transform.position.y <= 0) {
			playerPosition.y = 0;
			player.transform.position = playerPosition;

			teleportingPlayer = false;

			directionTeleporting = Directions.DOWN;

			PlayerMovementManager.Instance.enableWalking = true;
		}
	}

	public void EffectTeleportObject(GameObject player) {
		if (teleportingPlayer)
			return;

		this.player = player;

		Vector3 destinationTeleport = RandomTeleportPoint ().position;
		Vector3 distFromField = new Vector3 (0, distFromFieldY, 0);

		GameObject blackH1 = Instantiate (blackHole, player.transform.position + distFromField, Quaternion.identity) as GameObject;
		GameObject blackH2 = Instantiate (blackHole, destinationTeleport + distFromField, Quaternion.identity) as GameObject;

		directionTeleporting = Directions.UP;
		teleportingPlayer = true;

		Destroy (blackH1, blackHoleTimeSpan);
		Destroy (blackH2, blackHoleTimeSpan);

		destinationPosition = destinationTeleport;

		PlayerMovementManager.Instance.enableWalking = false;
	}

	public Transform RandomTeleportPoint() {
		int index = Random.Range (0, teleportPoints.Length);
		return teleportPoints [index].transform;
	}

}
