public class Student extends Person implements Uniperson {
	// Yes, we do support very long educations
	private long semester;
	private String degree;

	// GPA stuff
	private double gradesum;
	private int gradecount;
	
	public Student(String name, short age, String gender, long semester, String degree) {
		super(name, gender, age);
		this.semester = semester;
		this.degree = degree;
		this.gradesum = 0;
		this.gradecount = 0;
	}
	
	public void addGrade(double grade) {
		this.gradesum += grade;
		this.gradecount++;
	}

	public long getSem() {
		return this.semester;
	}
	
	public String getDeg() {
		return this.degree;
	}
	
	public double getGPA() {
		if (this.gradecount == 0) {
			return 0;
		}
		return this.gradesum / this.gradecount;
	}
}
