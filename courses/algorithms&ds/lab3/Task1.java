package hashtable;

public class Task1 {

	public static void main(String[] args) {
		Vector v1 = new Vector(1, 0.2);
		Vector v2 = new Vector(2, 3);
		Vector v3 = new Vector(3, 2);
		Vector v4 = new Vector(-4, 8);
		
		System.out.println("Before insertion: ");
		v1.print();
		v2.print();
		v3.print();
		v4.print();

		Hashtable1 table = new Hashtable1();
		boolean wasPut;
		wasPut = table.put(v1.getPhiInDeg(), v1);
		System.out.format("Insertion by key %d°: %s\n", v1.getPhiInDeg(),(wasPut)?"TRUE":"FALSE");
		wasPut = table.put(v2.getPhiInDeg(), v2);
		System.out.format("Insertion by key %d°: %s\n", v2.getPhiInDeg(),(wasPut)?"TRUE":"FALSE");
		wasPut = table.put(v3.getPhiInDeg(), v3);
		System.out.format("Insertion by key %d°: %s\n", v3.getPhiInDeg(),(wasPut)?"TRUE":"FALSE");
		wasPut = table.put(v4.getPhiInDeg(), v4);
		System.out.format("Insertion by key %d°: %s\n", v4.getPhiInDeg(),(wasPut)?"TRUE":"FALSE");
		System.out.println("After insertion: ");
		table.print();
		
		System.out.format("\nDeleting vector by key: %d°\n",v1.getPhiInDeg());
		table.remove(v1.getPhiInDeg());
		table.print();
	}

}
