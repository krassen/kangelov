using UnityEngine;
using System.Collections;

public class ScrollEventCamera : MonoBehaviour {

	public int minZoom = 4;
	public int maxZoom = 15;

	Camera mainCamera;

	void Awake () {
		mainCamera = GetComponent<Camera> (); 
	}

	void FixedUpdate () {
		if (Input.GetAxis("Mouse ScrollWheel") < 0 && mainCamera.orthographicSize <= maxZoom) {
			mainCamera.orthographicSize++;
		} else if (Input.GetAxis("Mouse ScrollWheel") > 0 && mainCamera.orthographicSize >= minZoom) {
			mainCamera.orthographicSize--;
		}
	}
}
