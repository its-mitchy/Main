import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
	public static void main(String args[]) throws FileNotFoundException{
		File l10 = new File("listSeqs-errorlow-l10.txt");
		File h10 = new File("listSeqs-errorhigh-l10.txt");
		Scanner SC = new Scanner(l10);
//		EditDistance test = new EditDistance("hint" , "list");
//		System.out.println(test.MinimumDist());
//		test.showedits(test.dtable);
		
		try {
			int count = 1;
		while(SC.hasNextLine()){
			
			String one = SC.nextLine(); //item 1 of pair
			String two = SC.nextLine(); //item 2 of pair
			
			//LCS a = new LCS(one, two);
			EditDistance b = new EditDistance(one,two);  //init LCS and ED class
			
			System.out.println("Pair " + count);
			System.out.println("String Input: " + one + " and " + two);
//			System.out.println("The LCS Length is: "+ a.findLCS());
			
			System.out.println("The Edit distance is: " + b.MinimumDist());
			System.out.println("The edits are: "); b.showedits(b.dtable);
			count++;
			System.out.println();
		}
		}
		catch(Exception e){
			e.printStackTrace();
		}
		
		SC.close();
	}
}
