
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

Use UDP

1. We can just update the line for creating the socket.

https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html

2. Use Wireshark to verify



**Q:** Why it is better to use UDP in the tunnel, instead of TCP?

For security reasons? UDP is more resistant against attackers that control the network? Maybe the VPN protocol needs its own way
to do network control?


Resources
---------

https://gist.github.com/kevinxw/5334398
