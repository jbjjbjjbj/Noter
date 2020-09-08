import java.util.ArrayList;
import java.io.IOException;
import java.io.EOFException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.util.Scanner;
import java.io.PrintStream;

public class Lines {
	
	private ArrayList<int[]> lines;
	
	public Lines(String loadpath) throws IOException, LoadException {
		this.lines = new ArrayList<int[]>();
		FileReader f = null;
		BufferedReader buff = null;
		try {
			f = new FileReader(loadpath);
			buff = new BufferedReader(f);
			
			String line;
			while((line = buff.readLine()) != null) {
				this.readRow(line);
			}
			
		} finally {
			if (f != null) {
				f.close();
			}
		}
	}
	
	void readRow(String line) throws LoadException {
		// you are a pirate
		int[] arr = new int[10];
		

		int i;
		Scanner sc = null;
		try {
			sc = new Scanner(line);
			for (i = 0; i < 10; i++) {
				if (!sc.hasNextInt()) {
					break;
				}
				int n = sc.nextInt();
				// OPG 3
				if (n > 90) {
					throw new LoadException(n, "is above 90");
				}
				// OPG 4
				//a assert (n <= 90) : "is above 90";
				arr[i] = n;
			}
		} finally {
			sc.close();
		}
		if (i > 0) {
			lines.add(arr);
		}
	}
	
	public void print(PrintStream out) {
		for (int[] arr : this.lines) {
			for (int i : arr) {
				out.printf("%-3d ", i);
			}
			out.print(System.lineSeparator());
		}
	}
}
