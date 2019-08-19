import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class FasterBSearch {

	public static int[] scantolst(String s,int cap) throws FileNotFoundException{  //simple scanner to read each line to a list
		Scanner scanner = new Scanner(new File(s));									//takes the file name as a string and the initial capacity of the list as an int
		int[] numlist = new int[cap];
		int count = 0;
		while(scanner.hasNextDouble()){

			numlist[count]= scanner.nextInt();
			count++;
		}
		scanner.close();
		return numlist;
	}

	public static boolean FSearch(int[] lst, int u){  //receives list to be searched and U value
		for(int i : lst){  //for each element in the list
			int x = (u-i);
			if(x<0){ //checking for array indexing purposes
				//System.out.println("The Integer: " + u + " cannot be summed by two elements present in the list.");
				return false;}
			if(BSearch(lst, (x))){  //if the required element: x = u-z is present
				System.out.println("The Two elements that add to: " + u + " are: " + i + ", " + x);
				return true; //then return true
			}
		}
		return false;
	}
	public static boolean BSearch(int[] lst, int tofind){  //receives list to be searched and U value
		double left = 0;				//left and right iterators for binary searching
		double right = lst.length-1;

		while(left<right){
			int piv = (int)Math.floor((left+right)/2);
			if(lst[piv] > tofind){	//if the target value is less than the value at the pivot
				right = --piv;		//move the right iterator to the left of the pivot
			}						//which effectively cuts the list in half

			if(lst[piv] < tofind){	//if the target value is greater than the value at the pivot
				left = ++piv;		//move the left iterator to the right of the pivot
			}						//which effectively cuts the list in half

			//comparison statement put at end to allow for piv to be inc/dec and still return true within that iteration

			if(lst[piv] == tofind){ //if the target value is equal to the value at the pivot, success, return true
				return true;
			}
		}
		return false;
	}
}
