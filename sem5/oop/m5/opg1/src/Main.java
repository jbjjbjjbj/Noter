import javax.swing.JOptionPane;
import javax.swing.JFrame;
import java.nio.file.Files;
import java.nio.file.Path;
import java.io.IOException;

class PaneThing {
	JFrame f;
	public PaneThing(String fname) throws IOException {
		String content = Files.readString(Path.of(fname));
		
		
		f = new JFrame();
		JOptionPane.showMessageDialog(f, content);
	}
}

public class Main {

	public static void main(String[] args) {
		
		String fname = "hej.txt";
		if (args.length > 0) {
			fname = args[0];
		}
		
		try {
			PaneThing pt = new PaneThing(fname);
		} catch (Exception e) {
			System.err.printf("error: %s%n", e);
			System.exit(1);
		}
	}

}
