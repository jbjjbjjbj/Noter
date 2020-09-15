
public class MyTriangle implements Shape2d {
	private MyPoint a, b, c;
	
	/**
	 * Creates a new triangle with the 3 corners a, b, c
	 */
	public MyTriangle(MyPoint a, MyPoint b, MyPoint c) {
		this.a = a;
		this.b = b;
		this.c = c;
	}
	
	// https://www.mathopenref.com/coordtrianglearea.html
	public double area() {
		return Math.abs((
				this.a.getX() * (this.b.getY() - this.c.getY()) +
				this.b.getX() * (this.c.getY() - this.a.getY()) +
				this.c.getX() * (this.a.getY() - this.b.getY())) / 2);
	}
	
	public double perimeter() {
		// Calculate the length of the 3 lines between points
		double ab = b.sub(a).modulo();
		double bc = c.sub(b).modulo();
		double ca = a.sub(c).modulo();
		
		return ab + bc + ca;
	}
}
