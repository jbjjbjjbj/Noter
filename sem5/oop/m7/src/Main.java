public class Main {

	public static void main(String[] args) {
		System.out.println("YEAH LETS GO");

		try {
			Node n = new Node(args[0], args[1]);
			InputHandler h = new InputHandler(n);
			for (int i = 2; i < args.length; i++) {
				n.addNeighbor(args[i]);
			}
			
			h.start();
			n.start();
		} catch (Exception e) {
			System.err.printf("Fatal err: %s%n", e);
		}
	}

}