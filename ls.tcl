# Create a new simulator object
set ns [new Simulator]

# Enable Link State routing protocol in the simulation
$ns rtproto LS

# Open a trace file to record simulation events
set nf [open ls1.tr w]
$ns trace-all $nf

# Open a NAM trace file for animation visualization
set nr [open ls2.nam w]
$ns namtrace-all $nr

# Procedure that executes when simulation ends
proc finish {} {
    global ns nf nr
    
    # Flush remaining trace data
    $ns flush-trace
    
    # Close trace files
    close $nf
    close $nr
    
    # Launch NAM animator
    exec nam ls2.nam
    
    # Exit simulation
    exit 0
}

# Create four nodes (routers)
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Create duplex links between nodes
# Format: node1 node2 bandwidth delay queue-type
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n0 1Mb 10ms DropTail

# Create UDP agent on node n0 (sender)
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0

# Create CBR traffic generator and attach it to UDP agent
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

# Configure packet size and interval
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005

# Create Null agent (receiver) on node n3
set null0 [new Agent/Null]
$ns attach-agent $n3 $null0

# Create second UDP agent on node n1 (second sender)
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1

# Create second CBR traffic generator
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1

# Configure packet parameters
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005

# Second receiver also on node n3
set null1 [new Agent/Null]
$ns attach-agent $n3 $null1

# Connect senders to receivers
$ns connect $udp0 $null0
$ns connect $udp1 $null1

# Schedule traffic start times
$ns at .1 "$cbr1 start"
$ns at .2 "$cbr0 start"

# Schedule traffic stop times
$ns at 45.0 "$cbr1 stop"
$ns at 45.1 "$cbr0 stop"

# End simulation at 50 seconds
$ns at 50.0 "finish"

# Run the simulation
$ns run