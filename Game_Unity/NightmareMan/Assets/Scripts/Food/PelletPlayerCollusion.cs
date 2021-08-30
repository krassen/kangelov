using UnityEngine;
using System.Collections;

public class PelletPlayerCollusion : MonoBehaviour {
	
	void OnTriggerEnter(Collider other) {
		if (other.tag == "Player") {
			GameScoreManager.Instance.EatFoodPellet();
			EnemyMovementManager.Instance.StartFrigthenMode();
			Destroy(gameObject);
		}
	}
}
