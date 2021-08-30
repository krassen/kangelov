using UnityEngine;
using System.Collections;

public class LevelConstructorManager : SingletonManager<LevelConstructorManager> {

	public TextAsset  fileLevel;
	public GameObject field; 
	public GameObject wall;
	public GameObject environment;
	public GameObject spawnEnemyPoint;
	public GameObject spawnPlayerPoint;
	public GameObject enemyScatterPoint;
	public GameObject teleportEnter;
	public GameObject teleportExit;
	public GameObject enemyFollowDots;
	public GameObject foodDot;
	public GameObject foodPellet;
	public GameObject foodCherry;
	public GameObject foodStrawberry;
	public GameObject enemyBaseDoor;
	public char wallFlag = '1';
	
	void Awake() {
		char[,] bitmap = ParseFunctions.ParseLevelTextAsset(fileLevel);
		NavigationManager.Instance.SetMap (bitmap, wallFlag);
		GenerateMap (bitmap);
	}

	void GenerateMap(char [,] bitmap){
		int rows = bitmap.GetLength (0);
		int cols = bitmap.GetLength (1);
		
		float cubeSize = wall.transform.localScale.y;
		
		GameObject generatedEnvironment = Instantiate (environment);
		GameObject generatedField = Instantiate (field);

		SetParent (generatedEnvironment, generatedField);
		
		generatedField.transform.localScale = new Vector3 (rows, cols, 0);
		
		Vector3 currentPosition = generatedField.transform.position;
		currentPosition.z -= (cols * cubeSize) / 2f - cubeSize / 2;
		currentPosition.x -= (rows * cubeSize) / 2f - cubeSize / 2;
		
		currentPosition.y = cubeSize / 2;
		float startingZ = currentPosition.z;

		GameObject staticObjects = new GameObject("ImmutableObjects");
		SetParent (generatedEnvironment, staticObjects);

		for (int i = 0; i < rows; i++) {
			currentPosition.z = startingZ;
			for (int k = 0; k < cols; k++) {
				switch (bitmap [i, k]) {
				case '0':// player dot food points
					CreateBlock (currentPosition, staticObjects, foodDot);
					break;
				case '1': // wall
					CreateBlock (currentPosition, staticObjects, wall);
					break;
				case '2': // player spawn point
					CreateBlock (currentPosition, generatedEnvironment, spawnPlayerPoint);
					break;
				case '3': // enemy spawn point
					CreateBlock (currentPosition, generatedEnvironment, spawnEnemyPoint);
					break;
				case '4': // for scatter
					CreateBlock (currentPosition, generatedEnvironment, enemyScatterPoint);
					break;
				case '5': // teleport enter
					CreateBlock (currentPosition, generatedEnvironment, teleportEnter);
					break;
				case '6': // teleport exit
					CreateBlock (currentPosition, generatedEnvironment, teleportExit);
					break;
				case '7': // enemy follow dots and dot food point
					CreateBlock (currentPosition, generatedEnvironment, enemyFollowDots);
					CreateBlock (currentPosition, staticObjects, foodDot);
					break;
				case 'p':// player pellet food points
					CreateBlock (currentPosition, staticObjects, foodPellet);
					break;
				case 'c':// player cherry food points
					CreateBlock (currentPosition, staticObjects, foodCherry);
					break;
				case 's':// player Strawberry dot food points
					CreateBlock (currentPosition, staticObjects, foodStrawberry);
					break;
				case 'd':// enemy base door, player can't move through it
					CreateBlock (currentPosition, staticObjects, enemyBaseDoor);
					break;
				}
				currentPosition.z += cubeSize;
			}
			currentPosition.x += cubeSize;
		}
	}

	GameObject CreateBlock(Vector3 position, GameObject environment, GameObject prefab) {
		GameObject newObject = Instantiate (prefab, position, wall.transform.rotation) as GameObject;
		SetParent (environment, newObject);

		return newObject;
	}

	void SetParent(GameObject parent, GameObject child) {
		child.transform.parent = parent.transform;
	}
}
