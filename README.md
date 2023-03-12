# ping-blocker
Simple C++ script that blocks pings

This program listens for incoming ICMP packets and drops any packets with type ICMP_ECHO, which corresponds to ping packets. To run this program in the background on Linux, you can use the nohup command:

$ nohup ./ping_blocker &

This will run the program in the background and redirect any output to a file called nohup.out. The & symbol at the end of the command runs the program in the background. Note that you will need root privileges to bind to a raw socket and intercept ICMP packets.
