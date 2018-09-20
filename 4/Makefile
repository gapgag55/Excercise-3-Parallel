default: clear complie run

clear:
	clear

complie:
	mpicc -o 4 4.c

run:
	mpirun -np 8 -hostfile /etc/cluster-hosts.txt 4
