EXE	= rfea
MAKE	= make

.PHONY: all clean	

all:
	@echo "\nCompiling program..."
	$(MAKE) -C src
	@echo "\nCopying program..."
	cp src/$(EXE) .
	@echo "\nDone."	

clean:
	@echo "\nCleaning the program in src..."
	-$(MAKE) -C src clean
	@echo "\nCleaning in this directory..."
	-rm -f $(EXE) *~ .*
	@echo "\nCleaning the output directory..."
	cd output
	-rm -f .RData .Rhistory	
