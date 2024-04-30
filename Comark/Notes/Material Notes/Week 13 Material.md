# Building Reliable Transport: Stop-and-Wait
**Stop-and-wait** here a sender only sends one outstanding package at a time. If there is no response, the packet may be retransmitted.
![[Stop and wait.png]]
With packet loss however the reciever is not aware off the loss and thinks that Data[N] is just slow to arrive.
![[lost packet.png]]
As seen on the right, when a ACK is lost, one can assume that the *retransmit-on-duplicate* is implemented for the ACK to retransmit.
![[Pasted image 20240424144517.png]]

# Sliding Windows
**Window size** is how many packets the sender is allowed to send before the sender has to receive a ACK.  
![[Slide windows.png]]

# User Datagram Protocol - UDP
![[Pasted image 20240429082203.png]]
UDP header looks like the above.

UDP is unreliable. There is no udp layer attempt at timeouts, acknowledgement and retransmission. Applications using UDP must implement these themselves. 
UDP is unconnected or stateless.
UDP uses 16-bit checksum on the data.
UDP is sometimes used for traffic amplification attacks and flooding attacks on the internet, due to the fact that it is easy to sendUDP packets with spoofed source address.


## QUIC
Google created the protocol called QUIC (quick UDP internet Connections).
This transport protocol is specifically tailored to the HTTP protocol.

## DCCP
Datagram Congestion Control Protocol is another transport protocol build atop UDP.
Adds a number of TCP-like features, the most significant one is connection setup and teardown.

## Simplex talk
*One of the early standard examples for socket programming is simplex-talk. The client side reads lines of text from the user’s terminal and sends them over the network to the server; the server then displays them on its terminal.*

![[Pasted image 20240429083754.png]]

## The Server
This chapter explains the basics of creating a Java socket implementation.


# Trivial File Transport Protocol, TFTP
Is based on UDP.
TFTP does not have a mechanism for authentication. This is the servers responsibility to handle these cases.
Uses Stop-and-wait.
This protocol is typically used within LAN and internal connections.
The TFTP has 5 packet types. RRQ (read reQuest), WRQ(write ReQuest), Data, ACK, Error.

# Fundamental Transport Issues
Typical issues is:
- Old duplicate packets
- Lost final ACK
- Duplicated Connection Request
- Reboots
## Old Duplicate Packets
This is a issue where a past packet arriving late, bit is still accepted as current.
This could happen if  an old port is reused.
A scenario where it could happen could be:
- A first copy of the old duplicate was sent
- A routing error occurs, the packet is stuck in routing loop
- An alternative path between the original hosts is restored, and the packet is retransmitted successfully
- Some time later, the packet stuck in routing loop is released and reaches its final destination.

## Lost Final ACK
In protocols, most packets will be acknowledged. However the last packet, cannot be acknowledged, since it has to be the last. Typically the last package is a ACK. This means that the sender will have uncertainty about if the packet ever reached the receiver.
A problem could be like this:
- Server sends last data to client.
- Client sends ACK to confirm
- ACK is lost
- Client "leaves", since it is done
- Server resends the data.
- No client to receive, this results in server keep going until giving up.

Another example is the two-generals problem:
![[75272020-86d4-4f04-816d-08e99a42df13_189674486091.avif]]


## Duplicated Connection Request

• The client sends RRQ("foo")
• The client changes its mind, or aborts, or reboots, or whatever
• The client sends RRQ("bar")
• The server responds with Data(I) from the first RRQ, that is, with file "foo",
expecting file "bar"
while the client is expecting file "bar".

## Reboots
- **Communication Protocol Considerations:**
  - Any ongoing communications protocol must consider potential reboots on either side.
  - Detecting reboot crucial for closing broken connections.

- **TFTP Behavior on Reboots:**
  - If sender reboots: Packet exchange stops.
  - If receiver reboots: Sender keeps sending data without acknowledgment.

- **Port Reuse Challenges:**
  - Rebooting system forgets recent port usage, risking old duplicates.

- **Scenario Example:**
  - Client sends RRQ(“foo”), reboots before ACK[1].
  - After reboot, sends RRQ(“bar”) from same port, unable to guarantee not reusing port.
  - Server sends Data[1] for “foo” belatedly.
  - Client accepts “foo” thinking it's “bar”.

- **Practical Importance:**
  - Limited practical importance, but relevant for "diskless" devices using TFTP for boot image retrieval.

# The End-to-End principle
This principles states that the transportation issues named above, are not the core networks problems, however each endpoint should itself handle the problems.

# TCP header
![[Pasted image 20240429171644.png]]
Here is a diagram of a TCP header.

The TCP header defines some different flag bits. This is what they stand for:
- **SYN**: for SYNchronize; marks packets that are part of the new-connection handshake.
-  **ACK**: indicates that the header Acknowledgment field is valid; that is, all but the first packet
-  **FIN**: for FINish; marks packets involved in the connection closing
-  **PSH**: for PuSH; marks "non-full" packets that should be delivered promptly at the far end
-  **RST**: for ReSeT; indicates various error conditions
-  **URG**: for URGent; part of a now-seldom-used mechanism for high-priority data
-  **CWR** and ECE: part of the Explicit Congestion Notification mechanism, 14.8.3 Explicit Congestion
Notification (ECN)

# TCP Connection Establishment
**The three way handshake** is used to establish a connection.
![[Pasted image 20240429172257.png]]
**To Close Connection** - also called *FIN handshake*
![[Pasted image 20240429172508.png]]

# TCP state diagram

![[Pasted image 20240429173832.png]]
Used for implement how a system should respond to each packet arrival.
Alternatively this could have been explained with a ladder diagram:
![[Pasted image 20240429173953.png]]

# Nagle Algorithm
The algorithm attempts too improve the behavior if interactive small-packet applications. It specifies that TCP endpoints should queue small data segments untill until it eirther accumulates a full segments's worth or recieves an ACK for the previous batch.
![[img.png]]
# TCP flow control
If a sender can send more packets than the reciever can handle, the reciever can adjust the window size when sending back it ACK. this is caled flowcontrol. 
There is also a possibility of adjusting the window size to 0. This indicates that the data was recieved, but that no more data can be recieved at this time.

# Silly Window Syndrome
Can occur when the reciever or sender is too slow.
![[unnamed.png]]
An illustatrion above.
An example case is below:
![[Pasted image 20240430085152.png]]


# Keepalive
![[Pasted image 20240430085431.png]]
![[Pasted image 20240430085445.png]]
