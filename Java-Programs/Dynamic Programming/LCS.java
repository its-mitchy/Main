import java.lang.reflect.Array;

public class LCS {
	String s1;
	String s2;
	int[][] ltable;
	
	public LCS(String Sinit1, String Sinit2){
		this.s1 = Sinit1;
		this.s2 = Sinit2;
	}
	
	public void createTable(){
		ltable = new int[s1.length()+1][s2.length()+1]; //7*7
		//System.out.println("New Table: " +  s1.length() + " by " + s2.length());
	}
	
	public void returnLCS(){
		char[] LCS = new char[Array.getInt(ltable[s1.length()-1], s2.length()-1)+1];
		for(int i = s1.length(); i >= 1; i--){
			for(int j = s2.length(); j >= 1; j--){
				int Backi = Array.getInt(ltable[i-1], j-1);  //up and left 1 position of current index
				int Currenti = Array.getInt(ltable[i], j);	//current index
				
				if(Currenti == 1 + Backi){					//if the LCS value of the current is 1 more than the up and right LCS
					LCS[Currenti-1] = s1.charAt(i-1);			//add the char to the string
				}
				//else{  Math.min(ltable[i-1][j],ltable[i][j-1]);  }
			}
		}
		
		for(char c: LCS){
			String tocon = Character.toString(c);
			System.out.print(tocon);
		}
	}
	
	public int findLCS(){  //creates the LCS table
		createTable();
		for (int i = 0; i <= s1.length(); i++){	ltable[i][0] = 0;}
		for (int j = 0; j <= s2.length(); j++){ ltable[0][j] = 0;}

		for(int i = 1; i < s1.length()+1; i++){
			for(int j = 1; j < s2.length()+1; j++){
				if(s1.charAt(i-1) == s2.charAt(j-1)){
					ltable[i][j] = 1 + ltable[i-1][j-1];
				}
				else{ ltable[i][j] = Math.max(ltable[i-1][j],ltable[i][j-1]);
				}
			}
		}
		//showtable(ltable);
		System.out.print("The LCS for the Two Strings is: ");
		returnLCS();
		System.out.println();
		return ltable[s1.length()][s2.length()];
	}
	
	


	public static void showtable(int[][] t){
		for(int i = 0; i < t.length; i++){
			for(int j = 0; j < t[i].length; j++){
				System.out.print(t[i][j]);
			}System.out.println();
		}
	}
}
