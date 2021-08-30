using UnityEngine;
using System.Collections;

public class EnemyMovement : MonoBehaviour
{
   	Transform player;
    PlayerHealth playerHealth;
    EnemyHealth enemyHealth;
    NavMeshAgent nav;

    void Awake ()
    {
        enemyHealth = GetComponent <EnemyHealth> ();
        nav = GetComponent <NavMeshAgent> ();
    }

    void Update ()
    {
		if (GameManager.IsGameOver () || enemyHealth.currentHealth <= 0) 
		{
			nav.enabled = false;
		} 
		else if (playerHealth == null || playerHealth.currentHealth <= 0) 
		{
			FindTarget();
		}
		else
        {
			nav.SetDestination (player.position);
        }
    }

	void FindTarget() {
		GameObject [] players = GameObject.FindGameObjectsWithTag ("Player");
		if (players == null)
			return;

		float minDist = Mathf.Infinity;
		foreach(GameObject currPlayer in players) {
			float dist = Vector3.Distance(transform.position, currPlayer.transform.position);
			if(dist < minDist) {
				minDist = dist;
				player = currPlayer.transform;
			}
		}
		playerHealth = player.GetComponent <PlayerHealth> ();
	}
}

