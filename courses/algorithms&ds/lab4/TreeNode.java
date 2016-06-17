package lab4;

public class TreeNode implements Comparable<TreeNode> {
	private Integer id;
	private Student st;
	private TreeNode parent;
	private TreeNode left;
	private TreeNode right;
	
	public TreeNode(int id, Student s){
		this.st = s;
		this.id = id;
	}
	
	public TreeNode(int id, Student s, TreeNode parent){
		this.id = id;
		this.st = s;
		this.parent = parent;
	}
	
	public TreeNode(Student student, TreeNode parent, TreeNode left, TreeNode right){
		this.st = student;
		this.parent = parent;
		this.left = left;
		this.right = right;
	}
	
	public int getId(){
		return id;
	}
	
	public Student getData(){
		return st;
	}
	
	public TreeNode getParent(){
		return parent;
	}
	
	public TreeNode getLeft(){
		return left;
	}
	
	public TreeNode getRight(){
		return right;
	}
	
	public void setData(Student student){
		this.st = student;
	}
	
	public void setParent(TreeNode parent){
		this.parent = parent;
	}
	
	public void setLeft(TreeNode left){
		this.left = left;
	}
	
	public void setRight(TreeNode right){
		this.right = right;
	}
	
	public boolean hasParent(){
		return (this.parent != null);
	}
	
	public boolean hasLeft(){
		return (this.left != null);
	}
	
	public boolean hasRight(){
		return (this.right != null);
	}
	
	public boolean hasChildren(){
		return (hasLeft() || hasRight());
	}
	
	public int compareTo(TreeNode other){
        return this.id.compareTo(other.getId());
    } 
	
	public String getShortInfo(){
		return st.getShortInfo();
	}
	
}
