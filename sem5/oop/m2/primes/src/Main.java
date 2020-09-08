
public class Main {

	public static void main(String[] args) {
		System.out.println("Lets find some primes!!");
		
		int runto = 10000;
		if (args.length > 0) {
			runto = Integer.parseInt(args[0]);
		}
		
		// Calculate length of runto as string
		int numlen = String.valueOf(runto).length();
		
		PrimeGen pg = new PrimeGen();
		
		int p;
		int index = 1;
		while ((p = pg.next(runto)) != -1) {
			// Terrible two level format
			System.out.printf(String.format("%%-%dd ", numlen), p);
			if (index % 10 == 0) {
				System.out.print(System.lineSeparator());
			}
			index++;
		}
		System.out.print(System.lineSeparator());
		System.out.printf("Found %d primes%n", index-1);

	}

}
