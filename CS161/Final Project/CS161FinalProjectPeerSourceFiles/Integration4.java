/******************************************************
 **     Program:  Integration4.java
 **      Author:  One of your peers - OSU CS161-Unit3
 **        Date:  Jul 15, 2012
 ** Description:  A programming exercise:
 **  calculates area of function 2x^2 by 
 **  either rect, trap, or both methods  
 **  Input:  start/end pts, method(s), # of rect/trap,
 **			 continue?
 ** Output:  area under function for method(s) selected
 *******************************************************/

	import java.util.Scanner;
	import java.util.InputMismatchException;
	
	public class Integration4 {

	    public static void main(String[] args) {
	    	//declare variables
	        int		xChoice, nRect=0, nTrap=0;
	        double	x1=0, x2=0, xAval=0, xBval=0, xWidth=0, xHeight=0, rectArea=0, trapArea=0;
	        boolean bWantsContinue = true, bBadData = true, bBadAnswer = false, doRect, doTrap; 
	        String	xYorN = null, strRectOutput, strTrapOutput;
	        
	        Scanner input = new Scanner(System.in);
	        
	        //print header
	        System.out.print("CALCULATING THE AREA UNDER A FUNCTION\n-------------------------------------\n");
	  
			while (bWantsContinue) //loop until user no longer wants to continue (set at bottom of loop)
			{
				//reset variables, since we're possibly looping thru again
				rectArea=0;
				trapArea=0;
				strRectOutput = "";
				strTrapOutput = "";
				
				//print greeting
				System.out.print("\nIn order to calculate the area under the function f(x)=2x^2, we need some information." +
						"\n\nFirst, the start and end points on the x axis.");
		        
				//get start point input
				bBadData = true;
				while (bBadData) //loop until user provides useable data
				{
					try { //get start point, checking for values less than zero and non-numbers
						System.out.print("\nStart point?: ");
						xAval =  input.nextDouble();
						if (xAval < 0) throw new ArithmeticException("Please enter a positive value.");
						bBadData = false;
					} catch (ArithmeticException ex) {
						System.out.println(ex.getMessage());
					} catch (InputMismatchException ex) {
						System.out.println("Please enter a number.");
						input.next(); //clear scanner of bad data
					}
				}

				//get end point input
				bBadData = true;
				while (bBadData) //loop until user provides useable data
				{
					try { //get end point, checking for values less than zero and non-numbers
						System.out.print("End point?: ");
						xBval =  input.nextDouble();
						if (xBval <= 0) throw new ArithmeticException("Please enter a positive value.");
						if (xBval <= xAval) throw new ArithmeticException("The end point value must be higher than the start point value (which was " + xAval + ")");
						bBadData = false;
					} catch (ArithmeticException ex) {
						System.out.println(ex.getMessage());
					} catch (InputMismatchException ex) {
						System.out.println("Please enter a number.");
						input.next(); //clear scanner of bad data
					}
				}
		        
				
				//get method(s) of calculation input
				bBadData = true;
				doRect = false; //reset variables
				doTrap = false;
				while (bBadData) //loop until user provides useable data
				{
					try { //get method(s) of calculation using numbered menu choices, checking for bad inputs (non-numbers, <1, >3)
						System.out.print("\nWhich method(s) would you like to use to calculate the area?  Enter a number from the menu below.\n" +
								"[ 1 ] Rectangles\n[ 2 ] Trapezoids\n[ 3 ] Both\n\nSelection: ");
						xChoice = input.nextInt();
						if ((xChoice < 1)|(xChoice > 3)) throw new ArithmeticException("Please enter 1, 2, or 3.");
						bBadData = false;
						switch (xChoice) //depending on menu choice, set our doRect/doTrap flags so we know which calcs to do later
						{
						case 1: 
							{
								doRect = true;
								break;
							}
						case 2: 
							{
								doTrap = true ;
								break;
							}
						case 3: 
							{
								doRect = true;
								doTrap = true ;
								break;
							}
						}
						
					} catch (ArithmeticException ex) {
						System.out.println(ex.getMessage());
					} catch (InputMismatchException ex) {
						System.out.println("Please enter 1, 2, or 3.");
						input.next(); //clear scanner of bad data
					}
				}
				
				
				if (doRect) //if user chose rectangle method, do it
				{
					bBadData = true;
					while (bBadData) //loop until user provides useable data
					{
						try { //get rectangle #, checking for bad input (<=0, non-integer)
							System.out.print("\nHow many rectangles should we use to calculate the area?: ");
							nRect =  input.nextInt();
							if (nRect <= 0) throw new ArithmeticException("Please enter a value greater than zero.");
							bBadData = false;
						} catch (ArithmeticException ex) {
							System.out.println(ex.getMessage());
						} catch (InputMismatchException ex) {
							System.out.println("Please enter a whole number.");
							input.next(); //clear scanner of bad data
						}
					}
					
					//calculate area under function using rectangles
					xWidth = ((xBval - xAval)/nRect); //width of each rectangle
					for (int i = nRect; i != 0; --i) { 	//for each rectangle...
						x1 = xAval + ((i-1)*xWidth);	// calc x value 
						xHeight = 2 * (Math.pow(x1, 2));// calc f(x)
						rectArea += xWidth * xHeight;	// add area of rectangle to running total
					}
					
					//round running total rectArea to three decimal places
					rectArea = (double)(Math.round(rectArea*1000))/1000;
					//set our output string for later
					strRectOutput = ("\n The area calculated using " + nRect + " rectangles is: " + rectArea);
				}
				
				
				if (doTrap) //if user chose trapezoid method, do it
				{
					bBadData = true;
					while (bBadData) //loop until user provides useable data
					{
						try { //get trapezoid #, checking for bad input (<=0, non-integer)
							System.out.print("\nHow many trapezoids should we use to calculate the area?: ");
							nTrap =  input.nextInt();
							if (nTrap <= 0) throw new ArithmeticException("Please enter a value greater than zero.");
							bBadData = false;
						} catch (ArithmeticException ex) {
							System.out.println(ex.getMessage());
						} catch (InputMismatchException ex) {
							System.out.println("Please enter a whole number.");
							input.next(); //clear scanner of bad data
						}
					}
					
					//calculate area under function using trapezoids
					xWidth = ((xBval - xAval)/nTrap); //width of each rectangle
					for (int i = nTrap; i != 0; --i) { 	//for each rectangle...
						x1 = xAval + ((i-1)*xWidth);	// calc x value for short base of trapezoid
						x2 = xAval + ((i)*xWidth);		// calc x value for long base of trapezoid
						xHeight = ( ((2 * (Math.pow(x1, 2))) + (2 * (Math.pow(x2, 2)))) / 2 ) ; //calc f(x) for each base, take average
						trapArea += xWidth * xHeight;	// add area of trapezoid to running total
					}
					
					//round running total trapArea to three decimal places
					trapArea = (double)(Math.round(trapArea*1000))/1000;
					//set our output string for later
					strTrapOutput = ("\n The area calculated using " + nTrap + " trapezoids is: " + trapArea);
				}
				
				//print results
				System.out.print("\nRESULTS:" +
						"\n Evaluated function: f(x)=2x^2" +
						"\n Start point on x axis: " + xAval +
						"\n End point on x axis: " + xBval + 
						strRectOutput + strTrapOutput + "\n\n"); //print both output strings - any unused method will have blank output string
				
				
				do { //loop until user indicates Y(es) or N(o) to continue question
					bBadAnswer = true;
					System.out.print("\nWould you like to continue with another calculation? (Y or N):\t");
					xYorN = input.next(); //get string input
					if ((xYorN.equalsIgnoreCase("Y")) | (xYorN.equalsIgnoreCase("YES"))) //if user types Y or YES
					{
						System.out.println("\nOk! - - - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
						bBadAnswer = false;		//user entered good input
						bWantsContinue = true;	//continue w/ another loop
					}
					else if ((xYorN.equalsIgnoreCase("N")) | (xYorN.equalsIgnoreCase("NO"))) //if user types N or NO
					{
						System.out.print("\nGoodbye!\n\n\n"); 
						bWantsContinue = false; //do not continue (don't really need this, given return below, but here for clarity)
						bBadAnswer = false;		//user entered good input (again, don't really need, but here for clarity)
						return;					//quit
					}
					else 
					{
						System.out.print("\nI didn't understand your answer.\n");
						bBadAnswer = true; //user entered bad input
					}
				} while (bBadAnswer); //loop if user entered bad input
				
				
			} //end of main while - loops if user wants to continue (checked at top of while loop)
				
		
		} // end main

	} // end class