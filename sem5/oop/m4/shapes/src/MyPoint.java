
public class MyPoint {
	private double x, y;
	
	public MyPoint(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	public double getX() {
		return this.x;
	}
	public double getY() {
		return this.y;
	}
	
	/**
	 * Subtracts two vectors, thus returning the difference.
	 * @param b point to subtract from this.
	 * @return returns a MyPoint which is actually a vector
	 */
	public MyPoint sub(MyPoint b) {
		// This is actually a vector and not a point
		return new MyPoint(this.getX() - b.getX(), this.getY() - b.getY());
	}
	/**
	 * Returns a new MyVector with positive components
	 */
	public MyPoint abs() {
		return new MyPoint(Math.abs(this.getX()), Math.abs(this.getY()));
	}

	/**
	 * Calculates the length of MyPoint as if it was a vector.
	 * @return
	 */
	public double modulo() {
		return Math.sqrt(this.getX() * this.getX() + this.getY() * this.getY());
	}
	
	public String toString() {
		return String.format("[%f, %f]", this.getX(), this.getY());
	}
}
