package SharedBufferTest;

import java.util.Random;
/**
 *
 * @author issam
 */
public class Consumer implements Runnable {
    private final static Random GENERATOR = new Random();
    private final Buffer sharedLocation;
    private final int cells;
    
    public Consumer ( Buffer shared, int cells) {
        sharedLocation = shared;
        this.cells = cells;
    }
    
    @Override
    public void run() {
        int sum = 0;
        
        for( int count = 1; count <= this.cells; count++) {
            try {
                Thread.sleep (GENERATOR.nextInt( 1000 ) );
                int read_value = sharedLocation.get();
                sum += read_value;
                System.out.println("Consumer reads: \t <<<  " + read_value);
            }
            catch (InterruptedException exception) {
                exception.printStackTrace();
            } // end catch
        } // end for
        
        System.out.println("Consumer done with sum of: \t" +
                sum );
    } // end run()
}
