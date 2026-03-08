#include <stdio.h>
#include <stdlib.h>

/*
Function: leaky_bucket

Simulates the Leaky Bucket traffic shaping algorithm.

Parameters:
bucket_capacity -> Maximum number of packets the bucket can hold
leak_rate       -> Number of packets that can leave per time unit
num_packets     -> Total number of incoming packets
packets[]       -> Array containing packet sizes arriving at each time unit
*/

void leaky_bucket(int bucket_capacity, int leak_rate, int num_packets, int packets[]) {

    int bucket = 0;   // Current number of packets stored in the bucket

    // Table header for simulation output
    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");

    /*
    Process each incoming packet one time step at a time
    */
    for (int i = 0; i < num_packets; i++) {

        // Print time and incoming packet size
        printf("%d%10d", i + 1, packets[i]);

        /*
        Step 1: Add incoming packets to the bucket
        */
        bucket += packets[i];

        /*
        Step 2: Check if bucket exceeds capacity
        If yes, overflow occurs and extra packets are dropped
        */
        if (bucket > bucket_capacity) {

            printf("%10d(Overflowed, Dropped %d)",
                   bucket_capacity,
                   bucket - bucket_capacity);

            bucket = bucket_capacity;  // keep bucket only at max capacity
        }
        else {
            printf("%10d", bucket);
        }

        /*
        Step 3: Leak packets at constant leak rate
        If bucket has fewer packets than leak_rate,
        leak only what is available.
        */

        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;

        // Reduce bucket level after leaking
        bucket -= leaked;

        /*
        Print number of leaked packets and remaining packets
        */
        printf("%10d%10d\n", leaked, bucket);
    }


    /*
    After all packets arrive,
    we continue leaking remaining packets until bucket becomes empty
    */

    int time = num_packets + 1;

    while (bucket > 0) {

        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;

        printf("%d%10d%10d%10d%10d\n",
               time,        // time step
               0,           // no incoming packets now
               bucket,      // bucket level before leaking
               leaked,      // packets leaked
               bucket - leaked); // remaining packets

        bucket -= leaked;

        time++;
    }
}


/*
Main function
Handles user input and starts the simulation
*/

int main() {

    int bucket_capacity;
    int leak_rate;
    int num_packets;

    // Read bucket capacity
    printf("Enter the bucket capacity: ");
    scanf("%d", &bucket_capacity);

    // Read leak rate
    printf("Enter the leak rate: ");
    scanf("%d", &leak_rate);

    // Number of incoming packets
    printf("Enter the number of packets: ");
    scanf("%d", &num_packets);

    /*
    Create an array to store incoming packet sizes
    */
    int packets[num_packets];

    printf("Enter the size of each incoming packet:\n");

    for (int i = 0; i < num_packets; i++) {
        scanf("%d", &packets[i]);
    }

    printf("\nLeaky Bucket Simulation:\n");

    // Call the simulation function
    leaky_bucket(bucket_capacity, leak_rate, num_packets, packets);

    return 0;
}