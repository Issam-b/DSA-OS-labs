package SharedBufferTest;

import java.util.Random;

/**
 *
 * @author issam
 */
public class Producer implements Runnable{
    private final static Random GENERATOR = new Random();
    private final Buffer sharedLocation;
    private final int cells;
    
    // constructor
    public Producer( Buffer shared, int cells) {
        sharedLocation = shared;
        this.cells = cells;
    }
    
    @Override
    public void run() {
        int sum = 0;
        for (int count = 1; count <= this.cells; count++) {
            try {
                Thread.sleep(GENERATOR.nextInt( 1000 ) ); // random sleep time
                int random = GENERATOR.nextInt(10);
                System.out.println("Producer produced: \t >>>  " + random);
                sharedLocation.set( random ); // set value in buffer
                sum += random; // increment sum value
            }
            catch (InterruptedException exception) {
                exception.printStackTrace();
            } // end catch
        } // end for
        
        System.out.println("Producer finished with sum of: \t" +
                sum );
    } // end run()
} // end class Producer
