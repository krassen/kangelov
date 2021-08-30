using UnityEngine;
using System.Collections;

public class DotPlayerCollusion : MonoBehaviour {

	void OnTriggerEnter(Collider other) {
		if (other.tag == "Player") {
			GameScoreManager.Instance.EatFoodDot();			
			Destroy(gameObject);
		}
	}
}
