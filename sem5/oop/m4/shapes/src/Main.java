import java.util.ArrayList;

public class Main {

	public static void main(String[] args) {
		System.out.println("Doing the stuff.");
		
		ArrayList<Shape2d> shp = new ArrayList<>();

		shp.add(new MyCircle(new MyPoint(3, 4), 10));
		shp.add(new MyTriangle(
				new MyPoint(0, 0), 
				new MyPoint(4, 5), 
				new MyPoint(23, 4)));
		shp.add(new MyRectangle(new MyPoint(0, 3), new MyPoint(-10, 10)));
		
		
		for (Shape2d s : shp) {
			System.out.printf("area: %f, p: %f%n", s.area(), s.perimeter());
		}
	}

}
