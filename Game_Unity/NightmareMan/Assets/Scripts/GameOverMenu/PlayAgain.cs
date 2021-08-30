using UnityEngine;
using System.Collections;

public class PlayAgain : MonoBehaviour {
	public void PlayAgainLevel(){
		Application.LoadLevel (Application.loadedLevelName);
	}
}
