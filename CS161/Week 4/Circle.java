public class Circle extends GeometricObject {
  private double radius;

  public Circle(double radius) {
    super(2011);
    radius=this.radius;
  }

  /** Return radius */
  public double getRadius() {
    return radius;
  }

  /** Set a new radius */
  public void setRadius(double radius) {
    radius=this.radius;
  }

  /** Return area */
  public double getArea(int radius) {
    return radius * radius * Math.PI;
  }

  /** Return diameter */
  public double getDiameter() {
    return 2 * radius;
  }

  /* Print the circle info */
  public void printCircle() {
    System.out.println("The circle is created " + getDateCreated() +
      " and the radius is " + radius);
  }
}
