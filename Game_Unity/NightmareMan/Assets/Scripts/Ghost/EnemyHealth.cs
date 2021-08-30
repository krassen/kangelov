using UnityEngine;
using System.Collections;

public class EnemyHealth : MonoBehaviour {

	Animator anim;
	GhostMovement movement;
	SphereCollider sphereCollider;

	void Awake() {
		anim = GetComponent<Animator> ();
		movement = GetComponent<GhostMovement> ();
		sphereCollider = GetComponent<SphereCollider> ();
	}

	public void TakeDamage() {
		anim.SetTrigger ("Dead");
		tag = "EnemyDead";
		movement.DisableMovement ();
		sphereCollider.enabled = false;
		Invoke ("Respawn", 2f);
	}

	void Respawn() {
		SpawnEnemyManager.Instance.Respawn (gameObject);
		sphereCollider.enabled = true;
		anim.SetTrigger ("Revive");
		tag = "Enemy";
		movement.EnableMovement ();
	}

}