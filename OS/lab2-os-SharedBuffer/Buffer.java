package SharedBufferTest;

/**
 *
 * @author issam
 */
public class Buffer {
    private final int[] buffer; // shared buffer array
    private int occupiedcells = 0; // cell that has data in them
    private int in = 0;
    private int out = 0;
    
    // constructor
    public Buffer ( int size ) {
        buffer = new int[size]; // set buffer size upon instantiation
    }
    
    // set or write method 
    public synchronized void set( int value ) throws InterruptedException{
        // if all cells have data then producer waits until consumer 
        // consume a cell or more
        while( occupiedcells == buffer.length ) {
            System.out.println("Buffer full");
            wait();
        }
        
        buffer[in] = value; // write value to buffer
        in = ( in + 1 ) % buffer.length; // move to next cell and rotate when needed
        ++occupiedcells; // update occupied cells number
        notifyAll();
    }
    
    // read buffer method
    public synchronized int get() throws InterruptedException {
        // check if buffer if empty to wait
        while( occupiedcells == 0 ) {
            System.out.println("Buffer empty");
            wait();
        }
        
        // read buffer values to value_read
        int value_read = buffer[out];
        out = ( out + 1 ) % buffer.length;
        --occupiedcells; 
        notifyAll();
        
        return value_read;
    }
} // end class Buffer
