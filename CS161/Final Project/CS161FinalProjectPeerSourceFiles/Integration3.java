 /******************************************************
** Program: Integration3.java
** Author: One of your peers
** Date: 7/15/2012
** Description:  Calculates the area under the function of f(x)=2(x^2) either by rectangles and/or trapezoids depending on the users preference
** Input: Starting point for area, Ending point for area, Method of calculating area, # of rectangles and/or trapezoids
** Output:  Function used, starting and ending points, # of rectangles and/or trapezoids, area calculated by chosen method(s)
******************************************************/

import java.util.*;

public class Integration3 
{

	public static void main(String[] args)
	{

		Scanner input = new Scanner(System.in);
		
		// Declaring Variables
		String KeepGoing="y";
		double UserStart;
		double UserEnd;
		double RectArea;
		double TrapArea;
		int NumberRect;
		int NumberTrap;
		double base1;
		double base2;
		double height;
		double width;
		int UserSelect;
		double count;
		
		do  // Loop while user wants to perform a calculation
		{
			//Set variables to 0.
			UserStart=0.0;
			UserEnd=0.0;
			RectArea=0.0;
			TrapArea=0.0;
			NumberRect=0;
			NumberTrap=0;
			base1=0.0;
			base2=0.0;
			UserSelect=0;
			width=0.0;
			
			// Ask user for calculation method
			System.out.println("How would you like to calculate the area under f(x)=2(x^2):");
			System.out.println("[1] - Rectangle");
			System.out.println("[2] - Trapezoid");
			System.out.println("[0] - Both");
			
			// Get user input for method of area calculation
			while(true)
			{
				try {
					UserSelect=input.nextInt();
					
					if (UserSelect != 0 && UserSelect != 1 && UserSelect != 2)
						throw new InputMismatchException();
					break;
				}
				catch (InputMismatchException ex) {
					System.out.print("Please choose only 0, 1, or 2: ");
					input.next();
				}
			}
			
			// Get user input for starting point for calculation
			System.out.print("Where would you like to start (choose a number not less than 0): ");
			
			while(true)
			{
				try {
					UserStart=input.nextDouble();
					
					if (UserStart < 0)
						throw new InputMismatchException();
					break;
				}
				catch (InputMismatchException ex) {
					System.out.print("Please choose a number not less than 0: ");
					input.next();
				}
			}
			
			// Get user input for ending point for calculation
			System.out.print("Where would you like to end (choose a number more than the starting point): ");
			
			while(true)
			{
				try {
					UserEnd=input.nextDouble();
					
					if (UserEnd <= UserStart)
						throw new InputMismatchException();
					break;
				}
				catch (InputMismatchException ex) {
					System.out.print("Please choose a number more than the starting point: ");
					input.next();
				}
			}
			
			// Calculate the area by rectangles if the user requested
			if (UserSelect==0 || UserSelect==1) {
				
				System.out.print("How many rectangles would you like to use for the calculation (integer): ");
				
				while(true) {
					
					try {
						NumberRect=input.nextInt();
						
						if (NumberRect < 1)
							throw new InputMismatchException();
						break;
					}
					catch (InputMismatchException ex) {
						System.out.print("Please choose a integer number not less than 1 and not more than " + Integer.MAX_VALUE + ": ");
						input.next();
					}
				}
				
				width=(UserEnd-UserStart)/(double) (NumberRect);
				height=0.0;
				
				// Looping through all of the rectangles
				for (count=UserStart; count < UserEnd;count=count+width) {
					height=2 * count * count;
					RectArea=RectArea + (width*height);
				}
							
			}
			
			// Calculate the area by trapezoids if the user requested
			if (UserSelect==0 || UserSelect==2) {
				System.out.print("How many trapezoids would you like to use for the calculation (integer): ");
					
				while(true) {
					
					try {
						NumberTrap=input.nextInt();
						
						if (NumberTrap < 1)
							throw new InputMismatchException();
						break;
					}
					catch (InputMismatchException ex) {
						System.out.print("Please choose a integer number not less than 1 and not more than " + Integer.MAX_VALUE + ": ");
						input.next();
					}
				}
				
				width=(UserEnd-UserStart)/(double) (NumberTrap);
				height=0.0;
					
				// Looping through all of the trapezoids
				for (count=UserStart; count < UserEnd; count=count+width) {
					base1=2 * count * count;
					base2=2 * count * (count+width);
					height=(base1 + base2)/2.0;
					TrapArea=TrapArea + (width*height);					
				}
			}
				
			// Output Results
			System.out.println();
			System.out.println("The area for the function f(x)=2(x^2) with a starting point of " + UserStart + " and " + UserEnd + " and bounded by the x-axis is as follows:");
			
			if (RectArea>0)
				System.out.println("The area calculated by using " + NumberRect + " rectangles is " + RectArea + ".");
			if (TrapArea>0)
				System.out.println("The area calculated by using " + NumberTrap + " trapezoids is " + TrapArea + ".");
				
			// Ask user if they would like to do another calculation
			System.out.print("Would you like to do another calculation (y/n)? ");
			
			while(true) {
				
				try {
					KeepGoing=input.next();
					
					if ((KeepGoing.compareTo("y")==0) || (KeepGoing.compareTo("n")==0))
						break;
					else
						throw new InputMismatchException();
				}
				catch (InputMismatchException ex) {
					System.out.print("Please choose either y or n: ");
					input.next();
				}
			}
					
		} while (KeepGoing.compareTo("y")==0 );
		
	}

}
