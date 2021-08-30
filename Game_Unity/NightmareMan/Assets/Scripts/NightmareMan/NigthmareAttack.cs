using UnityEngine;
using System.Collections;

public class NigthmareAttack : MonoBehaviour {

	void OnTriggerEnter(Collider other) {
		if (EnemyMovementManager.Instance.FrigthenModeActive () && other.tag == "Enemy") {
			other.gameObject.GetComponent<EnemyHealth>().TakeDamage();
			GameScoreManager.Instance.EatGhost();
		}
	}

}
