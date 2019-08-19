import java.io.FileNotFoundException;
import java.util.Arrays;

public class Main {
	public static void main(String[] args) throws FileNotFoundException{
		int[] list10 = FasterBSearch.scantolst("CollectionNumbers/listNumbers-10.txt",10);
		int[] list10nsol = FasterBSearch.scantolst("CollectionNumbers/listNumbers-10-nsol.txt",10); //n=10
		int[] list100 = FasterBSearch.scantolst("CollectionNumbers/listNumbers-100.txt",100);
		int[] list100nsol = FasterBSearch.scantolst("CollectionNumbers/listNumbers-100-nsol.txt",10); //n=100
		int[] list1000 = FasterBSearch.scantolst("CollectionNumbers/listNumbers-1000.txt",1000);
		int[] list1000nsol = FasterBSearch.scantolst("CollectionNumbers/listNumbers-1000-nsol.txt",10); //n=1,000
		int[] list10000 = FasterBSearch.scantolst("CollectionNumbers/listNumbers-10000.txt",10000);
		int[] list10000nsol = FasterBSearch.scantolst("CollectionNumbers/listNumbers-10000-nsol.txt",10); //n=10,000
		int[] list100000 = FasterBSearch.scantolst("CollectionNumbers/listNumbers-100000.txt",100000);
		int[] list100000nsol = FasterBSearch.scantolst("CollectionNumbers/listNumbers-100000-nsol.txt",10); //n=100,000
		int[] list1000000 = FasterBSearch.scantolst("CollectionNumbers/listNumbers-1000000.txt",1000000);
		int[] list1000000nsol = FasterBSearch.scantolst("CollectionNumbers/listNumbers-1000000-nsol.txt",10); //n=1000,000


		Arrays.sort(list10);   //java's array sort(int[]) method: O(nlogn)
		Arrays.sort(list100);
		Arrays.sort(list1000);
		Arrays.sort(list10000);
		Arrays.sort(list100000);
		Arrays.sort(list1000000);

		//Faster Binary search implemented running of data

		System.out.println("Faster Binary Search Algorithm Runtimes: ");
		Timer time = new Timer();  //new instance of timer class
		
		time.start();
		for(int i: list10nsol){ 					//for n=10 
			if(FasterBSearch.FSearch(list10, i)){	//each of the 12 for loops below are the same with the only changes
				time.end();							//being to the two methods of searching and the input file's size
				break;}								//the for loop just iterates through the U values and calls the respective methods to
		}											//check each list. if the method returns true, the timer stops and the loops breaks
		System.out.print("Runtime in Nano Time, for n = 10: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list100nsol){ 					//for n=100  
			if(FasterBSearch.FSearch(list100, i)){	
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 100: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list1000nsol){ 					//for n=1000
			if(FasterBSearch.FSearch(list1000, i)){
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 1000: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list10000nsol){ 					//for n=10000
			if(FasterBSearch.FSearch(list10000, i)){
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 10000: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list100000nsol){ 				//for n=100000
			if(FasterBSearch.FSearch(list100000, i)){
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 100000: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list1000000nsol){ 				//for n=1000000
			if(FasterBSearch.FSearch(list1000000, i)){
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 1000000: ");
		System.out.println(time.totalttime());

		//Brute Forcing the data
		System.out.println();
		System.out.println("Brute Force Search Algorithm Runtimes: ");

		time.start();
		for(int i: list10nsol){ //for n=10
			if(BruteForce.BruteForceFind(list10, i)){
				time.end();
				break;}
		}
		
		System.out.print("Runtime in Nano Time, for n = 10: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list100nsol){ //for n=100
			if(BruteForce.BruteForceFind(list100, i)){
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 100: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list1000nsol){ //for n=1000
			if(BruteForce.BruteForceFind(list1000, i)){
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 1000: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list10000nsol){ //for n=10000
			if(BruteForce.BruteForceFind(list10000, i)){
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 10000: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list100000nsol){ //for n=100000
			if(BruteForce.BruteForceFind(list100000, i)){
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 100000: ");
		System.out.println(time.totalttime());

		time.start();
		for(int i: list1000000nsol){ //for n=1000000
			if(BruteForce.BruteForceFind(list1000000, i)){
				time.end();
				break;}
		}
		System.out.print("Runtime in Nano Time, for n = 1000000: ");
		System.out.println(time.totalttime());
	}
}
