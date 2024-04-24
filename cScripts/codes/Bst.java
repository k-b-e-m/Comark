import java.beans.Statement;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

public class Bst {
    static int size;
    static int A[];
    static long prevTime;
    // Two basic functions for time measurement. 
    // Java is not very exact wrt to this but it's ok for now. 
    static void startTest(String s){
        System.out.println(s);
        prevTime = System.currentTimeMillis();
    }
    static void stopPrintTimer(){
        System.out.println("Elapsed time: "+(System.currentTimeMillis()-prevTime));
    }
    static int predBST(int x){
        int left=0;
        int right=size;
        int mid=0;
        while (true) {
            mid = left+(right-left)/2;
            if (right <= left) return -1;
            if (x == A[mid]) return mid;
            int pred = (x-A[mid])>>31; // >> is arithmetic shift
            right = (pred&mid) + ((~pred)&right);
            left = (pred&left) + ((~pred)&(mid+1));
        }
    }

    static int slcompBST(int x, int slFactor){
        int left=0;
        int right=size;
        int mid=0;
        while (true) {
            mid = left + ((right-left)>>slFactor);
            if (right <= left) return -1;
            if (x == A[mid]) return mid;
            if (x < A[mid] ) {
                right = mid;
            } else {
                left = mid+1;
            }
        }
    }
    static int compBST(int x){
        int left=0;
        int right=size;
        int mid=0;
        while (true) {
            mid = left+((right-left)>>1);// >>1 is shift right once, i.e., division by 2.
            if (right <= left) return -1;
            if (x == A[mid]) return mid;
            if (x < A[mid] ) {
                right = mid;
            } else {
                left = mid+1;
            }
        }
    }

    static void test(int[] B, int[] C){ // For testing purposes
        int err=0;
        for (int i=0 ;i<20 ; i++){
            if  (B[i]%2 == 1) {
                if (C[i] != -1) {
                    System.out.println("Error found: "+B[i] + " = " +C[i]);
                    err = 1;
                }
            } else {
                if (C[i] != B[i]/2) {
                    System.out.println("Error found: "+B[i] + " = " +C[i]);
                    err = 1;
                }
            }
        }
        if (err == 0) ;//System.out.println("All correct ...");
    }

    public static void main(String []args){
        if (args.length <= 0) {
            System.err.println("Enter the size of the array.");
            System.exit(-1);
        }
    int pred = 0;
    int comp = 0;
    int[] slant = new int[4];
    int n = 3;
    for(int j = 0; j<n;j++){
      System.out.println("Iteration: " + j);
        size = Integer.parseInt(args[0]);
        int bSize = 1 << 23;  // 2^23
        A = new int[size];
        java.util.Random rand = new java.util.Random();
        for (int i=0 ; i<size ; i++){
            A[i]= 2*i;                  // Fill with even values
        }
        int B[] = new int[bSize];       // items to search for
        int C[] = new int[bSize];       // Results of the search

        for (int i=0 ; i<bSize ; i++) {
            B[i]= rand.nextInt(2*size); // Values we are searching for 
        }

      long currentTime = System.currentTimeMillis();
        startTest("Pred BST test...");
        for (int i=0 ; i<bSize ; i++){
            C[i] = predBST(B[i]);
        }
        stopPrintTimer();
      long ElapsedTime = currentTime - System.currentTimeMillis();
      pred += ElapsedTime;
        test(B,C);

      currentTime = System.currentTimeMillis();
        startTest("Comp BST test...");
        for (int i=0 ; i<bSize ; i++){
            C[i] = compBST(B[i]);
        }
        stopPrintTimer();
      ElapsedTime = System.currentTimeMillis() - currentTime; 
      comp += ElapsedTime;
        test(B,C);

        for (int t=2 ; t<6 ; t++) {
            startTest("Slanted Comp BST test with slant " + t);
            currentTime = System.currentTimeMillis();
            for (int i=0 ; i<bSize ; i++){
                C[i] = slcompBST(B[i],t);
            }
            ElapsedTime = currentTime - System.currentTimeMillis();
            String expression = "slant"+t+"+="+ElapsedTime+";";
            slant[t-2] += ElapsedTime;
            stopPrintTimer();
            test(B,C);
      }
        }
    System.out.println(pred*-1);
    System.out.println("###### ---- Averages ---- ######");
    System.out.println("Average of predBST: " + (pred/n));
    System.out.println("Average of compBST: " + (comp/n));
    System.out.println("Average of slant2BST: " + (slant[0]/n));
    System.out.println("Average of slant3BST: " + (slant[1]/n));
    System.out.println("Average of slant4BST: " + (slant[2]/n));
    System.out.println("Average of slant5BST: " + (slant[3]/n));
    }
}
