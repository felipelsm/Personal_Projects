using UnityEngine;
using UnityEngine.SceneManagement;

public class Menu : MonoBehaviour
{
    public GameObject optionsMenuMainUI;
    public GameObject mainMenuUI;

    private void Update ()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (optionsMenuMainUI.activeSelf)
            {
                CloseOptionsMenu();
            }
        } 
    }

    public void StartGame ()
    {
        Debug.Log("START GAME");
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);   // Next scene
    }

    public void QuitGame ()
    {
        Debug.Log("QUIT");
        Application.Quit(); // Quit
    }

    public void CloseOptionsMenu ()
    {
        optionsMenuMainUI.SetActive(false);
        mainMenuUI.SetActive(true);
    }
}
