using UnityEngine;

public class EndTrigger : MonoBehaviour
{

    public GameManager gameManager;

    // Check if collision is with "Player"
    
    void OnTriggerEnter (Collider triggerInfo)
    {
        if (triggerInfo.GetComponent<Collider>().CompareTag("Player"))
        {
            gameManager.CompleteLevel();    // Call "Complete Level"
        }
    }
}
