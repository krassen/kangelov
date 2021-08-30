using UnityEngine;
using System.Collections;

public class SpawnPlayerManager : SingletonManager<SpawnPlayerManager> {

	public GameObject player;
	Transform spawnPoint;

	void Awake() {
		spawnPoint = GameObject.FindGameObjectWithTag ("SpawnPlayerPoint").transform;
	}

	public void SpawnPlayer() {
		Instantiate (player, spawnPoint.position, player.transform.rotation);
	}

	public void Respawn(GameObject player) {
		player.transform.position = spawnPoint.position;
	}
	
}
