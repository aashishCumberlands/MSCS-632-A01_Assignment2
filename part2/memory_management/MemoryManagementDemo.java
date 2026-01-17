
/**
 * Java Memory Management Demonstration
 * Demonstrates: Garbage collection, references, memory monitoring
 */

import java.util.ArrayList;
import java.util.List;
import java.lang.ref.WeakReference;

class DataBuffer {
    private int[] data;
    private String name;
    private static int instanceCount = 0;

    public DataBuffer(String name, int size) {
        this.name = name;
        this.data = new int[size];
        instanceCount++;
        System.out.println("✓ Creating buffer '" + name + "' with " + size +
                " elements (Instance #" + instanceCount + ")");
        System.out.println("  Hash code: " + System.identityHashCode(this));
    }

    public void fillWithValues(int start) {
        for (int i = 0; i < data.length; i++) {
            data[i] = start + i;
        }
        System.out.println("  ✓ Filled buffer '" + name + "'");
    }

    public void displayInfo() {
        System.out.println("  Buffer '" + name + "' has " + data.length + " elements");
        System.out.println("  Hash code: " + System.identityHashCode(this));
    }

    public int getSum() {
        int sum = 0;
        for (int value : data) {
            sum += value;
        }
        return sum;
    }

    // Finalizer (deprecated but shown for educational purposes)
    @Override
    protected void finalize() throws Throwable {
        try {
            instanceCount--;
            System.out.println("  ✗ GC collecting '" + name +
                    "' (Remaining: " + instanceCount + ")");
        } finally {
            super.finalize();
        }
    }
}

public class MemoryManagementDemo {

    // ═══════════════════════════════════════════════════
    // DEMO 1: Reference Management
    // ═══════════════════════════════════════════════════
    public static void demonstrateReferences() {
        System.out.println("\n--- DEMO 1: Reference Management ---");

        DataBuffer buffer1 = new DataBuffer("RefBuffer", 100);
        DataBuffer buffer2 = buffer1; // Both point to same object

        System.out.println("buffer1 and buffer2 point to same object:");
        buffer1.displayInfo();
        buffer2.displayInfo();

        buffer1 = null; // Remove one reference
        System.out.println("  ℹ buffer1 = null, object still alive");
        buffer2.displayInfo();

        buffer2 = null; // Remove last reference
        System.out.println("  ℹ buffer2 = null, object now eligible for GC");
    }

    // ═══════════════════════════════════════════════════
    // DEMO 2: Scope and Lifetime
    // ═══════════════════════════════════════════════════
    public static void demonstrateScope() {
        System.out.println("\n--- DEMO 2: Scope and Lifetime ---");

        {
            DataBuffer scopedBuffer = new DataBuffer("ScopedBuffer", 50);
            scopedBuffer.fillWithValues(1);
            System.out.println("  Inside scope, sum: " + scopedBuffer.getSum());
        } // scopedBuffer goes out of scope

        System.out.println("  ℹ Exited scope, object eligible for GC");
        System.gc(); // Suggest garbage collection
    }

    // ═══════════════════════════════════════════════════
    // DEMO 3: Memory Allocation and Cleanup
    // ═══════════════════════════════════════════════════
    public static void demonstrateAllocation() {
        System.out.println("\n--- DEMO 3: Mass Allocation ---");

        List<DataBuffer> bufferList = new ArrayList<>();

        System.out.println("  Creating 100 buffers...");
        for (int i = 0; i < 100; i++) {
            bufferList.add(new DataBuffer("Buffer" + i, 10000));
        }

        printMemoryInfo("After allocation");

        System.out.println("\n  Clearing all buffers...");
        bufferList.clear(); // Remove all references

        System.gc(); // Suggest GC
        sleep(100); // Give GC time

        printMemoryInfo("After clearing and GC");
    }

    // ═══════════════════════════════════════════════════
    // DEMO 4: Weak References
    // ═══════════════════════════════════════════════════
    public static void demonstrateWeakReferences() {
        System.out.println("\n--- DEMO 4: Weak References ---");

        DataBuffer strongRef = new DataBuffer("WeakBuffer", 100);
        WeakReference<DataBuffer> weakRef = new WeakReference<>(strongRef);

        System.out.println("  With strong reference:");
        System.out.println("  Weak ref valid: " + (weakRef.get() != null));

        strongRef = null; // Remove strong reference
        System.gc();
        sleep(100);

        System.out.println("\n  After removing strong reference:");
        System.out.println("  Weak ref valid: " + (weakRef.get() != null));
    }

    // ═══════════════════════════════════════════════════
    // DEMO 5: Memory Leak Simulation
    // ═══════════════════════════════════════════════════
    public static void demonstrateMemoryLeak() {
        System.out.println("\n--- DEMO 5: Potential Memory Leak ---");

        // Static collection that's never cleared = memory leak
        List<DataBuffer> leakyList = new ArrayList<>();

        System.out.println("  Adding objects to never-cleared list...");
        for (int i = 0; i < 50; i++) {
            leakyList.add(new DataBuffer("LeakBuffer" + i, 5000));
        }

        System.out.println("  ⚠ Objects in static/global collections won't be GC'd");
        System.out.println("  ⚠ This is a common source of memory leaks in Java");

        // In real code, you'd need to: leakyList.clear();
    }

    // ═══════════════════════════════════════════════════
    // Helper Methods
    // ═══════════════════════════════════════════════════

    public static void printMemoryInfo(String label) {
        Runtime runtime = Runtime.getRuntime();
        long usedMemory = (runtime.totalMemory() - runtime.freeMemory()) / 1024 / 1024;
        long totalMemory = runtime.totalMemory() / 1024 / 1024;
        long maxMemory = runtime.maxMemory() / 1024 / 1024;

        System.out.println("\n  === " + label + " ===");
        System.out.println("  Used:  " + usedMemory + " MB");
        System.out.println("  Total: " + totalMemory + " MB");
        System.out.println("  Max:   " + maxMemory + " MB");
    }

    public static void sleep(int ms) {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    // ═══════════════════════════════════════════════════
    // Main
    // ═══════════════════════════════════════════════════

    public static void main(String[] args) {
        System.out.println("═══════════════════════════════════════════════");
        System.out.println("JAVA: Garbage Collection Demo");
        System.out.println("═══════════════════════════════════════════════");

        printMemoryInfo("Initial state");

        demonstrateReferences();
        demonstrateScope();
        demonstrateAllocation();
        demonstrateWeakReferences();
        demonstrateMemoryLeak();

        System.out.println("\n--- Final GC Suggestion ---");
        System.gc();
        sleep(200);

        printMemoryInfo("Final state");

        System.out.println("\n═══════════════════════════════════════════════");
        System.out.println("Demo Complete");
        System.out.println("═══════════════════════════════════════════════");
    }
}