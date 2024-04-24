import java.util.Random; 

public class Producer extends ConsumerProducer {
    public Producer(BoundedBuffer bb){
        this.bb=bb;
    }
    public void run(){
        while (true){
            try {
                Character obj = (Character)bb.retrieve();
            } catch (Exception e) {
                System.out.println("Error " +e);
            }
        }
    }
}
