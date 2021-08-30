using UnityEngine;
using System.Collections;

public static class Struct {

	public struct DoubleIndex : System.IEquatable<DoubleIndex> {
		public int first, second;

		public DoubleIndex(int first, int second) { 
			this.first = first; 
			this.second = second; 
		}

		public bool Equals(DoubleIndex other) {
			return first == other.first && second == other.second;
		}

		public DoubleIndex Clone() {
			return new DoubleIndex (first, second);
		}
	}
}
