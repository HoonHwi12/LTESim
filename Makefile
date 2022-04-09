make:
	if test -f LTE-Sim; then rm LTE-Sim; fi;
	clear;
	cat CONFIG/LTE-Sim
<<<<<<< HEAD
	cd TOOLS; make; cd ../;
	./CONFIG/make_load-parameter-file.sh; 
	cd Debug; make clean; make; cd ..;
	ln -sf Debug/LTE-Sim LTE-Sim 
=======
	sleep 2
	cd TOOLS; make; cd ../;
	./CONFIG/make_load-parameter-file.sh; 
	cd Debug; make clean; make; cd ..;
	ln -s Debug/LTE-Sim LTE-Sim 
>>>>>>> ad05299149aa732f4d064f67e737dda4046b36a9
# 	clear;
	cat CONFIG/LTE-Sim-end
clean:
	rm LTE-Sim; cd Debug; make clean
	cd ..
	cd TOOLS; make clean;
	cd ..
	clear
	cat CONFIG/LTE-Sim-end-clear
	
