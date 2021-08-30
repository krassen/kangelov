using UnityEngine;
using System.Collections;

public class NavigationManager : SingletonManager<NavigationManager> {

	public GameObject wall;
	public char [,] movementMap;
	public char wallFlag;

	public void SetMap(char [,] map, char passableArea) {
		movementMap = map;
		wallFlag = passableArea;
	}

}
