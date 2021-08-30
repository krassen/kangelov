using UnityEngine;
using System.Collections;

public class CameraFollow : MonoBehaviour {
	public Transform player;
	public float smooth = 5f;

	Camera mainCamera;
	GameObject [] players;
	Vector3 derp;

	void Start () {
		mainCamera = GetComponent<Camera> ();
		derp = player.position - transform.position;
		players = GameObject.FindGameObjectsWithTag ("Player");
	}

	void FixedUpdate() {
		MoveCamera ();
	}

	void MoveCamera() {
		Vector3 vector = Vector3.zero;
		foreach(GameObject playerObject in players) {
			vector += playerObject.transform.position;
		}
		vector /= players.Length;
		float dist = System.Math.Max(5, Vector3.Distance(vector, players[0].transform.position));
		Vector3 newPosition = vector - derp;
		mainCamera.orthographicSize = dist;
		transform.position = Vector3.Lerp (transform.position, newPosition, smooth * Time.deltaTime);
	}
}
