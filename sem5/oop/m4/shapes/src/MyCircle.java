
public class MyCircle implements Shape2d {
	private MyPoint center;
	private double r;
	
	/**
	 * Creates a 2d circle object 
	 * 
	 * @param center Center of the circle
	 * @param r Radius of the circle
	 */
	public MyCircle(MyPoint center, double r) {
		this.center = center;
		this.r = Math.abs(r);
	}
	
	public double area() {
		return Math.PI * this.r * this.r;
	}
	
	public double perimeter() {
		return 2 * this.r * Math.PI;
	}
}
