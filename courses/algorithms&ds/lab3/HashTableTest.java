package hashtable;

public class HashTableTest {

	public static void main(String[] args) {
		Hashtable2 table = new Hashtable2();
		int count = 20;
		fillHashtableWithRandomVectors(table, count);
		System.out.println("");

		table.print();
		System.out.println("Vectors added: " + count);
		System.out.println("Vectors in table: " + table.size());
		System.out.println("Capacity of table: " + table.capacity());
	}
	
	static void fillHashtableWithRandomVectors(Hashtable2 table, int count){
		for (int i = 0; i < count; i++){
			Vector v = new Vector((int)(Math.pow(-1, (Math.random() > 0.5)?0:1) * Math.random() * 10), (int)(Math.pow(-1, (Math.random() > 0.5)?0:1) * Math.random() * 10));
			table.put(v.getPhiInDeg(), v);
			v.print();
		}
	}
}
