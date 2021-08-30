using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PlayerHealth : MonoBehaviour
{
    public int startingHealth = 100;
    public int currentHealth;
    public AudioClip secondClip;
    public float flashSpeed = 5f;
    public Color flashColour = new Color(1f, 0f, 0f, 0.1f);
	public RectTransform healthBarGUI;

	Image damageImage;
	Slider healthSlider;
	Animator anim;
    AudioSource playerAudio;
    PlayerMovement playerMovement;
    PlayerShooting playerShooting;
    bool isDead;
	bool damaged = false;
	CapsuleCollider capsuleCollider;
	SphereCollider sphereCollider;

    void Awake ()
    {
		damageImage = GameObject.FindGameObjectWithTag("DamageImage").GetComponent<Image> ();
		healthSlider = CreateHealthBar ();
		anim = GetComponent <Animator> ();
        playerAudio = GetComponent <AudioSource> ();
        playerMovement = GetComponent <PlayerMovement> ();
        playerShooting = GetComponentInChildren <PlayerShooting> ();
		capsuleCollider = GetComponent <CapsuleCollider> ();
		sphereCollider = GetComponent<SphereCollider> ();
        currentHealth = startingHealth;
    }

	Slider CreateHealthBar() {
		GameObject playerCanvas = GameObject.FindGameObjectWithTag ("CanvasPlayerGUI");
		int players = playerCanvas.GetComponentsInChildren<Slider>().Length;
		GameObject tempObject = Instantiate (healthBarGUI.gameObject, new Vector3(0, players*50, 0),  Quaternion.identity) as GameObject;
		tempObject.transform.SetParent (playerCanvas.transform, false);
		tempObject.transform.SetAsFirstSibling ();
		return tempObject.GetComponentInChildren<Slider> ();
	}

    void Update ()
    {
        if(damaged)
        {
            damageImage.color = flashColour;
        }
        else
        {
            damageImage.color = Color.Lerp (damageImage.color, Color.clear, flashSpeed * Time.deltaTime);
        }
        damaged = false;
    }


    public void TakeDamage (int amount)
    {
        damaged = true;

        currentHealth -= amount;

        healthSlider.value = currentHealth;

        playerAudio.Play ();

        if(currentHealth <= 0 && !isDead)
        {
            Death ();
        }
    }

	void OnTriggerEnter (Collider other)
	{
		if (other.gameObject.tag == "Player") {
			anim.SetTrigger("Revive");
		}
	}

	void Revive() {
		isDead = false;
		playerShooting.EnableEffects ();
		gameObject.tag = "Player";
		Functions.SwapAudioSource(ref secondClip, ref playerAudio);
		playerAudio.Play ();
		playerMovement.enabled = true;
		playerShooting.enabled = true;
		capsuleCollider.enabled = true;
		currentHealth = startingHealth;
		healthSlider.value = currentHealth; 
		sphereCollider.enabled = false;
	}

	void Death ()
    {
        isDead = true;
		playerMovement.enabled = false;
        playerShooting.DisableEffects ();

        anim.SetTrigger ("Die");
		Functions.SwapAudioSource(ref secondClip, ref playerAudio);
		playerAudio.Play ();
        playerShooting.enabled = false;
		capsuleCollider.enabled = false;
		gameObject.tag = "DeathPlayer";
		sphereCollider.enabled = true;
	}

    public void RestartLevel ()
    {
        Application.LoadLevel (Application.loadedLevel);
    }
}
