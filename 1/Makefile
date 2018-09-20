default: clear complie run

clear:
	clear

complie:
	mpicc -o 1 1.c

run:
	mpirun -np 4 -hostfile /etc/cluster-hosts.txt 1
