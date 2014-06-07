public class TestCircleRectangle {
	public static void main(String[] args) {

		Circle circle = new Circle(1);
		System.out.println("A circle " + circle.toString());
		System.out.println("The radius is " + circle.getRadius());
		System.out.println("The area is " + circle.getArea(1));
		System.out.println("The circumference is" + circle.getPerimeter());
		System.out.println("The diameter is " + circle.getDiameter());
		System.out.println("Setting the color to red... ");
		circle.setColor("red");
		System.out.println("A circle " + circle.toString());
		
		Rectangle rectangle = new Rectangle(2, 4);
		System.out.println("\nA rectangle " + rectangle.toString());
		System.out.println("The area is " + rectangle.getArea());
		System.out.println("The perimeter is " + rectangle.getPerimeter());
		rectangle.setHeight(8);  rectangle.setWidth(10);
		System.out.println("A rectangle " + rectangle.toString());
		System.out.println("The area is " + rectangle.getArea());
		System.out.println("The perimeter is " + rectangle.getPerimeter());


	}
}
