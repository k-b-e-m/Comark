import java.util.Random; 

public class Consumer extends ConsumerProducer {

    public Consumer(BoundedBuffer bb){
        this.bb=bb;
    }


    public void run(){
        Random r = new Random();
        while (true){
            char c = (char)(r.nextInt(26) + 'a');
            Character obj = new Character(c);
            try { 
                bb.insert(obj);
            } catch (Exception e) {
                System.out.println("Error " +e);
            }
        }
    }
}
