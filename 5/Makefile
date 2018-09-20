default: clear complie run

clear:
	clear

complie:
	mpicc -o 5 5.c

run:
	mpirun -np 4 -hostfile /etc/cluster-hosts.txt 5
