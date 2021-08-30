using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public static class ShortestPathAlgorithms {

	static List<Struct.DoubleIndex> currentPath = new List<Struct.DoubleIndex>();
	static List<Struct.DoubleIndex> bestPath;

	static int[] directionsX = {0, 1, 0, -1}; 
	static int[] directionsY = {-1, 0, 1, 0}; 

	public static List<Struct.DoubleIndex> Dfs(char [,] map, Struct.DoubleIndex current, Struct.DoubleIndex target, char wall, bool isNew = true) {
		if (isNew) {
			currentPath.Clear ();
			bestPath = null;
		}

		currentPath.Insert (0, current.Clone());

		if (current.Equals (target) && (bestPath == null || bestPath.Count > currentPath.Count))
			bestPath = new List<Struct.DoubleIndex> (currentPath);

		if (bestPath != null && bestPath.Count <= currentPath.Count)
			return bestPath;

		for (int i = 0; i < directionsX.Length; i++) {
			current.first  += directionsY[i];
			current.second += directionsX[i];

			if(!currentPath.Contains(current) && CanMove(map, current, wall))
				Dfs (map, current, target, wall, false);

			current.first  -= directionsY[i];
			current.second -= directionsX[i];
		}

		currentPath.RemoveAt (0);

		return bestPath;
	}

	static bool CanMove(char [,] map, Struct.DoubleIndex index, char wall) {
		return 	index.first >= 0 && index.second >= 0 &&
				index.first < map.GetLength (0) && index.second < map.GetLength (1) &&
				map[index.first, index.second] != wall;
	}

}
