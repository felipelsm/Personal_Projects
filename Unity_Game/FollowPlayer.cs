using UnityEngine;

public class FollowPlayer : MonoBehaviour {

    public Transform player;
    public Vector3 offset;

    // Update is called once per frame
    void Update ()
    {
        //transform.position = player.position + offset;  // Follow player coordinates with offset
        transform.position.Set(transform.position.x , transform.position.y, transform.position.z);
    }
}
