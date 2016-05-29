package hashtable;

public class Hashtable2 {

	private Entry[] table;

	private Entry DEL;
	
	private int size;

	private int capacity = 11;

	private double loadFactor = 0.75;
	
	private final double A = Math.sqrt(5) - 2;
		
	public Hashtable2() {
		table = new Entry[capacity];
	}

	public Hashtable2(int initialCapacity) {
		this.capacity = initialCapacity;
		table = new Entry[this.capacity];
	}

	public Hashtable2(int initialCapacity, double loadFactor) {
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
	
	public int capacity(){ //technical, for debug
		return capacity;
	}
	
	public boolean contains(int key) {
		int probe = 0;
		int index;
		do {
			index = hash(key, probe);
			if (table[index] != null && table[index].getKey() == key) {
				return true;
			} else
				probe++;

		} while (probe != capacity - 1);

		return false;
	}

	public Vector get(int key) {
		int probe = 0;
		int index;
		do {
			index = hash(key, probe);
			if (table[index] != null && table[index].getKey() == key) {
				return table[index].getValue();
			} else
				probe++;

		} while (probe != capacity - 1);

		return null;
	}

	private void rehash() {
		Entry[] oldTable = table;
		/*capacity *= 2;
		capacity = nextPrime(capacity);*/
		capacity += 16;
		size = 0;
		table = new Entry[capacity];
		for (int i = 0; i < oldTable.length; i++) {
			if (oldTable[i] != null && oldTable[i] != DEL) {
				put(oldTable[i].getKey(), oldTable[i].getValue());
			}
		}
	}
	
	private int nextPrime(int n){
		n++;
		while (!isPrime(n))
			n++;
		return n;
	}
	
	private boolean isPrime(int n){
		if (n == 1)
			return false;
		for (int d = 2; d < n; d++) {
			if (n % d == 0)
				return false;
		}
		return true;
	}

	public Vector put(int key, Vector value) {
		int probe = 0;
		if ((double)(size + 1) / (double)capacity > loadFactor)
			rehash();
		do {
			int index = hash(key, probe);
			if (table[index] == null || table[index] == DEL) {
				table[index] = new Entry(value);
				size++;
				return null;
			} else {
				if (table[index].getKey() == key) {
					Vector old = table[index].getValue();
					table[index] = new Entry(value);
					return old;
				} else
					probe++;
			}
		} while (probe != capacity - 1);

		return null; //just like false
	}

	private int hash(int key) {
		return key % capacity;
	}

	private int hash(int key, int probe) {
		return (hash(key) + probe * hashMult(key)) % capacity;
	}

	private int hash2(int key) {
		return (int)(key / 7);
	}

	private int hashMult(int key) {
		return (int)(capacity * (key * A - (int)(key * A)));
	}
	
	public Vector remove(int key) {
		int probe = 0;
		int index;
		do {
			index = hash(key, probe);
			if (table[index] != null && table[index].getKey() == key) {
				Vector del = table[index].getValue();
				table[index] = DEL;
				size--;
				return del;
			} else
				probe++;
		} while (probe != capacity - 1);

		return null;
	}
	
	public void print() {
		for (int i = 0; i < table.length; i++) {
			if (table[i] != null || table[i] != DEL) {
				System.out.format("[%2d] Key: %3d°; Value: %s\n", i,
						table[i].getKey(), table[i].getValue().getData());
			} else
				System.out.format("[%2d] %s\n", i, "NULL");
		}
	}
}
