package lab4;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TestName;

public class BSTUnitTests {
	
	BST tree;
	Student st1, st2, st3, st4, st5, st6, st7, st8, st9, st10;

	@Rule
	public TestName name = new TestName();
	
	@Before
	public void setUp() throws Exception {
		System.out.println("-----Test-----");
		System.out.println("\"" + name.getMethodName() + "\"");
		st1 = new Student("Abramov", "Alex", 12, 1, "KP-52", "English");
		st2 = new Student("Andrianov", "Alex", 5, 2,  "KP-42", "English");
		st3 = new Student("Boyko", "Anton", 18, 3,  "KP-32", "French");
		st4 = new Student("Butnev", "Max", 2, 3, "KP-32", "English");
		st5 = new Student("Petrov", "Ivan", 9, 1, "KP-52", "English");
		st6 = new Student("Marchenko", "Alex", 15, 4,  "KP-21", "German");
		st7 = new Student("Dmitrenko", "Ivan", 19, 5, "KP-51m", "English");
		st8 = new Student("Ivanov", "Dmitry", 13, 2, "KP-41", "English");
		st9 = new Student("Petrenko", "Petr", 17, 2, "KP-31", "Spanish");
		st10 = new Student("Ivanenko", "Petr", 17, 2, "KP-41", "English");
		tree = new BST();
	}

	@After
	public void tearDown() throws Exception {
		System.out.println("-----End-----\n");
	}

	@Test
	public void new_emptyBST_zeroSize() {
		assertEquals(tree.size(), 0);
	}
	
	@Test
	public void insert_emptyBST_sizeOne(){
		st1.printInfo();
		tree.insert(st1.getKey(), st1);
		assertEquals(tree.size(), 1);
	}
	
	@Test
	public void insert_numerousInsertions_correctSizeAndLook(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.insert(st3.getKey(), st3);
		tree.insert(st4.getKey(), st4);
		tree.insert(st5.getKey(), st5);
		tree.insert(st6.getKey(), st6);
		tree.insert(st7.getKey(), st7);
		tree.insert(st8.getKey(), st8);
		tree.insert(st9.getKey(), st9);
		assertEquals(tree.size(), 9);
		tree.print();
	}
	
	@Test
	public void insert_reinsertionWithSameKey_correctSize_differentContent(){
		st9.printInfo();
		st10.printInfo();
		assertEquals(st9.getKey(), st10.getKey());
		tree.insert(st9.getKey(), st9);
		assertEquals(tree.size(), 1);
		Student prev = tree.insert(st10.getKey(), st10);
		assertSame(prev, st9);
	}
	
	@Test
	public void containsKey_filledWithOneStudent_returnsTrue(){
		tree.insert(st1.getKey(), st1);
		assertTrue(tree.containsKey(st1.getKey()));
	}
	
	@Test
	public void containsKey_emptyKey_returnsFalse(){
		assertFalse(tree.containsKey(777));
	}
	
	@Test
	public void get_filledWithOneStudent_returnsSame(){
		tree.insert(st1.getKey(), st1);
		assertSame(st1, tree.get(st1.getKey()));
	}
	
	@Test
	public void get_filledWithSomeStudents_returnsSame(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.insert(st3.getKey(), st3);
		assertSame(st3, tree.get(st3.getKey()));
	}
	
	@Test
	public void get_wrongKey_returnsNull(){
		assertNull(tree.get(777));
	}
	
	@Test
	public void remove_onlyRootAdded_correctSizeAndSameObject(){
		tree.insert(st1.getKey(), st1);
		Student prev = tree.remove(st1.getKey());
		assertEquals(tree.size(), 0);
		assertSame(prev, st1);
	}
	
	@Test
	public void remove_containsRootAndLeftChild_removingRoot_correctSizeAndSameObject(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.print();
		Student prev = tree.remove(st1.getKey());
		assertSame(prev, st1);
		assertEquals(tree.size(), 1);
		tree.print();
	}
	
	@Test
	public void remove_containsRootAndRightChild_removingRoot_correctSizeAndSameObject(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st3.getKey(), st3);
		tree.print();
		Student prev = tree.remove(st1.getKey());
		assertSame(prev, st1);
		assertEquals(tree.size(), 1);
		tree.print();
	}
	
	@Test
	public void remove_containsRootAndLeftChild_removingLeftChild_correctSizeAndSameObject(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.print();
		Student prev = tree.remove(st2.getKey());
		assertSame(prev, st2);
		assertEquals(tree.size(), 1);
		tree.print();
	}
	
	@Test
	public void remove_containsRootAndRightChild_removingRightChild_correctSizeAndSameObject(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st3.getKey(), st3);
		tree.print();
		Student prev = tree.remove(st3.getKey());
		assertSame(prev, st3);
		assertEquals(tree.size(), 1);
		tree.print();
	}
	
	@Test 
	public void remove_containsRootAndBothChildren_removingRoot_correctSizeAndSameObject(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.insert(st4.getKey(), st4);
		Student prev = tree.remove(st1.getKey());
		assertSame(st1, prev);
		assertEquals(tree.size(), 2);
	}
	
	@Test
	public void remove_nodeInMiddleWithNoChildren_correctSizeAndSameObj(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		Student prev = tree.remove(st2.getKey());
		assertSame(prev, st2);
	}
	
	@Test
	public void remove_nodeInMiddleWithOneChild_correctSizeAndLook(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.insert(st3.getKey(), st3);
		tree.insert(st4.getKey(), st4);
		tree.print();
		Student prev = tree.remove(st2.getKey());
		assertSame(st2, prev);
		assertEquals(tree.size(), 3);
		tree.print();
	}
	
	@Test
	public void remove_nodeInMiddleWithTwoChildren_correctSizeAndLook(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.insert(st3.getKey(), st3);
		tree.insert(st4.getKey(), st4);
		tree.insert(st5.getKey(), st5);
		tree.print();
		Student prev = tree.remove(st2.getKey());
		st2.printInfo();
		assertEquals(tree.size(), 4);
		assertSame(prev, st2);
		tree.print();
	}
	
	@Test
	public void remove_farNodeInMiddleWithTwoChildren_correctSizeAndLook(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.insert(st3.getKey(), st3);
		tree.insert(st4.getKey(), st4);
		tree.insert(st5.getKey(), st5);
		tree.insert(st6.getKey(), st6);
		tree.insert(st7.getKey(), st7);
		tree.insert(st8.getKey(), st8);
		tree.insert(st9.getKey(), st9);
		tree.print();
		st3.printInfo();
		Student prev = tree.remove(st3.getKey());
		assertEquals(tree.size(), 8);
		assertSame(prev, st3);
		tree.print();		
	}
	
	@Test
	public void remove_wrongKey_returnNull(){
		assertNull(tree.remove(777));
	}
	
	@Test 
	public void removeWithParam_secondCourseEnglishmen_correctSize(){
		tree.insert(st1.getKey(), st1);
		tree.insert(st2.getKey(), st2);
		tree.insert(st3.getKey(), st3);
		tree.insert(st4.getKey(), st4);
		tree.insert(st5.getKey(), st5);
		tree.insert(st6.getKey(), st6);
		tree.insert(st7.getKey(), st7);
		tree.insert(st8.getKey(), st8);
		tree.insert(st9.getKey(), st9);
		tree.print();
		int prevSize = tree.size();
		int deleted = tree.remove(2, "English");
		tree.print();
		assertEquals(deleted, 2);
		assertEquals(tree.size() + deleted, prevSize);	
	}
	

}
