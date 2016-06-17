package lab4;

public class BSTTest {
	public static void main(String[] args) {
		Student st1 = new Student("Abramov", "Alex", 12, 1, "KP-52", "English");
		Student st2 = new Student("Andrianov", "Alex", 5, 2,  "KP-42", "English");
		Student st3 = new Student("Boyko", "Anton", 18, 3,  "KP-32", "French");
		Student st4 = new Student("Butnev", "Max", 2, 3, "KP-32", "English");
		Student st5 = new Student("Petrov", "Ivan", 9, 1, "KP-52", "English");
		Student st6 = new Student("Marchenko", "Alex", 15, 4,  "KP-21", "German");
		Student st7 = new Student("Dmitrenko", "Ivan", 19, 5, "KP-51m", "English");
		Student st8 = new Student("Ivanov", "Dmitry", 13, 2, "KP-41", "French");
		Student st9 = new Student("Petrenko", "Petr", 17, 3, "KP-31", "Spanish");
		Student st10 = new Student("Ivanenko", "Petr", 17, 2, "KP-41", "English");
		BST tree = new BST();
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.insert(st3.getKey(), st3);
		tree.insert(st4.getKey(), st4);
		tree.insert(st5.getKey(), st5);
		tree.insert(st6.getKey(), st6);
		tree.insert(st7.getKey(), st7);
		tree.insert(st8.getKey(), st8);
		tree.insert(st9.getKey(), st9);
		tree.insert(st10.getKey(), st10);
		tree.remove(18);
		tree.print();
		
		tree.traverse();
		
		//int dif = tree.remove(2, "English");
		//tree.traverse();
		//System.out.println(tree.size());
		/*Student test = tree.get(st3.getKey());
		System.out.println(test.getInfo());*/
		/*boolean OK = tree.containsKey(st4.getKey());
		System.out.println(OK);*/
		

	}

}
