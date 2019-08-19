public class BruteForce {
	public static boolean BruteForceFind(int[] ar, int u){
		for(int element : ar){ //for each element in the list
			for(int el2 : ar){	//check if the sum with another element (or the same element) is equal to U
				if(el2 + element == u){
					System.out.println("The Two elements that add to: " + u + " are: " + element + ", " + el2);
					return true;
				}
			}
		}
		return false;
	}

}
