import java.io.Serializable;
import java.util.ArrayList;

public class PingMessage extends Message implements Serializable {
	private boolean is_response;
	private boolean do_trace;
	public ArrayList<String> trace;

	public PingMessage(String from, String to, boolean trace) {
		super(from, to);
		this.is_response = false;
		this.do_trace = trace;
		if (trace) {
			this.trace = new ArrayList<>();
		}
	}
	
	public void trace(String node) {
		if (!this.do_trace || this.is_response) {
			return;
		}
		System.out.println("DOING TRACE");
		
		this.trace.add(node);
	}
	
	public void handle(Node node) throws Exception {
		if (this.is_response) {
			System.out.printf("%s >> Ping response%n", this.from);
			if (this.do_trace) {
				System.out.print("  Trace: ");
				for (String t : this.trace) {
					System.out.printf("%s -> ", t);
				}
				System.out.print(System.lineSeparator());
			}
			return;
		}

		this.is_response = true;
		this.to = this.from;
		this.from = node.name;
		
		node.sendMsgLocal(this);
	}
}
