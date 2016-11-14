/**
 * 
 * Consumer-Producer problem
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

package SharedBufferTest;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 *
 * @author issam
 */
public class SharedBufferTest {
    public static void main(String[] args) {
        ExecutorService executor = Executors.newCachedThreadPool(); // create a thread pool executor
        Buffer shared = new Buffer(10);
        executor.execute(new Producer(shared, 10)); // execute executor with producer runnable
        executor.execute(new Consumer(shared, 10)); // execute executor with consumer runnable
        
        executor.shutdown(); // stop the executor thread pool
    }
}
