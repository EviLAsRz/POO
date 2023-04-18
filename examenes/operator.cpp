

	
	X &operator ++();
	X operator ++(int);

	//1
	//X &operator ++() ->operador pre-incremento (referencia y no int function)
	//X &operator ++() ->operador post-incremento

	//2
	//Permite al compilador distinguir entre las funciones, al añadir int, cambiamos la signatura de la funcion permitiendo la sobrecarga
	//3

	//En el pre-incremento se devuelve el valor actualizado, mientras que en el post-incremento se actualiza el valor antes de ser devuelto, por lo que debemos de devolver una copia del estado previo a la modificacion.
	

