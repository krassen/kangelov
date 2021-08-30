using UnityEngine;
using System.Collections;

public static class ParseFunctions {

	public static char[,] ParseLevelTextAsset(TextAsset file) {
		string [] context = SplitByLines(file.text);
		
		int rows = context.Length;
		int cols = context[0].Length; 
		
		char [,] levelBitmap = new char[rows, cols];
		for (int i = 0; i < rows; i++) {
			for(int k = 0; k < cols; k++) {
				levelBitmap[i, k] = context[i][k];
			}
		}
		
		return levelBitmap;
	}

	static string [] SplitByLines(string text) {
		return text.Split(new string[] { System.Environment.NewLine }, System.StringSplitOptions.None);
	}

}
