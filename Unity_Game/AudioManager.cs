//using System;
//using UnityEngine.Audio;
//using UnityEngine;
//
//public class AudioManager : MonoBehaviour
//{
//    public Sound[] sounds;
//
//    public static AudioManager instance;
//
//    // Start is called before the first frame update
//    void Awake ()
//    {
//        if (instance == null)
//            instance = this;
//        else
//        {
//            Destroy(gameObject);
//            return;
//        }
//
//        DontDestroyOnLoad(gameObject);
//
//        foreach (Sound _s in sounds)
//        {
//            _s.soundSource = gameObject.AddComponent<AudioSource>();
//            _s.soundSource.clip = _s.clip;
//
//            _s.soundSource.volume = _s.volume;
//            _s.soundSource.pitch = _s.pitch;
//            _s.soundSource.loop = _s.loop;
//        }
//    }
//
//    void Start ()
//    {
//        Play("Music");
//    }
//
//    public void Play (string name)
//    {
//        Sound s = Array.Find(sounds, s => s.name == name);
//        if (s == null)
//        {
//            Debug.LogWarning("Sound " + name + " not found!");
//            return;
//        }
//
//        s.soundSource.Play();
//    }
//}
//