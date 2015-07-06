OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH("i386")
ENTRY(main)

PHDRS
{
    code PT_LOAD;
    data PT_LOAD;
}

SECTIONS
{
  . = 0x4000 + SIZEOF_HEADERS;

  .text :
  {
    *(.text)
  } : code

  .rodata :
  {
    *(.rodata)
  } : data

  .data :
  {
    *(.data) *(.bss) *(COMMON)
  } : data
}
