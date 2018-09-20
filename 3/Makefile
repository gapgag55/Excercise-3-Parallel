default: clear complie run

clear:
	clear

complie:
	mpicc -o 3 3.c

run:
	mpirun -np 2 -hostfile /etc/cluster-hosts.txt 3
