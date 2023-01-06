using System.Runtime.CompilerServices;
using TMPro;
using UnityEditor;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseMenu : MonoBehaviour
{
    public static bool gameIsPaused = false;

    public GameObject pauseMenuUI;
    public GameObject optionsMenuPauseUI;

    public string sceneMenu;

    void Start()
    {
        pauseMenuUI.SetActive(false);   // Disable "pauseMenuUI"
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))   // Pause game pressing "Escape"
        {
            if (gameIsPaused)
            {
                if (!optionsMenuPauseUI.activeSelf) // If optionsMenuPauseUI is disabled
                {
                    Resume ();                      // Call "Resume"
                }
            } else
            {
                pauseMenuUI.GetComponent<Animator>().enabled = true;     // Enable animation
                Pause ();                                                // Call "Pause"
            }

            if (optionsMenuPauseUI.activeSelf)  // If "optionsMenuPauseUI" is enabled
            {
                CloseOptionsPause ();   // Close "optionsMenuUI"
            }
        }
    }

        void Pause()
        {
            Debug.Log("PAUSE");

            pauseMenuUI.SetActive(true);    // Enable "pauseMenuUI"
            Time.timeScale = 0;             // Freeze time
            gameIsPaused = true;            // "Paused state"
        }

        public void CloseOptionsPause ()
        {
            Debug.Log("CLOSE OPTIONS");

            pauseMenuUI.GetComponent<Animator>().enabled = false;   // Disable animation
            optionsMenuPauseUI.SetActive(false);                    // Disable "optionsMenuPauseUI"
            pauseMenuUI.SetActive(true);                            // Enable "pauseMenuUI"
        }

        public void Resume()
        {
            Debug.Log("RESUME");

            pauseMenuUI.SetActive(false);   // Disable "pauseMenuUI"
            Time.timeScale = 1;             // Reset TimeScale
            gameIsPaused = false;           // "not Paused state"
        }

        public void LoadMenu()
        {
            Debug.Log("LOAD MENU");

            SceneManager.LoadScene(sceneMenu);  // Load "Menu" scene
            Time.timeScale = 1;                 // Reset TimeScale
            gameIsPaused = false;               // "not Paused state"
    }
}
