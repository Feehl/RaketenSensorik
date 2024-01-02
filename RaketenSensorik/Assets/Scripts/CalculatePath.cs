using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;

public class CalculatePath : MonoBehaviour
{
    private string filepath;
    private List<Vector3> data = new List<Vector3>();
    private List<float> delays = new List<float>();
    public Transform rocketTransform;
    
    private Vector3 velocity = Vector3.zero;
    private float timer = 0;
    private int i = 0;
    private Vector3 g = new Vector3(0f, 9.81f, 0f);
    private bool running = true;
    private string[] stringVectors;
    private float currentDelay;
    private bool finished = false;

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
        stringVectors = File.ReadAllLines(path);

        for(int i = 0; i < stringVectors.Length; i+=3)
        {
            delays.Add(float.Parse(stringVectors[i]));
            AddStringVector(i+1);
            AddStringVector(i+2);
        }

        currentDelay = ConvertDelayToSeconds(delays[0]);
    }

    private void AddStringVector(int index)
    {
        string[] stringVector = stringVectors[index].Split(new string[] { ";" }, StringSplitOptions.None);

        if (stringVector.Length != 3)
        {
            print("Error");
        }

        data.Add(new Vector3(float.Parse(stringVector[0]), float.Parse(stringVector[2]), float.Parse(stringVector[1])));
    }

    //Simulate
    private void Update()
    {
        if(finished) return;
        if (i >= data.Count / 2)
        {
            finished = true;
            Debug.Log("Final Height: " + rocketTransform.position.y.ToString());
        }
        if(!running) return;
        timer += Time.deltaTime;
        if(timer >= currentDelay)
        {
            running = false;
            CalculateVelocity(i);
            CalculatePosition();
            CalculateRotation(i + 1);
            i += 2;
            currentDelay = ConvertDelayToSeconds(delays[i / 2] - delays[(i / 2) - 1]);
            timer = 0;
            running = true;
        }
    }    

    private void CalculateRotation(int index)
    {
        Vector3 rotationAngle = data[index] * Mathf.Rad2Deg * currentDelay;
        rocketTransform.Rotate(rotationAngle, Space.Self);
    }

    private void CalculateVelocity(int index)
    {
        velocity += ((data[index]+g) * currentDelay);
    }
    private void CalculatePosition()
    {
        rocketTransform.Translate(velocity * currentDelay);
    }

    private float ConvertDelayToSeconds(float delayInMs)
    {
        return delayInMs / 1000f;
    }
}
