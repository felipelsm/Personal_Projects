using UnityEngine;

public class PlayerCollision : MonoBehaviour
{
    public GameObject gamemanager;
    // Function runs when hitting object
    // Gets information abour collision and calls it "collisionInfo"
    void OnCollisionEnter (Collision collisionInfo)
    {
        Debug.Log("Hit: " + collisionInfo.collider.tag);

        // Check if the collision is with an "Obstacle"
        if (collisionInfo.collider.tag == "Obstacle")
        {
            FindObjectOfType<GameManager>().GameOver(); // Call "Game Over"
        }
    }

    void OnCollisionExit (Collision groundInfo)
    {
        Debug.Log("Hit: " + groundInfo.collider.tag);

        // Check if the collision is with "Ground"
        if (groundInfo.collider.tag == "Ground")
        {
            FindObjectOfType<GameManager>().GameOver(); // Call "Game Over"
        }
    }
}