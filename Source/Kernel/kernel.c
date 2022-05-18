long* terminal_buffer = (long*)0xb8000;

int lines_size = 25;
int columns_size = 80;

void clear_screen(long long attribute)
{
    for(int i = 0; i < lines_size * columns_size; i += 1)
        terminal_buffer[i] = attribute;
}

void kernel_main()
{
    clear_screen(0x1F201F201F201F20);
    return;
}
