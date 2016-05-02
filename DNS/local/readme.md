

**Q:** How to setup the environment for the user machine?

There are 2 network interfaces. For the user machine, I changed the DNS server
for both interfaces.

**Q:** Why the user machine is still able to resolve "www.google.com" after
the DNS server is set to 192.168.56.101?

By doing "dig +trace www.google.com", we can see that 192.168.56.101 returns
the dns root servers:
  
    ; <<>> DiG 9.8.1-P1 <<>> +trace www.google.com
    ;; global options: +cmd
    .			504990	IN	NS	g.root-servers.net.
    .			504990	IN	NS	d.root-servers.net.
    .			504990	IN	NS	b.root-servers.net.
    .			504990	IN	NS	k.root-servers.net.
    .			504990	IN	NS	h.root-servers.net.
    .			504990	IN	NS	e.root-servers.net.
    .			504990	IN	NS	f.root-servers.net.
    .			504990	IN	NS	l.root-servers.net.
    .			504990	IN	NS	a.root-servers.net.
    .			504990	IN	NS	i.root-servers.net.
    .			504990	IN	NS	j.root-servers.net.
    .			504990	IN	NS	c.root-servers.net.
    .			504990	IN	NS	m.root-servers.net.
    ;; Received 228 bytes from 192.168.56.101#53(192.168.56.101) in 871 ms
    
    com.			172800	IN	NS	a.gtld-servers.net.
    com.			172800	IN	NS	b.gtld-servers.net.
    com.			172800	IN	NS	c.gtld-servers.net.
    com.			172800	IN	NS	d.gtld-servers.net.
    com.			172800	IN	NS	e.gtld-servers.net.
    com.			172800	IN	NS	f.gtld-servers.net.
    com.			172800	IN	NS	g.gtld-servers.net.
    com.			172800	IN	NS	h.gtld-servers.net.
    com.			172800	IN	NS	i.gtld-servers.net.
    com.			172800	IN	NS	j.gtld-servers.net.
    com.			172800	IN	NS	k.gtld-servers.net.
    com.			172800	IN	NS	l.gtld-servers.net.
    com.			172800	IN	NS	m.gtld-servers.net.
    ;; Received 492 bytes from 199.7.83.42#53(199.7.83.42) in 675 ms
    
    google.com.		172800	IN	NS	ns2.google.com.
    google.com.		172800	IN	NS	ns1.google.com.
    google.com.		172800	IN	NS	ns3.google.com.
    google.com.		172800	IN	NS	ns4.google.com.
    ;; Received 168 bytes from 192.5.6.30#53(192.5.6.30) in 159 ms
    
    www.google.com.		300	IN	A	216.58.217.68
    ;; Received 48 bytes from 216.239.34.10#53(216.239.34.10) in 29 ms


But the first DNS query captured by Wireshark goes to 199.7.83.42:

    3064	2016-05-01 20:06:21.098031	10.0.2.15	199.7.83.42	DNS	74	Standard query A www.google.com

And even if we do, the DNS query to 192.168.56.101 is still missing, and the first query is:

    3080	2016-05-01 20:16:23.670337	10.0.2.15	198.97.190.53	DNS	75	Standard query A www.example.com

198.97.190.53 is the h.root-servers.net.

**Q:** Why the DNS query to 192.168.56.101 is missing?

Modified the /etc/nsswitch.conf as follows.

    #hosts:          files mdns4_minimal [NOTFOUND=return] dns mdns4
    hosts:		files dns

Source:
http://unix.stackexchange.com/questions/28941/what-dns-servers-am-i-using

Solved. Wireshark was listening on the wrong interface.

**Q:** It seems that the OS sends out a DNS query to each interface. Why? 

Task 2:

**Q:** When doing "ping www.example.com", Wireshark does not capture a DNS query
to the DNS server? Why?

One possibility is that there is a OS-level DNS cache. I think Windows has this.
However, this thread says that Linux does not have OS-level DNS cache:
http://unix.stackexchange.com/questions/28553/how-to-read-the-local-dns-cache-contents
