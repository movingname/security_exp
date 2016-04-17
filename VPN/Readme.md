
http://www.cis.syr.edu/~wedu/seed/Labs_12.04/Networking/VPN/

Setup
-----

Issues for setting up multiple VMs in VirtualBox

See the Host-only Network Setup
http://www.cis.syr.edu/~wedu/seed/Documentation/VirtualBox/VirtualBox_MultipleVMs.pdf

If the VM is cloned, need to update its MAC address.

Step 1. Understand the TUN/TAP
------------------------------

The VPN is enabled by TUN/TAP device driver. My understanding is that TUN/TAP creates a virtual network interface 
that enables user-space programs to send and receive network packets. As a VPN program, it receives packets from TUN/TAP, 
encrypt it, and then sends out through the real network interface. So TUN/TAP adds a layer of indirection.

Some resources for TUN/TAP

https://www.kernel.org/doc/Documentation/networking/tuntap.txt
http://backreference.org/2010/03/26/tuntap-interface-tutorial/

simpletun.c

This program creates a simple tunnel using TUN/TAP. Basically, when it starts, it asks the kernel to create a TUN/TAP virtual interface.
This program needs to have a connection to both the TUN/TAP interface and the network interface. Then it serves as intermediary between
these two interfaces.

Task 1: Create a Host-to-Host Tunnel using TUN/TAP
--------------------------------------------------

We updated the code to support both TCP and UDP.

Reference:
https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html

We used Wireshark to verify.

**Q:** Why it is better to use UDP in the tunnel, instead of TCP?

For security reasons? UDP is more resistant against attackers that control the network? Maybe the VPN protocol needs its own way
to do network control? But what about the unreliability of UDP?

Task 2: Create a Host-to-Gateway Tunnel
---------------------------------------

We now create two networks in two hosts. In one host, we create a gateway and a private network. In another host, we have a client that will connect to the private network through a tunnel. I think the client can be a EC2 VM. The gateway and the private network can be built in VirtualBox.

Now, the challenge is to enable an outside machine connects to VMs inside the VirtualBox. The idea is to use port forwarding. In VirtualBox setting, use the address of Host-only Adapter because the IP address for NAT is the same for all VMs.

But the problem with this idea is that my desktop is also in a private network. So the EC2 VM cannot directly connect to my desktop.

Solution 1: Do port forwarding at my router.

See section "If You're Connecting from Inside Your Network" in the following article
http://lifehacker.com/5902654/use-your-home-computer-from-anywhere-a-comprehensive-guide-to-remote-controlling-your-pc

Test with nmap. Not working if just do "nmap -p <port> <my ip>".

Ah, need to skip the host discovery step using "-PN". See the following discussion:
http://serverfault.com/questions/309357/ping-a-specific-port

Then it shows filtered. But actually other ports are also filtered. Here are information about the port state:
https://nmap.org/book/man-port-scanning-basics.html

**Q:** How to test if the port forwarding works?

**Q:** How to have persistent address? The lifehacker article above talked about DNS. Could try.


Solution 2: Use two physical computers in my wifi network.


Resources
---------

https://gist.github.com/kevinxw/5334398
