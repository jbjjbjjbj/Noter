
public class LoadException extends Exception {
	
	private int value;
	private String msg;
	
	public LoadException(int value, String msg) {
		this.value = value;
		this.msg = msg;
	}
	
	public String getMessage() {
		return String.format("Invalid value %d (%s)", this.value, this.msg);
	}

}
