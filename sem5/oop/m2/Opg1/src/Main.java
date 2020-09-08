import java.io.FileWriter;
import java.io.IOException;

public class Main {
	
	static void writeLines(String name) throws IOException{
		FileWriter f = null;
		try {
			f = new FileWriter(name);

			for (int i = 1; i <= 100; i++) {
				f.write(String.format("%-3d ", i));
				if (i % 10 == 0) {
					f.write(System.lineSeparator());
				}
			}
		} finally {
			if (f != null) {
				f.close();
			}
		}
	}
	
	public static void main(String[] args) {
		String name = "hej.txt";
		if (args.length > 0) {
			name = args[0];
		}
		
		System.out.printf("Writing to %s%n", name);
		try {
			writeLines(name);
		} catch(IOException e) {
			System.err.printf("Failed with: %s%n", e);
		}
	}

}
