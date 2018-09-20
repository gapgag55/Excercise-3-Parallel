default: clear complie run

clear:
	clear

complie:
	mpicc -o 2 2.c

run:
	mpirun -np 4 -hostfile /etc/cluster-hosts.txt 2
