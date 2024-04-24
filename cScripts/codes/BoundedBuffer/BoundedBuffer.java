public class BoundedBuffer {
    private Object[] buffer = new Object[20]; // arbitrary size
    private int numOccupied = 0;
    private int firstOccupied = 0;
    /* invariant: 0 <= numOccupied <= buffer.length
    0 <= firstOccupied < buffer.length
    buffer[(firstOccupied + i) % buffer.length]
    contains the (i+1)th oldest entry,
    for all i such that 0 <= i < numOccupied */

    public synchronized void insert(Object o)
    throws InterruptedException {
        while(numOccupied == buffer.length) wait();
        buffer[(firstOccupied + numOccupied) % buffer.length] = o;
        numOccupied++;
        // in case any retrieves are waiting for data, wake them
        printBuffer();
        System.out.println(" inserted " + o);
        notifyAll();
    }

    public synchronized Object retrieve()
    throws InterruptedException {
        while(numOccupied == 0)
        // wait for data
        wait();
        Object retrieved = buffer[firstOccupied];
        buffer[firstOccupied] = null; // may help garbage collector
        firstOccupied = (firstOccupied + 1) % buffer.length;
        numOccupied--;
        // in case any inserts are waiting for space, wake them
        notifyAll();
        // print:
        printBuffer();
        System.out.println(" retrieved " + retrieved);
        return retrieved;
    }

    synchronized void printBuffer(){
        if (numOccupied == 0) {
            System.out.print("[]");
            return;
        }
        String s="[" + buffer[firstOccupied];
        for (int i=1 ; i<numOccupied ; i++) {
            s=s + "," +buffer[(firstOccupied+i)%buffer.length];
        }
        System.out.print(s+"]");
    }

}
