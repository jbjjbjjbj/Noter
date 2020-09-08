
public class Main {
	public static void main(String[] args) {
		Student std = new Student("Julian", (short)21, "Male", (long)123213213, "COMTEK");
		Uniperson hej = std;
		
		hej.addGrade(7);
		hej.addGrade(12);
		
		System.out.printf("deg: %s, sem: %d, avg: %f\n", hej.getDeg(), hej.getSem(), hej.getGPA());
		
		System.out.printf("person: %s\n", std);
	}
}
