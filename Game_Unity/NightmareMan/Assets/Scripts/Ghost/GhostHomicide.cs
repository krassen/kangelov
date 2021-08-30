using UnityEngine;
using System.Collections;

public class GhostHomicide : GhostMovement {

	protected override void Chase() {
		target = EnemyMovementManager.Instance.FindConditionPath (target, player);
		navigation.SetDestination (target.position);
	}

}
