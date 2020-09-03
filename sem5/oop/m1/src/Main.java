
public class Main {
	public static void main(String[] args) {
		Student std = new Student("Julian", (short)21, "Male", (long)123213213, "COMTEK");
		Uniperson hej = std;
		
		hej.addGPA(0.32);
		hej.addGPA(12);
		
		System.out.printf("deg: %s, sem: %d, avg: %f\n", hej.getDeg(), hej.getSem(), hej.avgGPA());
		
		System.out.printf("person: %s\n", std);
	}
}
