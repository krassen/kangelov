using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class PathFinder : MonoBehaviour {

	public GameObject wall;
	public float movementSpeed = 4f;
	
	struct Field {
		public Vector3 position;
		public Vector3 size;  /* z = height, x = width */
	}

	Field field;
	Vector3 wallSize;
	Vector3 targetLocation;
	Vector3 enemyMovementDirection = new Vector3 (0, 0, 1f);
	List<Struct.DoubleIndex> pathPoints = null;

	void Update() {
		if (pathPoints == null)
			return;

		if (DestinationReached()) 
			targetLocation = TopLocation();

		MoveEnemy ();
	}

	Vector3 TopLocation() {
		if (pathPoints == null || pathPoints.Count == 0)
			return targetLocation;
		
		Struct.DoubleIndex nextPoint = pathPoints[pathPoints.Count - 1];
		pathPoints.RemoveAt (pathPoints.Count - 1);
		return GetPosition(nextPoint);
	}

	bool DestinationReached() {
		return Vector3.Distance (targetLocation, transform.position) < 0.05f;
	}

	void MoveEnemy() {
		transform.LookAt (targetLocation);
		transform.Translate( enemyMovementDirection * movementSpeed * Time.deltaTime );
	}

	void Awake() {
		SetField ();
	}

	void SetField() {
		GameObject fieldObject = GameObject.FindGameObjectWithTag ("Field");

		wallSize = ObjectSize (NavigationManager.Instance.wall);
		field.size = ObjectSize(fieldObject);

		field.position = fieldObject.transform.position;
		
		field.position.z -= field.size.z / 2;
		field.position.x -= field.size.x / 2;
	}

	Vector3 ObjectSize(GameObject objectArg) {
		Renderer objectCollider = objectArg.GetComponent<Renderer> ();

		return objectCollider.bounds.size;
	}

	public void SetDestination(Vector3 targetPosition) {
		Struct.DoubleIndex enemyIndex  = new Struct.DoubleIndex(0, 0);
		Struct.DoubleIndex targetIndex = new Struct.DoubleIndex(0, 0);

		FindIndex (ref enemyIndex, gameObject.transform.position);
		FindIndex (ref targetIndex, targetPosition);

		char [,] movementMap = NavigationManager.Instance.movementMap;
		char wallFlag = NavigationManager.Instance.wallFlag;

		pathPoints = ShortestPathAlgorithms.Dfs (movementMap, enemyIndex, targetIndex, wallFlag);

		targetLocation = gameObject.transform.position;
	}

	void FindIndex(ref Struct.DoubleIndex index, Vector3 targetPosition) {
		index.first  = Mathf.Abs ((int) (field.position.x - targetPosition.x));
		index.second = Mathf.Abs ((int) (field.position.z - targetPosition.z));
	}

	Vector3 GetPosition(Struct.DoubleIndex index) {
		Vector3 worldPosition = new Vector3(field.position.x + index.first, 0, field.position.z + index.second);
		worldPosition += wallSize / 2;

		return worldPosition;
	}

}
