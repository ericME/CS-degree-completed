/*********************
 *  Integration2.java
 *  One of your peers
 *  13 July 2012
 *  Description:	Using Riemann sums, the area under the curve for
 *  				2x^2 is found, given the users input for start 
 *  				point, end point, and number of subdivisions.
 *  				Left Hand Sum and Trapezoid methods are used.
 *  
 *  Input:			Start point, end point, number of subdivisions,
 *  				method for area, try again
 *  
 *  Output			The user's inputs, plus the area under the 
 *  				curve given the user's inputs.
 *
 */

import java.util.Scanner;
import java.text.*;  //http://www.gamedev.net/topic/390114-printing-a-double-to-2-decimal-places-in-java-14/
//post #3

public class Integration2 {


	public static void main(String[] args) {
		//variable declaration
		double a; //start point a
		double b; //endpoint b
		int n; //number subdivisions
		double w; //width, to be calc'd from a,b,n
		double area;
		int selection; //LHS, trapezoid, both
		String retrySelection;
		char retryChar;
		boolean startAgain=true;
		Scanner input = new Scanner(System.in);

		DecimalFormat decimals3 = new DecimalFormat("#.###");
		DecimalFormat decimals6 = new DecimalFormat("#.######");


		while(startAgain){//this encompasses everything and will be to end program
			area=0;

			System.out.println("This program will calculate the area under the curve");
			System.out.println("for the function f(x) = 2x^2 using reimann sums");
			System.out.println("Please choose a method selection");
			System.out.println("[1] Left Hand Sum");
			System.out.println("[2] Trapezoid");
			System.out.println("[3] Both");

			while(true){ //kicks out when selection is verified int and btwn 1 and 3
				while(!input.hasNextInt()){  //verify correct input

					System.out.println("Please choose a selection from the menu");	
					System.out.println("[1] Left Hand Sum");
					System.out.println("[2] Trapezoid");
					System.out.println("[3] Both");
					input.next();
				}

				selection = input.nextInt();
				if(selection > 0 && selection <4) break;
				else System.out.println("Please enter a valid selection.");
			}

			System.out.println("Please enter the starting point, a");
			while(!input.hasNextDouble()){  //verify correct input
				input.next();
				System.out.println("Please enter a decimal number only");	
			}
			a = input.nextDouble();

			System.out.println("Please enter the ending point, b");

			while(true){ //kicks out when b is verified double and bigger than a
				while(!input.hasNextDouble()){  //verify correct input

					System.out.println("Please enter a decimal number only");	
					input.next();
				}

				b=input.nextDouble();
				if(b>a) break;
				else System.out.println("Please enter a value larger than a");
			}

			System.out.println("Please enter the number of subdivisions, n");
			while(true){ //kicks out when n is verified int and bigger than 0
				while(!input.hasNextInt()){  //verify correct input

					System.out.println("Please enter a natural number only");	
					input.next();
				}

				n=input.nextInt();
				if(n>0) break;
				else System.out.println("Please enter a value larger than 0");
			}

			w=(b-a)/n; //calc width
			System.out.println(" ");
			System.out.println("Calculations are as follows:");
			System.out.println("The starting point 'a' is:       " + decimals3.format(a));
			System.out.println("The ending point 'b' is:         " + decimals3.format(b));
			System.out.println("The number of subdivions 'n' is: " + n);
			System.out.println("The width of each subdivions is: " + decimals6.format(w));
			System.out.println(" ");
			if(selection == 1 || selection==3){
				for(double i = a; i<(b-1e-10); i+=w){ //b-1*10^-10 to counteract bad rounding

					//System.out.println(i);
					area+= 2*(i*i)*w;
				}

				System.out.println("The area using a LHS is: " + decimals3.format(area));
			}

			if(selection == 2 || selection==3){
				area=0; //reset area just in case of both
				for(double i = a; i<(b-1e-10); i+=w){ //b-1*10^-10 to counteract bad rounding

					//System.out.println(i);
					area+= (((2*(i*i))+(2*(i+w)*(i+w)))/2)*w; //this (should) read: 
					//2*i*i + 2*(i+w)(i+w) all over 2 times w
				}

				System.out.println("The area using trapezoids is: " + decimals3.format(area));
			}
			
			retry: while(true){
				System.out.println("Do you wish to calculate another interval?");
				System.out.println("[Y]es or [N]o");
				retrySelection = input.next();
				retryChar = retrySelection.charAt(0);  //can't use switches and Strings together, so char conversion
				switch(retryChar){
				case 'y': case 'Y':
					break retry;

				case 'n': case 'N':
					startAgain = false;
					System.out.println("Program Terminated");
					break retry;

				default:
					System.out.println("You provided an improper entry.");
					
				}
			}

		}//end of main while loop



	}

}
