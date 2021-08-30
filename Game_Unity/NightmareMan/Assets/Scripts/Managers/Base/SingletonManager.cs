using UnityEngine;
using System.Collections;

public abstract class SingletonManager<T> : MonoBehaviour where T : SingletonManager<T> {

	static T Instance_;
	public static T Instance {
		get {
			if(Instance_ == null)
				Instance_ = GameObject.FindObjectOfType<T>();

			return Instance_;
		}
	}

}
