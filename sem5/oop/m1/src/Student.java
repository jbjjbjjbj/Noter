public class Student extends Person implements Uniperson {
	// Yes, we do support very long educations
	private long semester;
	private String degree;

	private double GPA;
	private int GPAcount;
	
	public Student(String name, short age, String gender, long semester, String degree) {
		super(name, gender, age);
		this.semester = semester;
		this.degree = degree;
		this.GPA = 0;
		this.GPAcount = 0;
	}
	
	public void addGPA(double GPA) {
		this.GPA += GPA;
		this.GPAcount++;
	}

	public long getSem() {
		return this.semester;
	}
	
	public String getDeg() {
		return this.degree;
	}
	
	public double avgGPA() {
		if (this.GPAcount == 0) {
			return 0;
		}
		return this.GPA / this.GPAcount;
	}
}
