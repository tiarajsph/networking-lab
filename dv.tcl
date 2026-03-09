# Create a new simulator object
set ns [new Simulator]

# Enable Distance Vector routing protocol
$ns rtproto DV

# Open trace file to record simulation events
set nf [open dv1.tr w]
$ns trace-all $nf

# Open NAM trace file for animation
set nr [open dv2.nam w]
$ns namtrace-all $nr

# Procedure executed when simulation finishes
proc finish {} {

    global ns nf nr

    # Flush remaining traces
    $ns flush-trace

    # Close trace files
    close $nf
    close $nr

    # Animation command (disabled in your program)
    # exec nam dv2.nam

    exit 0
}

# Create network nodes (routers)
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Create duplex links between nodes
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n0 1Mb 10ms DropTail

# Create UDP agent on node n0 (sender)
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0

# Create CBR traffic generator
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

# Configure traffic parameters
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005

# Create Null agent (receiver) on node n3
set null0 [new Agent/Null]
$ns attach-agent $n3 $null0

# Connect sender to receiver
$ns connect $udp0 $null0

# Schedule traffic start
$ns at .1 "$cbr0 start"

# Schedule traffic stop
$ns at 45.0 "$cbr0 stop"

# End simulation
$ns at 50.0 "finish"

# Run simulation
$ns run