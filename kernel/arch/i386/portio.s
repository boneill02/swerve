.global inb
.global outb

inb:
	mov 4(%esp),      	%dx
	in 	%dx,            %al
	ret

outb:
	mov 4(%esp), 	    %edx
	mov 8(%esp),        %al
	out %al,            %dx 
	ret
