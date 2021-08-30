using UnityEngine;
using System.Collections;
using System.Collections.Generic;

[System.Serializable]
public class PlayerScore {

	public int playerScore { get; set; }
	public string playerName { get; set; }

	public PlayerScore(string name, int score) {
		playerName  = name;
		playerScore = score;
	}

}
