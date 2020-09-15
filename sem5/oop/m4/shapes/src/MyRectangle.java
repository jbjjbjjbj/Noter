
public class MyRectangle implements Shape2d{
	private MyPoint a, b;
	
	/**
	 * Creates a new rectangle where a, b are opposing corners.
	 */
	public MyRectangle(MyPoint a, MyPoint b) {
		this.a = a;
		this.b = b;
	}
	
	public double area() {
		MyPoint size = this.b.sub(this.a);
		return Math.abs(size.getX() * size.getY());
	}
	
	public double perimeter() {
		MyPoint size = this.b.sub(this.a).abs();
		return size.getX() * 2 + size.getY() * 2;
	}
}
