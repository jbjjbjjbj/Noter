import java.io.BufferedReader;
import java.io.InputStreamReader;

public class InputHandler extends Thread {
	private Node node;

	public InputHandler(Node node) {
		this.node = node;
	}
	
	public void run() {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		try {
			String line;
			while ((line = in.readLine()) != null) {
				char cmd = line.charAt(0);
				Message msg = null;
				if (cmd == '#' || cmd == '!') {
					msg = new PingMessage(this.node.name, line.substring(1), cmd == '!');
				} else {
					msg = new TextMessage(this.node.name, "", line);
				}
				this.node.sendMsgLocal(msg);
			}
		} catch (Exception e){
			System.err.printf("Send err: %s%n", e);
		}
	}
}
