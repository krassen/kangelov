using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ScoreManager : MonoBehaviour
{
    public static int score;
	static int oldScore = 0;


    Text text;


    void Awake ()
    {
        text = GetComponent <Text> ();
        score = 0;
    }


    void Update ()
    {
		if (score != oldScore) {
			text.text = "Score : " + score;
			oldScore = score;
		}
    }
}
