void my_printf(const char* fmt, ...)
{
    int* argp = (int*)&fmt;
    argp += sizeof(fmt) / sizeof(int);  // argp points at 1
    argp++;                             // argp points at 2
    argp++;                             // argp points at 3 
    argp+=2;                            // argp points at 4   
}

int main()
{  
    my_printf("Test %d %u %llx %i", 1, 2, 3ll, 4);
}