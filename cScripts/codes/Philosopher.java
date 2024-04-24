public class Philosopher extends Thread{
    private Object leftFork, rightFork;
    private int myNumber;

    public Philosopher(Object left, Object right, int number){
        leftFork = left;
        rightFork = right;
        myNumber = number;
    }

    public void run(){
        int timesDined = 0;
        while(true){
            synchronized(leftFork){
                synchronized(rightFork){
                    timesDined++;
                }
            }
            if(timesDined % 1000 == 0)
                System.err.println("Thread " + myNumber + " is running.");
        }
    }

    public static void main(String[] args){
        final int PHILOSOPHERS = 5;
        Object[] forks = new Object[PHILOSOPHERS];
        for(int i = 0; i < PHILOSOPHERS; i++){
            forks[i] = new Object();
        }
        for(int i = 0; i < PHILOSOPHERS; i++){
            int next = (i+1) % PHILOSOPHERS;
            Philosopher p = new Philosopher(forks[i], forks[next], i);
            p.start();
        }
    }
}
