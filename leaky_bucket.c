#include<stdio.h>

/*
This program simulates the Leaky Bucket algorithm.

Leaky Bucket is used in computer networks to control traffic flow.
Packets enter the bucket at variable rates, but they leave the bucket
at a fixed outgoing rate.
If the bucket becomes full, extra packets are dropped.
*/

void main(){

    int in;      // size of incoming packet
    int out;     // outgoing packet rate (leak rate)
    int bsize;   // total bucket capacity
    int n;       // number of incoming packets
    int bucket=0; // current number of packets in the bucket

    // Read bucket size from user
    printf("Enter the bucket size:"); 
    scanf("%d",&bsize);

    // Read how many packets will arrive
    printf("Enter the number of inputs:");
    scanf("%d",&n);

    // Read outgoing packet rate
    printf("Enter the packet outgoing rate:");
    scanf("%d",&out);

    /*
    Continue processing packets until all inputs are handled
    */
    while(n!=0)
    {

        // Read incoming packet size
        printf("\nEnter the incoming packet size:");
        scanf("%d",&in);

        printf("Incoming packet size:%d\n",in);

        /*
        Check if incoming packet can fit in the remaining bucket space
        Remaining space = bucket capacity - current bucket level
        */
        if(in <= (bsize - bucket))
        {
            // Add packet to bucket
            bucket += in;

            printf("Bucket status:%d out of %d\n",bucket,bsize);
        }
        else
        {
            /*
            If packet size exceeds remaining bucket space,
            packet is dropped (overflow condition)
            */
            printf("Packet size greater than remaining bucket size !!\n");
            printf("Packet dropped\n");
        }

        /*
        Simulate packet transmission:
        Packets leave the bucket at constant rate (out)
        */
        bucket = bucket - out;

        /*
        If outgoing packets are more than bucket contents,
        bucket becomes empty (not negative)
        */
        if(bucket < 0)
            bucket = 0;

        // Display bucket status after outgoing packets
        printf("After outgoing,bucket status:%d packets out of %d\n",bucket,bsize);

        // Decrease number of remaining inputs
        n--;
    }
}