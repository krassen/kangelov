using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

public static class LoadSaveDataList {
	// saving data in list, not working

	public static void AddData<T>(T data, string fileName) {
		List<T> dataList = LoadData<T> (fileName);
		dataList.Add(data);
		BinaryFormatter bf = new BinaryFormatter ();
		FileStream file = File.Create (Application.persistentDataPath + fileName);
		bf.Serialize (file, dataList);
		file.Close ();
	}

	public static List<T> LoadData<T>(string fileName) {
		BinaryFormatter bf = new BinaryFormatter ();
		string filePath = Application.persistentDataPath + fileName;
		FileStream file = File.Exists (filePath) ? File.OpenRead (filePath) : File.Create (filePath);

		// FORFIX: throwing exception when the lenght of file is 0
		List<T> dataList = null;
		try {
		dataList = (List<T>) bf.Deserialize (file);
		} catch (System.Runtime.Serialization.SerializationException) {
		}

		file.Close ();
		return dataList ?? new List<T>();
	}
}
