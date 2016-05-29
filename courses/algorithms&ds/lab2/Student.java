package sort;

public class Student implements Comparable<Student> {
	
	private String Surname;
	private String Name;
	private String Facultative;
	private Integer Mark;
	
	
	public Student(){
		String[] surnamesToPick = { "Jones", "Williams", "Campbell", "Davis", "Thompson", "Kelly", "Sullivan", "O'Brien", "Evans", "Brown", "Lewis", "Wilson", "Wallace", "Ryan", "Moore", "Anderson", "Jackson", "Johnson", "Smith", "Murphy", "Rogers", "Phillips", "Jones", "Morgan", "Graham" };
		String[] namesToPick = { "Noah", "Liam", "Mason", "Jacob", "William", "Ethan", "Michael", "Alexander", "James", "Daniel", "Elijah", "Benjamin", "Logan", "Aiden", "Jayden", "Emma", "Olivia", "Sophia", "Isabella", "Ava", "Mia", "Emily", "Abigail", "Madison", "Charlotte", "Harper", "Sofia", "Avery", "Elizabeth", "Amelia" };
		String[] facultativesToPick = { "Calculus", "Algebra", "Python", "C#", "C/C++", "Java", "Swift", "Obj-C", "Scala", "HTML/CSS", "Node.JS", "Pascal" };
		
		this.Surname = surnamesToPick[(int)(surnamesToPick.length * Math.random())];
		this.Name = namesToPick[(int)(namesToPick.length * Math.random())];
		this.Facultative = facultativesToPick[(int)(facultativesToPick.length * Math.random())];
		this.Mark = new Integer((int)(Math.random() * 101));
	}
	
	public String getSurname(){
		return this.Surname;
	}
	
	public String getName(){
		return this.Name;
	}
	
	public String getFacultative(){
		return this.Facultative;
	}
	
	public int getMark(){
		return this.Mark;
	}
	
	public String getData(){
		String result = String.format("%8s %c. |%3d | %s ", this.Surname, this.Name.charAt(0), this.Mark, this.Facultative);
		return result;
	}
	
	public int compareTo(Student anotherStudent){
		return Mark.compareTo(anotherStudent.getMark());
	}
	
}
