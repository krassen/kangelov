using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class EnemyMovementManager : SingletonManager<EnemyMovementManager> {

	public GameObject [] chasePoints;
	public enum MovementStates { Chase, Scatter, Frightened };
	public MovementStates enemyState  = MovementStates.Chase;
	public float scatterModeDuration  = 20;
	public float chaseModeDuration    = 7;
	public float frightenModeDuration = 5;

	public Text displayMode;
	MovementStates oldEnemyState;

	/* Frigthen mode help values */
	int frigthenModeInProgress = 0;
	MovementStates saveLastState;

	float timer = 0;

	void Awake() {
		chasePoints = GameObject.FindGameObjectsWithTag ("EnemyMovementPoint");
	}

	void Update() {
		DisplayMode ();
	}

	void DisplayMode() {
		if (oldEnemyState != enemyState) {
			displayMode.text = "Mode : " + enemyState;
			oldEnemyState = enemyState;
		}
	}

	void FixedUpdate() {
		if (GameStateManager.Instance.IsGamePaused())
			return;

		if (FrigthenModeActive() || !timerEnded())
			return;

		switch (enemyState) {
		case MovementStates.Chase:
			enemyState = MovementStates.Scatter;
			timer = scatterModeDuration;
			break;
		case MovementStates.Scatter:
			enemyState = MovementStates.Chase;
			timer = chaseModeDuration;
			break;
		}
	}

	bool timerEnded () {
		return (timer -= Time.deltaTime) < 0;
	}

	public void StartFrigthenMode() {
		StartCoroutine("FrigthenMode");
	}

	public bool FrigthenModeActive() {
		return enemyState == MovementStates.Frightened;
	}

	// complicated function
	IEnumerator FrigthenMode() {
		if (frigthenModeInProgress++ == 0) {
			saveLastState = enemyState;
			enemyState = MovementStates.Frightened;
		}

		yield return new WaitForSeconds (frightenModeDuration);

		if (--frigthenModeInProgress == 0) {
			enemyState = saveLastState;
		}
	}

	public Transform RandomChasePoint() {
		int index = Random.Range (0, chasePoints.Length);
		return chasePoints [index].transform;
	}

	public Transform FindConditionPath(Transform currentPosition, GameObject target, bool shortest = true) {
		Transform shortestPath = null;
		float shortestDistance = shortest ? Mathf.Infinity : 0;
		foreach(GameObject chasePoint in chasePoints) {
			if(chasePoint.transform == currentPosition) 
				continue;

			float currentIterationDist = Vector3.Distance(chasePoint.transform.position, target.transform.position);
			if((shortestDistance > currentIterationDist) == shortest) {
				shortestPath = chasePoint.transform;
				shortestDistance = currentIterationDist;
			}
		}

		return shortestPath;
	}

}
