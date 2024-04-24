public class Main {
    private static BoundedBuffer bb = new BoundedBuffer();
    private static ConsumerProducer[] threads = new ConsumerProducer[10];

    public static void main(String[] args){
        int i;
        for (i=0 ; i<5 ; i++){
            threads[2*i] = new Consumer(bb);
            threads[2*i+1] = new Producer(bb);
            threads[2*i].start();
            threads[2*i+1].start();
        }
    }
}
