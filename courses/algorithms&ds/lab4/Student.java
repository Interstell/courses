package lab4;

public class Student {
	private String surname;
	private String name;
	private Integer id;
	private Integer course;
	private String group;
	private String foreignLang;
	
	public Student(String Surname, String Name, int StudentID, int CourseNum, String Group, String ForeignLanguage){
		this.surname = Surname;
		this.name = Name;
		this.id = StudentID;
		this.course = CourseNum;
		this.group = Group;
		this.foreignLang = ForeignLanguage;
	}
	
	public String getSurname(){
		return surname;
	}
	
	public String getName(){
		return name;
	}
	
	public int getStudentId(){
		return id;
	}
	
	public int getCourseNum(){
		return course;
	}
	
	public String getGroup(){
		return group;
	}
	
	public String getForeignLanguage(){
		return foreignLang;
	}
	
	public int getKey(){
		return id;
	}
	
	public String getInfo(){
		return String.format("%s %s | %d | %s %s", name, surname, id, group, foreignLang);
	}
	
	public String getShortInfo(){
		return String.format("%d : %s %c.", id,surname, name.charAt(0));
	}
	
	public void printInfo(){
		System.out.format("%s %s | %d | Ñourse ¹%d %s %s\n", name, surname, id, course, group, foreignLang);
	}
}