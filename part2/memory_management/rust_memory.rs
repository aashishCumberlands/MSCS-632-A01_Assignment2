//! Rust Memory Management Demonstration
//! Demonstrates: Ownership, borrowing, move semantics, memory safety

use std::collections::HashMap;

/// Structure to demonstrate ownership
#[derive(Debug)]
struct DataBuffer {
    data: Vec<i32>,
    name: String,
}

impl DataBuffer {
    /// Creates a new DataBuffer (takes ownership of name)
    fn new(name: String, size: usize) -> Self {
        println!("✓ Creating buffer '{}' with {} elements", name, size);
        println!("  Memory allocated for vector");
        DataBuffer {
            data: vec![0; size],
            name,
        }
    }
    
    /// Borrows self immutably - can have multiple
    fn display_info(&self) {
        println!("  Buffer '{}' has {} elements", self.name, self.data.len());
        println!("  Memory address: {:p}", self.data.as_ptr());
    }
    
    /// Borrows self mutably - only one at a time
    fn fill_with_values(&mut self, start: i32) {
        for (i, item) in self.data.iter_mut().enumerate() {
            *item = start + i as i32;
        }
        println!("  ✓ Filled buffer '{}'", self.name);
    }
    
    /// Takes ownership (consumes the buffer)
    fn into_sum(self) -> i32 {
        let sum: i32 = self.data.iter().sum();
        println!("  ✓ Buffer '{}' consumed, sum = {}", self.name, sum);
        sum
        // self is dropped here, memory is automatically freed
    }
}

// When DataBuffer goes out of scope, this is called
impl Drop for DataBuffer {
    fn drop(&mut self) {
        println!("  ✗ Dropping buffer '{}' - memory freed", self.name);
    }
}

/// Demonstrates borrowing (read-only)
fn process_buffer(buffer: &DataBuffer) -> i32 {
    println!("  Processing buffer '{}'...", buffer.name);
    buffer.data.iter().filter(|&&x| x > 0).count() as i32
}

/// Demonstrates mutable borrowing
fn modify_buffer(buffer: &mut DataBuffer, multiplier: i32) {
    for item in buffer.data.iter_mut() {
        *item *= multiplier;
    }
    println!("  ✓ Modified buffer '{}'", buffer.name);
}

fn main() {
    println!("═══════════════════════════════════════════════");
    println!("RUST: Memory Management with Ownership");
    println!("═══════════════════════════════════════════════\n");
    
    // ═══════════════════════════════════════════════════
    // DEMO 1: Ownership Transfer (Move Semantics)
    // ═══════════════════════════════════════════════════
    println!("--- DEMO 1: Ownership Transfer ---");
    {
        let buffer1 = DataBuffer::new(String::from("Buffer1"), 5);
        buffer1.display_info();
        
        let buffer1_moved = buffer1;  // Ownership transferred
        buffer1_moved.display_info();
        
        // buffer1.display_info();  // ❌ Compile error: value moved
        println!("  ℹ buffer1 is no longer accessible\n");
    } // buffer1_moved dropped here
    
    // ═══════════════════════════════════════════════════
    // DEMO 2: Borrowing (Immutable)
    // ═══════════════════════════════════════════════════
    println!("\n--- DEMO 2: Immutable Borrowing ---");
    {
        let buffer2 = DataBuffer::new(String::from("Buffer2"), 5);
        
        // Multiple immutable borrows allowed
        let count1 = process_buffer(&buffer2);
        let count2 = process_buffer(&buffer2);
        
        println!("  Counts: {}, {}", count1, count2);
        buffer2.display_info();  // buffer2 still valid
    }
    
    // ═══════════════════════════════════════════════════
    // DEMO 3: Mutable Borrowing
    // ═══════════════════════════════════════════════════
    println!("\n--- DEMO 3: Mutable Borrowing ---");
    {
        let mut buffer3 = DataBuffer::new(String::from("Buffer3"), 8);
        buffer3.fill_with_values(10);
        
        // Only one mutable borrow at a time
        modify_buffer(&mut buffer3, 2);
        
        // let ref1 = &mut buffer3;
        // let ref2 = &mut buffer3;  // ❌ Compile error: already borrowed
        
        buffer3.display_info();
    }
    
    // ═══════════════════════════════════════════════════
    // DEMO 4: Consuming (Taking Ownership)
    // ═══════════════════════════════════════════════════
    println!("\n--- DEMO 4: Consuming Value ---");
    {
        let mut buffer4 = DataBuffer::new(String::from("Buffer4"), 6);
        buffer4.fill_with_values(1);
        
        let sum = buffer4.into_sum();  // buffer4 consumed
        println!("  Final sum: {}", sum);
        
        // buffer4.display_info();  // ❌ Compile error: value moved
    }
    
    // ═══════════════════════════════════════════════════
    // DEMO 5: Heap Allocation with Box
    // ═══════════════════════════════════════════════════
    println!("\n--- DEMO 5: Heap Allocation ---");
    {
        let boxed_value = Box::new(42);
        println!("  Boxed value: {}", boxed_value);
        println!("  Address: {:p}", &*boxed_value);
        
        let large_data = Box::new([0u8; 1024 * 1024]);
        println!("  Large data (1MB) allocated on heap");
        
        // Box automatically freed when out of scope
    }
    
    // ═══════════════════════════════════════════════════
    // DEMO 6: Collections and Ownership
    // ═══════════════════════════════════════════════════
    println!("\n--- DEMO 6: Collections ---");
    {
        let mut cache: HashMap<String, Vec<i32>> = HashMap::new();
        
        cache.insert(String::from("key1"), vec![1, 2, 3]);
        cache.insert(String::from("key2"), vec![4, 5, 6]);
        
        // Borrow from HashMap
        if let Some(values) = cache.get("key1") {
            println!("  Cache values: {:?}", values);
        }
        
        // Ownership transferred out of HashMap
        if let Some(values) = cache.remove("key2") {
            println!("  Removed values: {:?}", values);
        }
    }
    
    // ═══════════════════════════════════════════════════
    // DEMO 7: Memory Safety Guarantees
    // ═══════════════════════════════════════════════════
    println!("\n--- DEMO 7: Memory Safety ---");
    println!("  ✓ No dangling pointers - impossible at compile time");
    println!("  ✓ No double-free - prevented by ownership");
    println!("  ✓ No use-after-free - borrow checker enforces");
    println!("  ✓ No data races - enforced at compile time");
    
    println!("\n═══════════════════════════════════════════════");
    println!("All buffers automatically cleaned up!");
    println!("═══════════════════════════════════════════════");
}