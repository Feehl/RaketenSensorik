using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;

public class CalculatePath : MonoBehaviour
{
    private string filepath;
    private List<Vector3> data = new List<Vector3>();
    private float time;
    public Transform rocketTransform;
    
    private Vector3 velocity = Vector3.zero;
    private float timer = 0;
    private int i = 0;
    private float g = 9.81f;
    private bool running = true;

    // Start is called before the first frame update
    void Start()
    {
        //Initialization
        filepath = Application.dataPath + "/TEST.txt";
        ReadFile(filepath);
        rocketTransform.position = Vector3.zero;
        rocketTransform.rotation = Quaternion.identity;
    }

    private void ReadFile(string path) 
    {
        string[] stringVectors = File.ReadAllLines(path);

        time = float.Parse(stringVectors[0]) / 1000;

        for(int i = 1; i < stringVectors.Length; i++)
        {
            string[] stringVector = stringVectors[i].Split(new string[] {";"}, StringSplitOptions.None);

            if(stringVector.Length != 3) 
            { 
                print("Error"); 
            }

            data.Add(new Vector3(float.Parse(stringVector[0]), -float.Parse(stringVector[2]) + g, float.Parse(stringVector[1])));
        }
    }

    private void Update()
    {
        if (i >= data.Count / 2) return;
        if(!running) return;
        timer += Time.deltaTime;
        if(timer > time)
        {
            running = false;
            CalculateVelocity(i);
            CalculatePosition();
            CalculateRotation(i + 1);
            i += 2;
            timer = 0;
            running = true;
        }
    }    

    private void CalculateRotation(int index)
    {
        Vector3 rotationAngle = data[index] * Mathf.Rad2Deg * time;
        rocketTransform.Rotate(rotationAngle, Space.Self);
    }

    private void CalculateVelocity(int index)
    {
        velocity += (data[index] * time);
    }
    private void CalculatePosition()
    {
        rocketTransform.Translate(velocity * time);
    }
}
