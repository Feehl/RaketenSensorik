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

    public string fileName = "TEST";
    public Transform rocketTransform;
    public Transform velocityObject;
    public bool applyGravity;
    public bool lockHeight;

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
        filepath = Application.dataPath + "/" + fileName + ".txt";
        ReadFile(filepath);
        rocketTransform.position = Vector3.zero;
        rocketTransform.rotation = Quaternion.identity;
        velocityObject.position = Vector3.zero;
    }

    private void ReadFile(string path) 
    {
        stringVectors = File.ReadAllLines(path);
        delays.Add(float.Parse(stringVectors[0]));

        for(int i = 1; i < stringVectors.Length; i+=3)
        {
            AddStringVector(i);
            AddStringVector(i+1);
            delays.Add(float.Parse(stringVectors[i+2]));
        }
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
        //End
        if(finished) return;
        if (i >= data.Count)
        {
            finished = true;
            Debug.Log("Final Height: " + rocketTransform.position.y.ToString());
            return;
        }

        //Timer
        if (!running) return;
        timer += Time.deltaTime;
        if(timer >= currentDelay)
        {
            running = false;
            currentDelay = ConvertDelayToSeconds(delays[(i / 2)+1] - delays[(i / 2)]);

            CalculateRotation(i+1);
            CalculateVelocity(i);
            CalculatePosition();
            
            i += 2;
            timer = 0;
            Debug.Log("rotation: " + velocityObject.localRotation.eulerAngles.ToString());
            Debug.Log("forward: " + velocityObject.forward.ToString());
            Debug.Log(currentDelay.ToString() + " seconds passed");
            running = true;
        }
    }    

    private void CalculateRotation(int index)
    {
        Vector3 rotationAngle = data[index] * currentDelay * Mathf.Rad2Deg;
        rocketTransform.Rotate(rotationAngle);
        velocityObject.Rotate(rotationAngle);
    }

    private void CalculateVelocity(int index)
    {
        if(applyGravity) 
            ApplyGravity();

        velocityObject.Translate(data[index] * currentDelay);

        if(lockHeight)
            velocityObject.position = new Vector3(velocityObject.position.x, 0f, velocityObject.position.z);
    }

    private void CalculatePosition()
    {
        rocketTransform.Translate(velocityObject.position * currentDelay, Space.World);
    }

    private void ApplyGravity()
    {
        velocityObject.Translate(g * currentDelay, Space.World);
    }

    private float ConvertDelayToSeconds(float delayInMs)
    {
        return delayInMs / 1000f;
    }

    //private Vector3 GetObjectVector(Vector3 vector, Transform ObjectSpace)
    //{
    //    Vector3 right = ObjectSpace.transform.right;
    //    Vector3 up = ObjectSpace.transform.up;
    //    Vector3 forward = ObjectSpace.transform.forward;

    //    return (vector.x * right + vector.y * up + vector.z * forward);
    //}
}
