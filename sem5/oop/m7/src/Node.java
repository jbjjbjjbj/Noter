import java.net.InetAddress;
import java.net.UnknownHostException;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.Semaphore;

import java.io.OutputStream;
import java.io.ObjectInputStream;
import java.io.InputStream;

class NodeAddr {
	public int port;
	public InetAddress addr;

	public NodeAddr(String addr, int port) throws UnknownHostException {
		this.port = port;
		this.addr = InetAddress.getByName(addr);
	}

	public NodeAddr(String fulladdr) throws UnknownHostException {
		String fields[] = fulladdr.split(":");
		this.port = Integer.parseInt(fields[1]);
		this.addr = InetAddress.getByName(fields[0]);
	}
}

public class Node {
	private NodeAddr bind;
	private ArrayList<NodeAddr> neighbors;

	private HashSet<String> seenMsgs;
	private Semaphore lock;

	public String name;

	public Node(String bind, String name) throws UnknownHostException {
		this.bind = new NodeAddr(bind);
		this.neighbors = new ArrayList<>();
		this.name = name;
		this.seenMsgs = new HashSet<>();
		this.lock = new Semaphore(1);
	}
	
	public void addNeighbor(String addr) throws UnknownHostException {
		this.neighbors.add(new NodeAddr(addr));
	}

	public void start() throws IOException {
		ServerSocket socket = null;
		try {
			socket = new ServerSocket(this.bind.port, 50, this.bind.addr);

			while (true) {
				Socket conn = socket.accept();
				Handler h = new Handler(conn, this);
				h.start();
			}
		} finally {
			if (socket != null) {
				socket.close();
			}
		}
	}
	
	public void sendMsgLocal(Message msg) throws Exception {
		// Kind of hacky but thats how we do it
		msg.id = ThreadLocalRandom.current().nextInt();
		
		if (!this.checkMsg(msg)) {
			this.sendMsg(msg);
		}
	}
	
	private boolean checkMsg(Message msg) throws InterruptedException {
		String msgid = String.format("%s%d", msg.from, msg.id);
		this.lock.acquire();

		if (this.seenMsgs.contains(msgid)) {
			this.lock.release();
			return true;
		}
		this.seenMsgs.add(msgid);
		this.lock.release();
		return false;
	}

	private void sendMsg(Message msg) throws Exception {
		for (NodeAddr n : this.neighbors) {
			Socket conn = null;
			OutputStream out = null;
			try {
				conn = new Socket(n.addr, n.port);
				out = conn.getOutputStream();

				msg.send(out);

			} finally {
				if (conn != null) {
					conn.close();
				}
				if (out != null) {
					out.close();
				}
			}
		}
	}
	
	public void handleMsg(Message msg) throws Exception {
		if (this.checkMsg(msg)) {
			return;
		}
		if (!msg.to.equals(this.name)) {
			msg.trace(this.name);

			// Forward
			this.sendMsg(msg);
			
			if (!msg.to.equals("")) {
				return;
			}
		}
		
		msg.handle(this);
	}
}

class Handler extends Thread {
	private Socket conn;
	private Node node;

	public Handler(Socket conn, Node node) {
		this.conn = conn;
		this.node = node;
	}

	public void run() {
		InputStream in = null;
		ObjectInputStream objin = null;
		try {
			in = this.conn.getInputStream();
			objin = new ObjectInputStream(in);
			Object obj = objin.readObject();
			if (!(obj instanceof Message)) {
				throw new Exception("Received object is not a message");
			}
			this.node.handleMsg((Message) obj);
		} catch (Exception e) {
			System.err.printf("Client err: %s%n", e);
		}
	}
}