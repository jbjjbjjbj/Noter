import java.io.OutputStream;
import java.io.ObjectOutputStream;
import java.io.IOException;
import java.io.Serializable;
import java.util.Random;

public class Message implements Serializable {
	public String from;
	// If too is empty it is for all
	public String to;
	public int id;
	
	public Message(String from, String to) {
		this.from = from;
		this.to = to;
	}
	
	public void send(OutputStream out) throws IOException{
		ObjectOutputStream objout = null;
		try {
			objout = new ObjectOutputStream(out);
			objout.writeObject(this);
		} finally {
			if (objout != null) {
				objout.close();
			}
		}
	}
	
	public void trace(String node) {}
	
	public void handle(Node n) throws Exception {}
}

