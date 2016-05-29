package hashtable;

import java.util.Random;

public class Task2 {
	public static void main(String[] args) {
		
		Vector v1 = new Vector(1, 0.2);
		Vector v2 = new Vector(1, 0.41);
		Vector v3 = new Vector(1, 0.24);
		
		System.out.println("Before insertion: ");
		v1.print();
		v2.print();
		v3.print();

		Hashtable2 table = new Hashtable2(19);
		Vector output;
		output = table.put(v1.getPhiInDeg(), v1);
		System.out.format("table.put(..) by key %d returned %s\n", v1.getPhiInDeg(), (output == null)?"NULL":"Object");
		output = table.put(v2.getPhiInDeg(), v2);
		System.out.format("table.put(..) by key %d returned %s\n", v2.getPhiInDeg(), (output == null)?"NULL":"Object");
		output = table.put(v3.getPhiInDeg(), v3);
		System.out.format("table.put(..) by key %d returned %s\n", v3.getPhiInDeg(), (output == null)?"NULL":"Object");

		System.out.println("After insertion: ");
		table.print();
		
		System.out.format("\nDeleting vector by key: %d°\n",v1.getPhiInDeg());
		table.remove(v1.getPhiInDeg());
		table.print();
		
		System.out.format("\nGetting vector by key: %d°\n",v3.getPhiInDeg());
		Vector v11 = table.get(v3.getPhiInDeg());
		if (v11 != null) v11.print();
			else System.out.println("NULL");
		
	}
}
