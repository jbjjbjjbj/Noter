
public class Main {

	public static void main(String[] args) {
		System.out.println("Get ready for cool stuff.");
		
		String fname = "hej.txt";
		if (args.length > 0) {
			fname = args[0];
		}
		
		Lines l = null;
		try {
			l = new Lines(fname);
		} catch (Exception e) {
			System.err.printf("error: %s%n", e);
			System.exit(1);
		}
		
		l.print(System.out);
	}

}
