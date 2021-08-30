using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class Ranking : MonoBehaviour {

	public GameObject rankingCanvas;
	public GameObject textPrefab;
	public GameObject rankingPanel;
	public int startingTextY = -10;

	public const int VerticalSpaceBetweenText = 40;
	public const int MaxResultsShown  = 10;

	bool scoreLoaded = false;
	Vector3 currentTextPosition;	

	public void ShowRanking() {
		rankingCanvas.SetActive (true);

		if (!scoreLoaded) {
			LoadScore ();
			scoreLoaded = true;
		}
	}

	public void HideRanking() {
		rankingCanvas.SetActive(false);
	}

	public void LoadScore(){
		List<PlayerScore> data = (List<PlayerScore>) LoadSaveDataList.LoadData<PlayerScore> ("playerRanking.infos");
		data.Sort ((PlayerScore first, PlayerScore second) => second.playerScore.CompareTo(first.playerScore));
		int i = 0;
		currentTextPosition = new Vector3 (0, startingTextY, 0);
		foreach (PlayerScore score in data) {
			if(i++ >= MaxResultsShown)
				break;
			AddText (score.playerName + " : " + score.playerScore);
		}
	}

	void AddText(string text) {
		GameObject textUI = Instantiate (textPrefab, currentTextPosition, textPrefab.transform.rotation) as GameObject;
		currentTextPosition.y -= VerticalSpaceBetweenText;
		textUI.transform.SetParent(rankingPanel.transform, false);
		textUI.GetComponent<Text>().text = text;
	}
}
