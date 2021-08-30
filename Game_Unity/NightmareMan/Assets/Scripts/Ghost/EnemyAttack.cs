using UnityEngine;
using System.Collections;

public class EnemyAttack : MonoBehaviour {

	void OnTriggerEnter (Collider other) {
		if(!EnemyMovementManager.Instance.FrigthenModeActive() && other.gameObject.tag == "Player")	{
			other.gameObject.GetComponent<NightmareHealth>().TakeDamage();
		}
	}
}
