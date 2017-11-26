
DIR_OUTPUT = ./out
DIR_SRC = ./source
NOMBRE_EJECUTABLE = lab4
NOMBRE_SRC = lab4.c

all: lab4


lab4:
	@echo 'Compilando lab4'
	mkdir -p $(DIR_OUTPUT)
	gcc $(DIR_SRC)/$(NOMBRE_SRC) -o $(DIR_OUTPUT)/$(NOMBRE_EJECUTABLE)
	@echo ' '
	@echo $@ compilado en el directorio $(DIR_OUTPUT)
	@echo "Ingrese al directorio '"$(DIR_OUTPUT)"' escribiendo: cd "$(DIR_OUTPUT)
	@echo "Para ejecutar escriba: ./"$(NOMBRE_EJECUTABLE)" 'PARAMETROS'"
	@echo ' '

clean:
	rm -rf $(DIR_OUTPUT)/*
	-@echo ' ' 
