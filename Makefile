LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:src/:

build:
	mkdir -p build
	$(LATEXCMD) macacario.tex </dev/null
	$(LATEXCMD) macacario.tex </dev/null
	cp build/macacario.pdf .

fast:
	mkdir -p build
	$(LATEXCMD) macacario.tex </dev/null
	cp build/macacario.pdf .

clean:
	rm build/*

.PHONY: build clean
