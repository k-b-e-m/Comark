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
