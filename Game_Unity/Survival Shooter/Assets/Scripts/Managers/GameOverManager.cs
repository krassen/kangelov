using UnityEngine;

public class GameOverManager : MonoBehaviour
{
    public PlayerHealth playerHealth;


    Animator anim;


    void Awake()
    {
        anim = GetComponent<Animator>();
    }


    void Update()
    {
        if (GameManager.IsGameOver())
        {
            anim.SetTrigger("GameOver");
        }
    }

	public void PlayAgain(){
		Application.LoadLevel ("main_scene");
	}

	public void QuitToMainMenu() {
		Application.LoadLevel ("menu");
	}
}
