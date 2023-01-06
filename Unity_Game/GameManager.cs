using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public PlayerMovement movement;     // Reference to PlayerMovement script

    bool gameHasEnded = false;

    public float restartDelay = 1f;

    public GameObject completeLevelUI;

    public void CompleteLevel ()
    {
        Debug.Log("LEVEL COMPLETE!");
        completeLevelUI.SetActive(true);    // "Level Complete" animation
    }

    public void GameOver ()
    {
        if (gameHasEnded == false)
        {
            gameHasEnded = true;
            movement.enabled = false;   // Disable player movements
            Debug.Log("GAME OVER");
            Invoke("Restart", restartDelay);    // Call "Restart" with delay
        }
    }

    void Restart ()
    {
        Debug.Log("RESTART");
        SceneManager.LoadScene(SceneManager.GetActiveScene().name); // Restart level
    }
}
