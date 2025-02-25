build:
	armips $(SRC)/$(SRC).s
exe:
	python bin2exe.py $(SRC).bin $(SRC).ps-exe
	move $(SRC).bin ./$(SRC)
	move $(SRC).ps-exe ./$(SRC)
buildc:
	ccpsx -O2 -Xo0x80010000 $(SRC)/$(SRC).c -o $(SRC).cpe
	cpe2x $(SRC).cpe
	move $(SRC).cpe ./$(SRC)
	move $(SRC).exe ./$(SRC)