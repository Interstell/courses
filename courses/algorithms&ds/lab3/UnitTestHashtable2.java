package hashtable;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TestName;

public class UnitTestHashtable2 {

	Hashtable2 table;
	Vector testVector1;
	Vector testVector2;
	Vector testVector3;
	Vector testVector4;
	Vector testVector5;

	@Rule
	public TestName name = new TestName();

	@Before
	public void setUp() throws Exception {
		System.out.println("-----Test-----");
		System.out.println("\"" + name.getMethodName() + "\"");
		table = new Hashtable2();
		testVector1 = new Vector(1, 0.2);
		testVector1.print();
		testVector2 = new Vector(1, 0.41);
		testVector2.print();
		testVector3 = new Vector(3, 5);
		testVector3.print();
		testVector4 = new Vector(-2, 3.3);
		testVector4.print();
		testVector5 = new Vector(2, 0.4);
		testVector5.print();
	}

	@After
	public void tearDown() throws Exception {
		System.out.println("-----End-----\n");
	}

	@Test
	public void new_newTable_zeroSize() {
		assertEquals(table.size(), 0);
	}

	@Test
	public void put_emptyTable_returnsNull_sizeOne() {
		assertNull(table.put(testVector1.getPhiInDeg(), testVector1));
		assertEquals(table.size(), 1);
	}

	@Test
	public void put_withoutCollisionIntoFilledTable_sizeIncrement() {
		table.put(testVector1.getPhiInDeg(), testVector1);
		assertNull(table.put(testVector3.getPhiInDeg(), testVector3));
		assertEquals(table.size(), 2);
	}

	@Test
	public void put_filledTable_collision_sizeInc_returnNull() {
		table.put(testVector1.getPhiInDeg(), testVector1);
		assertNull(table.put(testVector2.getPhiInDeg(), testVector2));
		assertEquals(table.size(), 2);
	}

	@Test
	public void put_filledTable_insertionIntoFilledPlaceWithoutCollision_returnNull() {
		// null == succesfully inserted, we also check size incremention
		table.put(testVector1.getPhiInDeg(), testVector1);
		table.put(testVector2.getPhiInDeg(), testVector2);
		assertNull(table.put(testVector4.getPhiInDeg(), testVector4));
		assertEquals(table.size(), 3);
		table.print();
	}

	@Test
	public void put_insertionWithSameKey_returnPrevElem() {
		table.put(testVector1.getPhiInDeg(), testVector1);
		Vector prev = table.put(testVector5.getPhiInDeg(), testVector5);
		assertNotNull(prev);
		assertSame(testVector1, prev);
	}

	@Test
	public void put_previoslyDeletedPosition_returnNull_sizeInc() {
		table.put(testVector1.getPhiInDeg(), testVector1);
		table.remove(testVector1.getPhiInDeg());
		assertNull(table.put(testVector2.getPhiInDeg(), testVector2));
		assertEquals(table.size(), 1);
	}

	@Test
	public void contains_noElementOnThisKey_returnNull() {
		assertFalse(table.contains(123));
	}

	@Test
	public void contains_tableHasElemOnThisKey_returnTrue() {
		table.put(testVector1.getPhiInDeg(), testVector1);
		assertTrue(table.contains(testVector1.getPhiInDeg()));
	}

	@Test
	public void get_noElementOnThisKey_returnNull() {
		assertNull(table.get(123));
	}

	@Test
	public void get_tableHasElemOnThisKey_returnElem() {
		table.put(testVector1.getPhiInDeg(), testVector1);
		Vector v = table.get(testVector1.getPhiInDeg());
		assertNotNull(v);
		assertSame(testVector1, v);
	}

	@Test
	public void remove_tableHasElemOnThisKey_returnElem_sizeDecrement() {
		table.put(testVector1.getPhiInDeg(), testVector1);
		Vector v = table.remove(testVector1.getPhiInDeg());
		assertNotNull(v);
		assertSame(v, testVector1);
		assertEquals(table.size(), 0);
	}

	@Test
	public void remove_tableHasNoElemOnThisKey_returnNull() {
		assertNull(table.remove(123));
	}

	@Test
	public void remove_task3_insertionWithCollision_sizeDec() {
		table.put(testVector1.getPhiInDeg(), testVector1);
		table.put(testVector2.getPhiInDeg(), testVector2);
		table.put(testVector3.getPhiInDeg(), testVector3);
		table.put(testVector4.getPhiInDeg(), testVector4);
		assertEquals(table.size(), 4);
		table.print();
		System.out.println("");
		table.remove(testVector2.getPhiInDeg());
		table.remove(testVector3.getPhiInDeg());
		assertEquals(table.size(), 2);
		table.print();
	}

	@Test
	public void rehash_makingTableFull_capacityIncrement() {
		table = new Hashtable2(4);
		int prevCapacity = table.capacity();
		table.put(testVector1.getPhiInDeg(), testVector1);
		table.put(testVector2.getPhiInDeg(), testVector2);
		table.put(testVector3.getPhiInDeg(), testVector3);
		table.print();
		System.out.println("");
		table.put(testVector4.getPhiInDeg(), testVector4);
		table.print();
		assertTrue(prevCapacity != table.capacity());
	}

}