using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    // Reference to the Rigid Body component called "rb"
    public Rigidbody rb;

    [Header("Forces")]
    public float forwardForce = 2000f;
    public float sidewaysForce = 500f;

    // Update is called once per frame
    // Fixed Update to mess with Phisycs
    void FixedUpdate ()
    {
        // Add forces
        rb.AddForce(0, 0, forwardForce * Time.deltaTime);   // Continuous forwards force

        if (Input.GetKey("d"))  // Right force pressing "d"
        {
            rb.AddForce(sidewaysForce * Time.deltaTime, 0, 0, ForceMode.VelocityChange);
        }
        if (Input.GetKey("a"))  // Left force pressing "a"
        {
            rb.AddForce(-sidewaysForce * Time.deltaTime, 0, 0, ForceMode.VelocityChange);
        }
    }
}