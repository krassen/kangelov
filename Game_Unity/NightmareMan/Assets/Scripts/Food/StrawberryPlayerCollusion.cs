using UnityEngine;
using System.Collections;

public class StrawberryPlayerCollusion : MonoBehaviour {
	
	void OnTriggerEnter(Collider other) {
		if (other.tag == "Player") {
			GameScoreManager.Instance.EatFoodStrawberry();			
			Destroy(gameObject);
		}
	}
}
