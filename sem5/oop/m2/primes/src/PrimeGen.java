import java.io.PrintStream;
import java.util.ArrayList;

public class PrimeGen {
	
	private ArrayList<Integer> primes;
	private int at;

	public PrimeGen() {
		this.primes = new ArrayList<>();
		
		this.at = 1;
	}
	
	public int next(int limit) {
		// Run until a prime
		primeloop:
		while (true) {
			this.at++;
			if (this.at >= limit) {
				return -1;
			}

			for (int prime : this.primes) {
				if (this.at % prime == 0) {
					continue primeloop;
				}
			}
			break;
		}
	
		this.primes.add(at);
		return at;
	}
	
	public int next() {
		return next(-1);
	}
	
}
