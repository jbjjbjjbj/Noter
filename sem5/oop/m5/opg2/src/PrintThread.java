public class PrintThread extends Thread {
	private int sleepTime;
   
	public PrintThread(String id )
		{
		super(id);
	   	sleepTime = (int) ( Math.random() * 5000 );
	   	System.out.println( "Name: " + getName() +" Sleep: " + sleepTime );
	  }
	  
	public void run()
		{
			try {
				sleep( sleepTime );
				}
			catch ( InterruptedException exception ) {}
		System.out.println( "Thread " + getName() );
   }

}