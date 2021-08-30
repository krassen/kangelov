using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class SpawnEnemyManager : SingletonManager<SpawnEnemyManager> {

	public List<GameObject> enemy;
	public int spawnIntervalSeconds = 4;
	Transform spawnPoint;

	void Awake() {
		spawnPoint = GameObject.FindGameObjectWithTag ("SpawnEnemyPoint").transform;
		for(int i = 0; i < 4/*enemy.Count*/; i++)
			StartCoroutine( InvokeSpawnEnemy(enemy[i], spawnIntervalSeconds*i) );
	}

	IEnumerator InvokeSpawnEnemy(GameObject enemyPrefab, int waitTime) {
		yield return new WaitForSeconds(waitTime);
		SpawnEnemy (enemyPrefab);
	}

	public void SpawnEnemy(GameObject enemyPrefab) { 
		Instantiate (enemyPrefab, spawnPoint.position, enemyPrefab.transform.rotation);
	}

	public void Respawn(GameObject enemy) {
		enemy.transform.position = spawnPoint.position;
	}
}
