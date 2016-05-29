package hashtable;

public class Hashtable1 {
	private Entry[] table;

	private Entry DEL;

	private int size;

	private int capacity = 11;

	private double loadFactor = 0.75;

	public Hashtable1() {
		table = new Entry[capacity];
	}

	public Hashtable1(int initialCapacity) {
		this.capacity = initialCapacity;
		table = new Entry[this.capacity];
	}

	public Hashtable1(int initialCapacity, double loadFactor) {
		this.capacity = initialCapacity;
		table = new Entry[this.capacity];
		if (loadFactor > 0 && loadFactor < 1) {
			this.loadFactor = loadFactor;
		}
	}

	public boolean isEmpty() {
		return (this.size == 0);
	}

	public int size() {
		return size;
	}

	public boolean contains(int key) {
		int index = hash(key);
		if (table[index].getKey() == key) {
			return true;
		} else
			return false;
	}

	public Vector get(int key) {
		int index = hash(key);
		if (table[index].getKey() == key) {
			return table[index].getValue();
		} else
			return null;
	}

	public boolean put(int key, Vector value) {
		if ((double) (size + 1) / (double) capacity > loadFactor)
			rehash();
		int index = hash(key);
		if (table[index] == null) {
			table[index] = new Entry(value);
			size++;
			return true;
		} else if (table[index].getKey() == key) {
			//Vector old = table[index].getValue();
			table[index] = new Entry(value);
			return true;
		} else
			return false;
	}
	
	public Vector remove(int key) {

		int index = hash(key);
		if (table[index].getKey() == key) {
			Vector del = table[index].getValue();
			table[index] = DEL;
			size--;
			return del;
		}

		return null;
	}
	
	public void print() {
		for (int i = 0; i < table.length; i++) {
			if (table[i] != null || table[i] != DEL) {
				System.out.format("[%2d] Key: %3d°; Value: %s\n", i,
						table[i].getKey(), table[i].getValue().getData());
			} else
				System.out.format("[%2d] %s\n", i, (table[i] == null) ? "NULL"
						: "DEL");
		}
	}
	
	private void rehash() {
		Entry[] oldTable = table;
		capacity += 16;
		size = 0;
		table = new Entry[capacity];
		for (int i = 0; i < oldTable.length; i++) {
			if (oldTable[i] != null && oldTable[i] != DEL) {
				put(oldTable[i].getKey(), oldTable[i].getValue());
			}
		}
	}

	private int hash(int key) {
		return key % capacity;
	}

}
