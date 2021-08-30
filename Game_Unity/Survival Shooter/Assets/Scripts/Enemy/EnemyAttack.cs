using UnityEngine;
using System.Collections;

public class EnemyAttack : MonoBehaviour
{
    public float timeBetweenAttacks = 0.5f;
    public int attackDamage = 10;

    Animator anim;
    GameObject player;
    PlayerHealth playerHealth;
    EnemyHealth enemyHealth;
    bool playerInRange;
    float timer;


    void Awake ()
    {
        enemyHealth = GetComponent<EnemyHealth>();
        anim = GetComponent <Animator> ();
    }


    void OnTriggerEnter (Collider other)
    {
		if(other.gameObject.tag == "Player")
        {
			player = other.gameObject;
			playerHealth = player.GetComponent <PlayerHealth> ();
			playerInRange = true;
        }
    }


    void OnTriggerExit (Collider other)
    {
		if(other.gameObject == player)
        {
            playerInRange = false;
        }
    }

    void Update ()
    {
        timer += Time.deltaTime;

        if(timer >= timeBetweenAttacks && playerInRange && enemyHealth.currentHealth > 0)
        {
            Attack ();
        }

        if(GameManager.IsGameOver())
        {
            anim.SetTrigger ("PlayerDead");
        }
    }


    void Attack ()
    {
        timer = 0f;

        if (playerHealth.currentHealth > 0) {
			playerHealth.TakeDamage (attackDamage);
		} else {
			playerInRange = false;
		}
    }
}
