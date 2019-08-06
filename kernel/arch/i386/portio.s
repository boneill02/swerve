.global inp
.global outp

inp:
	mov 4(%esp),      	%dx
	in 	%dx,            %al
	ret

outp:
	mov 4(%esp), 	    %edx
	mov 8(%esp),        %al
	out %al,            %dx 
	ret
