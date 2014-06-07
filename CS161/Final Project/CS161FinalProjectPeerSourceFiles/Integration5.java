
/******************************************************
** Program: Integration5.java
** Author: One of your peers
** Date: July 15, 2012
** Description:  This program finds the Area Under a Curve 
** using the area of rectangles or trapezoids or both.  Based
** on the inputs from the user.
** Input: Which shape they want to use, the starting point,
** the ending point, how many shapes to use and whether they
** want to continue.
** Output: The function being used, the starting and ending
** points entered by the user, the number of rectangles,
** Trapezoids used and the area of each.
******************************************************/


import java.util.Scanner;

public class Integration5 {

	/**
	 * @param args
	 */
	
	public static void main(String[] args) {
		boolean m;
		System.out.println("Would like to find the Area under a" +
				" Curve?");
		while (true){
		float a =0;
		float b =0;
		float w =0;
		float h =0;
		float h1 =0;
		float h2 =0;
		int n = 0;
		int n1 =0;
		int i;
		int c;
		float Area;
		float curve =0;
		float curve1=0;
		
		Scanner input = new Scanner(System.in);
		
		
		
			
		System.out.print("To use Rectangles enter(1), Trapezoids" +
				" enter(2) or both enter(3) ");
		
		while(!(input.hasNextInt())){ //Error Checking for number only
			input.next();
			System.out.println("That's not a number, try again");
			System.out.print("To use Rectangles enter(1), Trapezoids" +
					" enter(2) or both enter(3) ");
		}
		c = input.nextInt();
		
		if(c<3){  //Error checking for entry values
		System.out.print("Please enter a starting x value ");
			while(!(input.hasNextFloat())){
				input.next();
				System.out.println("That's not a number, try again");
				System.out.print("Please enter a starting x value ");
			}
			a = input.nextFloat();
		
		System.out.print("Please enter an ending x value ");
			while(!(input.hasNextFloat())){
				input.next();
				System.out.println("That's not a number, try again");
				System.out.print("Please enter an ending x value ");
				}
			b = input.nextFloat();
			
			while(a >b){
				System.out.print("Please re-enter a beginning x value ");
				a=input.nextFloat();
				System.out.print("Please re-enter an ending x value ");
				b=input.nextFloat();
		}
			while(a<0 || b <0){
				System.out.print("Re-enter your starting x value ");
				a=input.nextFloat();
				System.out.print("Re-enter your ending x value ");
				b=input.nextFloat();
		}
		
		if(c==1){
			System.out.print("Please enter the number of" +
					" Rectangles you would like to use ");
				while(!(input.hasNextInt())){
					input.next();
					System.out.println("That's not a number, try again");
					System.out.print("Please enter the number of" +
							" Rectangles you would like to use ");
				}
				n = input.nextInt();
			
				while(n==0){
					System.out.println("In correct choice you can't divide by" +
							" 0.");
					System.out.print("Please re-enter the number of " +
							"rectangles you wish to use ");
					n=input.nextInt();
			}
		// The Calculations for the rectangle area.		
		float g = a;
		w = (b-a)/n;
		for(i = 1; i <= n; i++){
		
			h = 2 * (float) Math.pow(a,2);
			Area = w * h;
			a = a + w;
			curve = Area + curve;

	}	// Rectangle output.
		System.out.println("The Function being evaluated" +
				" is f(x)=2x^2.");
		System.out.println("The starting integral point is " + g 
				+ " and the ending integral point is " + b +".");
		System.out.println("The number of Rectangles used" +
				" was " + n + ".");
		System.out.println("The Area for the Trapezoid" +
				" method is " + curve +".");
		}
		
		if(c==2){
			System.out.print("Please enter the number of" +
					" Trapezoids you would like to use ");
				while(!(input.hasNextInt())){
					input.next();
					System.out.println("That's not a number, try again");
					System.out.print("Please enter the number of" +
							" Trapezoids you would like to use ");
				}
				n = input.nextInt();
			
				while(n==0){
					System.out.println("In correct choice you can't divide by" +
							" 0.");
					System.out.print("Please re-enter the number of " +
							"Trapezoids you wish to use ");
					n=input.nextInt();
			}
			// The Calculations for Trapezoid area.	
			float k=a;
			w = (b-a)/n;
			for(i = 1; i <=n; i++){
			
			h1 = 2 * (float) Math.pow(a,2);
			a = a + w;
			h2 = 2 * (float) Math.pow(a,2);
			h= (h1 + h2)/2;
			Area = w * h;
			curve = Area + curve;
		}
			// Trapezoid output.
			System.out.println("The Function being evaluated" +
					" is f(x)=2x^2.");
			System.out.println("The starting integral point is " + k 
					+ " and the ending integral point is " + b +".");
			System.out.println("The number of Trapezoids used" +
					" was " + n +".");
			System.out.println("The Area for the Trapezoid" +
					" method is " + curve +".");
		}
		
		}
		if(c==3){//Error Checking for x inputs using both shapes
			System.out.print("Please enter a starting x value ");
				while(!(input.hasNextFloat())){
					input.next();
					System.out.println("That's not a number, try again");
					System.out.print("Please enter a starting x value ");
					}
				a=input.nextFloat();
			
			System.out.print("Please enter an ending x value ");
				while(!(input.hasNextFloat())){
					input.next();
					System.out.println("That's not a number, try again");
					System.out.print("Please enter an ending x value ");
					}
				b = input.nextFloat();
			
			System.out.print("Please enter the number of" +
					" Rectangles you would like to use ");
				while(!(input.hasNextInt())){
					input.next();
					System.out.println("That's not a number, try again");
					System.out.print("Please enter the number of" +
							" Rectangles you would like to use ");
				}
				n=input.nextInt();
			
			System.out.print("Please enter the number of" +
					" Trapezoids you would like to use ");
			
				while(!(input.hasNextInt())){
					input.next();
					System.out.println("That's not a number, try again");
					System.out.print("Please enter the number of" +
							" Trapezoids you would like to use ");
				}
				n1 = input.nextInt();
			
				while(a >b){
					System.out.print("Please re-enter a beginning x value ");
					a=input.nextFloat();
					System.out.print("Please re-enter an ending x value ");
					b=input.nextFloat();
			}
				while(a<0 || b <0){
					System.out.print("Re-enter your starting x value ");
					a=input.nextFloat();
					System.out.print("Re-enter your ending x value ");
					b=input.nextFloat();
			}
				while(n==0){
					System.out.println("In correct choice you can't divide by" +
							" 0.");
					System.out.print("Please re-enter the number of " +
							"rectangles you wish to use ");
					n=input.nextInt();
				}
				while(n1==0){
					System.out.println("In correct choice you can't divide by" +
							" 0.");
					System.out.print("Please re-enter the number of " +
							"Trapezoids you wish to use ");
					n1=input.nextInt();
				}
			//Calculations for the Rectangle area.
			float d = a;
			float e = b;
			float t = a;
			
			w = (b-a)/n;
			for(i = 1; i <= n; i++){
			
				h = 2 * (float) Math.pow(a,2);
				Area = w * h;
				a = a + w;
				curve = Area + curve;
			}			
			//Calculations for the Trapezoid area.
			int j;
			w = (e-d)/n1;
			for(j = 1; j <=n1; j++){
			
			h1 = 2 * (float) Math.pow(d,2);
			d = d + w;
			h2 = 2 * (float) Math.pow(d,2);
			h= (h1 + h2)/2;
			Area = w * h;
			curve1 = Area + curve1;
		}
		//Rectangle and Trapezoid output.
		System.out.println("The Function being evaluated" +
				" is f(x)=2x^2.");
		System.out.println("The starting integral point is " + t 
				+ " and the ending integral point is " + b + ".");
		System.out.println("The number of Rectangles used" +
				" was " + n +".");
		System.out.println("The number of Trapezoids used" +
				" was " +n1 +".");
		System.out.println("The Area for the Rectangles" +
				" method is " + curve +".");
		System.out.println("The Area for the Trapezoid" +
				" method is " + curve1 +".");
		}
		//Continuation loop
		System.out.println("Would you like to continue to find" +
				" the Area under a Curve?");
		System.out.print("Enter Y or N ");
		String in1 = input.next();
		
		while(!(in1.equalsIgnoreCase(null))){
			
			if (in1.equalsIgnoreCase("N")){
				return;	
			}	
			if (in1.equalsIgnoreCase("Y")){
				m = true;
				break;
			}
			
			System.out.print("Please enter Y or N ");	
			in1 = input.next();
		}
		}	
}		
}

