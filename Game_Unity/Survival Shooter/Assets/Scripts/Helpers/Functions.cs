using UnityEngine;

public class Functions
{
	public static void SwapAudioSource(ref AudioClip clipOne, ref AudioSource audio) {
		AudioClip temp = audio.clip;
		audio.clip = clipOne;
		clipOne = temp;
	}
}