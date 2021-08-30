using UnityEngine;
using System.Collections;

public class CherryPlayerCollusion : MonoBehaviour {
	
	void OnTriggerEnter(Collider other) {
		if (other.tag == "Player") {
			GameScoreManager.Instance.EatFoodCherry();			
			Destroy(gameObject);
		}
	}
}
