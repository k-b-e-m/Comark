# Packet Delay
**Bandwidth delay** the time needed for sender to get the packet onto the wire.
$$
bandwidth_{delay}=\frac{packet_{size}}{bandwidth}
$$

**propagation delay** related to the propagation of the bits at the speed of light.
$$
propagation_{delay}=\frac{distance}{speedOfLight}
$$

**Store-and-forward delay** time read read entire packet before any of it can be transmitted.

![[ladder diagrams.png]]
![[cases for ladder diagram.png]]
**Round-trip time (RTT)** is the time from sending a packet to recieving a response.

# Error *detection*
**Error-detection code** is some extra bits that allow a receiver to determine if a packet has been corrupted in transit. A corrupted package can then be discarded by the receiver.


