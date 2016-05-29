package sort;

public class ListNode {
	Student student;
	ListNode next = null;
	ListNode prev = null;
	
	public ListNode(){
		this.student = new Student();
	}
	
	public ListNode(Student st){
		this.student = st;
	}
}
