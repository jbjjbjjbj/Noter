import java.io.Serializable;

public class TextMessage extends Message implements Serializable {
	private String msg;

	public TextMessage(String from, String to, String msg) {
		super(from, to);
		this.msg = msg;
	}
	
	public void handle(Node node) throws Exception {
		System.out.printf("%s >> %s%n", this.from, this.msg);
	}
}
