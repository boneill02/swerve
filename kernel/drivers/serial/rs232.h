void rs232_initialize(void);
int rs232_received(void);
char rs232_getchar(void);
void rs232_getline(char *dest);

int rs232_is_transmit_empty(void);
void rs232_putchar(char a);
void rs232_print(const char *str);
void rs232_println(const char *str);
