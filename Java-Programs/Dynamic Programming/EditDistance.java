
public class EditDistance {
	String word1;
	String word2;
	int m;
	int n;

	int[][] dtable;


	public EditDistance(String w1, String w2){
		this.word1 = w1;
		this.word2 = w2;
		m = word1.length();
		n = word2.length();
		dtable = new int[m+1][n+1];
	}

	public int MinimumDist(){
		for(int i = 0; i < m; i++){
			dtable[i][0]=0;
		}
		for(int j = 0; j < n; j++){
			dtable[0][j]=0;
		}

		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				char s1c = word1.charAt(i);
				char s2c = word2.charAt(j);

				if(s1c==s2c){
					dtable[i+1][j+1] = dtable[i][j];
				}else{
					int replace = dtable[i][j]+1;
					int insert = dtable[i][j+1]+1;
					int delete = dtable[i+1][j]+1;

					int min = Math.min(replace, insert);
					min = Math.min(min, delete);

					dtable[i+1][j+1] = min;
				}
			}
		}
		//showtable(dtable);
		return dtable[m][n];
	}
	public void showedits(int[][] dp){

		System.out.println(m +" "+ n);
		char[] edit = word1.toCharArray();

		while(m > 0 && n > 0){
			//System.out.println(m + " and " + n);

			if(dp[m][n] == dp[m-1][n-1]){ //they have the same letter

				System.out.println(word1 + " and " + word2 + " Both have " + word1.charAt(m-1));

				edit[m-1] = word1.charAt(m-1);
				m--; n--;
			}else{
				if(dp[m][n] == dp[m-1][n-1] + 1){
					System.out.println("In " + word1 + " you need to replace " + word1.charAt(m-1) + " with " + word2.charAt(n-1));
					edit[m-1] = word2.charAt(n-1);
					m--; n--;

				}else{
					if(dp[m][n] == dp[m][n-1] + 1){ //delete
						System.out.println("In word " + word1 + " delete " + word1.charAt(m-1));

						edit[m-1] = "*".charAt(0);
						n--;

					}else{
						if(dp[m][n] == dp[m-1][n] +1){ //insert
							System.out.println("In word " + word1 + " insert " + word2.charAt(n-1) + " at position " + m);

							edit[m-1] = "+".charAt(0);
							m--;
						}
					}
				}

			}
//			for(char s: edit){
//				System.out.print(s);
//			}System.out.println();
		}
	}

		public static void showtable(int[][] t){
			for(int i = 0; i < t.length; i++){
				for(int j = 0; j < t[i].length; j++){
					System.out.print(t[i][j]);
				}System.out.println();
			}
		}
	}
