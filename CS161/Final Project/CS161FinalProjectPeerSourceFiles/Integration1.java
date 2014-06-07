 /******************************************************
** Program: Integration1.java
** Author: One of your peers
** Date: Jul 15 2012
** Description:  Finds the area under a curve.
** Input: Starting and ending points for the area, which shape, number of rectangles to use
** Output:
******************************************************/

import java.util.Scanner;


public class Integration1 {


	public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        double shape,n,x,x2,a,b,b1,b2,width,height,area,hold; //initialization of variables
		double rectangleTotalArea = 0;
		double trapezoidTotalArea = 0;
		
		boolean run = true;

		while (run) {
	    	System.out.println("Which shape?\nAvailable options:\n[1] rectangle\n[2] trapezoid\n[3] both");
	    	shape = scan.nextInt();
	    	if (shape == 3) {
	    		System.out.println("Please enter values for the rectangle calculation:");
	    	}
	    	System.out.println("How many?");
	    	n = scan.nextInt();
	    	System.out.println("Starting X Value");
	    	a = scan.nextInt();
	    	System.out.println("Ending X Value");
	    	b = scan.nextInt();
	    	
	    	if (a < b) { // make sure that a is smaller than b
	    		hold = a;
	    		a = b;
	    		b = hold;
	    	}
	    	
	    	width = b - a;
	    	width /= n; //calculate width
	
	
	    	if (shape == 1 || shape == 3) {
				// rectangle
				width=(b-a)/n;
		    	for ( double i = a ; i < b ; i++ ) {
					x = a+i*width;
					height = (Math.pow(x,2) * 2);
					area = height * width;
					rectangleTotalArea += area;
		    	}
	    	}
	    	
	    	if (shape == 3) {
	    		System.out.println("Rectangle calculated, please enter values for the trapezoid calculation:");
	        	System.out.println("How many?");
	        	n = scan.nextInt();
	        	System.out.println("Starting X Value");
	        	a = scan.nextInt();
	        	System.out.println("Ending X Value");
	        	b = scan.nextInt();
	    	}
	    	
	    	if (a < b) { // make sure that a is smaller than b
	    		hold = a;
	    		a = b;
	    		b = hold;
	    	}
				
	    	if (shape == 2 || shape == 3) {
				// trapezoid
		    	for ( double i = a + 1 ; i < b ; i++ ) {
					x = a+i*width;
					x2 = (a-1)+i*width;
					b1 = Math.pow(x,2) * 2;
					b2 = Math.pow(x2,2) * 2; 
					height = (b1+b2)/2; 
					area = height* width;  
					trapezoidTotalArea += area;
		    	}
	    	}
	    	if (shape == 1 || shape == 3) {
	    		System.out.println("Total area under curve (rectangle): " + rectangleTotalArea);
	    	}
	    	if (shape == 2 || shape == 3) {
	    		System.out.println("Total area under curve (trapezoid): " + trapezoidTotalArea);
	    	}
	    	
	    	
        	System.out.println("Would you like to do another calculation? (valid options are 'y' and 'n', case doesn't matter)");
        	String cont = scan.next();

        	if (cont.equals("y") || cont.equals("Y")) {
        		run = true;
        	} else if (cont.equals("n") || cont.equals("N")) {
        		run = false;
        	} 		
        }
    	
		
	}
}