package hashtable;

public class Entry {

	
	private int key;

	
	private Vector value;

	public Entry(Vector vector) {
		this.key = vector.getPhiInDeg();
		this.value = vector;
	}

	public int getKey() {
		return key;
	}

	public Vector getValue() {
		return value;
	}

}

