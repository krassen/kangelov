using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
	public float speed = 6f;
	public string moveHorizontal = "Horizontal";
	public string moveVertical = "Vertical";
	public bool controllerEnable = false;

	Rigidbody playerRigid;
	Animator anim;
	float ray = 100f;
	int floorMask;
	Vector3 movement;

    void Awake() {
		playerRigid = GetComponent<Rigidbody> ();
		anim = GetComponent<Animator> ();
		movement = new Vector3();
		floorMask = LayerMask.GetMask("Floor");
	}

	void FixedUpdate() {
		float h = Input.GetAxisRaw (moveHorizontal);
		float v = Input.GetAxisRaw (moveVertical);

		Move (h, v);
		Animation (h, v);
		Turning ();
	}

	void Move (float h, float v) {
		if (!isWaking (h, v))
			return;
		movement.Set (h , 0f, v);
		movement = movement.normalized * speed * Time.deltaTime;
		playerRigid.MovePosition(transform.position + movement);
	}

	bool isWaking(float h, float v) {
		return h != 0 || v != 0;
	}

	void Animation (float h, float v) {
		anim.SetBool ("IsWalking", isWaking(h, v) );
	}

	void Turning() {
		if (controllerEnable) {
			float h = Input.GetAxis("RotationJsH");
			float v = Input.GetAxis("RotationJsV");
			Vector3 playerToMouse = new Vector3(h, 0f, v);
			Quaternion newRotation = Quaternion.LookRotation (playerToMouse) * Quaternion.Euler(0, 90, 0);
			playerRigid.MoveRotation (newRotation);
		} else {
			Ray camRay = Camera.main.ScreenPointToRay (Input.mousePosition);
		
			RaycastHit floorHit;
		
			if (Physics.Raycast (camRay, out floorHit, ray, floorMask)) {
				Vector3 playerToMouse = floorHit.point - transform.position;
				playerToMouse.y = 0f;
				Quaternion newRotation = Quaternion.LookRotation (playerToMouse);
				playerRigid.MoveRotation (newRotation);
			}
		}
	}
}
