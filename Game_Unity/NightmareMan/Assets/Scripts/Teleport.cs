using UnityEngine;
using System.Collections;

public class Teleport : MonoBehaviour {

	void OnTriggerEnter (Collider other)
	{
		if(other.tag == "Player")
		{
			TeleportManager.Instance.EffectTeleportObject(other.gameObject);
		}
	}

}
