# Montador-Software-Basico

### entrada_teste1.a

- Equivalente ao seguinte código em C:

>resultado = (A0 + (_a * _b)) * 4 - 2) / 2;

>if( resultado >= 0 )
>     printf("%d\n1\n", resultado);

>else
>     printf("%d\n-1\n", resultado);


- Onde A0 é o registrador A0, _a e _b são valores guardados em memoria pelo .data.

### entrada_teste2.a

- Eleva o numero do Registrador A0 pelo numero do registrador A0 -> pow(A0,A1)



### Instruções Utilizadas

Entrada 1
----
> 12/24 -> 50.00% (contando o .data)

> 11/23 => 47.82% (sem contar o .data)

- read
- load_c
- load        
- multiply 
- add   
- subtract
- divide 
- write   
- jmpn
- move  
- stop     
- .data   

Entrada 2
----
> 11/24 -> 45.83% (contando o .data)

> 10/23 => 43.47% (sem contar o .data)

- read
- move
- load_c
- jmpz
- subtract
- multiply 
- call
- write 
- stop 
- return
- .data   

Total -> Entrada 1 + Entrada 2
----
> 16/24 -> 66.66% (contando o .data)

> 15/23 => 65.21% (sem contar o .data)

- load        
- add   
- subtract
- divide 
- jmpn
- read
- move
- load_c
- jmpz
- subtract
- multiply 
- call
- write 
- stop 
- return
- .data   
